#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

int vectContSum(vector<int> vect)
{
	int count = 0;

	for (int i = 0; i < vect.size(); i++)
	{
		count += vect[i];
	}

	return count;
}


void changeslow(vector<int> V, int A, vector<int> &change)
{
	vector<vector<int>> solutions;
	vector<int> retValue; 

	// set solutions[0]
	vector<int> zeroSolution(V.size(), 0);
	solutions.push_back(zeroSolution);

    int sum = 0;    //Ben
    
	// bottom up fill the solutions table
	for (int i = 1; i <= A; i++)
	{
		vector<int> tempchange(V.size(), 0);
		int count = A;
		int j = 0;

		// while the coin at V[j] is less than or equal to value A subtract V[j] from A and get the solution out 
		// of the solution table. We know that is is there since we are building from V[0] up 
		while (j < V.size() && V[j] <= i)
		{
			vector<int> tempChange(V.size(), 0);
			int tempCount = A;

			tempChange = solutions[i - V[j]];
			tempChange[j]++; // add one to tempchange to cover the addition of one V[i] coin
			tempCount = vectContSum(tempChange);

			if (tempCount <= count)
			{
				retValue = tempChange;
				count = tempCount;
                sum = tempCount;    //Ben
			}

			j++;
		}

		// solutions[i] = min from above while loop 
		solutions.push_back(retValue);
        
	}

	change = solutions[A];
    change.push_back(sum);
    

}

//Ben
int main (int algc, char* algv[])
{
    
    // Test 1: V = [1, 3, 7, 12] and A = 29 should return C = [0, 1, 2, 1] with m = 4.
    vector<int> V {1, 3, 7, 12};
    vector<int> change;
    changeslow(V, 29, change);
    //now change should have array followed by sum

    cout << "[";
    for (int x = 0; x < change.size()-2; x++)
    {
        cout << change[x] << ", ";
    }
    
    cout << change[change.size()-2] << "]" << endl;
    cout << change[change.size()-1] << endl;

    
    
    return 0;
}