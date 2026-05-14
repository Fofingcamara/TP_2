#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include <vector>

class Vaisseau : public GameObject {
private:
    float m_VitesseMax;
    float m_Acceleration;
    float m_Friction;
    float m_VitesseRotation;
    float m_CooldownTir;
    float m_TimerTir;


public:
    Vaisseau(float x, float y);
    void Update() override;
    void Draw() override;
    void Hyperspace();
    std::vector<Projectile*> GetProjectiles() { return m_Projectiles; }
    float GetRayon() const { return 10.0f; }
    bool HyperspaceEchoue() const { return !m_Actif; }

private:
    void Tourner(float direction);
    void Accelerer();
    void WrapEcran();
    void Tirer();
    std::vector<Projectile*> m_Projectiles;
};