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
        if ((cin >> betAmount) && (betAmount <= netWorth))
        {
            break;
        }
        else
        {
            cout << "Your net worth is only: $" << netWorth << ". Please adjust your bet: ";
        }
    }

    return betAmount;
}

int playCraps()
{
    double netWorth = 50.00;

    displayCrapsStart();
    promptCrapsBet(netWorth);

    return 0;
}