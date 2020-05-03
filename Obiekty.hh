#ifndef OBIEKTY_HH_INCLUDED
#define OBIEKTY_HH_INCLUDED

#include <iostream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
#include <limits.h>

#include "Dijkstra.hh"
struct Dane{

    int wierzcholkow1, krawedzi, startowy, x, y;
};
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
    ~Krawedz(){};
};

struct Macierz{

    Krawedz **Mac;
    int rozmiar;

    Macierz(int procent, int wierzcholkow);
    Macierz(int wierzcholkow);
    void Wypisz();
    void Dijkstra(int korzen);
    ~Macierz(){
        for(int i=0; i<rozmiar; i++){
            delete [] Mac[i];
        }
        delete [] Mac;
    }
};



struct Lista_sasiedztwa{

    Krawedz *poczatek;

    Lista_sasiedztwa(){poczatek=0;}
    void DodajKr(int w1, int w2, int dystans);
    void Wypisz();
};
struct Graf{

    Lista_sasiedztwa *lista;
    int ile_w;

    Graf(int wierzcholkow){

        lista=new Lista_sasiedztwa[wierzcholkow];
        ile_w=wierzcholkow;
    }
    ~Graf(){
        for(int i=0; i<ile_w; i++){
            Krawedz *pomoc=lista[i].poczatek;
            while(pomoc!=NULL){
                lista[i].poczatek=pomoc->nastepna;
                delete pomoc;
                pomoc=lista[i].poczatek;
            }
        }
        delete [] lista;
    }
//    void dodaj(Lista_sasiedztwa lista1, int idx){
//
//        lista[idx]=lista1;
//    }
    void Dijkstra(int korzen);
    void Wypisz(){

        for(int i=0; i<ile_w; i++){
            std::cout<<"Wierzcholek nr "<<i<<std::endl;
            lista[i].Wypisz();
            std::cout<<std::endl;
        }
    }
};

#endif // OBIEKTY_HH_INCLUDED
