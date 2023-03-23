#include "Turtle.h"

Turtle::Turtle()
    :   tete       (Skeleton("tete"       , {0.f , 6.f , 8.5f })),
        corps      (Skeleton("corps"      , {0.f , 9.5f, 0.f  })),
        patte1     (Skeleton("patte1"     , {7.f , 6.f , 6.5f })),
        jambePatte1(Skeleton("jambePatte1", {7.f , 3.f , 6.5f })),
        patte2     (Skeleton("patte2"     , {7.f , 6.f , -6.5f})),
        jambePatte2(Skeleton("jambePatte2", {7.f , 3.f , -6.5f})),
        patte3     (Skeleton("patte3"     , {-7.f, 6.f , 6.5f })),
        jambePatte3(Skeleton("jambePatte3", {-7.f, 3.f , 6.5f })),
        patte4     (Skeleton("patte4"     , {-7.f, 6.f , -6.5f})),
        jambePatte4(Skeleton("jambePatte4", {-7.f, 3.f , -6.5f}))
{
    initObjects();
    initSkeleton();
    initTextures();
    initAnimations();

    corps.playAnimation(&animMarche, 0.f, true);
}

void Turtle::update(const float& dt)
{
    corps.update(dt);
}

void Turtle::jump()
{
    // On joue l'animation depuis le début avec un blend de 0,5 secondes. A la fin du saut, on repart sur une animation de marche en looping.
    corps.playAnimation(&animSaut, 0.f, .5f, false, [this](){ this->corps.playAnimation(&animMarche, 0.f, .5f, true); });
}

void Turtle::onDrawObject() const
{
    corps.draw();
}

void Turtle::initObjects()
{
    crane = Cube3D
    (
        {{0.f, 6.f, 12.f}, Vector3f(), {6.f, 4.f, 7.f}}
    );
    oeilD = Sphere3D
    (
        {{3.f, 7.5f, 14.f}}
    );
    oeilG = Sphere3D
    (
        {{-3.f, 7.5f, 14.f}}
    );
    basCorps = Cube3D
    (
        {{0.f, 5.5f, 0.f}, Vector3f(), {16.f, 1.f, 15.f}}
    );
    basCarapace = Cube3D
    (
        {{0.f, 7.f, 0.f}, Vector3f(), {18.f, 2.f, 17.f}}
    );
    milieuCarapace = Cube3D
    (
        {{0.f, 10.f, 0.f}, Vector3f(), {16.f, 4.f, 15.f}}
    );
    hautCarapace = Cube3D
    (
        {{0.f, 13.f, 0.f}, Vector3f(), {12.f, 2.f, 11.f}}
    );
    hautPatte1 = Cube3D
    (
        {{7.f, 4.5f, 6.5f}, Vector3f(), {4.f, 3.f, 4.f}}
    );
    basPatte1 = Cube3D
    (
        {{7.f, 1.5f, 6.5f}, Vector3f(), {4.f, 3.f, 4.f}}
    );
    hautPatte2 = Cube3D
    (
        {{7.f, 4.5f, -6.5f}, Vector3f(), {4.f, 3.f, 4.f}}
    );
    basPatte2 = Cube3D
    (
        {{7.f, 1.5f, -6.5f}, Vector3f(), {4.f, 3.f, 4.f}}
    );
    hautPatte3 = Cube3D
    (
        {{-7.f, 4.5f, 6.5f}, Vector3f(), {4.f, 3.f, 4.f}}
    );
    basPatte3 = Cube3D
    (
        {{-7.f, 1.5f, 6.5f}, Vector3f(), {4.f, 3.f, 4.f}}
    );
    hautPatte4 = Cube3D
    (
        {{-7.f, 4.5f, -6.5f}, Vector3f(), {4.f, 3.f, 4.f}}
    );
    basPatte4 = Cube3D
    (
        {{-7.f, 1.5f, -6.5f}, Vector3f(), {4.f, 3.f, 4.f}}
    );
}

void Turtle::initSkeleton()
{
    tete.addObject(&crane, &oeilD, &oeilG);
    corps.addObject(&basCorps, &basCarapace, &milieuCarapace, &hautCarapace);
    patte1.addObject(&hautPatte1);
    jambePatte1.addObject(&basPatte1);
    patte2.addObject(&hautPatte2);
    jambePatte2.addObject(&basPatte2);
    patte3.addObject(&hautPatte3);
    jambePatte3.addObject(&basPatte3);
    patte4.addObject(&hautPatte4);
    jambePatte4.addObject(&basPatte4);

    corps.addChild(&tete, &patte1, &patte2, &patte3, &patte4);
    patte1.addChild(&jambePatte1);
    patte2.addChild(&jambePatte2);
    patte3.addChild(&jambePatte3);
    patte4.addChild(&jambePatte4);
}

void Turtle::initTextures()
{
    tCrane.loadFromFile("textures/crane.jpg");
    tHautCarapace.loadFromFile("textures/hautCarapace.jpg");
    tMilieuCarapace.loadFromFile("textures/milieuCarapace.jpg");
    tBasCarapace.loadFromFile("textures/basCarapace.jpg");
    tBasCorps.loadFromFile("textures/basCorps.jpg");
    tHautPatte.loadFromFile("textures/hautPatte.jpg");
    tBasPatteDroite.loadFromFile("textures/basPatteDroite.jpg");
    tBasPatteGauche.loadFromFile("textures/basPatteGauche.jpg");
    tOeil.loadFromFile("textures/oeil.jpg");

    crane.setTexture(&tCrane);
    hautCarapace.setTexture(&tHautCarapace);
    milieuCarapace.setTexture(&tMilieuCarapace);
    basCarapace.setTexture(&tBasCarapace);
    basCorps.setTexture(&tBasCorps);
    hautPatte1.setTexture(&tHautPatte);
    hautPatte2.setTexture(&tHautPatte);
    hautPatte3.setTexture(&tHautPatte);
    hautPatte4.setTexture(&tHautPatte);
    basPatte1.setTexture(&tBasPatteGauche);
    basPatte2.setTexture(&tBasPatteGauche);
    basPatte3.setTexture(&tBasPatteDroite);
    basPatte4.setTexture(&tBasPatteDroite);
    oeilD.setTexture(&tOeil);
    oeilG.setTexture(&tOeil);
}

