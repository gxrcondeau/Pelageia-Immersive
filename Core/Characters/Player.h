//
// Created by admin on 24/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_PLAYER_H
#define PELAGEIA_IMMERSIVE_PLAYER_H


#include "Character.h"
#include "../Physics/RigidBody.h"
#include "../Animation/Animation.h"

#define FORWARD 1
#define BACKWARD -1
#define UPWARD 1
#define DOWNWARD -1

class Player : public Character{
public:
    Player(Properties* props);

    virtual void Draw() override;
    virtual void Update(float dt) override;
    virtual void Clean() override;

private:
    Animation* m_Animation;
    RigidBody* m_RigidBody;
};


#endif //PELAGEIA_IMMERSIVE_PLAYER_H
