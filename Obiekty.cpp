
#include "Dijkstra.hh"
#include "Obiekty.hh"

Macierz::Macierz(int procent, int wierzcholkow){
    Mac=new Krawedz*[wierzcholkow];
    for(int i=0; i<wierzcholkow; i++){
        Mac[i]=new Krawedz[wierzcholkow];
    }
    rozmiar=wierzcholkow;
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

Macierz::Macierz(int wierzcholkow){

    Mac=new Krawedz*[wierzcholkow];
    for(int i=0; i<wierzcholkow; i++){
        Mac[i]=new Krawedz[wierzcholkow];
    }
    rozmiar=wierzcholkow;
}

void Macierz::Wypisz(){
    for(int i=0; i<rozmiar; i++){
        for(int j=0; j<rozmiar; j++){
            if(Mac[i][j].dystans==0) std::cout<<std::setw(5)<<0;
            else std::cout<<std::setw(5)<<Mac[i][j].dystans;
        }
        std::cout<<'\n';
    }
}

void Macierz::Dijkstra(int korzen){

    int odleglosci[rozmiar];
    bool drzewo[rozmiar];

    for (int i=0; i<rozmiar; i++){
        odleglosci[i]=INT_MAX, drzewo[i]=false;
    }
    odleglosci[korzen]=0;

    for (int i=0; i<rozmiar-1; i++){
        int x=najblizszy(odleglosci, drzewo, rozmiar);
        drzewo[x]=true;

        for(int i=0; i<rozmiar; i++){
            if (drzewo[i]==false && odleglosci[x]+Mac[x][i].dystans<odleglosci[i]
                && Mac[x][i].dystans!=0 && odleglosci[x]!=INT_MAX){

                    odleglosci[i]=odleglosci[x]+Mac[x][i].dystans;
            }
        }
    }
    std::cout<<"Macierz: odległości od wierzchołka numer "<<korzen<<":\n";
    for(int i=0; i<rozmiar; i++){
        std::cout<<"Do "<<i<<"    ";
        if(odleglosci[i]!=INT_MAX)std::cout<<odleglosci[i]<<std::endl;
        else std::cout<<"Brak połączenia.\n";
    }
}

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



void Graf::Dijkstra(int korzen){

    int odleglosci[ile_w];
    kopiec Kopiec(ile_w);
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

        el_kopca element=wyciung_najmn(Kopiec);
        int x=element.wierzcholek;
        Krawedz *krawedz=lista[x].poczatek;
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
//            std::cout<<"KOPIEC:\n";
//            Kopiec.Wypisz();
//            std::cout<<"Koniec kopca\n";
    }

    std::cout<<"Lista: odległości od wierzchołka numer "<<korzen<<":\n";
//    std::cout<<"drugi for\n";
    for(int i=0; i<ile_w; i++){
    std::cout<<"Do "<<i<<"    "<<odleglosci[i]<<std::endl;
    }
}

void Lista_sasiedztwa::Wypisz(){

    Krawedz *pomoc=poczatek;
    while(pomoc!=NULL){
        std::cout<<pomoc->w2<<' '<<pomoc->dystans<<std::endl;
        pomoc=pomoc->nastepna;
    }
}


