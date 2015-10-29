#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

/** Function: print_array *****************************************************
 ** Description: This function prints a vector's contents to the filestream 
 **   passed in. "print_array" is the vector we print from. "low_idx" and 
 **   "high_idx" is the index range this function prints. "* alg_file" is the
 **   address of an open ofstream to which the array will be printed.
 ** Parameters: vector<int> print_array, int low_idx, int high_idx,
 **   ofstream * alg_file
 ** Preconditions: The ofstream argument must be open when passed in.
 ** Postconditions: This function prints the range of the array passed in to
 **   the open filestream passed in, formatted by the form:
 **
 **                       [i, j, k, ..., t]
 **
 *****************************************************************************/
void print_array(vector<int> print_array, int low_idx, 
  int high_idx, ofstream * alg_file) {

  // Print each array to the file, formatted
  *alg_file << "[";
  for(int i = low_idx; i < high_idx; i++) {

    // Print each value
    *alg_file << print_array[i];

    if(i != (high_idx - 1))
      *alg_file << ", ";
  }

  *alg_file << "]" << endl;
}

// Algorithm 1
// Brute Force or Divide and Conquer Algorithm
void algorithm_1(vector< vector <int> > input_arrays) {

  // We will put Algorithm 1's results in the file below.
  ofstream f_output;
  f_output.open("Coin1change.txt");
  f_output << endl << "Beginning algorithm 1" << endl << endl; 

  // These are used to store the runtime of the algorithm
  clock_t t1, t2;
  double runtime;
  
  // For each problem from the set of problems
  for(int u = 0; u < input_arrays.size(); u++) {
    
    // "Start" the clock at the beginning of the algorithm
    t1 = clock();

    // This is Algorithm 1


    
    // "Stop" the clock at the end of the algorithm
    t2 = clock();
    runtime = (t2 - t1) / (double) CLOCKS_PER_SEC;

  }

  f_output.close();
}

// Algorithm 2
// Greedy Algorithm
void algorithm_2(vector< vector<int> > input_arrays) {

  // We will put Algorithm 2's results in the file below.
  ofstream f_output;
  f_output.open("Coin1change.txt", ios::out | ios::app);
  f_output << endl << "Beginning algorithm 2" << endl << endl; 

  // These are used to store the runtime of the algorithm
  clock_t t1, t2;
  double runtime;
  
  // For each problem from the set of problems
  for(int u = 0; u < input_arrays.size(); u++) {
  
    // "Start" the clock at the beginning of the algorithm
    t1 = clock();
    
    // This is Algorithm 2

    

    // "Stop" the clock at the end of the algorithm
    t2 = clock();
    runtime = (t2 - t1) / (double) CLOCKS_PER_SEC;
    
  }
  
  f_output.close();
}

// Algorithm 3
// Dynamic Programming
void algorithm_3(vector< vector<int> > input_arrays) {
  // We will put Algorithm 3's results in the file below.
  ofstream f_output;
  f_output.open("Coin1change.txt", ios::out | ios::app);
  f_output  << endl << "Beginning algorithm 3" << endl << endl; 

  // These are used to store the runtime of the algorithm
  clock_t t1, t2;
  double runtime; 

  for(int u = 0; u < input_arrays.size(); u++) {

    int low = 0;
    int high = input_arrays[u].size() - 1;
    int max = -1;

    if(high != -1) 
    {
      // "Start" the clock at the beginning of the algorithm
      t1 = clock();

      
      // This is Algorithm 3


      // "Stop" the clock at the end of the algorithm
      t2 = clock();
      
      runtime = (t2 - t1) / (double) CLOCKS_PER_SEC;
    }
  }

  f_output.close();
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

// generate the random input for the evaluation 
vector <vector<int> > generateRandInput(int inputs[], int size)
{
  vector< vector<int> > randNumbers; 
  vector<int> temp;
  
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < inputs[i]; j++)
    {
      temp.push_back(rand() % 199 - 100); 
    }
    
    randNumbers.push_back(temp);
    temp.clear(); 
  }
  
  return randNumbers;
}

int main(int argc, char *argv[]) {
  // seed random generator
  srand(time(0));

  // This stores the problem arrays that we will use to do calculations
  vector< vector<int> > input_arrays;
  
  // This stores the all problems lines of file input
  vector<string> problem_set;

  // This stores each string as we read it in from file
  string input_string;

  // if there is a command line argument use evaluation mode where test numbers are randomly generated
  if(argc > 1)
  {
    cout << "Evaluation mode: Generating random input strings of varying sizes." << endl; 
  

    // Modify the input to match the coin problems
    // Modify to accept 1 line of coin size and 1 line of total change amount
    int alg1inputs[] = { 50, 100, 150, 200, 250, 300, 350, 400, 450, 500 };
    int alg2inputs[] = { 50, 100, 150, 200, 250, 300, 350, 400, 450, 500 };
    int alg3inputs[] = { 50, 100, 150, 200, 250, 300, 350, 400, 450, 500 };

    // input_arrays for algorithm 1 
    input_arrays = generateRandInput(alg1inputs, 10); 
    
    // Call algorithm 1
    algorithm_1(input_arrays);
    
    // clear input arrays 
    for (int i = 0; i < input_arrays.size(); i++)
    {
      input_arrays[i].clear(); 
    }
    
    input_arrays.clear();
    
    // input arrays for algorithm 2
    input_arrays = generateRandInput(alg2inputs, 10); 

    // Call algorithm 2
    algorithm_2(input_arrays);
    
    // clear input arrays 
    for (int i = 0; i < input_arrays.size(); i++)
    {
      input_arrays[i].clear(); 
    }
    
    input_arrays.clear();
    
    // input arrays for algorithm 3
    input_arrays = generateRandInput(alg3inputs, 10);
    
    // Call algorithm 3
    algorithm_3(input_arrays);
    
  }

  // else use provided test problems file 
  else
  {
    // Open problems text
    ifstream problems ("Coin1.txt", ifstream::in);

    while(problems.good()) {
      getline(problems, input_string);
      if(input_string.length() != 0) {
        problem_set.push_back(input_string);
      }
    }
    
    input_arrays = parse_input(problem_set);


    // Use "input_arrays" to do the calculations for each of the algorithms
    // For i, if i is even, input_arrays[i] == set of coins
    //        if i is odd, input_arrays[i] == sum of coins

    // Call algorithm 1
    algorithm_1(input_arrays);

    // Call algorithm 2
    algorithm_2(input_arrays);

    // Call algorithm 3
    algorithm_3(input_arrays);

    problems.close();
  }

  return 0;
}