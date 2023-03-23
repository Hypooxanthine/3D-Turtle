#pragma once

#include <HypoGl/Cube3D.h>
#include <HypoGl/Sphere3D.h>
#include <HypoGl/Skeleton.h>
#include <HypoGl/Animation.h>
#include <HypoGl/Texture.h>

class Turtle : public Object3D
{
public:
    Turtle();

    virtual void update(const float& dt) override;

    void jump();

protected:
    virtual void onDrawObject() const override;

private:
    void initObjects();
    void initSkeleton();
    void initTextures();
    void initAnimations();

private:
    // Objets 3D
    Cube3D crane;
    Cube3D basCorps;
    Cube3D basCarapace;
    Cube3D milieuCarapace;
    Cube3D hautCarapace;
    Cube3D hautPatte1;
    Cube3D basPatte1;
    Cube3D hautPatte2;
    Cube3D basPatte2;
    Cube3D hautPatte3;
    Cube3D basPatte3;
    Cube3D hautPatte4;
    Cube3D basPatte4;
    Sphere3D oeilG;
    Sphere3D oeilD;

    // Squelettes / os
    Skeleton tete;
    Skeleton corps;
    Skeleton patte1;
    Skeleton jambePatte1;
    Skeleton patte2;
    Skeleton jambePatte2;
    Skeleton patte3;
    Skeleton jambePatte3;
    Skeleton patte4;
    Skeleton jambePatte4;

    // Animations
    Animation animMarche, animSaut;

    // Textures
    Texture tCrane;
    Texture tHautCarapace;
    Texture tMilieuCarapace;
    Texture tBasCarapace;
    Texture tBasCorps;
    Texture tHautPatte;
    Texture tBasPatteDroite;
    Texture tBasPatteGauche;
    Texture tOeil;
};
