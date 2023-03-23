#pragma once

#include <GL/glut.h>
#include <iostream>

#include "DataStructures.h"
#include "Texture.h"

/*
    Classe permettant de modéliser un objet queconque en 3D. Possède une transformation accessible aux enfants,
    et de méthodes pour dessiner l'objet, ouvertes à la virtualisation pour les enfants.
 */
class Object3D
{
public:
    Object3D() = default;
    Object3D(const Transform& t) : transform(t) {}

    inline void setVisible(const bool& val = true) { bVisible = val; }
    inline const bool& getVisible() const { return bVisible; }

    inline void setTexture(const Texture* tex) { texture = tex; }
    inline const Texture* getTexture() const { return texture; }

    inline const Transform& getTransform() const { return transform; }
    inline void setTransform(const Transform& t) { transform = t; }

    void draw() const;
    void drawObject() const;

    void applyScale() const;
    void applyInvScale() const;

    void applyRotation() const;
    void applyInvRotation() const;

    void applyTranslation() const;
    void applyInvTranslation() const;

    // La méthode applyTransform permet simplement d'appliquer la transformation à l'état openGL.
    // Aucun push/popMatrix n'est effectué, leur exécution est confiée à la fonction appelante.
    void applyTransform() const;

    virtual void update(const float& dt) {}

protected:
    // La méthode draw doit dessiner un objet complet, en prenant en compte sa transformation. Par défaut, elle applique la transformation
    // puis appelle la méthode drawObject().
    virtual void onDraw() const;

    /*
        La méthode drawObject doit dessiner uniquement l'objet sans sa transformation.
        Par exemple, si openGL n'est dans aucun état particulier, un cube unitaire sera dessiné à l'origine du repère,
        avec les bords alignés aux repères et de taille unitaire.
    */
    virtual void onDrawObject() const {}

protected:
    Transform transform;
    bool bVisible = true;

    const Texture* texture = &Texture::White;
};
