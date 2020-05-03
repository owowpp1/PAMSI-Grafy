#include "Obiekty.hh"
using namespace std;

int najblizszy(int dys[], bool drzewo[], int wierzcholkow){

    int najk_dro=INT_MAX;
    int wierzcholek;

    for(int i=0; i<wierzcholkow; i++){
        if(drzewo[i]==false && dys[i]<=najk_dro){
            najk_dro=dys[i];
            wierzcholek=i;
        }
    }
    return wierzcholek;
}

void Kopcuj(kopiec &Kopiec, int indeks){

    int najkrotsza, lewy, prawy;
    najkrotsza=indeks;
    lewy =2*indeks+1;
    prawy=2*indeks+2;

    if(Kopiec.Kopiec[lewy].dystans<Kopiec.Kopiec[najkrotsza].dystans&&
       lewy<Kopiec.rozmiar)     najkrotsza=lewy;

    if(Kopiec.Kopiec[prawy].dystans<Kopiec.Kopiec[najkrotsza].dystans&&
       prawy<Kopiec.rozmiar)    najkrotsza=prawy;

    if(najkrotsza!=indeks){
        el_kopca najmniejszy=Kopiec.Kopiec[najkrotsza];
        el_kopca index      =Kopiec.Kopiec[indeks];

        Kopiec.pomoc[najmniejszy.wierzcholek]=indeks;
        Kopiec.pomoc[index.wierzcholek]=najkrotsza;

        Kopiec.Podmien(Kopiec.Kopiec[najkrotsza], Kopiec.Kopiec[indeks]);

        Kopcuj(Kopiec, najkrotsza);
    }
}

bool czypustykopiec(kopiec Kopiec){
    if(Kopiec.rozmiar==0)return true;
    else return false;
}

el_kopca wyciung_najmn(kopiec &Kopiec){

    if(!czypustykopiec(Kopiec)) {

    el_kopca korzen=Kopiec.Kopiec[0];
    el_kopca ostatni=Kopiec.Kopiec[Kopiec.rozmiar-1];
    Kopiec.Kopiec[0]=ostatni;

    Kopiec.pomoc[korzen.wierzcholek]=Kopiec.rozmiar-1;
    Kopiec.pomoc[ostatni.wierzcholek]=0;

    Kopiec.rozmiar--;
    Kopcuj(Kopiec, 0);

    return korzen;
    }
}

void zmniejszklucz(kopiec &Kopiec, int wierzcholek, int dystans){

    int indeks=Kopiec.pomoc[wierzcholek];
    Kopiec.Kopiec[indeks].dystans=dystans;
    while (indeks!=0&& Kopiec.Kopiec[indeks].dystans<Kopiec.Kopiec[(indeks-1)/2].dystans){

        Kopiec.pomoc[Kopiec.Kopiec[indeks].wierzcholek]=(indeks-1)/2;
        Kopiec.pomoc[Kopiec.Kopiec[(indeks-1)/2].wierzcholek]=indeks;
        Kopiec.Podmien(Kopiec.Kopiec[indeks], Kopiec.Kopiec[(indeks-1)/2]);
        indeks=(indeks-1)/2;
    }
}

bool Czywkopcu(kopiec Kopiec, int wierzcholek){

   if(Kopiec.pomoc[wierzcholek]<Kopiec.rozmiar)return true;
   else return false;
}
