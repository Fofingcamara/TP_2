#include "Vaisseau.h"
#include <cmath>

Vaisseau::Vaisseau(float x, float y) : GameObject(x, y) {
    m_VitesseMax = 5.0f;
    m_Acceleration = 0.2f;
    m_Friction = 0.98f;
    m_VitesseRotation = 3.0f;
    m_CooldownTir = 0.3f;
    m_TimerTir = 0.0f;
}

void Vaisseau::Update() {
    if (IsKeyDown(KEY_LEFT)) Tourner(-1);
    if (IsKeyDown(KEY_RIGHT)) Tourner(1);
    if (IsKeyDown(KEY_UP)) Accelerer();
    if (IsKeyPressed(KEY_H)) Hyperspace();


    if (!m_Actif) return;

    m_TimerTir -= GetFrameTime();
    if (IsKeyDown(KEY_SPACE) && m_TimerTir <= 0) {
        Tirer();
        m_TimerTir = m_CooldownTir;
    }

    for (Projectile* p : m_Projectiles) {
        p->Update();
    }

    for (int i = m_Projectiles.size() - 1; i >= 0; i--) {
        if (!m_Projectiles[i]->EstActif()) {
            delete m_Projectiles[i];
            m_Projectiles.erase(m_Projectiles.begin() + i);
        }
    }

    m_Vitesse.x *= m_Friction;
    m_Vitesse.y *= m_Friction;
    m_Position.x += m_Vitesse.x;
    m_Position.y += m_Vitesse.y;
    WrapEcran();
}

void Vaisseau::Tourner(float direction) {
    m_Rotation += direction * m_VitesseRotation;
}

void Vaisseau::Accelerer() {
    float angle = m_Rotation * DEG2RAD;
    m_Vitesse.x += cosf(angle) * m_Acceleration;
    m_Vitesse.y += sinf(angle) * m_Acceleration;

    float speed = sqrtf(m_Vitesse.x * m_Vitesse.x + m_Vitesse.y * m_Vitesse.y);
    if (speed > m_VitesseMax) {
        m_Vitesse.x = (m_Vitesse.x / speed) * m_VitesseMax;
        m_Vitesse.y = (m_Vitesse.y / speed) * m_VitesseMax;
    }
}

void Vaisseau::WrapEcran() {
    if (m_Position.x > 800) m_Position.x = 0;
    if (m_Position.x < 0) m_Position.x = 800;
    if (m_Position.y > 600) m_Position.y = 0;
    if (m_Position.y < 0) m_Position.y = 600;
}

void Vaisseau::Tirer() {
    Projectile* p = new Projectile(m_Position.x, m_Position.y, m_Rotation);
    m_Projectiles.push_back(p);
}

void Vaisseau::Draw() {
    float angle = m_Rotation * DEG2RAD;
    Vector2 p1 = {
        m_Position.x + cosf(angle) * 45,
        m_Position.y + sinf(angle) * 45
    };
    Vector2 p2 = {
        m_Position.x + cosf(angle + 2.4f) * 25,
        m_Position.y + sinf(angle + 2.4f) * 25
    };
    Vector2 p3 = {
        m_Position.x + cosf(angle - 2.4f) * 25,
        m_Position.y + sinf(angle - 2.4f) * 25
    };
    DrawTriangleLines(p1, p2, p3, YELLOW);

    for (Projectile* p : m_Projectiles) {
        p->Draw();
    }
}
void Vaisseau::Hyperspace() {
    m_Position.x = (float)(rand() % 800);
    m_Position.y = (float)(rand() % 600);
    m_Vitesse = { 0, 0 };
    if (rand() % 5 == 0) {
        Desactiver();
    }
}