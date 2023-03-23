#include "HypoGl/Skeleton.h"

#include "GL/glut.h"

Skeleton::Skeleton(const std::string& name, const Vector3f& initialPos)
    : Object3D(Transform()), initialPosition(initialPos), boneName(name)
{}

void Skeleton::move(const Vector3f& vec)
{
    transform.position += vec;
}

void Skeleton::rotate(const Vector3f& rot)
{
    transform.rotation += rot;
}

void Skeleton::scale(const Vector3f& sca)
{
    transform.scale += sca;
}

bool Skeleton::move(const std::string& bone, const Vector3f& vec)
{
    if(getName() == bone)
    {
        move(vec);
        return true;
    }

    for(Skeleton*& c : children)
    {
        if(c->move(bone, vec))
            return true;
    }

    return false;
}

bool Skeleton::rotate(const std::string& bone, const Vector3f& rot)
{
    if(getName() == bone)
    {
        rotate(rot);
        return true;
    }

    for(Skeleton*& c : children)
    {
        if(c->rotate(bone, rot))
            return true;
    }

    return false;
}

bool Skeleton::scale(const std::string& bone, const Vector3f& sca)
{
    if(getName() == bone)
    {
        scale(sca);
        return true;
    }

    for(Skeleton*& c : children)
    {
        if(c->scale(bone, sca))
            return true;
    }

    return false;
}

/*
    La lecture se fait en sens inverse.
    Pour chaque objet, on le dessine (o->draw()).
    Ensuite, on replace l'objet au centre en prenant en compte la position initiale du noeud (= du squelette = de l'articulation).
    On applique la transformation de son noeud, puis on replace l'objet.
    Puisque la méthode draw() appelle la méthode draw() de tous les descendants d'un squelettes, il persistera
    le reliquat des transformations des noeuds parents au moment de l'affichage. Cela permet une réaction en
    chaîne lorsque l'on modifie la transformation d'un noeud : les effets se répercuteront sur tous ses descendants.
*/
void Skeleton::onDraw() const
{
    glPushMatrix();

    glTranslatef(initialPosition.x, initialPosition.y, initialPosition.z);
    applyTransform();
    glTranslatef(-initialPosition.x, -initialPosition.y, -initialPosition.z);

    for(const Object3D* o : objects)
        o->draw();

    for(const auto* c : children)
        c->draw();

    glPopMatrix();
}

void Skeleton::update(const float& dt)
{
    if(currentAnimation != nullptr)
    {
        // On applique l'état correspondant à l'instant t au squelette.
        applyAnimationKey(currentAnimation->getAnimState(animTime));

        animTime += dt;
        if(animTime > currentAnimation->getDuration())
        {
            if(animLoop)
                animTime -= currentAnimation->getDuration();

            if(animEndCallback != nullptr)
                animEndCallback();
        }
    }
}

void Skeleton::applyAnimationKey(const AnimationKey& key)
{
    // Récursion dans le squelette. Pour chaque os, on récupère la transformation de cet os, qualifié par son nom, dans la clé.
    setTransform(key.getBoneTransform(getName()));

    for(Skeleton* c : children)
        c->applyAnimationKey(key);
}

// Animation avec blend
void Skeleton::playAnimation(const Animation* anim, const float& startTime, const float& blendTime, const bool& loop, const std::function<void()>& onAnimEnd)
{
    if(currentAnimation == nullptr) // Si le squelette ne joue aucune animation, aucun blend n'est nécessaire.
        playAnimation(anim, startTime, loop, onAnimEnd);
    else
    {
        // Le blend est une animation temporaire permettant de lier deux état du squelette grâce à deux clés.
        // La première est l'état du squelette dans l'animation currentAnimation à l'instant t.
        // La seconde est l'état du squelette dans l'animation anim à l'instant startTime + blendTime (là où l'animation suivante démarrera réellement).
        AnimationKey blendStart, blendEnd;

        blendStart = currentAnimation->getAnimState(animTime);
        blendStart.setTimeStamp(0.f);
        blendEnd = anim->getAnimState(startTime + blendTime);
        blendEnd.setTimeStamp(blendTime);

        blendAnimation = Animation();
        blendAnimation.addKey(blendStart);
        blendAnimation.addKey(blendEnd);

        blendAnimation.setDuration(blendTime);

        // On va donc jouer l'animation temporaire qui fait la jonction entre les deux état du squelette.
        // En callback, on demandera de jouer l'animation réelle "anim".
        this->playAnimation(&blendAnimation, 0.f, false, [this, anim, startTime, blendTime, loop, onAnimEnd](){ this->playAnimation(anim, startTime + blendTime, loop, onAnimEnd); });
    }
}

// Animation sans blend
void Skeleton::playAnimation(const Animation* anim, const float& startTime, const bool& loop, const std::function<void()>& onAnimEnd)
{
    currentAnimation = anim;
    animLoop = loop;
    animEndCallback = onAnimEnd;
    animTime = startTime;
}

void Skeleton::stopAnimation()
{
    currentAnimation = nullptr;
    animTime = 0.f;
}
