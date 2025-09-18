# Anagram Solver Challenge

This is a C++ command-line application that acts as an anagram and word finder. It provides a simple, menu-driven interface for interacting with a dictionary of words and performing various search tasks.

The program's core functionalities include:

* **Dictionary Management:** The ability to load different dictionary files of varying sizes to test the application's performance. The dictionaries used are provided as .csv files.

* **Word Finder:** Finds all possible words that can be formed from the letters of a user-provided word or phrase.

* **Largest Word Search:** Identifies the longest word in the dictionary that can be created using the available letters.

* **Specific Word Length Search:** Locates all 3-letter and 5-letter words that can be formed from the user's input.

* **Performance Monitoring:** Measures and displays the time taken to execute each search function, providing insight into the program's efficiency.

The code is well-commented and structured, demonstrating fundamental C++ concepts such as file I/O, string manipulation, and the use of modern libraries like `<chrono>` for precise timing.

## How to Run

1. **Clone this repository to your local machine.**

2. **Ensure you have a C++ compiler (like `g++`) installed.**

3. **Place the provided .csv dictionary files in the same directory as the source code.**

4. **Compile the code using a command-line tool.**

      ```bash
      g++ -o anagram_solver main.cpp
      ```

5. **Run the executable.**
      ```bash
      ./anagram_solver
      ```

The application will launch with a menu of options, guiding you through its features.
