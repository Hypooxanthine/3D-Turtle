#include "HypoGl/AnimationKey.h"

#include <iostream>

#include "HypoGl/Skeleton.h"

AnimationKey::AnimationKey()
{

}

void AnimationKey::initKey(const Skeleton& skeleton)
{
    clear();
    initKeyRecursive(skeleton);
}

void AnimationKey::initKeyRecursive(const Skeleton& skeleton)
{
    boneTransforms.insert({skeleton.getName(), Transform()});

    for(const Skeleton* c : skeleton)
        initKeyRecursive(*c);
}

void AnimationKey::setBoneTargetTransform(const std::string& bone, const Transform& target)
{
    boneTransforms.at(bone) = target;
}

void AnimationKey::removeBoneTargetTransform(const std::string& bone)
{
    boneTransforms.at(bone) = Transform();
}

Transform AnimationKey::getBoneTransform(const std::string& bone) const
{
    return boneTransforms.at(bone);
}
