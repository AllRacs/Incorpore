#include <iostream>
#include "../include/Jugador.h"

using namespace std;
using namespace sf;

Jugador::Jugador(Vector2f pos, int mejora){
    entityCenter = pos;
    mostrarTumba = false;
    entidadHitbox.setPosition(pos);
    setColisionadores();

    hp = 10;
    attack = 3;
    defense = 2;
    speed = 75.f;
    spd = speed;
    escudo = false;

    dirMov = 1.f;
    movement = Vector2f(0.f, 0.f);

    //Esquivar
    esquivando = false;
    puedeEsquivar = true;

    // Animaciones
    idle.setAnimacion("resources/sprites/personajes.png", IntRect(0, 28*3, 16, 28), IntRect(48, 28*3, 16, 28), 16, 0.1f);
    idle.sprite.setOrigin(9,20);
    run.setAnimacion("resources/sprites/personajes.png", IntRect(64, 28*3, 16, 28), IntRect(112, 28*3, 16, 28), 16, 0.1f);
    run.sprite.setOrigin(9,20);

    actual = &idle;
    actual->sprite.setPosition(pos);

    arma = new Arma(0, mejora, pos);
}

Jugador::Jugador(Vector2f pos, int vida, int tipoarma, int mejora, int ataque, int defensa, float velocidad, bool shield){
    entityCenter = pos;
    mostrarTumba = false;
    entidadHitbox.setPosition(pos);
    setColisionadores();
    escudo = shield;
    mostrarTumba = false;
    hp = vida;
    attack = ataque;
    defense = defensa;
    speed = velocidad;
    spd = speed;

    dirMov = 0.6f;
    movement = Vector2f(0.f, 0.f);

    //Esquivar
    esquivando=false;
    puedeEsquivar=true;

    // Animaciones
    idle.setAnimacion("resources/sprites/personajes.png", IntRect(0, 28*3, 16, 28), IntRect(48, 28*3, 16, 28), 16, 0.1f);
    idle.sprite.setOrigin(9,20);
    run.setAnimacion("resources/sprites/personajes.png", IntRect(64, 28*3, 16, 28), IntRect(112, 28*3, 16, 28), 16, 0.1f);
    run.sprite.setOrigin(9,20);


    actual = &idle;
    actual->sprite.setPosition(pos);

    arma = new Arma(tipoarma, mejora, pos);
}

int Jugador::update(float delta, RenderWindow& window, int nCol, FloatRect* colisiones){
    int cambia = -1;

    entityCenter = Vector2f(entidadHitbox.getPosition().x, entidadHitbox.getPosition().y);
    actual->sprite.setScale(1.f*(arma->getDireccionMov()), 1.f);
    // MOVIMIENTO con interpolacion

    //atacar();
    if(cInterp.getElapsedTime().asMilliseconds() > 500/15)
    {
        moverse(); // comprobar que el jugador se mueve
        cInterp.restart();
    }
    moverColisionadores(movement * delta);
    procesarColisiones(nCol, colisiones);
    entidadHitbox.move(movement * delta); // mover al jugador.
    ataqueHitbox.move(movement * delta);// mover la hitbox con la que el jugador ataca
    arma->update(movement * delta, nCol, colisiones); // para que la espada se mueva junto con el jugador.
    actual->update(movement, delta);

    arma->rotacionAtaque(window, dirMov, entityCenter, entidadHitbox);
    ataqueHitbox = arma->getHitbox();

    //Esquivar
    esquivarInicio();
    controlarEsquivar();

     if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        arma->crearProyectil(entidadHitbox.getPosition());
    }

    if(CDarma.getElapsedTime().asSeconds() >= 2.f || inicioArma){
        flagArma = true;
    }
    else{
        flagArma = false;
    }

    //Tecla para activar el ataque a distancia
    if(Keyboard::isKeyPressed(Keyboard::Q)){
        if(flagArma || inicioArma){
            CDarma.restart();
            if(arma->getOpcion()==0){
                cambiarArma(1);
            } else {
                cambiarArma(0);
            }
            cambia = arma->getOpcion();
            inicioArma = false;
        }
    }
    compruebaColor();

    return cambia;
}

bool Jugador::cogePortal(FloatRect portal){
    bool res = false;
    if(cuadrado_arr->getGlobalBounds().intersects(portal)||
       cuadrado_abj->getGlobalBounds().intersects(portal)||
       cuadrado_der->getGlobalBounds().intersects(portal)||
       cuadrado_izq->getGlobalBounds().intersects(portal)){
                res = true;
        }
    return res;
}

bool Jugador::cogeCofre(FloatRect cofre){
    bool res = false;
    if(cuadrado_arr->getGlobalBounds().intersects(cofre)||
       cuadrado_abj->getGlobalBounds().intersects(cofre)||
       cuadrado_der->getGlobalBounds().intersects(cofre)||
       cuadrado_izq->getGlobalBounds().intersects(cofre)){
                res = true;
    }
    return res;
}

