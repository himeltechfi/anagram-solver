//***********************************************************************************************
// Anagram Solver Challenge
// This program including all the code is my own work and has been tested fully
// **********************************************************************************************

#include <algorithm> // Required for functions like std::sort and std::transform
#include <cctype>    // Required for character handling functions like tolower()
#include <chrono> // Modern C++ library for high-resolution timing, provides precise duration measurements
#include <ctime>  // Old C-style time library (used in original code)
#include <fstream> // Required for file input/output operations (e.g., reading a file)
#include <iostream>
#include <map> // Required for using the map data structure to count character frequencies
#include <string>
#include <vector> // Required for using the vector data structure

// These preprocessor directives create fixed identifiers for the dictionary
// file names. This makes it easy to change the filenames in one place if
// needed.
#define cDATAFILE "Words_100.csv"
#define cDATAFILE1 "Words_1K.csv"
#define cDATAFILE2 "Words_75K.csv"

using namespace std;

// Global variables are declared here so they can be accessed and modified by
// any function in the program. This is done for simplicity in this small
// application.

// This vector is our main dictionary. It will hold all the words read from the
// chosen file.
vector<string> dictionary;

// This string variable stores the name of the currently loaded dictionary file.
string currentDictionaryFile;

// --- Function Prototypes ---
// Prototypes declare functions before they are used, allowing them to be called
// from other parts of the code (like the 'menu' or 'main' functions).

void ReadFile(const string &filename);
string GetWord();
void FindAnagrams(const string &originalString);
void LargestWordAvailable(const string &originalString);
void FindAll3LetterAnagrams(const string &originalString);
void FindAll5LetterAnagrams(const string &originalString);
void SelectDictionary();
void QuitNow(bool &quitFlag);
void menu();

// This function reads words from a specified file and stores them into the
// global dictionary vector. It performs data cleaning (lowercase conversion and
// whitespace removal) to ensure consistency.
void ReadFile(const string &filename) {
  dictionary.clear(); // Clears any words from a previous dictionary file.
  ifstream dbFile;
  dbFile.open(filename); // Attempts to open the specified file for reading.

  if (!dbFile.is_open()) {
    // This check ensures the file was opened successfully. If not, it prints an
    // error message.
    cout << "Error: Could not open the file " << filename << endl;
    return;
  }

  string currentWord;
  while (getline(dbFile, currentWord)) {
    // Reads the file line by line into the 'currentWord' string.

    // The remove_if and erase combination removes any trailing whitespace from
    // the line.
    currentWord.erase(
        remove_if(currentWord.begin(), currentWord.end(), ::isspace),
        currentWord.end());

    // This function converts the entire word to lowercase, making the search
    // case-insensitive.
    transform(currentWord.begin(), currentWord.end(), currentWord.begin(),
              ::tolower);

    // The cleaned word is added to the end of our global dictionary vector.
    dictionary.push_back(currentWord);
  }
  dbFile.close(); // It's important to close the file to release the resource.
  currentDictionaryFile = filename;
  cout << "\nLoaded " << dictionary.size() << " words from " << filename << "."
       << endl;
}

// This function gets a word or phrase from the user, cleans it, and returns it.
string GetWord() {
  string localString;
  cout << "\nPlease enter a word/phrase: ";
  cin.ignore(); // This clears the input buffer, preventing a bug where
                // getline() is skipped.
  getline(cin, localString); // Reads the entire line of input from the user,
                             // including spaces.

  // Remove spaces and convert to lowercase for proper anagram checking.
  localString.erase(
      remove_if(localString.begin(), localString.end(), ::isspace),
      localString.end());
  transform(localString.begin(), localString.end(), localString.begin(),
            ::tolower);

  cout << "You have entered: " << localString << " as your current word."
       << endl
       << endl;
  return localString; // Returns the cleaned string to the calling function.
}

// Helper function to create a frequency map of characters in a string.
// A frequency map (std::map) is used to count how many times each character
// appears. This is a much more efficient way to check for anagrams and
// sub-anagrams than sorting strings.
map<char, int> createFrequencyMap(const string &s) {
  map<char, int> freqMap;
  for (char c : s) {
    freqMap[c]++;
  }
  return freqMap;
}

