#pragma once

#include <map>

#include "AnimationKey.h"

class Animation
{
public:
    Animation() = default;

    inline void setDuration(const float& dur) { if(dur >= 0.f) duration = dur; }
    inline const float& getDuration() const { return duration; }

    void addKey(const AnimationKey& key);

    AnimationKey getAnimState(const float& time) const;

private:
    std::map<float, AnimationKey> keys;

    float duration = 0.f;
};
