//
// Created by pylinskyi.k on 03.11.2023.
//

#ifndef PELAGEIA_IMMERSIVE_TIMER_H
#define PELAGEIA_IMMERSIVE_TIMER_H

const int TARGET_FPS = 60;
const float TARGET_DELTA_TIME = 1.5f;

class Timer
{
public:
    static Timer* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer(); }

    inline float GetDeltaTime() const { return m_DeltaTime; }
    void Tick();

private:
    Timer(){};

    static Timer* s_Instance;
    float m_DeltaTime;
    float m_LastTime;
};

#endif  // PELAGEIA_IMMERSIVE_TIMER_H
