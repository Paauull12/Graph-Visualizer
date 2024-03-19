//
// Created by paaull on 14.03.2024.
//

#ifndef PROJECTGRAPHS_GRAF_H
#define PROJECTGRAPHS_GRAF_H

#include <iostream>
#include <utility>
#include <vector>
#include <tuple>

using namespace std;

/*
 * Graful este reprezentat sub orice forma doriti, fiecare element fie el din matrice
 * sau lista de adiacenta este de forma pair<muchie adiacenta, cost>
 *
 * Operatii valide:
 *
 * -> transformare Adiacenta in Incidenta
 * -> tranformare Incidenta in Lista Vecini
 * -> tranformare Adiacenta in Lista Vecini
 * -> tranformare Lista Vecini in Adiacenta
 *
 * Daca graful este regular nu vom putea folosi matricea de Incidenta
 *
 *
 * */
class Graf
{
private:
    vector<vector<std::pair<int, int>>> reprezentare;

    int modReprez = 1;
    // 1 = mat adiacenta
    // 2 = mat incidenta
    // 3 = liste vecini

    int cicluInNod = 1;
    //1 inseamna ca graful este regular
    //0 inseamna ca graful nu este regular

    int tipVector = 0;
    //tipVector = 0 neorientat
    //tipVector = 1 orientat

    int cost = 0;
    //cost = 0 nu avem costuri
    //cost = 1 avem cost

    int noduri;
    vector <tuple<int, int, int>> muchii;

    void setReprez(vector<vector<pair<int, int>>> reprez);
    vector <vector <pair<int, int>>> schimbareAdiacentaIncidenta(vector <vector<pair<int, int>>> reprez);
    vector <vector <pair<int, int>>> schimbareAdiacentaListaAd(vector <vector<pair<int, int>>> reprez);
    vector <vector <pair<int, int>>> schimbareListaAdMatAdiacenta(vector <vector<pair<int, int>>> reprez);
    void afisareListaAdiacenta(vector<vector<pair<int, int>>> reprez);
    void afisareIncidenta(vector<vector<pair<int, int>>> reprez);
    void afisareAdiacenta(vector<vector<pair<int, int>>> reprez);
    void dfs(int k, vector <int> &viz);
    void construiesteFisierMDist(vector <vector<int>> mat, int inf);
public:

    Graf(int noduri, vector<tuple<int, int, int>> muchii, int tipVector, int cost);
    vector<vector<pair<int, int>>> getReprez();
    void AdiacentaLista();
    void ListaIncidenta();
    void ListaAdiacenta();
    void aAdiacenta();
    void aIncidenta();
    void aLista();
    vector<int> noduriIzolate();
    int grafRegular();
    vector <vector <int>> matriceaDistantelor();
    int esteConex();
    void export1();
    void ruleaza();
    void exportMatriceDeDistante();
};


#endif //PROJECTGRAPHS_GRAF_H
