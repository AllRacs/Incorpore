#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Posicion.h"
#include "Mapa.h"
#include "Astar.h"

int main()
{
    std::cout << "creando mapa" << std::endl;
    Mapa *m = new Mapa(9,10);
    std::cout << "mapa creado" << std::endl;
                        //Y,X
    Posicion x = Posicion(9,0);
    Posicion y = Posicion(4,8);
    std::cout << "creando ia" << std::endl;
    Astar *ia = new Astar(x, y, *m);
    std::cout << "ia creada" << std::endl << ";;;;;;;;;;;;;" << std::endl;

    std::cout << "mapeando" << std::endl;
    std::vector<Posicion> path = ia->mapear();
    std::cout << "mapedao hecho" << std::endl;

    std::cout << "Path size: " << path.size() << std::endl;
    for(int a = 0; a < path.size(); a++)
    {
        std::cout << path.at(a).getY() << " .... " << path.at(a).getX() << std::endl;
    }

    std::cout << "________EL CAMINO________" << std::endl << std::endl;

    if(path.size()==0){
        std::cout << " ------- No hay solucion posible -------" << std::endl;
        std::cout << " ------- Feels Bad Man D: -------" << std::endl;
    }
    else
    {
        int flag = true;
        for(int a = 0; a < m->getHeight(); a++)
        {
            std::cout << "  ";
            for(int b = 0; b < m->getWidth(); b++)
            {
                flag = true;
                for(int c = 0; c < path.size()-1; c++)
                {
                    if(path.at(c).getX() == b && path.at(c).getY() == a)
                    {
                        std::cout << "- ";
                        flag = false;
                        break;
                    }
                }
                if(flag && x.getY()== a && x.getX() == b)
                {
                    std::cout << "# ";
                    flag = false;
                }
                if(flag && y.getY()== a && y.getX() == b)
                {
                    std::cout << "@ ";
                    flag = false;
                }
                if(flag)
                {
                    if(m->getMapa()[a][b] == 1)
                    {
                        std::cout << "1 ";
                    }
                    else
                    {
                        std::cout << "0 ";
                    }
                }
            }
            std::cout << std::endl << std::endl;
        }

    }



    delete m;
    exit(0);
}
