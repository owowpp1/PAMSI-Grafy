#include "Obiekty.hh"
using namespace std;

void kopiec::push(el_kopca element){

    Kopiec[rozmiar]=element;
    rozmiar++;
    while(rozmiar>0){
        if(Kopiec[(rozmiar-1)/2].dystans<Kopiec[rozmiar].dystans){
            Podmien((rozmiar-1)/2, rozmiar);
            rozmiar=(rozmiar-1)/2;
        }
    }
}

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

    int Max=indeks;
    int lewysyn =2*indeks+1;
    int prawysyn=2*indeks+2;

    if (lewysyn <Kopiec.rozmiar && Kopiec.Kopiec[lewysyn] .dystans>Kopiec.Kopiec[Max].dystans) Max=lewysyn;
    if (prawysyn<Kopiec.rozmiar && Kopiec.Kopiec[prawysyn].dystans>Kopiec.Kopiec[Max].dystans) Max=prawysyn;

    if (Max!=indeks){
        Kopiec.Podmien(Max, indeks);

        Kopcuj(Kopiec, Max);
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
        Kopiec.Podmien(indeks, (indeks-1)/2);
        indeks=(indeks-1)/2;
    }
}

bool Czywkopcu(kopiec Kopiec, int wierzcholek){

   if(Kopiec.pomoc[wierzcholek]<Kopiec.rozmiar)return true;
   else return false;
}
