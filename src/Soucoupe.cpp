#include "Soucoupe.h"
#include <cmath>
#include <cstdlib>

Soucoupe::Soucoupe(float x, float y, TypeSoucoupe type, int score) : GameObject(x, y) {
    m_Type = type;
    m_Score = score;
    m_Cible = { 400, 300 };
    m_TimerChangementDirection = 2.0f;

    float direction = (rand() % 2 == 0) ? 1.0f : -1.0f;

    if (m_Type == TypeSoucoupe::GRANDE) {
        m_Rayon = 30.0f;
        m_CooldownTir = 3.0f;
        m_Vitesse = { direction * 1.5f, (float)(rand() % 3 - 1) };
    }
    else {
        m_Rayon = 15.0f;
        m_CooldownTir = 1.0f;
        m_Vitesse = { direction * 3.0f, (float)(rand() % 3 - 1) };
    }

    m_TimerTir = m_CooldownTir;
}

void Soucoupe::Update() {
    m_TimerChangementDirection -= GetFrameTime();
    if (m_TimerChangementDirection <= 0) {
        m_Vitesse.y = (float)(rand() % 5 - 2);
        m_TimerChangementDirection = 2.0f;
    }

    m_Position.x += m_Vitesse.x;
    m_Position.y += m_Vitesse.y;
    WrapEcran();

    m_TimerTir -= GetFrameTime();
    if (m_TimerTir <= 0) {
        Tirer();
        m_TimerTir = m_CooldownTir;
    }

    for (int i = m_Projectiles.size() - 1; i >= 0; i--) {
        m_Projectiles[i]->Update();
        if (!m_Projectiles[i]->EstActif()) {
            delete m_Projectiles[i];
            m_Projectiles.erase(m_Projectiles.begin() + i);
        }
    }
}

void Soucoupe::Tirer() {
    float angle;

    if (m_Type == TypeSoucoupe::GRANDE) {

        angle = (float)(rand() % 360);
    }
    else {

        float dx = m_Cible.x - m_Position.x;
        float dy = m_Cible.y - m_Position.y;
        float angleVers = atan2f(dy, dx) * RAD2DEG;


        float imprecision = 30.0f - (m_Score / 40000.0f) * 30.0f;
        if (imprecision < 0) imprecision = 0;

        float offset = ((rand() % 100) / 100.0f - 0.5f) * 2.0f * imprecision;
        angle = angleVers + offset;
    }

    Projectile* p = new Projectile(m_Position.x, m_Position.y, angle);
    m_Projectiles.push_back(p);
}

void Soucoupe::WrapEcran() {
    if (m_Position.x > 800) m_Position.x = 0;
    if (m_Position.x < 0)   m_Position.x = 800;
    if (m_Position.y > 600) m_Position.y = 0;
    if (m_Position.y < 0)   m_Position.y = 600;
}

void Soucoupe::Draw() {
    Color couleur = (m_Type == TypeSoucoupe::GRANDE) ? GREEN : SKYBLUE;
    int r = (int)m_Rayon;


    DrawEllipse((int)m_Position.x, (int)m_Position.y, r, (int)(r * 0.4f), DARKGRAY);
    DrawEllipseLines((int)m_Position.x, (int)m_Position.y, r, (int)(r * 0.4f), couleur);


    DrawEllipse((int)m_Position.x, (int)m_Position.y - (int)(r * 0.3f),
        (int)(r * 0.5f), (int)(r * 0.35f), GRAY);
    DrawEllipseLines((int)m_Position.x, (int)m_Position.y - (int)(r * 0.3f),
        (int)(r * 0.5f), (int)(r * 0.35f), couleur);


    for (Projectile* p : m_Projectiles) {
        p->Draw();
    }
}
void Soucoupe::NettoyerProjectiles() {
    for (int i = m_Projectiles.size() - 1; i >= 0; i--) {
        if (!m_Projectiles[i]->EstActif()) {
            delete m_Projectiles[i];
            m_Projectiles.erase(m_Projectiles.begin() + i);
        }
    }
}