#ifndef DIJKSTRA_HH_INCLUDED
#define DIJKSTRA_HH_INCLUDED
#include <iostream>
struct el_kopca{

    int  wierzcholek;
    int  dystans;

    el_kopca(){

        wierzcholek=0;
        dystans=0;
    }
    el_kopca(int wierzcholek1, int odleglosc1){

        wierzcholek=wierzcholek1;
        dystans=odleglosc1;
    }
};

struct kopiec{
    int rozmiar;
    int pojemnosc;
    int *pomoc;
    el_kopca *Kopiec;

    void push(el_kopca element);
    kopiec(int pojemnosc1){

        rozmiar=0;
        pojemnosc=pojemnosc1;
        pomoc=new int[pojemnosc];
        Kopiec=new el_kopca[pojemnosc];
    }
    void Podmien(int e1, int e2){
        el_kopca tmp=Kopiec[e1];
        Kopiec[e1]=Kopiec[e2];
        Kopiec[e2]=tmp;
        pomoc[e2]=e1;
        pomoc[e1]=e2;
    }
    void Wypisz(){
        for(int i=0; i<rozmiar; i++){
            std::cout<<Kopiec[i].dystans<<' ';
        }
    }
};

int najblizszy(int dys[], bool chmura[], int wierzcholkow);
void Kopcuj(kopiec &Kopiec, int indeks);
bool czypustykopiec(kopiec Kopiec);
el_kopca wyciung_najmn(kopiec &Kopiec);
void zmniejszklucz(kopiec &Kopiec, int wierzcholek, int dystans);
bool Czywkopcu(kopiec Kopiec, int wierzcholek);

#endif // DIJKSTRA_HH_INCLUDED
