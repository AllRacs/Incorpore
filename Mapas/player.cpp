#include "player.h"
using namespace sf;

player::player(){
    jugador = new sf::RectangleShape({16,16});
    jugador->setFillColor(Color::White);
    jugador->setPosition(150,50);

    //cuadrados para las colisiones
    //cuadrado derecha
    cuadrado_der = new sf::RectangleShape({0.5,8});
    cuadrado_der->setFillColor(sf::Color::Blue);
    //cuadrado izquierda
    cuadrado_izq = new sf::RectangleShape({0.5,8});
    cuadrado_izq->setFillColor(sf::Color::Blue);
    //cuadrado superior
    cuadrado_arr = new sf::RectangleShape({16,0.5});
    cuadrado_arr->setFillColor(sf::Color::Blue);
    //cuadrado inferior
    cuadrado_abj = new sf::RectangleShape({16,0.5});
    cuadrado_abj->setFillColor(sf::Color::Blue);

    velocidad = 2;
}

RectangleShape player::getPlayer(){
    return *jugador;
}


///---------------------------------MOVIMIENTO
void player::movimiento()
{
     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && colisiona_derecha != true)
    {
        jugador->move(-velocidad, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && colisiona_izquierda != true)
    {
        jugador->move(velocidad, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && colisiona_abajo != true)
    {
        jugador->move(0, -velocidad);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && colisiona_arriba != true)
    {
        jugador->move(0, velocidad);

    }
    cuadrado_der->setPosition(jugador->getGlobalBounds().left + jugador->getGlobalBounds().width, jugador->getGlobalBounds().top + 8);
    cuadrado_arr->setPosition(jugador->getGlobalBounds().left, jugador->getPosition().y + 7.5);
    cuadrado_izq->setPosition(jugador->getGlobalBounds().left -0.5, jugador->getGlobalBounds().top+8);
    cuadrado_abj->setPosition(jugador->getGlobalBounds().left, jugador->getPosition().y + jugador->getGlobalBounds().height);
    colisiona_abajo = false;
    colisiona_arriba = false;
    colisiona_derecha = false;
    colisiona_izquierda = false;
}

void player::setColision(int num)
{
    if(num == 1)
        colisiona_arriba = true;
    if(num == 2)
        colisiona_abajo = true;
    if(num == 3)
        colisiona_izquierda = true;
    if(num == 4)
        colisiona_derecha = true;
}

void player::setPosicion(int x, int y)
{
    jugador->setPosition(x,y);
}

sf::RectangleShape player::cuadradoder(){
    return *cuadrado_der;
}

sf::RectangleShape player::cuadradoarr(){
    return *cuadrado_arr;
}

sf::RectangleShape player::cuadradoizq(){
    return *cuadrado_izq;
}

sf::RectangleShape player::cuadradoabaj(){
    return *cuadrado_abj;
}

