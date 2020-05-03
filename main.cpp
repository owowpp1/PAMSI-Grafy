#include "Obiekty.hh"
#include "Dijkstra.hh"

#define wierzcholkow 15
#define procent 100

#include <ctime>
#include <chrono>

using namespace std;

int main(){

    ofstream plikm,plikl;
    plikm.open("Pomiary/Macierz.dat");
    plikl.open("Pomiary/Lista.dat");
    int wybor=-1;
    int Wierzcholki[5]={100, 250, 500, 750, 1000};
    int Procentyhehe[4]={25, 50, 75, 100};
    auto poczatek=chrono::steady_clock::now();
    auto koniec=chrono::steady_clock::now();
    while(wybor!=0){
        cout<<"Co chcesz zrobić?\n";
        cout<<"1-Wczytaj z pliku Dane.dat\n";
        cout<<"2-Rozpocznij pomiary losowe\n";
        cout<<"0-Wyjdź\n";
        cin>>wybor;
        switch(wybor){

            case 1:
                cout<<"Program wczytuje plik Dane.dat i wykonuje obliczenia.\n";
                WykonajZPliku();
            break;
            case 2:
                cout<<"Rozpoczęto pomiary.\n";
                for(int i=0; i<5; i++){
                    for(int j=0; j<4; j++){
                        plikm<<Wierzcholki[i]<<" wierzchołków "<<Procentyhehe[j]<<"%\n";
                        plikl<<Wierzcholki[i]<<" wierzchołków "<<Procentyhehe[j]<<"%\n";
                        for(int k=0; k<100; k++){
                            Macierz mac(Procentyhehe[j], Wierzcholki[i]);

    //                        mac.Wypisz();
                            poczatek=chrono::steady_clock::now();
                            mac.Dijkstra(1);
                            koniec=chrono::steady_clock::now();
                            cout<<"Ogarnianko grafu "<<Wierzcholki[i]<<" wierzchołków "<<Procentyhehe[j]<<"%";
                            cout<<" jako macierz nr"<<k<<endl;


                            plikm<<chrono::duration_cast<chrono::microseconds>(koniec-poczatek).count()<<endl;

                            Graf graf(wierzcholkow);
                            for(int i=0; i<wierzcholkow; i++){
                                Lista_sasiedztwa lista;
                                for(int j=0; j<wierzcholkow; j++){
                                    if(mac.Mac[i][j].dystans!=0)
                                    graf.lista[i].DodajKr(i,j,mac.Mac[i][j].dystans);
                                }
                            }

                        //    graf.Wypisz(wierzcholkow);
                            poczatek=chrono::steady_clock::now();
                            graf.Dijkstra(1);
                            koniec=chrono::steady_clock::now();
                            cout<<"Ogarnianko grafu "<<Wierzcholki[i]<<" wierzchołków "<<Procentyhehe[j]<<"%";
                            cout<<" jako lista nr"<<k<<endl;

                            plikl<<chrono::duration_cast<chrono::microseconds>(koniec-poczatek).count()<<endl;
                        }
                    }
                }
            break;
            case 0:
                cout<<"Program zamyka się.\n";
            break;
            default:
                cout<<"Nie ma takiej opcji. Spróbuj ponownie.\n";
            break;
        }
    }

    Macierz mac(procent, wierzcholkow);

    mac.Wypisz();

    mac.Dijkstra(1);


    Graf graf(wierzcholkow);
    for(int i=0; i<wierzcholkow; i++){
        Lista_sasiedztwa lista;
        for(int j=0; j<wierzcholkow; j++){
            if(mac.Mac[i][j].dystans!=0)
            graf.lista[i].DodajKr(i,j,mac.Mac[i][j].dystans);
        }
    }

//    graf.Wypisz(wierzcholkow);
    graf.Dijkstra(1);


    cout << "Hello world!" << endl;
    return 0;
}
