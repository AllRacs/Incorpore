#ifndef JUGADOR_H
#define JUGADOR_H

#include "Entidad.h" //<- Hijo de

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Animacion.h"

using namespace std;
using namespace sf;

class Jugador: public Entidad{
    public:
        Jugador(Vector2f pos);


        void update(float, RenderWindow&, int, FloatRect*);
        void moverse();
        void rotacionAtaque(RenderWindow&);

        Vector2f getMousePos();
        Vector2f getMovement();
    private:
        float dirMov;

        Vector2f playerCenter; //centro del jugador
        Vector2f mousePos; //posicion del raton
        Vector2f movement; //movimiento del jugador
};
#endif