// This function finds and prints all anagrams of the given string from the
// dictionary.
void FindAnagrams(const string &originalString) {
  if (dictionary.empty()) {
    cout << "Error: Dictionary not loaded. Please select option 1 first."
         << endl;
    return;
  }

  // Create a frequency map for the original input string.
  map<char, int> originalFreqMap = createFrequencyMap(originalString);

  cout << "\nWords found from the letters of '" << originalString
       << "':" << endl;
  bool found = false;
  for (const string &word : dictionary) {
    // The condition `word.length() <= originalString.length()` is key for
    // finding "sub-anagrams" (words that can be formed from a subset of the
    // letters).
    if (word.length() <= originalString.length()) {
      map<char, int> wordFreqMap = createFrequencyMap(word);
      bool canFormWord = true;

      // This loop checks if the character counts in the dictionary word are
      // available in the input word's frequency map.
      for (auto const &[key, val] : wordFreqMap) {
        if (originalFreqMap.find(key) == originalFreqMap.end() ||
            originalFreqMap[key] < val) {
          canFormWord = false; // The word cannot be formed.
          break;
        }
      }

      if (canFormWord) {
        cout << word << endl;
        found = true;
      }
    }
  }

  if (!found) {
    cout << "No words found." << endl;
  }
}

// This function finds the longest word that can be formed using the letters of
// the given string.
void LargestWordAvailable(const string &originalString) {
  if (dictionary.empty()) {
    cout << "Error: Dictionary not loaded. Please select option 1 first."
         << endl;
    return;
  }

  map<char, int> originalFreqMap = createFrequencyMap(originalString);
  string largestWord = "";

  for (const string &word : dictionary) {
    // This condition checks if the current word is longer than the longest word
    // found so far.
    if (word.length() > largestWord.length() &&
        word.length() <= originalString.length()) {
      map<char, int> wordFreqMap = createFrequencyMap(word);
      bool canFormWord = true;

      for (auto const &[key, val] : wordFreqMap) {
        if (originalFreqMap.find(key) == originalFreqMap.end() ||
            originalFreqMap[key] < val) {
          canFormWord = false;
          break;
        }
      }

      if (canFormWord) {
        largestWord = word;
      }
    }
  }

  if (largestWord.empty()) {
    cout << "No words found that can be formed from the letters of '"
         << originalString << "'." << endl;
  } else {
    cout << "\nThe largest word found is: " << largestWord << endl;
  }
}

// This function finds all 3-letter words that can be formed using the letters
// of the given string.
void FindAll3LetterAnagrams(const string &originalString) {
  if (dictionary.empty()) {
    cout << "Error: Dictionary not loaded. Please select option 1 first."
         << endl;
    return;
  }

  map<char, int> originalFreqMap = createFrequencyMap(originalString);

  cout << "\nAll 3-letter words found from the letters of '" << originalString
       << "':" << endl;
  bool found = false;
  for (const string &word : dictionary) {
    if (word.length() == 3) {
      map<char, int> wordFreqMap = createFrequencyMap(word);
      bool canFormWord = true;
      for (auto const &[key, val] : wordFreqMap) {
        if (originalFreqMap.find(key) == originalFreqMap.end() ||
            originalFreqMap[key] < val) {
          canFormWord = false;
          break;
        }
      }
      if (canFormWord) {
        cout << word << endl;
        found = true;
      }
    }
  }
  if (!found) {
    cout << "No 3-letter words found." << endl;
  }
}

// This function finds all 5-letter words that can be formed using the letters
// of the given string.
void FindAll5LetterAnagrams(const string &originalString) {
  if (dictionary.empty()) {
    cout << "Error: Dictionary not loaded. Please select option 1 first."
         << endl;
    return;
  }

  map<char, int> originalFreqMap = createFrequencyMap(originalString);

  cout << "\nAll 5-letter words found from the letters of '" << originalString
       << "':" << endl;
  bool found = false;
  for (const string &word : dictionary) {
    if (word.length() == 5) {
      map<char, int> wordFreqMap = createFrequencyMap(word);
      bool canFormWord = true;
      for (auto const &[key, val] : wordFreqMap) {
        if (originalFreqMap.find(key) == originalFreqMap.end() ||
            originalFreqMap[key] < val) {
          canFormWord = false;
          break;
        }
      }
      if (canFormWord) {
        cout << word << endl;
        found = true;
      }
    }
  }
  if (!found) {
    cout << "No 5-letter words found." << endl;
  }
}

