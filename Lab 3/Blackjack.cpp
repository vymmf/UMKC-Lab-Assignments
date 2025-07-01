#include "Functions.h"
#include "Games.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <random>
using namespace std;

// --- Blackjack Game Functions ---
// Card structure
struct Card {
    string rank; // e.g., "2", "King", "Ace"
    int value; // Numeric value (e.g., 2, 10, 11 for Ace initially)
};
// Function to create a standard deck of 52 cards
vector<Card> createBlackjackDeck() {
    vector<Card> deck;
    vector<string> ranks = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack",
                             "Queen", "King", "Ace" };
    vector<int> values = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };
// Create 4 suits of each card
    for (int i = 0; i < 4; ++i) {
        for (size_t j = 0; j < ranks.size(); ++j) {
            deck.push_back({ ranks[j], values[j] });
        }
    }
    return deck;
}
// Function to shuffle the deck (using random_shuffle)
void shuffleBlackjackDeck(vector<Card>& deck) {
    static std::random_device rd; // Creates a random seed
    static std::mt19937 gen(rd()); // Random number generator engine
    std::shuffle(deck.begin(), deck.end(), gen); // Modern way to do the random_shuffle function
}
// Function to calculate the total value of a hand, handling Aces (1 or 11)
int calculateBlackjackHandValue(const vector<Card>& hand) {
    int value = 0;
    int aceCount = 0;
    for (const auto& card : hand) {
        value += card.value;
        if (card.rank == "Ace") {
            aceCount++;
        }
    }
// Adjust for Aces if hand value exceeds 21
    while (value > 21 && aceCount > 0) {
        value -= 10; // Change Ace from 11 to 1
        aceCount--;
    }
    return value;
}
// Function to display a hand
void displayBlackjackHand(const string& owner, const vector<Card>& hand, bool
hideDealerCard = false) {
    cout << owner << "'s hand: ";
    for (size_t i = 0; i < hand.size(); ++i) {
        if (hideDealerCard && i == 0) {
            cout << "[Hidden Card] ";
        }
        else {
            cout << hand[i].rank << " ";
        }
    }
    if (!hideDealerCard) {
        cout << "(Value: " << calculateBlackjackHandValue(hand) << ")";
    }
    cout << endl;
}
// Function to run the Blackjack Game
void playBlackjack() {
    char playAgain;
    cout << "\n--- Welcome to Blackjack! ---\n";
    do {
        vector<Card> deck = createBlackjackDeck();
        shuffleBlackjackDeck(deck);
        vector<Card> playerHand;
        vector<Card> dealerHand;
        int deckIndex = 0; // To keep track of current card in the deck
// Deal initial cards
        playerHand.push_back(deck[deckIndex++]);
        dealerHand.push_back(deck[deckIndex++]); // Dealer's first card (hidden)
        playerHand.push_back(deck[deckIndex++]);
        dealerHand.push_back(deck[deckIndex++]);
        displayBlackjackHand("Player", playerHand);
        displayBlackjackHand("Dealer", dealerHand, true); // Hide dealer's first card
// Player's turn
        char choice;
        while (true) {
            int playerValue = calculateBlackjackHandValue(playerHand);
            if (playerValue > 21) {
                cout << "Player busts!\n";
                break;
            }
            if (playerValue == 21) {
                cout << "Player has Blackjack!\n";
                break;
            }
            cout << "Do you want to (H)it or (S)tand? ";
            cin >> choice;
            choice = static_cast<char>(tolower(static_cast<unsigned
            char>(choice)));
// Clear the input buffer
            cin.ignore(10000, '\n');
            if (choice == 'h') {
                playerHand.push_back(deck[deckIndex++]);
                displayBlackjackHand("Player", playerHand);
            }
            else if (choice == 's') {
                cout << "Player stands.\n";
                break;
            }
            else {
                cout << "Invalid choice. Please enter 'H' or 'S'.\n";
            }
        }
// Dealer's turn (only if player hasn't busted)
        int playerFinalValue = calculateBlackjackHandValue(playerHand);
        if (playerFinalValue <= 21) {
            cout << "\nDealer's turn:\n";
            displayBlackjackHand("Dealer", dealerHand); // Reveal dealer's hidden card
            while (calculateBlackjackHandValue(dealerHand) < 17) {
                cout << "Dealer hits.\n";
                dealerHand.push_back(deck[deckIndex++]);
                displayBlackjackHand("Dealer", dealerHand);
            }
            int dealerValue = calculateBlackjackHandValue(dealerHand);
            if (dealerValue > 21) {
                cout << "Dealer busts! Player wins!\n";
            }
            else if (dealerValue > playerFinalValue) {
                cout << "Dealer wins!\n";
            }
            else if (playerFinalValue > dealerValue) {
                cout << "Player wins!\n";
            }
            else {
                cout << "It's a push (tie)!\n";
            }
        }
        cout << "Play again? (y/n): ";
        cin >> playAgain;
        playAgain = static_cast<char>(tolower(static_cast<unsigned
        char>(playAgain)));
        cin.ignore(10000, '\n'); // Clear input buffer
        cout << endl;
    } while (playAgain == 'y');
    cout << "Thanks for playing Blackjack!\n";

    main();
}