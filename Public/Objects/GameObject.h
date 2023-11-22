//
// Created by admin on 24/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_GAMEOBJECT_H
#define PELAGEIA_IMMERSIVE_GAMEOBJECT_H

#include <string>
#include "SDL.h"
#include "Utils.h"
#include "IObject.h"
#include "../Physics/Vector2D.h"
#include "../Physics/Transform.h"



class GameObject : public IObject{
public:
    GameObject(Properties* props):
        m_Width(props->Height),
        m_Height(props->Width),
        m_TextureID(props->TextureID),
        m_Flip(props->Flip)
        {
            m_Transform = new Transform(props->X, props->Y);

            float px = props->X + props->Width/2;
            float py = props->Y + props->Height/2;

            m_Origin = new Vector2D(px, py);
        }

    inline Vector2D* GetOrigin() { return m_Origin; }
    virtual void Draw() = 0;
    virtual void Update(float dt) = 0;
    virtual void Clean() = 0;
protected:
    Vector2D* m_Origin;
    Transform* m_Transform;
    int m_Width, m_Height;
    std::string m_TextureID;
    SDL_RendererFlip m_Flip;
};


#endif //PELAGEIA_IMMERSIVE_GAMEOBJECT_H
