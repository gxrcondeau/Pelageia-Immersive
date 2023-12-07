//
// Created by pylinskyi.k on 02/11/2023.
//

#ifndef PELAGEIA_IMMERSIVE_ANIMATION_H
#define PELAGEIA_IMMERSIVE_ANIMATION_H

#include "SDL.h"
#include "Characters/Character.h"
#include <string>
#include <functional>

class Animation
{
public:
    using AnimationEventCallback = std::function<void()>;

    Animation(bool repeat = true) : m_Repeat(repeat) { m_IsEnded = false; };

    virtual void Update() = 0;

    void SetAnimationEndCallback(const AnimationEventCallback& callback) { m_AnimationEndCallback = callback; }

    inline bool IsEnded() { return m_IsEnded; }

protected:
    AnimationEventCallback m_AnimationEndCallback;

    bool m_Repeat;
    bool m_IsEnded;
};

#endif  // PELAGEIA_IMMERSIVE_ANIMATION_H
