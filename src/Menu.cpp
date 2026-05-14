#include "Menu.h"

Menu::Menu(int width, int height) {
    m_ScreenWidth = width;
    m_ScreenHeight = height;
}

void Menu::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);


    DrawText("ASTEROIDS",
        m_ScreenWidth / 2 - 150,
        m_ScreenHeight / 2 - 100,
        60, YELLOW);


    DrawText("APPUYEZ SUR ENTREE POUR JOUER",
        m_ScreenWidth / 2 - 200,
        m_ScreenHeight / 2 + 20,
        20, WHITE);


    DrawText("APPUYEZ SUR ECHAP POUR QUITTER",
        m_ScreenWidth / 2 - 200,
        m_ScreenHeight / 2 + 60,
        20, RED);

    EndDrawing();
}

bool Menu::JouerClique() {
    return IsKeyPressed(KEY_ENTER);
}

bool Menu::QuitterClique() {
    return IsKeyPressed(KEY_ESCAPE);
}