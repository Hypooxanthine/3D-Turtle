#pragma once

#include <functional>

#include <GL/glut.h>

#include "Object3D.h"

/*
    La classe FuncObject3D est un objet 3D donc l'objet primaire est dessiné par une fonction externe.
    Utile pour les primitives offertes par glut, peut aussi servir pour une fonction dessinant d'autres primitives
    non définies par freeglut. On peut imaginer une fonction drawOctahedron() permettant de dessiner
    un octahèdre régulier de taille normalisée, et cette fonction pourrait servir à définir un nouveau genre de
    FuncObject3D.
*/
class FuncObject3D : public Object3D
{
public:
    FuncObject3D() = delete;
    FuncObject3D(const std::function<void()>& d, const Transform& t = Transform())
        : Object3D(t), drawer(d)
    {}

    void setPosition(const Vector3f& pos) { this->transform.position = pos; }
    void setRotation(const Vector3f& rot) { this->transform.rotation = rot; }
    void setScale(const Vector3f& sc)     { this->transform.scale = sc;     }

    void move(const Vector3f& delta)
    {
        transform.position = transform.position + delta;
    }

protected:

    // Comme précisé dans le prototype de Object3D, la méthode onDrawObject ne dessine que la primitive de l'objet,
    // sans transformations superflues. Ici, c'est la fonction dessinatrice externe qui s'en charge.
    virtual void onDrawObject() const override
    {
        drawer();
    }

protected:
    // La fonction dessinatrice dessine la primitive de l'objet et suppose qu'elle n'a aucune
    // transformation superflue (à l'origine, de taille normale et sans rotation).
    std::function<void()> drawer;
};
