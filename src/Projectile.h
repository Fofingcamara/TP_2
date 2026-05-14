#pragma once
#include "GameObject.h"

class Projectile : public GameObject {
public:
    Projectile(float x, float y, float angle);
    void Update() override;
    void Draw() override;
};