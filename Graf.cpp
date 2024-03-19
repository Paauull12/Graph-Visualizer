//
// Created by paaull on 14.03.2024.
//

#include <fstream>
#include <cstdlib>
#include "Graf.h"

using namespace std;

void Graf:: setReprez(vector<vector<pair<int, int>>> reprez)
{
    reprezentare = reprez;
}

vector <vector <pair<int, int>>> Graf :: schimbareAdiacentaIncidenta(vector <vector<pair<int, int>>> reprez)
{

    if(modReprez != 1)
        return vector <vector <pair<int, int>>>(0, vector<pair<int, int>>(0, make_pair(0, 0)));

    if(cicluInNod == 0)
        return vector <vector <pair<int, int>>>(0, vector<pair<int, int>>(0, make_pair(0, 0)));

    vector <vector <pair<int, int>>> mat(noduri, vector<pair<int, int>>(muchii.size(), make_pair(0, 0)));

    int index = 0;

    modReprez = 2;

    for(int i = 0; i < reprez.size(); ++i) {
        for (int j = 0; j < i; ++j)
        {
            if(reprez[i][j].first)
            {
                mat[i][index].first = 1;
                mat[j][index].first = -1;
                mat[i][index].second = reprez[i][j].second;
                mat[j][index].second = reprez[i][j].second;
                index++;
            }
        }
        if(tipVector == 1)
        {
            for(int j = i + 1; j < reprez[i].size(); ++j)
            {
                if(reprez[i][j].first)
                {

                    mat[i][index].first = 1;
                    mat[j][index].first = -1;
                    mat[i][index].second = reprez[i][j].second;
                    mat[j][index].second = reprez[i][j].second;
                    index++;
                }
            }
        }
    }
    setReprez(mat);
    return mat;
}


vector <vector <pair<int, int>>> Graf::schimbareAdiacentaListaAd(vector <vector<pair<int, int>>> reprez)
{
    if(modReprez != 1)
        return vector <vector <pair<int, int>>>(0,vector<pair<int,int>>(0, make_pair(0, 0)));

    vector <vector <pair<int, int>>> mat(noduri, vector<pair<int, int>>());
    modReprez = 3;
    //muchie adiacenta, cost

    for(int i = 0; i < reprez.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (reprez[i][j].first) {
                mat[i].emplace_back(make_pair(j, reprez[i][j].second));
                if (tipVector == 0)
                    mat[j].emplace_back(make_pair(i, reprez[i][j].second));
            }
        }

        if (tipVector == 1)
        {
            for(int j = i + 1; j < reprez[i].size(); ++j)
                if(reprez[i][j].first)
                {
                    mat[i].emplace_back(make_pair(j, reprez[i][j].second));
                }
        }
    }

    setReprez(mat);
    return mat;
}

vector <vector <pair<int, int>>> Graf::schimbareListaAdMatAdiacenta(vector <vector<pair<int, int>>> reprez)
{
    if(modReprez != 3)
        return vector <vector <pair<int, int>>>(0,vector<pair<int,int>>(0, make_pair(0, 0)));

    vector <vector <pair<int, int>>> mat(noduri, vector<pair<int, int>>(noduri, make_pair(0, 0)));

    for(int i = 0 ; i < reprez.size(); ++i)
    {
        for(auto it: reprez[i])
        {
            mat[i][it.first].first = 1;
            mat[i][it.first].second = it.second;
        }
    }

    modReprez = 1;

    setReprez(mat);
    return mat;
}

void Graf::afisareAdiacenta(vector<vector<pair<int, int>>> reprez)
{
    ListaAdiacenta();
    if(modReprez != 1)
        return;
    for(int i = 0; i < reprez.size(); ++i)
    {
        for(int j = 0; j < reprez[i].size(); ++j)
        {
            cout << "(" << reprez[i][j].first << ", " << reprez[i][j].second << ") ";
        }
        cout << '\n';
    }
    AdiacentaLista();
}

void Graf::afisareIncidenta(vector<vector<pair<int, int>>> reprez)
{
    ListaIncidenta();
    if(modReprez != 2)
        return;

    for(int i = 0; i < reprez.size(); ++i)
    {
        for (int j = 0; j < muchii.size(); ++j)
            cout << reprez[i][j].first << ' ';
        cout << '\n';
    }
    //TODO INCIDENTA LISTA
}

void Graf::afisareListaAdiacenta(vector<vector<pair<int, int>>> reprez)
{
    if(modReprez != 3)
        return;

    for (int i = 0; i < reprez.size(); ++i) {
        for (int j = 0; j < reprez[i].size(); ++j)
            cout << '(' << i + 1 << ", " << reprez[i][j].first + 1 << ", " << reprez[i][j].second << ") ";
        if(reprez[i].size())
            cout << endl;
    }
}

