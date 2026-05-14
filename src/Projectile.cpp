#include "Projectile.h"
#include <cmath>

Projectile::Projectile(float x, float y, float angle)
    : GameObject(x, y) {
    float vitesse = 10.0f;


    m_Vitesse.x = cosf(angle * DEG2RAD) * vitesse;
    m_Vitesse.y = sinf(angle * DEG2RAD) * vitesse;
}

void Projectile::Update() {
    m_Position.x += m_Vitesse.x;
    m_Position.y += m_Vitesse.y;

    if (m_Position.x > 800 || m_Position.x < 0 ||
        m_Position.y > 600 || m_Position.y < 0) {
        Desactiver();
    }
}

void Projectile::Draw() {
    DrawCircle(
        (int)m_Position.x,
        (int)m_Position.y,
        3,
        YELLOW
    );
}