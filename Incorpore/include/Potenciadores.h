#ifndef POTENCIADORES_H
#define POTENCIADORES_H

#include "Jugador.h"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Potenciadores
{
    public:
        Potenciadores(Vector2f);
        virtual ~Potenciadores();
        void abrirCofre(Jugador&, int);
        void gestionarHabilidades(Jugador&, int);

        Sprite getCofre();

        void draw(sf::RenderWindow&);
    protected:
        bool primera = true;

        Sprite *sprite;
        Texture tex;
    private:
};

#endif // POTENCIADORES_H
