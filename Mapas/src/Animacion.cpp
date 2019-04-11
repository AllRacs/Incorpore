
#include <iostream>
#include "../include/Animacion.h"

Animacion::Animacion()
{

}

Animacion::~Animacion()
{
    //dtor
}


void Animacion::setAnimacion(char* nTextura, sf::IntRect firstF, sf::IntRect finalF, int incremento, float tiempo)
{
    std::cout << "cargamos la textura: " << nTextura << std::endl;

    if(!texture.loadFromFile(nTextura)){
        std::cout << "ERROR AL CARGAR TEXTURA";
    }
    this->firstF = firstF;
    this->finalF = finalF;
    this->incremento = incremento;
    actualFrame = firstF;
    switchTime = tiempo;
    sprite = sf::Sprite(texture, actualFrame);
    sprite.setOrigin((firstF.width)/2, (firstF.height)/2);

}

void Animacion::update(float deltaTime, sf::Vector2f movement)
{
    totalTime += deltaTime;
    if(totalTime >= switchTime) {
        totalTime -= switchTime;

        if(actualFrame.left == finalF.left){
            actualFrame.left = firstF.left;
            std::cout << "Cambiamos de frame0" << std::endl;
        } else {
            actualFrame.left += incremento;
            std::cout << "Cambiamos de frame" << std::endl;
        }

        sprite.setTextureRect(actualFrame);
    }

    //sprite.setPosition(playerCenter.x, playerCenter.y);
    sprite.move(movement * deltaTime);


}