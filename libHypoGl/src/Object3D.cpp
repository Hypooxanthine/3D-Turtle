#include "HypoGl/Object3D.h"

void Object3D::draw() const
{
    if(!bVisible) return;

    onDraw();
}

void Object3D::drawObject() const
{
    if(!bVisible) return;

    // On demande à openGL d'utiliser la texture liée à cette instance
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->getWidth(), texture->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, texture->getData().data());
    glEnable(GL_TEXTURE_2D);

    onDrawObject();
}

void Object3D::applyScale() const
{
    glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
}

void Object3D::applyInvScale() const
{
    glScalef(1.f / transform.scale.x, 1.f / transform.scale.y, 1.f / transform.scale.z);
}

void Object3D::applyRotation() const
{
    glRotatef(transform.rotation.x, 1.f, 0.f, 0.f);
    glRotatef(transform.rotation.y, 0.f, 1.f, 0.f);
    glRotatef(transform.rotation.z, 0.f, 0.f, 1.f);
}

void Object3D::applyInvRotation() const
{
    glRotatef(-transform.rotation.z, 0.f, 0.f, 1.f);
    glRotatef(-transform.rotation.y, 0.f, 1.f, 0.f);
    glRotatef(-transform.rotation.x, 1.f, 0.f, 0.f);
}

void Object3D::applyTranslation() const
{
    glTranslatef(transform.position.x, transform.position.y, transform.position.z);
}

void Object3D::applyInvTranslation() const
{
    glTranslatef(-transform.position.x, -transform.position.y, -transform.position.z);
}

void Object3D::applyTransform() const
{
    applyTranslation();
    applyRotation();
    applyScale();
}

void Object3D::onDraw() const
{
    glPushMatrix();
    applyTransform();

    drawObject();

    glPopMatrix();
}
