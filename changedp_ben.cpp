#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

int changedpInternal(int change, const vector<int> V, vector<int> T, vector< vector<int> > C){

    int minCoins = change;
    vector<int> D (V.size());
    // or D.resize(V.size());
    
    if (change == 0){
        T.push_back(0); // should do T[0] = 0
        C[0] = D;
        return 0;
    }
    else if (change == 1){
        D[0] = 1;    // array [1,0,0,...,0]
        C[1] = D;
        T[1] = 1;
        return 1;
    }
    else if (change < T.size()){    // solution for change
                                    // should be in table T
        return T[change];
    }
    
    for (int d = 0; d < V.size(); d++){
        if (change == V[d]){ // V[d] is a coin's denomination or value
            D[d] = 1;
            C[change] = D;
            T[change] = 1;
            return 1;
        }
    }
    
    int numCoins;
    for (int i = 0; i < V.at(i); i++){
        numCoins = 1 + changedpInternal(change - V[i], V, T, C);
        if (numCoins <= minCoins){
            minCoins = numCoins;
            D = C[change - V[i]];     // (re)assign D
            D[i] = D[i] + 1;
            C.push_back(D);         // C[change] = D;
            T.push_back(minCoins);         // T[change] = minCoins;
        }
    }
    
    return minCoins;

}

struct solution{
    int m;
    vector<int> D;
};

solution changedp(int change, const vector<int> V){
    
    vector<int> T;
    // This will store minCoins solution for each amount of change i.
    T[0] = 0;
    
    vector< vector<int> > C;
    // This will store an array of denominations as the solution
    // for each amount of change i.
    
    int m = changedpInternal(change, V, T, C);
    solution sol;
    sol.m = m;
    sol.D = C[change];
    
    return sol;
    
}




int main (int argc, char* argv[]){
    
    
    return 0;
    
}