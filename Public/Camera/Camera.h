//
// Created by pylinskyi.k on 14.11.2023.
//

#ifndef PELAGEIA_IMMERSIVE_CAMERA_H
#define PELAGEIA_IMMERSIVE_CAMERA_H

#include "SDL.h"
#include "Physics/Vector2D.h"
#include "Utils/Config/ConfigLoader.h"

class Camera
{
public:
    static Camera* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera(); }

    void Update(float dt);

    inline Vector2D GetPosition() const { return m_Position; }
    inline SDL_Rect GetViewBox() const { return m_ViewBox; }
    inline void SetTarget(Vector2D* target) { m_Target = target; }

private:
    Camera();
    static Camera* s_Instance;

    Vector2D* m_Target;
    Vector2D m_Position;
    SDL_Rect m_ViewBox;
};

#endif  // PELAGEIA_IMMERSIVE_CAMERA_H
