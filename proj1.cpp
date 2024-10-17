/*
* Name: proj1.cpp
* Author: Daniel Finney
* Section: 45
* Description: Implement a fortune wheel program similar to Wheel of Fortune.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

// constants
const string DATA_FILE_NAME = "proj1_data.txt";
const int NUM_LINES = 48;
const int NUM_CATEGORIES = 24;
const int NUM_WORDS = 24;

// function prototypes
void loadFile(string[], string[]);
string getCatgAndWord(string[], string[]);
string printPuzzle(string);
int checkUserGuess(string, char);
string revealGuessedLetter(string, string, char);

// main function
int main(){
    

    string puzzleCategories[NUM_CATEGORIES] = {""};
    string puzzleWords[NUM_WORDS] = {""};

    // loads 2 arrays for categories and words respectively
    loadFile(puzzleCategories, puzzleWords);

    // prints welcome lines
    cout << "Welcome to UMBC Fortune Wheel!\n"
         << "24 puzzles loaded." << endl;
    
    // prints random category
    string word1 = "";
    word1 = getCatgAndWord(puzzleCategories, puzzleWords);

    // prints word in underscore format
    string newString = printPuzzle(word1);
    cout << newString << endl;

    // boolean array to keep track of guessed letters
    bool guessedLetters[26] = {false};

    // loops until full word is guessed and program is complete 
    while (newString != word1){

        // asks user to guess letter and checks if answer is in puzzle
        cout << "What letter would you like to guess?" << endl;
        char userGuess = '_';
        cin >> userGuess;
        char newUserGuess = toupper(userGuess);

        // check if the user has already guessed this letter
        if (guessedLetters[newUserGuess - 'A']) {
        
            cout << newUserGuess << " already guessed." << endl;
        
        }

        // mark the new guess as guessed
        guessedLetters[newUserGuess - 'A'] = true;

        // if guess in puzzle, the number of times the guess was found in the word is returned
        int numGuess = checkUserGuess(word1, newUserGuess);
        if (numGuess > 0) {
            
            cout << numGuess << " " << newUserGuess << " found in the puzzle." << endl;
        
        }
        else {
            
            cout << numGuess << " " << newUserGuess << " found in the puzzle." << endl;

        }

        // updates newString to replace underscores with newUserGuess
        newString = revealGuessedLetter(word1, newString, newUserGuess);
        cout << newString << endl;

    }

    cout << "You won!" << endl;

}

/**************************************************************************************
** Precondition: 
** -> puzzleCategory and puzzleWords are previously defined empty string arrays
** 
** Postcondition: 
** -> string arrays puzzleCategory and puzzleWords loaded with text from DATA_FILE_NAME
**************************************************************************************/
void loadFile(string puzzleCategory[], string puzzleWords[]){

    ifstream file(DATA_FILE_NAME);
    string line = "";
    int lineNum = 1;

    if (file.is_open()) { // checks if the file is open
        int j = 0;
        int m = 0;
        while (getline(file, line) && lineNum <= NUM_LINES) { // reads each line from the file
            if (lineNum % 2 == 0) {
                puzzleWords[j] = line;// adds even-numbered lines to evenLines 
                j++;
            } else {
                puzzleCategory[m] = line;// adds odd-numbered lines to oddLines 
                m++;
            }
            lineNum++;
        }
        file.close(); // closes the file
    } else {
        cerr << "Unable to open file!" << endl; // outputs error message if file cannot be opened
    }
    return;

}

/******************************************************************************************************
** Precondition:
** -> string arrays puzzleCategory and puzzleWord contain the appropriate data
**
** Postcondition:
** -> category is extracted at random index from string array puzzleCategory and displayed
** -> string word is extracted from string array puzzleWord at random index and returned back to main()
******************************************************************************************************/
string getCatgAndWord(string puzzleCategory[], string puzzleWord[]){

    srand((unsigned)time(0));
    int index = rand() % NUM_CATEGORIES;
    cout << "Category is: " << puzzleCategory[index] << endl;
    string word = puzzleWord[index];
    return word;

}       

/******************************************************************************
** Precondition:
** -> string contains appropriate data
**
** Postcondition:
** -> string word1 is returned to main with all letters replaced by underscores
******************************************************************************/
string printPuzzle(string word1){

    int newWord = word1.size();
    string newString = "";
    for (int i = 0; i < newWord; i++){

        if ((word1[i] >= 'A' && word1[i] <= 'Z') || (word1[i] >= 'a' && word1[i] <= 'z')){

            newString += '_';
        } 
        else {

            newString += word1[i];

        }
    }

    return newString;

}

/******************************************************************************************************
** Precondition:
** -> string puzzleWord and char newUserGuess contain the appropriate data
**
** Postcondition:
** -> checks if char newUserGuess is in string puzzleWord
** -> returns number of times the char newUserGuess appears in the string puzzleWord
******************************************************************************************************/
int checkUserGuess(string puzzleWord, char newUserGuess) {
    int count = 0;
    int wordLength = puzzleWord.length();
    for (int i = 0; i < wordLength; i++) {
        char letter = puzzleWord[i];
        if (letter == newUserGuess) {
            count++;
        }
    }

    return count;
    
}

/******************************************************************************************************
** Precondition:
** -> strings puzzleWord and underscoreWorld and char userGuess contain the appropriate data
**
** Postcondition:
** -> replaces underscores in string underscoreWord where userGuess appears
** -> returns updated word through string updatedWord
******************************************************************************************************/
string revealGuessedLetter(string puzzleWord, string underscoreWord, char userGuess) {
    string updatedWord = underscoreWord;
    int wordLength = puzzleWord.length();
    for (int i = 0; i < wordLength; i++) {

        if (puzzleWord[i] == userGuess) {
 
            updatedWord[i] = userGuess;
 
        }

    }

    return updatedWord;

}