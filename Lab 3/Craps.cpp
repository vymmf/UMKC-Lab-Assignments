#include "Functions.h"
#include "Games.h"

void displayCrapsStart()
{
    cout << "WELCOME TO CRAPS!" << endl << endl;
}

double promptCrapsBet(double& netWorth)
{
    double betAmount;

    cout << "Your net worth is: $" << netWorth << ". Please enter your bet: ";
    
    while (true)
    {
        if ((cin >> betAmount) && (betAmount <= netWorth) && (betAmount >= 0))
        {
            break;
        }
        else
        {
            cout << "Your net worth is only: $" << netWorth << ". Please adjust your bet: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return betAmount;
}

int rollDice()
{
    int dice1 = (rand() % 6) + 1;
    int dice2 = (rand() % 6) + 1;

    // cout << "Dice 1 roll: " << dice1 << "\nDice 2 roll: "<< dice2;
    cout << "You rolled: " << dice1 << " + " << dice2 << " = " << dice1 + dice2 << endl;
    return dice1 + dice2;
}

bool checkRoll(int rollTotal, int establishedPoint, bool displayPoint = true)
{
    if (displayPoint)
    {
        if (establishedPoint == 7 || establishedPoint == 11)
        {
            return true;
        }
        else if (establishedPoint == 2 || establishedPoint == 3 || establishedPoint == 12)
        {
            return false;
        }
    }

    rollTotal = rollDice();
    if (rollTotal == establishedPoint)
    {
        return true;
    }
    else if (rollTotal == 7)
    {
        return false;
    }
    else
    {
        return checkRoll(rollTotal, establishedPoint, false);
    }
}

double checkStatus(bool playerWin, double betAmount)
{
    if (playerWin)
    {
        cout << "Yay, you Win!!" << endl;
        return betAmount;
    }
    else
    {
        cout << "Sorry, but you Lost!!" << endl;
        return betAmount * -1;
    }
}

void playCraps()
{
    srand(time(0)); // Creates a seed based on the current time so the numbers that are randomly generated aren't always the same

    int establishedPoint;
    int dice1, dice2;
    double netWorth = 50.00;
    double betAmount;
    bool playerWin;
    char playAgain = 'Y';

    displayCrapsStart();
    while ((toupper(playAgain) == 'Y') || (netWorth > 0))
    {
        betAmount = promptCrapsBet(netWorth);
        establishedPoint = rollDice(); // Used to delay the roll for establishedPoint so it isn't the same as the rollTotal
        cout << endl << "Point is: " << establishedPoint << endl;
        playerWin = checkRoll(0, establishedPoint); // Not using rollDice() within the parameter because it displays the roll even after figuring out the point is 2,3, or 12 which would make the player lose automatically
        netWorth += checkStatus(playerWin, betAmount);
        if (netWorth <= 0)
        {
            break;
        }

        while (true)
        {
            cout << "Would you like to go again? Y or N : ";
            if ((cin >> playAgain) && (toupper(playAgain) == 'Y' || toupper(playAgain) == 'N'))
            {
                break;
            }
            else
            {
                cout << "Please choose a valid response (Y or N)" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        if (toupper(playAgain) == 'N')
        {
            break;
        }
    }

    if (netWorth > 0)
    {
        cout << "Thank you for playing. Your net worth is: " << netWorth << endl;
    }
    else
    {
        cout << "Sorry - you are out of money. Don't make us escort you out - that would be embarrassing!!" << endl;
    }

    cout << endl;
    main();
}