Graf::Graf(int noduri, vector<tuple<int, int, int>> muchii, int tipVector, int cost): noduri(noduri), muchii(muchii), tipVector(tipVector), cost(cost)
{
    vector <vector <pair<int, int>>> mat(noduri, vector<pair<int, int>>(noduri, make_pair(0, 0)));

    for(auto it: muchii)
    {
        //cout << get<0>(it) << " " << get<1>(it) << ' ' << get<2>(it) << endl;
        if(get<0>(it) == get<1>(it))
            cicluInNod = 0;
        mat[get<0>(it) - 1][get<1>(it) - 1].first = 1;
        mat[get<0>(it) - 1][get<1>(it)- 1].second = get<2>(it);
        if(tipVector == 0)
        {
            mat[get<1>(it) - 1][get<0>(it) - 1].first = 1;
            mat[get<1>(it) - 1][get<0>(it)- 1].second = get<2>(it);
        }
    }

    reprezentare = mat;
    AdiacentaLista();
}

vector<vector<pair<int, int>>> Graf::getReprez()
{
    return reprezentare;
}

void Graf::AdiacentaLista()
{
    schimbareAdiacentaListaAd(reprezentare);
}

void Graf::ListaIncidenta()
{
    schimbareListaAdMatAdiacenta(reprezentare);
    schimbareAdiacentaIncidenta(reprezentare);
}

void Graf::ListaAdiacenta()
{
    schimbareListaAdMatAdiacenta(reprezentare);
}

void Graf::aAdiacenta()
{
    cout << '\n';
    afisareAdiacenta(reprezentare);
    cout << '\n';
}

void Graf::aIncidenta()
{
    cout << '\n';
    afisareIncidenta(reprezentare);
    cout << '\n';
}
void Graf::aLista()
{
    cout << '\n';
    afisareListaAdiacenta(reprezentare);
    cout << '\n';
}

vector<int> Graf::noduriIzolate()
{
    if(modReprez != 3)
        return vector<int>(0);

    vector <int> rez;
    for(int i = 0; i < reprezentare.size(); ++i)
    {
        if(!reprezentare[i].size())
            rez.emplace_back(i + 1);
    }

    return rez;
}

int Graf::grafRegular()
{
    if(modReprez != 3)
        return 0;

    int var = reprezentare[0].size();

    for(int i = 0; i < reprezentare.size(); ++i)
        if(var != reprezentare[i].size())
            return 0;
    return 1;
}

vector <vector <int>> Graf::matriceaDistantelor()
{
    if(modReprez != 3)
        return vector< vector <int> > (0, vector<int>(0));

    ListaAdiacenta();

    int inf = 1e9;
    vector <vector <int>> mat(noduri, vector<int>(noduri, inf));
    for(int i = 0; i < mat.size(); ++i)
        mat[i][i] = 0;

    for(int i = 0 ; i < reprezentare.size(); ++i)
        for(int j = 0; j < reprezentare[i].size(); ++j)
            if(reprezentare[i][j].second)
                mat[i][j] = reprezentare[i][j].second;

    for(int k = 0; k < reprezentare.size(); ++k)
        for(int i = 0; i < reprezentare.size(); ++i)
            for(int j = 0; j < reprezentare.size(); ++j)
            {
                if (mat[i][k] + mat[k][j] < mat[i][j])
                    mat[i][j] = mat[i][k] + mat[k][j];

            }

    AdiacentaLista();

    construiesteFisierMDist(mat, inf);

    for(int i = 0; i < mat.size(); ++i)
        for(int j = 0; j < mat[i].size(); ++j)
            if(mat[i][j] == inf)
                mat[i][j] = -1;

    return mat;
}

void Graf::construiesteFisierMDist(vector <vector<int>> mat, int inf)
{
    ofstream out("/home/paaull/Documents/grafuri/GrafMDistante.txt");

    if(tipVector == 1)
        out << "dir\n";
    else
        out << "0\n";

    if(cost)
        out << "1\n";
    else
        out << "0\n";

    for(int i = 0; i < mat.size(); ++i)
        for(int j = 0; j < mat[i].size(); ++j)
            if(mat[i][j] and mat[i][j] != inf)
                out << "(" << i + 1 << "," << j + 1 << "," << mat[i][j] << ")\n";

    out.close();
}

void Graf::dfs(int k, vector <int> &viz)
{
    viz[k] = 1;
    for(auto it: reprezentare[k])
        if(!viz[it.first])
            dfs(it.first, viz);
    return;
}

int Graf::esteConex()
{
    AdiacentaLista();
    vector <int> vizitat(noduri, 0);
    dfs(0, vizitat);
    for(int i = 0; i < noduri; ++i)
        if(!vizitat[i])
            return 0;
    return 1;
}

void Graf::export1()
{
    ofstream out("/home/paaull/Documents/grafuri/GrafExportat.txt");

    if(tipVector)
        out << "dir\n";
    else
        out << "0\n";

    if(cost)
        out << "1\n";
    else
        out << "0\n";

    for(auto it: muchii)
        out << "(" << get<0>(it) << "," << get<1>(it) << ',' << get<2>(it) << ")\n";

    out.close();
}

void Graf::ruleaza()
{
    system("python3 /home/paaull/Documents/grafuri/main.py");
    system("python3 /home/paaull/Documents/grafuri/main1.py");
}