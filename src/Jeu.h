#pragma once
#include "raylib.h"
#include "Vaisseau.h"
#include "Asteroide.h"
#include "Soucoupe.h" 
#include <vector>

class Jeu {
private:
    int m_ScreenWidth;
    int m_ScreenHeight;
    bool m_Running;
    float m_TimerInvincible = 0.0f;
    float m_TimerSoucoupe = 15.0f;
    Vaisseau* m_Vaisseau;
    std::vector<Asteroide*> m_Asteroides;
    std::vector<Soucoupe*> m_Soucoupes;
    int m_Score;
    int m_Vies;
    int m_Niveau;
    int m_ProchaineBonusVie = 10000;



public:
    Jeu();
    ~Jeu();
    void Start();
    void Update();
    void Draw();

private:
    void SpawnAsteroides();
    void VerifierCollisions();
    void FragmenterAsteroide(Asteroide* a, int index);
    void DrawUI();
    bool EstTermine() { return m_Vies <= 0; }
};