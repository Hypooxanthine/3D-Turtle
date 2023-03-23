#pragma once

#include "DataStructures.h"
#include "AnimationKey.h"

/* Linear interpolations */

template <typename T>
T lerp(const T& first, const T& second, const float& value)
{
    return first + (second - first) * value;
}

Transform lerp(const Transform& first, const Transform& second, const float& value)
{
    return
    {
        lerp(first.position, second.position, value),
        lerp(first.rotation, second.rotation, value),
        lerp(first.scale, second.scale, value)
    };
}

AnimationKey lerp(const AnimationKey& first, const AnimationKey& second, const float& value)
{
    AnimationKey out = first;

    for(const auto& [bone, transform] : first)
    {
        out.setBoneTargetTransform(bone, lerp(transform, second.getBoneTransform(bone), value));
    }

    return out;
}
