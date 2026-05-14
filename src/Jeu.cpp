#include "Jeu.h"
#include <cstdlib>
#include <cmath>

Jeu::Jeu() {
    m_ScreenWidth = 800;
    m_ScreenHeight = 600;

    m_Vaisseau = new Vaisseau(400, 300);
    m_Score = 0;
    m_Vies = 3;
    m_Niveau = 1;
    m_ProchaineBonusVie = 10000;
    SpawnAsteroides();
}

Jeu::~Jeu() {
    delete m_Vaisseau;
    for (Asteroide* a : m_Asteroides) {
        delete a;
    }
    m_Asteroides.clear();
    for (Soucoupe* s : m_Soucoupes) delete s;
    m_Soucoupes.clear();
}

void Jeu::SpawnAsteroides() {
    int nombre = 3 + m_Niveau;


    if (m_Score >= 40000 && m_Score <= 60000) {
        nombre += (m_Score - 40000) / 4000;
    }
    else if (m_Score > 60000) {
        nombre += 5;
    }

    for (int i = 0; i < nombre; i++) {
        float x, y;
        do {
            x = rand() % 800;
            y = rand() % 600;
        } while (sqrtf((x - 400) * (x - 400) + (y - 300) * (y - 300)) < 300);

        m_Asteroides.push_back(new Asteroide(x, y, TailleAsteroide::GRAND));
    }
}

void Jeu::Start() {
    while (!WindowShouldClose()) {
        Update();
        Draw();
        if (m_Vies <= 0) {
            if (IsKeyPressed(KEY_ENTER)) {
                break;
            }
        }
    }
}

void Jeu::Update() {
    if (m_Vies <= 0) return;
    m_Vaisseau->Update();

    for (Asteroide* a : m_Asteroides) {
        a->Update();
    }

    m_TimerSoucoupe -= GetFrameTime();
    if (m_TimerSoucoupe <= 0) {
        float y = (float)(rand() % 600);
        float x = (rand() % 2 == 0) ? 0.0f : 800.0f;

        TypeSoucoupe type;
        if (m_Score >= 40000) {
            type = TypeSoucoupe::PETITE;
        }
        else {
            type = (rand() % 2 == 0) ? TypeSoucoupe::GRANDE : TypeSoucoupe::PETITE;
        }

        m_Soucoupes.push_back(new Soucoupe(x, y, type, m_Score));
        m_TimerSoucoupe = 15.0f;
    }

    for (Soucoupe* s : m_Soucoupes) {
        s->SetCible(m_Vaisseau->GetPosition());
        s->SetScore(m_Score);
        s->Update();
    }

    VerifierCollisions();


    if (m_Score >= m_ProchaineBonusVie) {
        m_Vies++;
        m_ProchaineBonusVie += 10000;
    }


    if (m_Score > 99990) m_Score = 0;

    for (Soucoupe* s : m_Soucoupes) {
        s->NettoyerProjectiles();
    }

    if (m_Asteroides.empty()) {
        m_Niveau++;
        SpawnAsteroides();
    }
}

