#include "Games.h"
#include "Functions.h"

void displayGameCollection()
{
    cout << "--- Welcome to the C++ Game Collection! ---\n1. Play Dice Rolling Game\n2. Play Hangman Game\n3. Play Blackjack Game\n4. Exit" << endl;
}

int promptChoice()
{
    int choice;

    cout << "Enter your choice: ";
    while (true)
    {
        if ((cin >> choice) && (choice == 1 || choice == 2 || choice == 3 || choice == 4))
        {
            break;
        }
        else
        {
            cout << "Please enter a valid choice (1, 2, 3, 4): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    if (choice == 1)
    {
        playCraps();
    }
    else if (choice == 2)
    {
        playHangman();
    }
    else if (choice == 3)
    {
        playBlackjack();
    }
    else if (choice == 4)
    {
        cout << "--- Thanks for playing the C++ Game Collection! ---" << endl;
        return 1;
    }
    else
    {
        cout << "An unexpected error occurred";
    }
}

int main()
{
    int exit = 0;

    displayGameCollection();
    while (exit == 0)
    {
        exit = promptChoice();
    }

    return 0;
}