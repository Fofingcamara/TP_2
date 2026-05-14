#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include <vector>

enum class TypeSoucoupe {
    GRANDE,
    PETITE
};

class Soucoupe : public GameObject {
private:
    float m_Rayon;
    float m_TimerTir;
    float m_CooldownTir;
    float m_TimerChangementDirection;
    Vector2 m_Cible;
    TypeSoucoupe m_Type;
    int m_Score;

public:
    Soucoupe(float x, float y, TypeSoucoupe type, int score = 0);
    void Update() override;
    void Draw() override;
    void NettoyerProjectiles();
    float GetRayon() const { return m_Rayon; }
    TypeSoucoupe GetType() const { return m_Type; }
    std::vector<Projectile*>& GetProjectiles() { return m_Projectiles; }
    void SetCible(Vector2 cible) { m_Cible = cible; }
    void SetScore(int score) { m_Score = score; }

private:
    void WrapEcran();
    void Tirer();

    std::vector<Projectile*> m_Projectiles;
};