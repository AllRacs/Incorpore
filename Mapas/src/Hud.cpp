#include <SFML/Graphics.hpp>
#include "../include/Hud.h"
using namespace std;
using namespace sf;

Hud::Hud(){
    //PIEZA HUD VIDA
    pieza_vida = new RectangleShape({115,20});
    pieza_vida->setFillColor(Color(28,17,23,255));
    pieza_vida->setPosition(0,0);

    //TEXTO DE VIDA
    texto_vida = new Text;
    fuente = new Font;
    fuente->loadFromFile("resources/hud/coolvetica.ttf");
    texto_vida->setFont(*fuente);
    texto_vida->setString("Life");
    texto_vida->setScale(0.5, 0.5);
    texto_vida->setPosition(5, 0);

    //ARRAY DE CORAZONES
    textura_vida = new Texture;
    textura_vida->loadFromFile("resources/hud/heart-life.png");

    corazon = new Sprite;
    corazon->setTexture(*textura_vida);
    corazon->setScale({0.03,0.03});

    cantidad_corazones = new vector<Sprite>;

    for(int i = 0; i < 3; i++)
    {
        cantidad_corazones->push_back(*corazon);
    }

    //ARRAY HABILIDADES
    vector_habilidades = new vector<Sprite>;
    textura_habilidades = new Texture;
    textura_habilidades->loadFromFile("resources/hud/habilidades.png");

    //mejora ataque
    mejora_ataque = new Sprite(*textura_habilidades);
    mejora_ataque->setTextureRect(IntRect(306,1,61,61));
    mejora_ataque->setScale(0.2, 0.2);

    //mejora cofre
    mejora_cofre = new Sprite(*textura_habilidades);
    mejora_cofre->setTextureRect(IntRect(61,122,61,61));
    mejora_cofre->setScale(0.2, 0.2);

    //mejora escudo
    mejora_escudo = new Sprite(*textura_habilidades);
    mejora_escudo->setTextureRect(IntRect(1,1,61,61));
    mejora_escudo->setScale(0.2, 0.2);

    //rompe-escudos
    rompe_escudos = new Sprite(*textura_habilidades);
    rompe_escudos->setTextureRect(IntRect(61,61,61,61));
    rompe_escudos->setScale(0.2, 0.2);

    //mana
    mana = new Sprite(*textura_habilidades);
    mana->setTextureRect(IntRect(122,1,61,61));
    mana->setScale(0.2, 0.2);

    //espada magica
    espada_magica = new Sprite(*textura_habilidades);
    espada_magica->setTextureRect(IntRect(244,61,61,61));
    espada_magica->setScale(0.2, 0.2);


    //PIEZA HUD HABILIDADES
    pieza_habilidades = new RectangleShape({90,16});
    pieza_habilidades->setFillColor(Color(28,17,23,255));
    pieza_habilidades->setOrigin(pieza_habilidades->getOrigin().x/2, pieza_habilidades->getOrigin().x/2);
    pieza_habilidades->setPosition(180,520);
}

void Hud::compruebaTeclas(){
    if(Keyboard::isKeyPressed(Keyboard::Up)){
        modificar_vida(1,1);
    }
    if(Keyboard::isKeyPressed(Keyboard::Down))
    {
        modificar_vida(1,2);
    }

    ///HABILIDADES
    //borrar todas las habilidades
    if(Keyboard::isKeyPressed(Keyboard::D))
    {
        borradoHabilidades();
    }
    //coger habilidades
    if(Keyboard::isKeyPressed(Keyboard::Num1))
    {
        setHabilidad(1);
    }
    if(Keyboard::isKeyPressed(Keyboard::Num2))
    {
        setHabilidad(2);
    }
    if(Keyboard::isKeyPressed(Keyboard::Num3))
    {
        setHabilidad(3);
    }
    if(Keyboard::isKeyPressed(Keyboard::Num4))
    {
        setHabilidad(4);
    }
    if(Keyboard::isKeyPressed(Keyboard::Num5))
    {
        setHabilidad(5);
    }
    if(Keyboard::isKeyPressed(Keyboard::Num6))
    {
        setHabilidad(6);
    }
}

