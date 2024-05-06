#include <chrono>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <sstream>
#include "SortingAlgorithm.hpp"

using namespace std;
using namespace SortLibrary;

vector<int> crea_vettore_int(const unsigned int& dimV) //crea un vettore di int 'random' tra 0 e 100
{
    vector<int> v(dimV);
    for (unsigned int i=0;i<dimV;i++)
    {
        v[i]=rand()%100;
    }
    return v;
}

vector<double> crea_vettore_double(const unsigned int& dimV) //crea un vettore di double 'random' tra 0 e 100
{
    vector<double> v(dimV);
    for (unsigned int i=0;i<dimV;i++)
    {
        v[i]=(rand()%10000)/100.;
    }
    return v;
}

vector<int> crea_ordinato(const unsigned int& dimV) //crea un vettore di int 'random' già ordinato dal numero più piccolo al numero più grande
{
    vector<int> v(dimV);
    v[0]=rand()%10;
    for (unsigned int i=1;i<dimV;i++)
    {
        unsigned int incremento=rand()%10;
        v[i]=v[i-1]+incremento;
    }
    return v;
}

template <typename T>
void stampa_vettore(const vector<T>& vettore)
{
    cout <<"[ ";
    for(unsigned int i=0;i<vettore.size();i++)
    {
        cout<< vettore[i]<<" ";
    }
    cout << "]"<<endl;
}

template <typename T>
double prova_BS(vector<T> vettore,const unsigned int& n_prove) //restituisce il tempo medio di BubbleSort per ordinare il vettore su n_prove prove
{
    double t_medio=0.;
    for(unsigned int i=0;i<n_prove;i++)
    {
        vector<T> vett_prova=vettore;
        chrono::steady_clock::time_point t_inizio=chrono::steady_clock::now();
        BubbleSort(vett_prova);
        chrono::steady_clock::time_point t_fine=chrono::steady_clock::now();
        double tempo=chrono::duration_cast<chrono::microseconds>(t_fine-t_inizio).count();
        t_medio+=tempo*1./n_prove;
    }
    return t_medio;
}

template <typename T>
double prova_MS(vector<T> vettore,const unsigned int& n_prove) //restituisce il tempo medio di MergeSort per ordinare il vettore su n_prove prove
{
    double t_medio=0.;
    for(unsigned int i=0;i<n_prove;i++)
    {
        vector<T> vett_prova=vettore;
        chrono::steady_clock::time_point t_inizio=chrono::steady_clock::now();
        MergeSort(vett_prova);
        chrono::steady_clock::time_point t_fine=chrono::steady_clock::now();
        double tempo=chrono::duration_cast<chrono::microseconds>(t_fine-t_inizio).count();
        t_medio+=tempo*1./n_prove;
    }
    return t_medio;
}

template <typename T>
void restituisci_esito(const vector<T>& vettore,const unsigned int& n_prove,const string& testo)
{
    cout << "-----------------------------------"<<endl;
    cout << "Prova: vettore di "<<testo <<endl;
    stampa_vettore(vettore);
    cout << "L'algoritmo 'BubbleSort' impiega mediamente un tempo di ";
    double t=prova_BS(vettore, n_prove);
    cout << t << " microsecondi per ordinare il vettore, mentre l'algoritmo 'MergeSort' impiega ";
    t=prova_MS(vettore, n_prove);
    cout << t << " microsecondi per ordinare il vettore."<<endl;
    cout << "-----------------------------------"<<endl<<endl;
}

int main(int argc, char ** argv)
{
    for(int i=1; i<argc; i++)
    {
        string stringa=argv[i];
        istringstream convertitore(stringa);
        unsigned int dimV;
        unsigned int n_prove = 30;
        convertitore >> dimV;
        if(dimV==0)
        {
            cerr << "Errore: la dimensione del vettore risulta essere 0"<<endl;
            continue;
        }
        cout <<"Dimensione vettore: "<<dimV <<endl;
        vector<double> vett_dou=crea_vettore_double(dimV);
        vector<int> vett_int=crea_vettore_int(dimV);
        vector<int> ord_int=crea_ordinato(dimV);
        restituisci_esito(vett_dou,n_prove,"double (non ordinato)");
        restituisci_esito(vett_int,n_prove,"int (non ordinato)");
        restituisci_esito(ord_int,n_prove,"int (gia' ordinato)");
    }
    return 0;
}
