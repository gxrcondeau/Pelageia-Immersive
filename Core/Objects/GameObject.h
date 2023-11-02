//
// Created by admin on 24/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_GAMEOBJECT_H
#define PELAGEIA_IMMERSIVE_GAMEOBJECT_H

#include <string>
#include "SDL.h"
#include "Utils.h"
#include "IObject.h"
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
        }

    virtual void Draw() = 0;
    virtual void Update(float dt) = 0;
    virtual void Clean() = 0;
protected:
    Transform* m_Transform;
    int m_Width, m_Height;
    std::string m_TextureID;
    SDL_RendererFlip m_Flip;
};


#endif //PELAGEIA_IMMERSIVE_GAMEOBJECT_H
