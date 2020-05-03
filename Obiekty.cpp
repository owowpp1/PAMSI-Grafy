
#include "Dijkstra.hh"
#include "Obiekty.hh"


void Lista_sasiedztwa::DodajKr(int w1, int w2, int dystans){

    Krawedz *krawedz=new Krawedz;

    krawedz->w1=w1;
    krawedz->w2=w2;
    krawedz->dystans=dystans;

    if(poczatek==0) poczatek=krawedz;
    else{
        Krawedz *temp=poczatek;
        while(temp->nastepna) temp=temp->nastepna;
        temp->nastepna=krawedz;
        krawedz->nastepna=0;
    }
}



void Lista_sasiedztwa::Dijkstra(int korzen){

    int odleglosci[ile_w];
    kopiec Kopiec(ile_k);
//    std::cout<<"Pierwszy for\n";
    for (int i=0; i<ile_w; i++){
        odleglosci[i]=INT_MAX;
        el_kopca pomoc(i, odleglosci[i]);
        Kopiec.Kopiec[i]=pomoc;
        Kopiec.pomoc[i]=i;
    }
    Kopiec.rozmiar=ile_w;
    odleglosci[korzen]=0;
    el_kopca pomoc(korzen, odleglosci[korzen]);
    Kopiec.Kopiec[korzen]=pomoc;
    Kopiec.pomoc[korzen]=korzen;
    zmniejszklucz(Kopiec, korzen, odleglosci[korzen]);

//    std::cout<<"Pierwszy while\n";
    while (czypustykopiec(Kopiec)==false){

        el_kopca Najblizszy=wyciung_najmn(Kopiec);
        int x=Najblizszy.wierzcholek;
        Krawedz *krawedz=poczatek;
//        std::cout<<"drugi while\n";
        while (krawedz!=NULL){

            int wierzcholek=krawedz->w2;

            if (Czywkopcu(Kopiec, wierzcholek) && odleglosci[x]!=INT_MAX &&
                krawedz->dystans+odleglosci[x]<odleglosci[wierzcholek]){

                odleglosci[wierzcholek]=odleglosci[x]+krawedz->dystans;
                zmniejszklucz(Kopiec, wierzcholek, odleglosci[wierzcholek]);
            }
            krawedz=krawedz->nastepna;
        }
            std::cout<<"KOPIEC:\n";
            Kopiec.Wypisz();
            std::cout<<"Koniec KOPCA\n";
    }

    std::cout<<"Lista: odległości od wierzchołka numer "<<korzen<<":\n";
//    std::cout<<"drugi for\n";
    for(int i=0; i<ile_w; i++){
    std::cout<<"Do "<<i<<"    "<<odleglosci[i]<<std::endl;
    }
}

void Lista_sasiedztwa::Wypisz(){

    Krawedz *pomoc=poczatek;
    std::cout<<"rozmiar: "<<ile_w<<std::endl;
    while(pomoc!=NULL){
        std::cout<<pomoc->w2<<' '<<pomoc->dystans<<std::endl;
        pomoc=pomoc->nastepna;
    }
}


