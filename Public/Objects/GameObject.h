//
// Created by pylinskyi.k on 24/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_GAMEOBJECT_H
#define PELAGEIA_IMMERSIVE_GAMEOBJECT_H

#include "SDL.h"
#include <string>
#include "IObject.h"
#include "Physics/Vector2D.h"
#include "Physics/Transform.h"

struct Properties
{
public:
    std::string TextureID;
    int X;
    int Y;
    int Width;
    int Height;
    SDL_RendererFlip Flip;

    Properties(std::string textureID, int x, int y, int width, int height, SDL_RendererFlip flip)
    {
        TextureID = textureID;
        X = x;
        Y = y;
        Width = width;
        Height = height;
        Flip = flip;
    }
};

class GameObject : public IObject
{
public:
    GameObject(Properties* props) : m_Width(props->Height), m_Height(props->Width), m_TextureID(props->TextureID), m_Flip(props->Flip)
    {
        m_Transform = new Transform(props->X, props->Y);

        float px = props->X + props->Width / 2;
        float py = props->Y + props->Height / 2;

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

#endif  // PELAGEIA_IMMERSIVE_GAMEOBJECT_H
