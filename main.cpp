#include "Obiekty.hh"
#include "Dijkstra.hh"

#define wierzcholkow 10
#define procent 50

using namespace std;

int main(){

    int Wierzcholki[5]={100, 250, 500, 750, 1000};
    int Procentyhehe[4]={25, 50, 75, 100};
    Macierz<wierzcholkow> mac(procent);

    mac.Wypisz();

    mac.Dijkstra(1);

    Lista_sasiedztwa lista(wierzcholkow);
    for(int i=0; i<wierzcholkow; i++){
        for(int j=0; j<wierzcholkow; j++){
            if(mac.Mac[i][j].dystans!=0)
            lista.DodajKr(i,j,mac.Mac[i][j].dystans);
            lista.ile_k++;
        }
    }
    lista.Wypisz();
    lista.Dijkstra(1);

    cout << "Hello world!" << endl;
    return 0;
}
