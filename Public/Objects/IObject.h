//
// Created by admin on 24/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_IOBJECT_H
#define PELAGEIA_IMMERSIVE_IOBJECT_H


class IObject {
public:
    virtual void Draw() = 0;
    virtual void Update(float dt) = 0;
    virtual void Clean() = 0;
};


#endif //PELAGEIA_IMMERSIVE_IOBJECT_H
