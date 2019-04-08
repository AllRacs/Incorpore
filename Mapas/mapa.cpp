#include "mapa.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace sf;
using namespace tinyxml2;
using namespace std;

mapa::mapa(){
    leerMapa(1);
    cargaObjetos();
    setDatos();
    getDatos();
    cargaTexturas();
    creaSprite();
}

mapa::~mapa(){
    //Destructor
}

void mapa::cargaObjetos(){
    caja = new int[2];
    cajadoble = new int[2];
    columna = new int[3];
    antorcha = new int[2];

    antorcha[0] = 153;
    antorcha[1] = 169;

    caja[0] = 101;
    caja[1] = 117;

    cajadoble[0] = 102;
    cajadoble[1] = 118;

    calavera = 49;

    cofre = 223;

    columna[0] = 189;
    columna[1] = 205;
    columna[2] = 221;

}

void mapa::leerMapa(int n){
    if(n == 1){
       docXML.LoadFile("resources/Mapa.tmx");
    }
    mapaXML = docXML.FirstChildElement("map");
    maxObj = 12;
}

void mapa::setDatos(){
    //Obtengo datos del tmx
    mapaXML->QueryIntAttribute("width", &width);
    mapaXML->QueryIntAttribute("height", &height);
    mapaXML->QueryIntAttribute("tilewidth", &tilewidth);
    mapaXML->QueryIntAttribute("tileheight", &tileheight);

    imagenTileset = mapaXML->FirstChildElement("tileset");
    ficheroImagen = (string)imagenTileset->FirstChildElement("image")->Attribute("source");
    capa = mapaXML->FirstChildElement("layer");
}

void mapa::cargaTexturas(){

    while(imagenTileset){
        if(!texturaTileset.loadFromFile(ficheroImagen)){
            std::cerr << "Error cargando la textura png";
            exit(0);
        }
        imagenTileset = imagenTileset->NextSiblingElement("tileset");
    }

    //Cuento el numero de capas que hay
    while(capa){
        nCapas++;
        capa = capa->NextSiblingElement("layer");
    }


    capa = mapaXML->FirstChildElement("layer"); //Volvemos a apuntar a la primera capa
    tileMap = new int**[nCapas]; //Asignamos el numero de capas
    string* nombreCapa = new string[nCapas];

    //Bucle declaracion capas
    for(int i = 0; i <  nCapas; i++){
        tileMap[i] = new int*[height]; //Asignamos el alto
        for(int j = 0; j < height; j++){
            tileMap[i][j] = new int[width]; //Asignamos el ancho
        }
    }

    //Inicializacion mapa de colisiones
    colisionMap = new bool*[height];
    for(int i = 0; i < height; i++){
        colisionMap[i] = new bool[width];
    }

    //Bucle asignacion por capas
    int n = 0; //Capa en la que nos encontramos en el bucle
    while(capa){
        data = capa->FirstChildElement("data")->FirstChildElement("tile");
        nombreCapa[n] = (string)capa->Attribute("name");
        while(data){
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    data->QueryIntAttribute("gid", &tileMap[n][i][j]);
                    if(n == nCapas-1){
                        if(tileMap[n][i][j] != 0){
                            colisionMap[i][j] = true;
                        }
                        else{
                            colisionMap[i][j] = false;

                        }
                    }
                    data = data->NextSiblingElement("tile");
                }
            }
        }

        capa = capa->NextSiblingElement("layer");
        n++;
    }

}

