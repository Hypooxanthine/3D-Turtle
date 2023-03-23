#pragma once

#include <cstdio>
#include <vector>
#include <string>
#include <functional>

#include "Object3D.h"
#include "Animation.h"
#include "AnimationKey.h"

/*
    La classe Skeleton suit un modèle arborescent. Un squelette peut avoir un ou plusieurs enfant dont il garde la trace, mais un seul parent
    dont il n'a pas la nécessité de garder la trace. Les capacités de calcul matriciel fournies par openGL permettent de ne pas garder en mémoire
    l'adresse du noeud parent.
    Les modalités de calcul des transformations sont détaillées dans la méthode onDraw().
*/
class Skeleton : public Object3D
{
public:
    using ChildrenContainer = std::vector<Skeleton*>;

    using children_iterator = ChildrenContainer::iterator;
    using children_const_iterator = ChildrenContainer::const_iterator;

public:
    Skeleton(const std::string& name, const Vector3f& initialPos);

    template <typename... Object3D>
    void addObject(const Object3D*... obj)
    {
        (objects.push_back(obj), ...);
    }

    template <typename... Skeleton>
    void addChild(Skeleton*... child)
    {
        (children.push_back(child), ...);
    }

    inline const std::string& getName() const { return boneName; }

    void move(const Vector3f& vec);
    void rotate(const Vector3f& rot);
    void scale(const Vector3f& sca);

    bool move(const std::string& bone, const Vector3f& vec);
    bool rotate(const std::string& bone, const Vector3f& rot);
    bool scale(const std::string& bone, const Vector3f& sca);

    // La méthode onDraw() permet de dessiner un squelette ainsi que tous ses descendants, à savoir, les objets associés à ce squelette
    // ainsi que les objets associés à tous ses descendants. Elle prend en compte la transformation des objets mais aussi
    // la transformation des maillons du squelette.
    virtual void onDraw() const override;

    virtual void update(const float& dt) override;

    void playAnimation(const Animation* anim, const float& startTime = 0.f, const float& blendTime = .5f, const bool& loop = true, const std::function<void()>& onAnimEnd = nullptr);
    void playAnimation(const Animation* anim, const float& startTime = 0.f, const bool& loop = true, const std::function<void()>& onAnimEnd = nullptr);
    void stopAnimation();

    /* Iterateurs */
    children_iterator begin() { return children.begin(); }
    children_iterator end() { return children.end(); }

    children_const_iterator begin() const { return children.begin(); }
    children_const_iterator end() const { return children.end(); }

private:
    void applyAnimationKey(const AnimationKey& key);

private:
    ChildrenContainer children;

    std::vector<const Object3D*> objects;
    Vector3f initialPosition;

    std::string boneName;

    const Animation* currentAnimation = nullptr;
    Animation blendAnimation;
    float animTime = 0.f;
    bool animLoop = true;
    std::function<void()> animEndCallback = nullptr;
};
