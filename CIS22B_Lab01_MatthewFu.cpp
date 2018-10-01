/*CIS22B
Lab 01: Search for a word from a text file.
Name: Matthew Fu

Program description. This program takes in an input file of the user's location and name, and 
stores all of its content into a string array of size 1024, the maximum number of strings allowed. 
It then sorts the array with selection sort, display the array, and then enters a do-while loop,
asking for the user to search for a word. If the word is found, it will display the index of the
word. The loop will run for as many times as the user wants. When the user is done, the program will
close, and all of the user's interaction will be put in an output file of the user's location 
and name.

Pseudocode: 
Prompt user for location and name of the input file.
Receive user input for the location and name of the input file. 
Opens the file. 
If the file successfully opens, take all 2-or-more character words and 
put them into a string array. If fails, exit the program
Prompt user for location and name of the output file.

*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int NUM_NAMES = 1024; // Global variable for size of string array

//Function protoypes
void selectionSort(string[], int);
int binarySearch(string[], int, string);
void showArray(const string[], int, ofstream &);

int main()
{
   //First, the location is asked for 
   string fileLocationForInput, fileNameForInput;
   cout << "What is the location of the file?" << endl;
   cin >> fileLocationForInput;
   cout << "What is the name of the file?" << endl;
   cin >> fileNameForInput;

   string myArray[NUM_NAMES];
   string fileNameAndLocationForInput = fileLocationForInput + "/" + fileNameForInput;

   ifstream myfile(fileNameAndLocationForInput);

   if (myfile.is_open())
   {
      
      for (int i = 0; i < NUM_NAMES; ++i) {
         
         myfile >> myArray[i];

         if (!myfile.eof() && myArray[i].size() == 1)
            i--;
         
         if (myfile.eof() && myArray[i].size() == 1)
         {
            myArray[i] = "";

            i = NUM_NAMES;
         }
      }
   }
   else //Program will close if unable to find the file
   {
      cout << "Was unable to open the file" << endl;
      return -1;
   }

   string fileNameAndLocationForOutput, fileLocationForOutput, fileNameForOutput;
   cout << "Where do you want to put the output file?" << endl;
   cin >> fileLocationForOutput; 
   cout << "What is the name of the output file?" << endl;
   cin >> fileNameForOutput;

   fileNameAndLocationForOutput = fileLocationForOutput + "/" + fileNameForOutput;

   ofstream thisfile;
   thisfile.open(fileNameAndLocationForOutput);

   char again; //Hold y to repeat

   string wordSearch; //string variable for 
   //Show array
   cout << "The unsorted values are\n";
   thisfile << "The unsorted values are\n";
   showArray(myArray, NUM_NAMES, thisfile);

   //Sort array
   selectionSort(myArray, NUM_NAMES);

   //Display sorted array
   cout << "The sorted values are\n";
   thisfile << "The sorted values are\n";
   showArray(myArray, NUM_NAMES, thisfile);

   do
   {
      cout << "What word would you like to search for?" << endl;
      thisfile << "\n" << "What word would you like to search for?" << endl;
         cin >> wordSearch;
         thisfile << wordSearch;
      
      binarySearch(myArray, NUM_NAMES, wordSearch);
      if (binarySearch(myArray, NUM_NAMES, wordSearch) == -1) {
         cout << "The word is not found" << endl;
         thisfile << "\n" << "The word is not found" << endl;
      }
      else {
         cout << "The word has been found and it is located in index " << binarySearch(myArray, NUM_NAMES, wordSearch) << endl;
         thisfile << "\n" << "The word has been found and it is located in index " << binarySearch(myArray, NUM_NAMES, wordSearch) << endl;
      }

      //Run program again?
      cout << "Would you like to run the program again? (Y/N): " << endl;
      thisfile << "Would you like to run the program again? (Y/N): ";
      cin >> again;
      thisfile << again;
   } while (again == 'y' || again == 'Y');
   
   return 0;
}

void selectionSort(string array[], int NUM_NAMES)
{
   int startScan, minIndex;
   string minValue;

   for (startScan = 0; startScan < (NUM_NAMES - 1); startScan++)
   {
      minIndex = startScan;
      minValue = array[startScan];
      for (int index = startScan + 1; index < NUM_NAMES; index++)
      {
         
         if (array[index] < minValue)
         {
            minValue = array[index];
            minIndex = index;
         }
      }
      array[minIndex] = array[startScan];
      array[startScan] = minValue;
   }
}

void showArray(const string array[], int size, ofstream &thisfile)
{
   for (int count = 0; count < size; count++){
      if (array[count] != "") {
         cout << array[count] << " ";
         thisfile << array[count] << " ";
      }
    }
    cout << endl;
    thisfile << endl;
    }

int binarySearch(string names[], int size, string value)
{
   int first = 0,             // First array element
      last = size - 1,       // Last array element
      middle,                // Mid point of search
      position = -1;         // Position of search value
   bool found = false;        // Flag

   while (!found && first <= last)
   {
      middle = (first + last) / 2;     // Calculate mid point
      if (names[middle] == value)      // If value is found at mid
      {
         found = true;
         position = middle;
      }
      else if (names[middle] > value)  // If value is in lower half
         last = middle - 1;
      else
         first = middle + 1;           // If value is in upper half
   }
   return position;
}