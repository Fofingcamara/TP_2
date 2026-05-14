#include "GameObject.h"

GameObject::GameObject(float x, float y) {
    m_Position = { x, y };
    m_Vitesse = { 0, 0 };
    m_Rotation = 0;
    m_Actif = true;
}