// This function handles the selection of a new dictionary file.
void SelectDictionary() {
  cout << "\n--- Select a Dictionary ---" << endl;
  cout << "\t1. " << cDATAFILE << " ("
       << "100 words)" << endl;
  cout << "\t2. " << cDATAFILE1 << " ("
       << "1K words)" << endl;
  cout << "\t3. " << cDATAFILE2 << " ("
       << "75K words)" << endl;
  cout << "Enter a number (1-3) to select a file: ";

  char choice;
  cin >> choice;

  switch (choice) {
  case '1':
    ReadFile(cDATAFILE);
    break;
  case '2':
    ReadFile(cDATAFILE1);
    break;
  case '3':
    ReadFile(cDATAFILE2);
    break;
  default:
    cout << "Invalid choice. The dictionary remains unchanged." << endl;
    break;
  }
}

void QuitNow(bool &quitFlag) {
  string quit;
  cout << "\nAre you sure (Y/N)?" << endl;
  cin >> quit;
  if (quit == "Y" || quit == "y" || quit == "Yes") {
    quitFlag = true;
  }
}

// This is the main menu loop. It continuously displays the menu and handles
// user input until the user decides to quit.
void menu() {
  // The current word defaults to your student ID.
  string currentWord = "16080142";
  char menuOption;
  double lastTimeTaken = 0.0;
  bool quitProgram = false;

  do { // The program will repeat this loop indefinitely until quitProgram is
       // true.
    cout << "\n--- C++ Anagram Solver Challenge ---" << endl;
    cout << "\t1. Enter a word or phrase (current word/phrase is: "
         << currentWord << ")" << endl;
    cout << "\t2. Find all possible words from these letters." << endl;
    cout << "\t3. Find the largest word containing (most of) these letters."
         << endl;
    cout << "\t4. Find all possible 3 letter words." << endl;
    cout << "\t5. Find all possible 5 letter words." << endl;
    cout << "\t6. Select a dictionary file (current: " << currentDictionaryFile
         << ")" << endl
         << endl;
    cout << "\t0. Quit the program." << endl << endl;

    // These lines format the output to show the time taken with 2 decimal
    // places.
    cout.precision(2);
    cout << fixed
         << "\tTime taken to complete the last function was: " << lastTimeTaken
         << "ms" << endl
         << endl;

    cout << "Please enter a valid option (0-6): ";
    cin >> menuOption;

    // Starts a high-resolution timer to measure the execution time of the
    // selected function.
    auto start = chrono::high_resolution_clock::now();

    // The switch statement directs the program's flow based on the user's menu
    // choice.
    switch (menuOption) {
    case '1':
      currentWord = GetWord();
      break;
    case '2':
      FindAnagrams(currentWord);
      break;
    case '3':
      LargestWordAvailable(currentWord);
      break;
    case '4':
      FindAll3LetterAnagrams(currentWord);
      break;
    case '5':
      FindAll5LetterAnagrams(currentWord);
      break;
    case '6':
      SelectDictionary();
      break;
    case '0':
      QuitNow(quitProgram);
      break;
    default:
      cout << "\n\nUnfortunately, " << menuOption
           << " is not a valid option, please try again." << endl
           << endl;
      break;
    }

    // Stops the timer and calculates the duration in milliseconds.
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    lastTimeTaken = duration.count();

  } while (!quitProgram);
}

// The main function is the entry point of the program.
int main() {
  // Read the smallest dictionary file once when the program starts.
  ReadFile(cDATAFILE);

  // Start the main menu loop.
  menu();

  return 0; // Return 0 indicates successful program execution.
}
