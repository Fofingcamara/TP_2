#include "entrypoint.h"
#include "Jeu.h"
#include "Menu.h"

void raylib_start(void) {
    InitWindow(800, 600, "Asteroids");
    SetTargetFPS(60);

    Menu menu(800, 600);
    bool enJeu = false;

    while (!WindowShouldClose()) {
        if (!enJeu) {

            menu.Draw();

            if (menu.JouerClique()) {
                enJeu = true;
            }
            if (menu.QuitterClique()) {
                break;
            }
        }
        else {

            Jeu jeu;
            jeu.Start();

            enJeu = false;
        }
    }

    CloseWindow();
}