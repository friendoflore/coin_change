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


void changedp(vector<int> V, int A, vector<int> &change)
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



//from Tim's work
vector< vector <int> > parse_input(vector<string> input_strings);


int main (int algc, char* algv[])
{
    
    // Test 1: V = [1, 3, 7, 12] and A = 29 should return C = [0, 1, 2, 1] with m = 4.
    // vector<int> V {1, 3, 7, 12};
    // vector<int> change;
    
    ofstream f_output;
    // These are used to store the runtime of the algorithm
    clock_t t1, t2;
    double runtime;
    
    // This stores the problem arrays that we will use to do calculations
    vector< vector<int> > input_arrays;
    
    // Open problems text
    ifstream problems ("Amount.txt", ifstream::in);
    
    // This stores the problem arrays that we will use to do calculations
    string input_string;
    
    // This stores the all problems lines of file input
    vector<string> problem_set;
    
    while(problems.good()) {
      getline(problems, input_string);
      if(input_string.length() != 0) {
        problem_set.push_back(input_string);
      }
    }
    input_arrays = parse_input(problem_set);
    // odd-indexed vectors in input_arrays are the input array
    // even-indexed vectors in input_arrays are A
    // Example: input_arrays[0] = {1, 3, 7, 12} and 
    //  input_arrays[1] = 29
    
    // variables to hold arguments to the function
    vector<int> V;
    int A;
    vector<int> change;
    
    //prepare output file
    f_output.open("Amountchange.txt");
    
    // loop over each pair of input lines
    for (int x = 0; x < input_arrays.size(); x=x+2)
    {
        V = input_arrays[x];
        A = input_arrays[x+1][0];
        
        //time the algorithm and print runtime to output
        t1 = clock();
        
        changedp(V, A, change);
        //now change should have array followed by sum
        
        t2 = clock();
        runtime = (t2 - t1) / (double) CLOCKS_PER_SEC;
        
        cout << "Runtime: " << runtime << endl;
        // check this runtime on the server
        
        // add results to the output file
        f_output << "[";
        for (int y = 0; y < change.size()-2; y++)
        {
            f_output << change[y] << ", ";
        }
        
        f_output << change[change.size()-2] << "]" << endl;
        f_output << change[change.size()-1] << endl;
        change.clear();
    
    }
    
    f_output.close();
    problems.close();
    
    return 0;
}


//from Tim's work
// Parse the string into vectors
vector< vector <int> > parse_input(vector<string> input_strings) {
  // This will store the parsed input arrays
  vector< vector<int> > input_arrays;

  // This stores each integer to parse the file input
  string tmp_string;

  // This stores the input sum
  int tmp_int;

  // This stores each problem set, each of which we will put in "input_arrays"
  vector<int> tmp_vector;

  // Iterators
  int u = 0;
  int v = 0;

  for(u = 0; u < input_strings.size(); u++) 
  {
    for(v = 0; v < input_strings[u].length(); v++) 
    {
      if((input_strings[u][v] == '[') || (input_strings[u][v] == ' ')) 
      {
        // Do nothing
      } 
      else if((isdigit(input_strings[u][v])) || (input_strings[u][v] == '-')) 
      {
        tmp_string.push_back(input_strings[u][v]);
      } 
      else if((input_strings[u][v] == ',') || (input_strings[u][v] == ']')) 
      {
        tmp_vector.push_back(atoi(tmp_string.c_str()));
        tmp_string = "";
      }

      if( (v == (input_strings[u].length() - 1)) && (input_strings[u][0] != '['))
      {
        tmp_vector.push_back(atoi(tmp_string.c_str()));
        tmp_string = "";
      }
    }

    input_arrays.push_back(tmp_vector);
    tmp_vector.clear();
    tmp_string = "";
  }

  return input_arrays;
}