int Jugador::recibeDmg(RectangleShape enemigoHitbox, int vida, float atkEnemigo){
    int res = 0;
    Vector2f enemyPos = enemigoHitbox.getPosition();
    if(getEntidadHitbox().getGlobalBounds().intersects(enemigoHitbox.getGlobalBounds()) && dmgCD.getElapsedTime().asSeconds() >= 1.5 && vida > 0 && !esquivando){
        if(!escudo){
            hp -= atkEnemigo - defense;
            actual->sprite.setColor(sf::Color::Red);
            res = atkEnemigo - defense;
        }
        else{
            escudo = false;
            res = -1;

        }
        dmgCD.restart();
    }
    return res;
}

void Jugador::esquivarInicio(){
     if(Keyboard::isKeyPressed(Keyboard::LShift) && puedeEsquivar){
        esquivando=true;
        puedeEsquivar=false;
        cdEsquivar.restart();
        duracionEsquivar.restart();
       // std::cout<<"Esquivar ha empezado"<<std::endl;
     }
}

void Jugador::controlarEsquivar(){
    if(duracionEsquivar.getElapsedTime().asSeconds()>=2.f){
        //std::cout<<"Esquivar ha terminado"<<std::endl;
        esquivando=false;
        speed = spd;
    }
    if(cdEsquivar.getElapsedTime().asSeconds()>=5.f){
        puedeEsquivar=true;
        //std::cout<<"Cooldown ha terminado"<<std::endl;
    }
    if(esquivando){
        actual->sprite.setColor(sf::Color(105,105,105, 50));
        //std::cout << "entra en esquivando" << std::endl;
        speed = spd + 25.f;
    }
}


void Jugador::moverse(){
    movement = Vector2f(0.f, 0.f);

    if (Keyboard::isKeyPressed(Keyboard::W) && colisiona_abajo != true){
        movement.y -= speed;
        if (actual != &run){
            //cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
//            std::cout << "Entity center: " << entityCenter.x << ", " << entityCenter.y << std::endl;
            actual->sprite.setPosition(entityCenter);
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::S) && colisiona_arriba != true){
        movement.y += speed;

        if (actual != &run){
            //cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(entityCenter);
        }
    }

    if(Keyboard::isKeyPressed(Keyboard::A) && colisiona_derecha != true){
        movement.x -= speed;

        if (actual != &run){
            //cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(entityCenter);
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::D) && colisiona_izquierda != true){
        movement.x += speed;

        if (actual != &run){
            //cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(entityCenter);
        }
    }

    if(movement.x == 0 & movement.y == 0) {
        if (actual != &idle){
            //cout << "CAMBIAMOS A IDLE" << endl;
            actual = &idle;
            actual->sprite.setPosition(entityCenter);
        }
    }

    colisiona_abajo = false;
    colisiona_arriba = false;
    colisiona_derecha = false;
    colisiona_izquierda = false;
}

void Jugador::compruebaColor(){
    if(escudo){
           actual->sprite.setColor(sf::Color::Yellow);
    }
    else if(!esquivando){
                actual->sprite.setColor(sf::Color::White);
    }
    if(cd.getElapsedTime().asSeconds() >= 0.25 && !esquivando && escudo){
        actual->sprite.setColor(sf::Color::White);
        cd.restart();
    }
}

Vector2f Jugador::getMovement() {
    return movement;
}

Arma& Jugador::getArma() {
    return *arma;
}

Arma* Jugador::getPuntArma() {
    return arma;
}

void Jugador::cambiarArma(int opcion){
    /*
    delete arma;
    arma=new Arma(opcion, entityCenter);
    */
    if(arma->getOpcion() == 1) {
        arma->cambiarArma(0);
    } else {
        arma->cambiarArma(1);
    }

}

float Jugador::getCooldownAtaque() {
    return meleCD.getElapsedTime().asSeconds();
}

void Jugador::restartCoolDownAtaque() {
    meleCD.restart();
}

void Jugador::muerteJugador(){
    mostrarTumba=true;

     if(!tTumba.loadFromFile("resources/sprites/muerte.png")){
        std::cout<<"No se cargo la tumba"<<std::endl;
    }
    tumba.setTexture(tTumba);
    tumba.setOrigin(16/2,20/2);
    tumba.setPosition(entityCenter);

}

bool Jugador::getEscudo(){
    return escudo;
}

void Jugador::escudarse(){
    escudo = true;
}
bool Jugador::flagEsquivar(){
    return puedeEsquivar;
}

bool Jugador::puedeCambiarArma(){
    return flagArma;
}

void Jugador::draw(sf::RenderWindow &app) {
    if(mostrarTumba==true){
        app.draw(tumba);
    } else {
        if(ataqueHitbox.getRotation() >= 0 && ataqueHitbox.getRotation() <= 180) {
            app.draw(actual->sprite);
            app.draw(arma->getEspada());
        } else {
            app.draw(arma->getEspada());
            app.draw(actual->sprite);
        }
        app.draw(ataqueHitbox);

        for(int i = 0; i < arma->getProyectiles().size(); i++) {
            arma->getProyectiles().at(i)->draw(app);
        }
    }
}
