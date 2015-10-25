#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
#include <assert.h>

using namespace std;

int changedpInternal(int change, const vector<int> V, vector<int> &T, vector< vector<int> > &C){

    int minCoins = change;
    vector<int> D (V.size(), 0);
    
    if (change == 0){
        T.at(0) = 0; // should do T[0] = 0
        C.at(0) = D;
        return 0;
    }
    /*
    else if (change == 1){
        D.at(0) = 1;    // array [1,0,0,...,0]
        C.at(1) = D;
        T.at(1) = 1;
        return 1;
    }
    */
    else if (T.at(change) != -1){   // solution for change
                                    // should be in table T
        return T.at(change);    //WE NEVER HIT THIS LINE!!
    }
    
    for (int d = 0; d < V.size(); d++){
        if (change == V.at(d)){ // V[d] is a coin's denomination or value
            D.at(d) = 1;
            C.at(change) = D;
            T.at(change) = 1;
            return 1;
        }
    }
    
    int numCoins;
    for (int i = 0; i < V.size() && V.at(i) <= change; i++){
        numCoins = 1 + changedpInternal(change - V.at(i), V, T, C);
        if (numCoins <= minCoins){
            minCoins = numCoins;
            D = C[change - V.at(i)];    // (re)assign D
            D.at(i) = D.at(i) + 1;
            C.at(change) = D;           // C[change] = D;
            T.at(change) = minCoins;    // T[change] = minCoins;
        }
    }
    
    return minCoins;

}

struct solution{
    int m;
    vector<int> D;
};

solution changedp(int change, const vector<int> V){
    
    vector<int> T (change+1, -1);
    // This will store minCoins solution for each amount of change i.
    T.at(0) = 0;
    
    vector< vector<int> > C (change+1, vector<int>(V.size(),-1) );
    // This will store an array of denominations as the solution
    // for each amount of change i.
    
    int m = changedpInternal(change, V, T, C);
    solution sol;
    sol.m = m;
    sol.D = C.at(change);
    
    return sol;
    
}

//NOTE: line 44 may be a problem


int main (int argc, char* argv[]){
    
    
    // Test 1: expected: m=4, [1,1,1,1]
    //vector<int> V {1, 2, 4, 8};
    //int change = 15;
    
    // Test 2: expected: m=4, [0,1,2,1]
    //vector<int> V {1, 3, 7, 12};
    //int change = 29;
    
    // Test 3: expected: m=3, [0,0,1,2]
    vector<int> V {1, 3, 7, 12};
    int change = 31;
    
    
    solution test_sol = changedp(change, V);
    
    cout << "test_sol.m: " << test_sol.m << endl;
    for (int x = 0; x < test_sol.D.size(); x++){
        cout << "test_sol.D[" << x << "]: " << test_sol.D[x] << endl;
    }
    
    
    return 0;
    
}