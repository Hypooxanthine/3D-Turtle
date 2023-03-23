#pragma once

#include <string>
#include <unordered_map>

#include "DataStructures.h"

class Skeleton;

class AnimationKey
{
public:
    using Container = std::unordered_map<std::string, Transform>;

    using iterator = Container::iterator;
    using const_iterator = Container::const_iterator;

    AnimationKey();

    // Le skeleton à donner en paramètre sert à définir l'arborescence du squelette. On ne pourra ainsi pas appliquer de transformation
    // à un os qui n'existe pas dans le squelette.
    void initKey(const Skeleton& skeleton);
    inline void clear() { boneTransforms.clear(); }

    // La targetTransform est relative à la transformation initiale de l'objet. Si la targetTransform est la transformation nulle, aucune modification ne sera
    // appliquée ni à l'os, ni à ses objets enfants.
    void setBoneTargetTransform(const std::string& bone, const Transform& target);
    void removeBoneTargetTransform(const std::string& bone);

    Transform getBoneTransform(const std::string& bone) const;

    inline const float& getTimeStamp() const { return timeStamp; }
    inline void setTimeStamp(const float& ts) { timeStamp = ts; }

    /* Iterateurs */
    iterator begin() { return boneTransforms.begin(); }
    iterator end() { return boneTransforms.end(); }

    const_iterator begin() const { return boneTransforms.begin(); }
    const_iterator end() const { return boneTransforms.end(); }

private:
    void initKeyRecursive(const Skeleton& skeleton);

private:
    Container boneTransforms;
    float timeStamp = 0.f;
};