void Turtle::initAnimations()
{
    AnimationKey key;

    // ANIMATION DE MARCHE
    animMarche.setDuration(8.f);

    key.initKey(corps);
    key.setTimeStamp(0.f);
        key.setBoneTargetTransform("patte1", {Vector3f(), {45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte4", {Vector3f(), {45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte2", {Vector3f(), {-45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte2", {Vector3f(), {45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte3", {Vector3f(), {-45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte3", {Vector3f(), {45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("corps", {{0.f, -0.879f, 0.f}, Vector3f()}); //3-3*cos(45)
        animMarche.addKey(key);
    key.setTimeStamp(8.f);
        animMarche.addKey(key);

    key.initKey(corps);
    key.setTimeStamp(2.f);
        key.setBoneTargetTransform("patte1", {Vector3f(), {0.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte1", {Vector3f(), {90.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte4", {Vector3f(), {0.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte4", {Vector3f(), {90.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte2", {Vector3f(), {0.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte2", {Vector3f(), {45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte3", {Vector3f(), {0.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte3", {Vector3f(), {45.f, 0.f, 0.f}});
        animMarche.addKey(key);

    key.initKey(corps);
    key.setTimeStamp(4.f);
        key.setBoneTargetTransform("patte2", {Vector3f(), {45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte3", {Vector3f(), {45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte1", {Vector3f(), {-45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte1", {Vector3f(), {45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte4", {Vector3f(), {-45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte4", {Vector3f(), {45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("corps", {{0.f, -0.879f, 0.f}, Vector3f()}); //3-3*cos(45)
        animMarche.addKey(key);

    key.initKey(corps);
    key.setTimeStamp(6.f);
        key.setBoneTargetTransform("patte2", {Vector3f(), {0.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte2", {Vector3f(), {90.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte3", {Vector3f(), {0.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte3", {Vector3f(), {90.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte1", {Vector3f(), {0.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte1", {Vector3f(), {45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte4", {Vector3f(), {0.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte4", {Vector3f(), {45.f, 0.f, 0.f}});
        animMarche.addKey(key);

    // ANIMATION DE SAUT
    animSaut.setDuration(9.f);

    key.initKey(corps);
    key.setTimeStamp(0.f);
        animSaut.addKey(key);
    key.setTimeStamp(9.f);
        animSaut.addKey(key);

    key.initKey(corps);
    key.setTimeStamp(2.f);
        key.setBoneTargetTransform("patte1", {Vector3f(), {-45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte1", {Vector3f(), {45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte2", {Vector3f(), {-45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte2", {Vector3f(), {45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte3", {Vector3f(), {-45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte3", {Vector3f(), {45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte4", {Vector3f(), {-45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte4", {Vector3f(), {45.f, 0.f, 0.f}});
        key.setBoneTargetTransform("corps", {{0.f, -0.879f, 0.f}, Vector3f()}); //3-3*cos(45)
        animSaut.addKey(key);

    key.initKey(corps);
    key.setTimeStamp(2.5f);
        key.setBoneTargetTransform("patte1", {Vector3f(), {-20.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte1", {Vector3f(), {25.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte3", {Vector3f(), {-20.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte3", {Vector3f(), {25.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte2", {Vector3f(), {-20.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte2", {Vector3f(), {25.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte4", {Vector3f(), {-20.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte4", {Vector3f(), {25.f, 0.f, 0.f}});
        key.setBoneTargetTransform("corps", {{0.f, -0.281f, 0.f}, {-5.f, 0.f, 0.f}}); //3-3*cos(25)
        animSaut.addKey(key);

    key.initKey(corps);
    key.setTimeStamp(3.f);
        key.setBoneTargetTransform("patte2", {Vector3f(), {10.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte2", {Vector3f(), {0.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte4", {Vector3f(), {10.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte4", {Vector3f(), {0.f, 0.f, 0.f}});
        key.setBoneTargetTransform("corps", {{0.f, 0.f, 0.f}, {-10.f, 0.f, 0.f}});
        animSaut.addKey(key);

    key.initKey(corps);
    key.setTimeStamp(5.f);
        key.setBoneTargetTransform("corps", {{0.f, 5.f, 0.f}, Vector3f()});
        animSaut.addKey(key);

    key.initKey(corps);
    key.setTimeStamp(6.f);
        animSaut.addKey(key);

    key.initKey(corps);
    key.setTimeStamp(7.f);
        key.setBoneTargetTransform("patte1", {Vector3f(), {-60.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte1", {Vector3f(), {60.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte2", {Vector3f(), {-60.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte2", {Vector3f(), {60.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte3", {Vector3f(), {-60.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte3", {Vector3f(), {60.f, 0.f, 0.f}});
        key.setBoneTargetTransform("patte4", {Vector3f(), {-60.f, 0.f, 0.f}});
        key.setBoneTargetTransform("jambePatte4", {Vector3f(), {60.f, 0.f, 0.f}});
        key.setBoneTargetTransform("corps", {{0.f, -1.5f, 0.f}, Vector3f()}); //3-3*cos(60)
        animSaut.addKey(key);
}
