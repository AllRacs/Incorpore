#ifndef CONSUMIBLE_H
#define CONSUMIBLE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "time.h"

class Consumible{
    public:
        Consumible(sf::Vector2f);
        virtual ~Consumible();
        void draw(sf::RenderWindow&);
        void creaConsumible(sf::Vector2f);
        bool consume(sf::RectangleShape);
        sf::FloatRect getConsumibleHitbox();
        bool isConsumible();
        int getTipo();
    private:
        sf::Sprite *sprite;
        sf::Texture *tex;
        bool hayConsumible;
        int tipo = 1;
};

#endif // CONSUMIBLE_H
