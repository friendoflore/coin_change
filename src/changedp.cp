#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string> 
#include <ctime> 
#include <limits>

using namespace std;

/** Function: print_array *****************************************************
 ** Description: This function prints a vector's contents to the filestream 
 **  passed in. "print_array" is the vector we print from. "count" is the 
 **  coin change count. "* outputFile" is the
 **  address of an open ofstream to which the array will be printed.
 **
 **                       [i, j, k, ..., t]
 **                       count 
 **
 *****************************************************************************/
void print_array(vector<int> print_array, int count, ofstream * outputFile) 
{
  // Print each array to the file, formatted
  *outputFile << "[";
  for(int i = 0; i < print_array.size(); i++) {

    // Print each value
    *outputFile << print_array[i];

    if(i != (print_array.size() - 1))
      *outputFile << ", ";
  }

  *outputFile << "]" << endl;
  
  *outputFile << count << endl;
}


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
	vector< vector<int> > solutions;
	vector<int> retValue; 

	// set solutions[0]
	vector<int> zeroSolution(V.size(), 0);
	solutions.push_back(zeroSolution);

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
			}

			j++;
		}

		// solutions[i] = min from above while loop 
		solutions.push_back(retValue);
	}

	change = solutions[A];

}

int main(int argc, char *argv[]) {
	
	if(argc != 2)
	{
		cout << "Usage: " << argv[0] << "[filename].txt" << endl; 
		return 1; 
	}
	
	// used for timing 
	clock_t t1, t2; 
	double runtime; 
	
    // This stores the problem arrays that we will use to do calculations
    vector< vector<int> > input_arrays;
  
    // This stores the all problems lines of file input
    vector<string> problem_set;

    // This stores each string as we read it in from file
    string input_string;
  
    // Open problems text
    ifstream problems (argv[1], ifstream::in);

    while(problems.good()) {
      getline(problems, input_string);
      if(input_string.length() != 0) {
        problem_set.push_back(input_string);
      }
    }

	problems.close();
	
    input_arrays = parse_input(problem_set);
	
	// get filename 
	string fileName = argv[1];
	int index = fileName.find_last_of(".");
	
	string outputFileName = fileName.substr(0, index) + "change.txt"; 
	
	ofstream fileOutput; 
	fileOutput.open(outputFileName.c_str(), ofstream::out);
	
    // Use "input_arrays" to do the calculations for each of the algorithms
    // For i, if i is even, input_arrays[i] == set of coins
    //        if i is odd, input_arrays[i] == sum of coins
	for (int i = 0; i < input_arrays.size(); i++)
	{
		int sum = i + 1;
		vector<int> change(input_arrays[i].size(),0);
		
		t1 = clock(); 
		
		changedp(input_arrays[i], input_arrays[sum][0], change); 
		
		t2 = clock(); 
		runtime = (t2 - t1) / (double) CLOCKS_PER_SEC; 
		
		cout << "The algorithm for change amount " << input_arrays[sum][0] << " ran in "; 
		cout << runtime << " seconds." << endl << endl;
		
		int count = vectContSum(change); 
		
		print_array(change, count, &fileOutput);
		
		change.clear();
		
		i++; // skips forward another i
	}
	
	fileOutput.close(); 
  
  return 0;
}