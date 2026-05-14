#include "Asteroide.h"
#include <cmath>

Asteroide::Asteroide(float x, float y, TailleAsteroide taille)
    : GameObject(x, y) {
    m_Taille = taille;


    switch (taille) {
    case TailleAsteroide::GRAND:  m_Rayon = 40.0f; break;
    case TailleAsteroide::MOYEN:  m_Rayon = 20.0f; break;
    case TailleAsteroide::PETIT:  m_Rayon = 10.0f; break;
    }

    InitVitesse();
}

void Asteroide::InitVitesse() {
    float angle = (float)(rand() % 360) * DEG2RAD;


    float vitesse;
    switch (m_Taille) {
    case TailleAsteroide::GRAND:  vitesse = 1.0f; break;
    case TailleAsteroide::MOYEN:  vitesse = 2.0f; break;
    case TailleAsteroide::PETIT:  vitesse = 3.0f; break;
    }

    m_Vitesse.x = cosf(angle) * vitesse;
    m_Vitesse.y = sinf(angle) * vitesse;
}

void Asteroide::Update() {
    m_Position.x += m_Vitesse.x;
    m_Position.y += m_Vitesse.y;
    WrapEcran();
}

void Asteroide::Draw() {
    DrawCircle(
        (int)m_Position.x,
        (int)m_Position.y,
        m_Rayon,
        GRAY

    );
}

void Asteroide::WrapEcran() {
    if (m_Position.x > 800) m_Position.x = 0;
    if (m_Position.x < 0) m_Position.x = 800;
    if (m_Position.y > 600) m_Position.y = 0;
    if (m_Position.y < 0) m_Position.y = 600;
}