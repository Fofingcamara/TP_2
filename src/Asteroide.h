#pragma once
#include "GameObject.h"

enum class TailleAsteroide {
    GRAND,
    MOYEN,
    PETIT
};

class Asteroide : public GameObject {
private:
    float m_Rayon;
    TailleAsteroide m_Taille;

public:
    Asteroide(float x, float y, TailleAsteroide taille);
    void Update() override;
    void Draw() override;
    TailleAsteroide GetTaille() const { return m_Taille; }
    float GetRayon() const { return m_Rayon; }

private:
    void WrapEcran();
    void InitVitesse();
};