void Hud::modificar_vida(int cantidad, int sr){
    if(sr == 1 && cantidad_corazones->size() < 10)
    {
        cantidad_corazones->push_back(*corazon);
    }
    if(sr == 2 && cantidad_corazones->size() > 0)
    {
        cantidad_corazones->pop_back();
    }

    for(int i = 0; i < cantidad_corazones->size(); i++)
    {
        cantidad_corazones->at(i).setPosition({pieza_vida->getPosition().x + 24 + (i * 8), pieza_vida->getPosition().y + 2});
    }
}

void Hud::setHabilidad(int habilidad){
    if(habilidad == 1 && mejora_escudo_esta == false)
    {
        vector_habilidades->push_back(*mejora_escudo);
        mejora_escudo_esta = true;
    }
    if(habilidad == 2 && mejora_cofre_esta == false)
    {
        vector_habilidades->push_back(*mejora_cofre);
        mejora_cofre_esta = true;
    }
    if(habilidad == 3 && mejora_ataque_esta == false)
    {
        vector_habilidades->push_back(*mejora_ataque);
        mejora_ataque_esta = true;
    }
    if(habilidad == 4 && mana_esta == false)
    {
        vector_habilidades->push_back(*mana);
        mana_esta = true;
    }
    if(habilidad == 5 && rompe_escudos_esta == false)
    {
        vector_habilidades->push_back(*rompe_escudos);
        rompe_escudos_esta = true;
    }
    if(habilidad == 6 && espada_magica_esta == false)
    {
        vector_habilidades->push_back(*espada_magica);
        espada_magica_esta = true;
    }

    for(int i = 0; i < vector_habilidades->size(); i++)
    {
       vector_habilidades->at(i).setPosition({pieza_habilidades->getPosition().x + (i*15.5),pieza_habilidades->getPosition().y});
    }
}

void Hud::borradoHabilidades(){
    vector_habilidades->clear();
    mejora_escudo_esta = false;
    mejora_cofre_esta = false;
    mejora_ataque_esta = false;
    mana_esta = false;
    espada_magica_esta = false;
    rompe_escudos_esta = false;
}


//SETTERS

void Hud::setPosicionVida(int x, int y){
    xVida = x;
    yVida = y;
    pieza_vida->setPosition(x,y);
    texto_vida->setPosition(pieza_vida->getPosition().x, pieza_vida->getPosition().y);
    for(int i = 0; i < cantidad_corazones->size(); i++)
    {
        cantidad_corazones->at(i).setPosition({pieza_vida->getPosition().x + 24 + (i * 8), pieza_vida->getPosition().y + 2});
    }
}

void Hud::setPosicionHabilidades(int x, int y){
    xHab = x;
    yHab = y;
    pieza_habilidades->setPosition(x,y);
    for(int i = 0; i < vector_habilidades->size(); i++)
    {
       vector_habilidades->at(i).setPosition({pieza_habilidades->getPosition().x + (i*15.5),pieza_habilidades->getPosition().y});
    }
}

//GETTERS

Sprite Hud::getCorazon(){
    return *corazon;
}

Text Hud::getTextoVida(){
    return *texto_vida;
}

RectangleShape Hud::getPiezaVida(){
    return *pieza_vida;
}

RectangleShape Hud::getPiezaHabilidades(){
    return *pieza_habilidades;
}

vector<Sprite> Hud::getArrayVida(){
    return *cantidad_corazones;
}

vector<Sprite> Hud::getArrayHabilidades(){
    return *vector_habilidades;
}

int Hud::getCantidadVida(){
    return cantidad_corazones->size();
}

int Hud::getCantidadHabilidades(){
    return vector_habilidades->size();
}

void Hud::draw(RenderWindow& target){
    target.draw(*pieza_vida);
    target.draw(*texto_vida);
    target.draw(*pieza_habilidades);

    for(int i = 0; i < cantidad_corazones->size(); i++)
    {
        target.draw(cantidad_corazones->at(i));
    }

    for(int i = 0; i < vector_habilidades->size(); i++)
    {
        target.draw(vector_habilidades->at(i));
    }
}

void Hud::move(Vector2f delta){
    pieza_vida->move(delta);
    texto_vida->move(delta);
    for(int i = 0; i < cantidad_corazones->size(); i++)
    {
        cantidad_corazones->at(i).move(delta);
    }
    pieza_habilidades->move(delta);
    for(int i = 0; i < vector_habilidades->size(); i++)
    {
       vector_habilidades->at(i).move(delta);
    }
}