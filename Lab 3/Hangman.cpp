#include "Functions.h"
#include "Games.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric>
using namespace std;

/*
 * Source: https://umsystem.instructure.com/files/folder/courses_312246/Labs/Games?preview=35163911
 * Games.cpp file from CS201 Lab Course Files
 */

// --- Hangman Game Functions ---
// Function to display the Hangman gallows based on incorrect guesses
void displayHangmanGallows(int incorrectGuesses) {
    cout << " +---+\n";
    cout << " | |\n";
    cout << " " << (incorrectGuesses > 0 ? "O" : " ") << " |\n";
    cout << " " << (incorrectGuesses > 2 ? "/" : " ") << (incorrectGuesses > 1 ?
                                                          "|" : " ") << (incorrectGuesses > 3 ? "\\" : " ") << " |\n";
    cout << " " << (incorrectGuesses > 4 ? "/" : " ") << " " << (incorrectGuesses >
                                                                 5 ? "\\" : " ") << " |\n";
    cout << " |\n";
    cout << "=========\n";
}
// Function to run the Hangman Game
void playHangman() {
// List of words for the game
    vector<string> words = {
            "programming", "computer", "keyboard", "monitor", "algorithm",
            "developer", "language", "hardware", "software", "internet",
            "blackjack", "hangman", "dice", "cplusplus", "console"
    };
// Choose a random word from the list
    string secretWord = words[rand() % words.size()];
    string guessedWord(secretWord.length(), '_'); // Initialize with underscores
    string guessedLetters = ""; // Stores letters already guessed
    int incorrectGuesses = 0; // Counter for incorrect guesses
    const int maxIncorrectGuesses = 6; // Maximum allowed incorrect guesses
    cout << "\n--- Welcome to Hangman! ---\n";
    cout << "Try to guess the word.\n";
// Game loop
    while (incorrectGuesses < maxIncorrectGuesses && guessedWord != secretWord) {
        displayHangmanGallows(incorrectGuesses); // Display gallows state
        cout << "\nWord: " << guessedWord << endl;
        cout << "Guessed letters: " << guessedLetters << endl;
        cout << "Incorrect guesses remaining: " << (maxIncorrectGuesses -
                                                    incorrectGuesses) << endl;
        cout << "Enter a letter: ";
        char guess;
        cin >> guess;
// Convert guess to lowercase for case-insensitivity
        guess = static_cast<char>(tolower(static_cast<unsigned char>(guess)));
// Clear the input buffer
        cin.ignore(10000, '\n');
// Check if letter has already been guessed
        if (guessedLetters.find(guess) != string::npos) {
            cout << "You already guessed that letter. Try again.\n";
            continue;
        }
        guessedLetters += guess; // Add the guessed letter to the list
        bool found = false;
// Check if the guessed letter is in the secret word
        for (size_t i = 0; i < secretWord.length(); ++i) {
            if (static_cast<char>(tolower(static_cast<unsigned
            char>(secretWord[i]))) == guess) {
                guessedWord[i] = secretWord[i]; // Reveal the letter
                found = true;
            }
        }
        if (!found) {
            cout << "Incorrect guess!\n";
            incorrectGuesses++; // Increment incorrect guess count
        }
        else {
            cout << "Good guess!\n";
        }
        cout << endl;
    }
// Game end conditions
    displayHangmanGallows(incorrectGuesses); // Final gallows display
    if (guessedWord == secretWord) {
        cout << "Congratulations! You guessed the word: " << secretWord << endl;
    }
    else {
        cout << "You ran out of guesses! The word was: " << secretWord << endl;
        cout << "Better luck next time!\n";
    }
    cout << "Thanks for playing Hangman!\n";

    main();
}