void Jeu::VerifierCollisions() {
    std::vector<Projectile*> projectiles = m_Vaisseau->GetProjectiles();

    if (m_TimerInvincible > 0) {
        m_TimerInvincible -= GetFrameTime();
    }

    for (int i = m_Asteroides.size() - 1; i >= 0; i--) {
        Asteroide* a = m_Asteroides[i];

        for (Projectile* p : projectiles) {
            if (!p->EstActif()) continue;

            float dx = p->GetPosition().x - a->GetPosition().x;
            float dy = p->GetPosition().y - a->GetPosition().y;
            float distance = sqrtf(dx * dx + dy * dy);

            if (distance < a->GetRayon() + m_Vaisseau->GetRayon()) {
                p->Desactiver();
                FragmenterAsteroide(a, i);
                break;
            }
        }

        if (m_TimerInvincible <= 0) {
            float dx = m_Vaisseau->GetPosition().x - a->GetPosition().x;
            float dy = m_Vaisseau->GetPosition().y - a->GetPosition().y;
            float distance = sqrtf(dx * dx + dy * dy);

            if (distance < a->GetRayon() + m_Vaisseau->GetRayon()) {
                m_Vies--;
                m_TimerInvincible = 3.0f;
                delete m_Vaisseau;
                m_Vaisseau = new Vaisseau(400, 300);
            }
        }
    }

    for (int i = m_Soucoupes.size() - 1; i >= 0; i--) {
        Soucoupe* s = m_Soucoupes[i];
        bool detruite = false;

        for (Projectile* p : projectiles) {
            if (!p->EstActif()) continue;
            float dx = p->GetPosition().x - s->GetPosition().x;
            float dy = p->GetPosition().y - s->GetPosition().y;
            if (sqrtf(dx * dx + dy * dy) < s->GetRayon()) {
                p->Desactiver();
                m_Score += 200;
                detruite = true;
                break;
            }
        }

        if (!detruite && m_TimerInvincible <= 0) {
            for (Projectile* p : s->GetProjectiles()) {
                if (!p->EstActif()) continue;
                float dx = p->GetPosition().x - m_Vaisseau->GetPosition().x;
                float dy = p->GetPosition().y - m_Vaisseau->GetPosition().y;
                if (sqrtf(dx * dx + dy * dy) < m_Vaisseau->GetRayon() + 5.0f) {
                    p->Desactiver();
                    m_Vies--;
                    m_TimerInvincible = 3.0f;
                    delete m_Vaisseau;
                    m_Vaisseau = new Vaisseau(400, 300);
                    break;
                }
            }
        }

        if (detruite) {
            delete m_Soucoupes[i];
            m_Soucoupes.erase(m_Soucoupes.begin() + i);
        }
    }
}

void Jeu::FragmenterAsteroide(Asteroide* a, int index) {
    if (a->GetTaille() == TailleAsteroide::GRAND) {
        m_Score += 20;
        m_Asteroides.push_back(new Asteroide(
            a->GetPosition().x, a->GetPosition().y, TailleAsteroide::MOYEN));
        m_Asteroides.push_back(new Asteroide(
            a->GetPosition().x, a->GetPosition().y, TailleAsteroide::MOYEN));
    }
    else if (a->GetTaille() == TailleAsteroide::MOYEN) {
        m_Score += 20;
        m_Asteroides.push_back(new Asteroide(
            a->GetPosition().x, a->GetPosition().y, TailleAsteroide::PETIT));
        m_Asteroides.push_back(new Asteroide(
            a->GetPosition().x, a->GetPosition().y, TailleAsteroide::PETIT));
    }
    else if (a->GetTaille() == TailleAsteroide::PETIT) {
        m_Score += 100;
    }

    delete m_Asteroides[index];
    m_Asteroides.erase(m_Asteroides.begin() + index);
}

void Jeu::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    m_Vaisseau->Draw();
    for (Asteroide* a : m_Asteroides) {
        a->Draw();
    }
    for (Soucoupe* s : m_Soucoupes) s->Draw();
    DrawUI();
    EndDrawing();
}

void Jeu::DrawUI() {
    DrawText(TextFormat("SCORE: %d", m_Score), 10, 10, 20, WHITE);
    DrawText(TextFormat("VIES: %d", m_Vies), m_ScreenWidth - 100, 10, 20, WHITE);
    DrawText(TextFormat("NIVEAU: %d", m_Niveau), m_ScreenWidth / 2 - 50, 10, 20, WHITE);

    if (m_Vies <= 0) {
        DrawText("GAME OVER",
            m_ScreenWidth / 2 - 100,
            m_ScreenHeight / 2,
            40, RED);
        DrawText("APPUYER SUR ENTREE POUR RETOURNER AU MENU",
            m_ScreenWidth / 2 - 280,
            m_ScreenHeight / 2 + 60,
            20, WHITE);
    }
}