#ifndef OBIEKTY_HH_INCLUDED
#define OBIEKTY_HH_INCLUDED

#include <iostream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
#include <limits.h>

#include "Dijkstra.hh"

struct Wierzcholek{

    std::string nazwa;
    int numer;
};

struct Krawedz{

    int dystans;
    int w1, w2;
    struct Krawedz* nastepna;

    Krawedz(){
        dystans=0;
        w2=0;
        nastepna=0;
    }
};

template<int wierzcholkow>
struct Macierz{

    Krawedz Mac[wierzcholkow][wierzcholkow];

    Macierz(int procent);
    void Wypisz();
    void Dijkstra(int korzen);
};
template<int wierzcholkow>
Macierz<wierzcholkow>::Macierz(int procent){
    int j=1;
    for(int i=0; i<wierzcholkow-1; i++){
        Mac[i][j].dystans=rand()%900+100;
        j++;
    }
    srand (time(NULL));
    int krawedzi=procent*(wierzcholkow*(wierzcholkow-1))/200-wierzcholkow+2;
    int w1,w2;
    for(int i=1; i<krawedzi; i++){
        w1=0; w2=1;
        while(Mac[w1][w2].dystans!=0){
            w1=rand()%(wierzcholkow-2);
            w2=rand()%(wierzcholkow-w1-1)+w1+1;
        }
        Mac[w1][w2].dystans=rand()%900+100;
    }
    int x=wierzcholkow-1;
    for(int j=0; j<wierzcholkow-1; j++){
        for(int i=x; i>0; i--){
            Mac[i+wierzcholkow-x-1][j].dystans=Mac[j][i+wierzcholkow-x-1].dystans;
        }
        x--;
    }
}
template<int wierzcholkow>
void Macierz<wierzcholkow>::Wypisz(){
    for(int i=0; i<wierzcholkow; i++){
        for(int j=0; j<wierzcholkow; j++){
            if(Mac[i][j].dystans==0) std::cout<<std::setw(5)<<0;
            else std::cout<<std::setw(5)<<Mac[i][j].dystans;
        }
        std::cout<<'\n';
    }
}
template<int wierzcholkow>
void Macierz<wierzcholkow>::Dijkstra(int korzen){

    int odleglosci[wierzcholkow];
    bool drzewo[wierzcholkow];

    for (int i=0; i<wierzcholkow; i++){
        odleglosci[i]=INT_MAX, drzewo[i]=false;
    }
    odleglosci[korzen]=0;

    for (int i=0; i<wierzcholkow-1; i++){
        int x=najblizszy(odleglosci, drzewo, wierzcholkow);
        drzewo[x]=true;

        for(int i=0; i<wierzcholkow; i++){
            if (drzewo[i]==false && odleglosci[x]+Mac[x][i].dystans<odleglosci[i]
                && Mac[x][i].dystans!=0 && odleglosci[x]!=INT_MAX){

                    odleglosci[i]=odleglosci[x]+Mac[x][i].dystans;
            }
        }
    }
    std::cout<<"Macierz: odległości od wierzchołka numer "<<korzen<<":\n";
    for(int i=0; i<wierzcholkow; i++){
        std::cout<<"Do "<<i<<"    "<<odleglosci[i]<<std::endl;
    }
}

struct Lista_sasiedztwa{

    Krawedz *poczatek;
    int ile_w, ile_k;

    Lista_sasiedztwa(){poczatek=0; ile_w=0; ile_k=0;}
    Lista_sasiedztwa(int wierzcholkow){poczatek=0; ile_w=wierzcholkow;}
    void DodajKr(int w1, int w2, int dystans);
    void Dijkstra(int korzen);
    void Wypisz();
};


#endif // OBIEKTY_HH_INCLUDED
