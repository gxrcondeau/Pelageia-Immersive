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
#include "Utils/Calculations/Coordinates.h"


class GameObject : public IObject
{
public:
    GameObject(std::string name, int positionRow, int positionCol)
    {
        m_Name = name;
        int px = Coordinates::GetIsoX(positionRow, positionCol);
        int py = Coordinates::GetIsoY(positionRow, positionCol);

        m_Transform = new Transform(px, py);
    }

    inline Vector2D GetOrigin() { return m_Transform->Origin; }
    int GetWorldPositionRow() { return Coordinates::GetIsoRow(m_Transform->Origin.X, m_Transform->Origin.Y); };
    int GetWorldPositionCol() { return Coordinates::GetIsoCol(m_Transform->Origin.X, m_Transform->Origin.Y); };
    virtual void Draw() = 0;
    virtual void Update(float dt) = 0;
    virtual void Clean() = 0;

protected:
    std::string m_Name;
    Transform* m_Transform;
};

#endif  // PELAGEIA_IMMERSIVE_GAMEOBJECT_H
