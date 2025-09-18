# Anagram Solver Changelog

### Version 1.0 (Initial Development - 2019)

* **March 19, 2019:**
    * Initial implementation of the menu-driven interface.
    * Created the `GetWord` and `QuitNow` functions.
    * Developed the repeating menu loop.
    * Tested core functions; `QuitNow` was only working for termination, not for continuing the program.
* **March 28, 2019:**
    * Implemented the `ReadFile` function and added timing code, though the clock's accuracy was uncertain.
* **March 29, 2019:**
    * Updated the `QuitNow` function to work as intended.
* **March 31, 2019:**
    * Modified the `GetWord` function to accept a full sentence.
    * Replaced the `if` statement with a `switch` statement for the menu options.
    * Rearranged code and added comments.
    * Updated the `FindAnagrams` function to sort the input word.
    * Added new data files for larger dictionary sizes.

### Version 2.0 (Modern Update - 2025)

* **September 18, 2025:**
    * **Major Refactor:** Replaced the original file reading logic to load all words into a `std::vector<std::string>` for more efficient searching.
    * **Bug Fix:** Resolved a logical error in the `FindAnagrams` function where it only found words of the same length, allowing it to now find all possible words from the given letters.
    * **Feature:** Added a new menu option (6) for dynamically selecting between different dictionary files (`Words_100.csv`, `Words_1K.csv`, `Words_75K.csv`).
    * **Improved Robustness:** Updated the `ReadFile` function to convert all words to lowercase and remove trailing whitespace, ensuring correct matching regardless of dictionary formatting.
    * **Code Style:** Replaced ASCII integer values in the `switch` statement with character literals for improved readability.
    * **Documentation:** Added a new `README.md` and `LICENSE` file and refactored the in-code documentation to be more descriptive and easier for beginners to understand.
    * **Project Management:** Updated the project for modern Git and GitHub practices, including setting up a repository, using a Personal Access Token, and creating this `CHANGELOG.md` file to track future updates.