void mapa::generaObjetos(int j, int k){
    srand(time(NULL));
    int random = rand() % 100;
    if(random >= 0 && random < 30){
        //Antorcha
        mapSprite[1][j][k] = new Sprite(texturaTileset,tilesetSprite[antorcha[1]].getTextureRect());
        mapSprite[1][j][k]->setPosition(k*tilewidth,j*tileheight);

        mapSprite[2][j-1][k] = new Sprite(texturaTileset,tilesetSprite[antorcha[0]].getTextureRect());
        mapSprite[2][j-1][k]->setPosition(k*tilewidth,j*tileheight);
    }
    else if(random >= 30 && random < 53){
        //Caja
        mapSprite[1][j][k] = new Sprite(texturaTileset,tilesetSprite[antorcha[1]].getTextureRect());
        mapSprite[1][j][k]->setPosition(k*tilewidth,j*tileheight);

        mapSprite[2][j-1][k] = new Sprite(texturaTileset,tilesetSprite[antorcha[0]].getTextureRect());
        mapSprite[2][j-1][k]->setPosition(k*tilewidth,j*tileheight);
    }
    else if(random >= 53 && random < 68){
        //CajaDoble
        mapSprite[1][j][k] = new Sprite(texturaTileset,tilesetSprite[antorcha[1]].getTextureRect());
        mapSprite[1][j][k]->setPosition(k*tilewidth,j*tileheight);

        mapSprite[2][j-1][k] = new Sprite(texturaTileset,tilesetSprite[antorcha[0]].getTextureRect());
        mapSprite[2][j-1][k]->setPosition(k*tilewidth,j*tileheight);
    }
    else if(random >= 68 && random < 90){
        //Calavera
        mapSprite[1][j][k] = new Sprite(texturaTileset,tilesetSprite[antorcha[1]].getTextureRect());
        mapSprite[1][j][k]->setPosition(k*tilewidth,j*tileheight);

        mapSprite[2][j-1][k] = new Sprite(texturaTileset,tilesetSprite[antorcha[0]].getTextureRect());
        mapSprite[2][j-1][k]->setPosition(k*tilewidth,j*tileheight);
    }
    else if(random >= 90 && random < 100){
        //Columna
        mapSprite[1][j][k] = new Sprite(texturaTileset,tilesetSprite[antorcha[1]].getTextureRect());
        mapSprite[1][j][k]->setPosition(k*tilewidth,j*tileheight);

        mapSprite[2][j-1][k] = new Sprite(texturaTileset,tilesetSprite[antorcha[0]].getTextureRect());
        mapSprite[2][j-1][k]->setPosition(k*tilewidth,j*tileheight);
    }

}

void mapa::creaSprite(){
    int c = 0;
    mapSprite = new Sprite***[nCapas];

    for(int i = 0; i < nCapas; i++){
        mapSprite[i] = new Sprite**[height];
        for(int j = 0; j < height; j++){
            mapSprite[i][j] = new Sprite*[width];
            for(int z = 0; z < width; z++){
                mapSprite[i][j][z] = new Sprite;
            }
        }
    }
    int columnas = texturaTileset.getSize().x / tilewidth;
    int filas = texturaTileset.getSize().y / tileheight;

    tilesetSprite = new Sprite[filas*columnas];
    int n = 0;
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            tilesetSprite[n].setTexture(texturaTileset);
            tilesetSprite[n].setTextureRect(IntRect(j*tilewidth,i*tileheight, tilewidth, tileheight));
            n++;
        }
    }
    srand(time(NULL));
    for(int i = 0; i < nCapas; i++){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < width; k++){
                gid = tileMap[i][j][k]-1;
                if(gid>0 && gid < width*height){
                    mapSprite[i][j][k] = new Sprite(texturaTileset,tilesetSprite[gid].getTextureRect());
                    mapSprite[i][j][k]->setPosition(k*tilewidth,j*tileheight);
                }
                else{
                    mapSprite[i][j][k] = NULL;
                }
                if(colisionMap[j][k] == false){
                    //Generacion de objetos aleatorios
                    int random = rand() % 100;
                    cout << random << endl;
                    if(random < 1 && c < 12){
                        colisionMap[j][k] = true;
                        generaObjetos(j, k);
                        c++;
                    }
                }
            }
        }
    }

}


void mapa::getDatos(){
    cout << "ancho:" << width << endl;
    cout << "alto: " << height << endl;
    cout << "ancho tile: " << tilewidth << endl;
    cout << "alto tile: " << tileheight << endl;
    cout << "imagen: " << ficheroImagen << endl;
}

int mapa::getNumCapas(){
    return nCapas;
}

int mapa::getHeight(){
    return height;
}

int mapa::getWidth(){
    return width;
}

Sprite**** mapa::getMapSprite(){
    return mapSprite;
}

bool** mapa::getColisiones(){
    return colisionMap;
}
