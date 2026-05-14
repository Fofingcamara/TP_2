#pragma once
#include "raylib.h"

class GameObject {
protected:
    Vector2 m_Position;
    Vector2 m_Vitesse;
    float m_Rotation;
    bool m_Actif;

public:
    GameObject(float x, float y);
    virtual ~GameObject() = default;

    virtual void Update() = 0;
    virtual void Draw() = 0;

    bool EstActif() const { return m_Actif; }
    void Desactiver() { m_Actif = false; }
    Vector2 GetPosition() const { return m_Position; }
};