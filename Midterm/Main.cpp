// Name: Vincent Yang
// Program 3 - Chocolate Factory
/* Purpose:
Keeps track of the chocolate bar inventory and allows the user to create orders efficiently.
Also creates a printout of each order and includes the tax and shipping costs and the ability
to order more chocolate.
*/

#include <iostream>
#include <iomanip>
using namespace std;

// Displays a welcome message to the user
void displayIntro()
{
    cout << "WELCOME TO MY CHOCOLATE FACTORY" << endl;
}

// Displays the current/remaining inventory of large, medium, and small bars
void displayInventory(int largeInv, int mediumInv, int smallInv)
{
    cout << "Remaining Inventory\n" <<
    "Small Bars: " << setw(4) << smallInv << endl <<
    "Medium Bars: " << setw(4) << mediumInv << endl <<
    "Large Bars: " << setw(4) << largeInv << endl
    << endl << endl;
}

// Fills an order by prompting the user to enter the total number of pounds of chocolate they would like, then optimizes the process by using large bars first, then medium bars, then small bars if necessary.
void fillOrder(int& largeInv, int& mediumInv, int& smallInv, float largePrice, float mediumPrice, float smallPrice, int& orderNum)
{
    int numPounds; // User's input for how many pounds they want
    int totalInv = (largeInv * 5) + (mediumInv * 3) + smallInv; // Measures the total inventory in pounds, large is 5 pounds, medium is 3 pounds, small is 1 pound.

    double largeTotal; // Amount of large bars that will be used in the order times the price; basically total cost of large bars
    double mediumTotal; // Amount of medium bars that will be used in the order times the price; basically total cost of medium bars
    double smallTotal; // Amount of small bars that will be used in the order times the price; basically total cost of small bars

    double totalCost; // All fo the totals of large, medium, and small bars and adds them up.

    cout << "Enter total number of pounds of chocolate you would like: ";
    if ((cin >> numPounds) && (numPounds > 0)) // Checks if the user's input is a positive integer, if not a warning message is displayed.
    {
        if (numPounds <= totalInv) // Checks if the user's input is equal to or less than the total inventory in pounds, if it's greater than the total inventory then a warning message is displayed.
        {
            int wantedLarge = numPounds / 5; // Amount of large bars needed to fulfill the order
            if (wantedLarge > largeInv) // Checks if the amount of large bars needed exceeds the inventory for large bars, and if it is, then makes the needed amount equal to the current inventory (Basically uses up all available large bars)
            {
                wantedLarge = largeInv;
            }
            numPounds -= (wantedLarge * 5); // Subtracts the amount of pounds needed from the user, this process makes it so the program doesn't count the amount that's already filled by the large bars
            largeTotal = wantedLarge * largePrice; // already explained above
            largeInv -= wantedLarge; // Subtracts the amount of needed large bars from the inventory, since they will be used for the order

            // Same process as the large bars as above, but with a different weight value (3 pounds per bar instead of 5 pounds)
            int wantedMedium = numPounds / 3;
            if (wantedMedium > mediumInv)
            {
                wantedMedium = mediumInv;
            }
            numPounds -= (wantedMedium * 3);
            mediumTotal = wantedMedium * mediumPrice;
            mediumInv -= wantedMedium;

            // Remaining amount of chocolate pounds needed will be fulfilled with small bars, since they are 1 pound each.
            int wantedSmall = numPounds;
            smallTotal = wantedSmall * smallPrice;
            smallInv -= wantedSmall;

            totalCost = largeTotal + mediumTotal + smallTotal; // Already explained above

            // Displays the order and the cost/total cost of each part of the order (small, medium, large bars)
            cout << fixed << setprecision(2) << setw(10); // fixed makes it so the numbers don't show up in fixed point notation and not scientific notation; setprecision sets the number of sig figs a number with decimals will have; setw() sets the width of the message.
            cout << "Your order has been filled:" << endl;
            cout << "Small Bars:  " << setw(4) << wantedSmall << " = " <<  setw(9) << smallTotal << endl;
            cout << "Medium Bars: " << setw(4) << wantedMedium << " = " << setw(9) << mediumTotal << endl;
            cout << "Large Bars:  " << setw(4) << wantedLarge << " = " << setw(9) << largeTotal << endl;
            cout << "Total Cost:  " << setw(16) << totalCost << endl << endl;

            orderNum++; // Increases the order number by 1
        }
        else
        {
            cout << "\nWARNING: Unable to fill order #" << orderNum << ". We are " << numPounds - totalInv << " pounds short. We are sorry for the inconvenience." << endl;
        }
    }
    else
    {
        cout << "\nWARNING: Input is not a valid positive integer. Command ignored." << endl;
        cin.clear(); // Clears the error state of the user input object
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores a number of characters (in this case, the maximum size/amount/number) until it reaches the break character (in this case, a new line) from the user input object.
    }
}

int main()
{
    int orderNum = 1;

    int largeInv = 620;
    int mediumInv = 500;
    int smallInv = 700;

    float largePrice = 27.99;
    float mediumPrice = 21.99;
    float smallPrice = 14.99;

    char loop = 'Y';

    displayIntro();
    while (toupper(loop) == 'Y')
    {
        fillOrder(largeInv, mediumInv, smallInv, largePrice, mediumPrice, smallPrice, orderNum);

        displayInventory(largeInv, mediumInv, smallInv);

        cout << "Enter Y to process more orders: ";
        cin >> loop;

        cout << endl;
    }

    cout << "\nThank you for using my program!" << endl;

    return 0;
}