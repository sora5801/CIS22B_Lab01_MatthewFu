/*CIS22B
Lab 01: Search for a word from a text file.
Name: Matthew Fu
Date: 10/03/18

Program description. This program takes in an input text file of the user's location and name, and 
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
put them into a string array. If fails, exit the program.
Prompt user for location and name of the output file.
Sort the array using a selection sort algorithm.
Display the sorted array.
Enter loop that asks user to search for a word.
If the word is found, returns the index location.
If the word is not found, then return nothing.
Asks user if they want to search for another word.
If the user enters 'y' or 'Y', the loop will run again.
If the user enters anything else, the program will end.
Display all user interaction and the sorted array into an output file.
*/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
using namespace std;

const int NUM_NAMES = 1024; // Global variable for size of string array

//Function protoypes
void selectionSort(string[], int);
int binarySearch(string[], int, string);
void showArray(const string[], int, ofstream &);

int main()
{
   //The file input name and location are concatenated.
   string fileLocationForInput, fileNameForInput;

   //A word count variable. 
   int count = 0;
   //This line is for user interactivity.

   cout << "This program will take in a text file from a directory of your choice and\n" <<
      "output to a directory of your choice. Please input a file that has less than or equal to 1024 words and make sure \n" <<
      "that the file's path and name are entered correctly. \n" <<
      "Otherwise, the program will close." << endl << endl;

   //Prompt user for location and name of the input file
   cout << "What is the location of the text file? Please make sure it is the correct path. e.g. 'C:/Users/MATTHEW/source/repos'" << endl;
   cin >> fileLocationForInput;
   cout << "What is the name of the file? Please be sure to enter a .txt at the end of the file name. e.g. 'File.txt'" << endl;
   cin >> fileNameForInput;

   //Declare a string array to hold all the texts.
   string myArray[NUM_NAMES];

   //The file input name and location are concatenated.
   string fileNameAndLocationForInput = fileLocationForInput + "/" + fileNameForInput;

   ifstream myfile(fileNameAndLocationForInput);

   //Check if the file is opened or not
   if (myfile.is_open())
   {
      //a counter variable
      int i = 0;
      while (!myfile.eof())
      {
       
            //Store characters into the array
            myfile >> myArray[i];

            //Discard single characters.
            if (!myfile.eof() && myArray[i].size() == 1)
               --i;

            //If the last character is a single character, this will discard it
            if (myfile.eof() && myArray[i].size() == 1)
            {
               myArray[i] = "";
               i = NUM_NAMES;
            }
            i++;
            count++;
         }
   }
   else //Program will close if unable to find the file
   {
      cout << "Was unable to open the file" << endl;
      getchar();
      return -1;
   }

   if(count > NUM_NAMES) //Program will close if the file is too large
   {
      cout << "Sorry, the file is too large" << endl;
      getchar();
      return -1;
   }

   //Declare string variables for output file name and location
   string fileNameAndLocationForOutput, fileLocationForOutput, fileNameForOutput;

   cout << "Where do you want to put the output file? Please make sure it is the correct path. e.g. 'C:/Users/MATTHEW/source/repos'" << endl;
   cin >> fileLocationForOutput; 
   cout << "What is the name of the output file? Please be sure to enter a .txt at the end of the file name. e.g. 'File.txt'" << endl;
   cin >> fileNameForOutput;

   //The file output name and location are concatenated 
   fileNameAndLocationForOutput = fileLocationForOutput + "/" + fileNameForOutput;

   //Declare the output file
   ofstream thisfile;
   thisfile.open(fileNameAndLocationForOutput);

   //Sort the array using selection sort
   selectionSort(myArray, NUM_NAMES);

   //Displays sorted array in the output file
   showArray(myArray, NUM_NAMES, thisfile);

   //All users interaction will go to a text file
   thisfile << "\n\nThis program will take in a text file from a directory of your choice and\n" <<
      "output to a directory of your choice. Please input a file that has less than or equal to 1024 words and make sure \n" <<
      "that the file's path and name are entered correctly. \n" <<
      "Otherwise, the program will close." << endl << endl;
   thisfile << "What is the location of the text file? Please make sure it is the correct path. e.g. 'C:/Users/MATTHEW/source/repos'" << endl;
   thisfile << fileLocationForInput <<endl;
   thisfile << "What is the name of the file? Please be sure to enter a .txt at the end of the file name. e.g. 'File.txt'" << endl;
   thisfile << fileNameForInput << endl;
   thisfile << "Where do you want to put the output file? Please make sure it is the correct path. e.g. 'C:/Users/MATTHEW/source/repos'" << endl;
   thisfile << fileLocationForOutput <<endl;
   thisfile << "What is the name of the output file? Please be sure to enter a .txt at the end of the file name. e.g. 'File.txt'" << endl;
   thisfile << fileNameForOutput;

   char again; //Char variable to ask if the user wants to run the loop multiple times

   string wordSearch; //string variable for the word that is to be searched
   
   //Start of the the do-while loop
   do
   {
      cout << "What word would you like to search for?" << endl;
      thisfile << "\n" << "What word would you like to search for?" << endl;
         cin >> wordSearch;
         thisfile << wordSearch;
     
      //Use of the binary search function
      binarySearch(myArray, NUM_NAMES, wordSearch);

      //If the word is not found, then display it
      if (binarySearch(myArray, NUM_NAMES, wordSearch) == -1) {
         cout << "The word is not found" << endl;
         thisfile << "\n" << "The word is not found" << endl;
      }
      else {
         cout << "The word has been found and it is located in index " << binarySearch(myArray, NUM_NAMES, wordSearch) << endl;
         thisfile << "\n" << "The word has been found and it is located in index " << binarySearch(myArray, NUM_NAMES, wordSearch) << endl;
      }

      //Prompts the user if they would like to run the loop again.
      cout << "Would you like to run the program again? (Y/N): " << endl;
      thisfile << "Would you like to run the program again? (Y/N): " << endl;
      cin >> again;
      thisfile << again;
   } while (again == 'y' || again == 'Y');
   
   return 0;
}

//A standard selection sort algorithm adjusted for strings
/*In pseudocode:
For startScan is set to each subscript in array from 0 through the next-to-last subscript
   Set index variable to startScan.
   Set minIndex variable to startScan.
   set MinValue variable to array[startScan].
   
   For index is set to each subscript in array from (startScan +1)
            through the last subscript
           If array[index[ is less than minValue
               Set minValue to array[index].
               Set minINdex to index.
           End if.
        End For.
        Set array[minIndex] to array[startScan].
        Set array[startScan] to minValue.
End For.*/
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

//This function shows the array 
void showArray(const string array[], int size, ofstream &thisfile)
{
   for (int count = 0; count < size; count++){
      if (array[count] != "") {
         thisfile << array[count] << " ";
      }
    }
    thisfile << endl;
    }

//A standard binary search algorithm
/*In pseudocode
Set first index to 0.
Set last index to the last subscript in the array.
Set found to false.
Set position to -1.
While found is not true and first is less than oe equal to last
   Set middle to the subscript halfway between array[first[]
   and array[last].
   If array[middle] equals the desired value
      Set found to true.
      Set position to middle.
      Else If array[middle] is greater than the desired value
         Set last to middle -1. 
      Else
         Set first to middle + 1.
      End If.
End While.
Return position*/
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