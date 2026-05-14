#pragma once
#include "raylib.h"

enum class EtatJeu {
    MENU,
    JEU,
    GAME_OVER
};

class Menu {
private:
    int m_ScreenWidth;
    int m_ScreenHeight;

public:
    Menu(int width, int height);
    void Draw();
    bool JouerClique();
    bool QuitterClique();
};