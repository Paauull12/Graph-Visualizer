#include <iostream>
#include <utility>
#include <vector>
#include <tuple>
#include "Graf.h"

using namespace std;

int main()
{
    vector<tuple<int, int, int>> muchii;
    muchii.emplace_back(1,2,1);
    //muchii.emplace_back(2,1,2);
    muchii.emplace_back(1,3,3);
   // muchii.emplace_back(1,4,4);
    muchii.emplace_back(1,5,1);
    Graf a = Graf(5, muchii, 0, 1);

    vector <int> x = a.noduriIzolate();
    for(auto it : x)
        cout << it << ' ';

    cout << endl;

    cout << a.grafRegular();

    cout << endl;

    vector<vector<int>> mat = a.matriceaDistantelor();

    cout << a.esteConex();

//    a.export1();
  //  a.ruleaza();
    //a.matriceaDistantelor();
    return 0;
}