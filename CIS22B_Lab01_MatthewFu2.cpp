#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int NUM_NAMES = 20;

//Function protoypes
void selectionSort(string[], int);
int binarySearch(string[], int, string);
void showArray(const string[], int);

int main()
{
   string line;
   cout << "Where is the file to input?" << endl;
   cin >> line;

   ifstream myfile(line);
   if (myfile.is_open())
   {
      while (!myfile.eof())
      {
         getline(myfile, line);
      }
   }
   else
   {
      cout << "Was unable to open the file" << endl;
   }


   string names[NUM_NAMES] = { "Collins, Bill", "Smith, Bart", "Allet, Jim",
      "Griffin, Jim", "Stamey, Marty", "Rose, Geri",
      "Taylor, Terri", "Johnson, Jill", "johnson, jill", "58",
      "Aliison, Jeff", "Weaver, Jim", "Pore, Bob",
      "Rutherford, Greg", "Javens, Renee",
      "Harrison, Rose", "Setzer, Cathy",
      "Pike, Gordon", "Holland, Beth" };

   char again; //Hold y to repeat

   do
   {
      //Show array
      cout << "The unsorted values are\n";
      showArray(names, NUM_NAMES);

      //Sort array
      selectionSort(names, NUM_NAMES);

      //Display sorted array
      cout << "The sorted values are\n";
      showArray(names, NUM_NAMES);

      //Run program again?
      cout << "Would you like to run the program again? (Y/N): ";
      cin >> again;
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

void showArray(const string array[], int size)
 {
    for (int count = 0; count < size; count++)
        cout << array[count] << " ";
    cout << endl;
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