#include <iostream>
#include <iomanip>
using namespace std;

double calculateShipping(int numPounds) // Calculates shipping costs based on branching
{
    if (numPounds <= 10) 
    {
        return 8.25;
    }
    else if (numPounds <= 20) 
    {
        return 12.75;
    }
    else if (numPounds <= 50) 
    {
        return 15.25;
    }
    else 
    {
        return 19.75;
    }
}

void printInventory(int largeInv, int mediumInv, int smallInv)
{
    cout << "Chocolate Inventory\n" << "Large Bars: " << setw(4) << largeInv << endl << "Medium Bars: " << setw(4) << mediumInv << endl << "Small Bars: " << setw(4) << smallInv << endl;
}


void orderInventory(int& largeInv, int& mediumInv, int& smallInv)
{
    int amount;
    int invOfType;
    char type;
    string typeAsString;

    char validTypes[3] = {'L', 'M', 'S'};

    while (true)
    {
        cout << "Enter the number of bars needed: ";
        if ((cin >> amount) && (amount > 0))
        {
            break;
        }
        else
        {
            cout << "\nWARNING: Input is not a valid positive integer. Command ignored." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while (true)
    {
        cout << "Enter the type (L, M, S): ";
        cin >> type;

        if (toupper(type) == 'L')
        {
            typeAsString = "large";
            largeInv += amount;
            invOfType = largeInv;
            break;
        }
        else if (toupper(type) == 'M')
        {
            typeAsString = "medium";
            mediumInv += amount;
            invOfType = mediumInv;
            break;
        }
        else if (toupper(type) == 'S')
        {
            typeAsString = "small";
            smallInv += amount;
            invOfType = smallInv;
            break;
        }
        else
        {
            cout << "\nWARNING: " << type << " is an invalid type. Command ignored." << endl;
        }
    }
    // else
    // {
    //     typeAsString = ""
    // }

    cout << "An additional " << amount << ' ' << typeAsString << " bars ordered. New total of " << typeAsString << " bars = " << invOfType << endl;
}

void fillOrder(int& largeInv, int& mediumInv, int& smallInv, float largePrice, float mediumPrice, float smallPrice, int& orderNum)
{
    int numPounds;
    int totalInv = (largeInv * 5) + (mediumInv * 3) + smallInv;
    double taxRate = 0.072;

    double largeTotal;
    double mediumTotal;
    double smallTotal;

    double subTotalCost;
    double totalCost;

    double taxTotal;
    double shipping;

    // while (true)
    // {
        cout << "Please enter the number of pounds of chocolate you would like to order: ";
        if ((cin >> numPounds) && (numPounds > 0))
        {
            if (numPounds <= totalInv)
            {
                shipping = calculateShipping(numPounds);

                int wantedLarge = numPounds / 5;
                if (wantedLarge > largeInv)
                {
                    wantedLarge = largeInv;
                }
                numPounds -= (wantedLarge * 5);
                largeTotal = wantedLarge * largePrice;
                largeInv -= wantedLarge;

                int wantedMedium = numPounds / 3;
                if (wantedMedium > mediumInv) 
                {
                    wantedMedium = mediumInv;
                }
                numPounds -= (wantedMedium * 3);
                mediumTotal = wantedMedium * mediumPrice;
                mediumInv -= wantedMedium;

                int wantedSmall = numPounds;
                smallTotal = wantedSmall * smallPrice;
                smallInv -= wantedSmall;

                subTotalCost = largeTotal + mediumTotal + smallTotal;

                taxTotal = taxRate * subTotalCost;

                totalCost = subTotalCost + taxTotal + shipping;

                cout << fixed << setprecision(2) << setw(10);
                cout << "Chocolate Order #" << orderNum << endl;
                cout << "Large Bars:  " << setw(4) << wantedLarge << setw(9) << wantedLarge * 5 << setw(12) << largeTotal << endl;
                cout << "Medium Bars: " << setw(4) << wantedMedium << setw(9) << wantedMedium * 3 << setw(12) << mediumTotal << endl;                
                cout << "Small Bars:  " << setw(4) << wantedSmall << setw(9) << wantedSmall << setw(12) << smallTotal << endl;
                cout << "Sub Total:  " << setw(14) << wantedLarge * 5 + wantedMedium * 3 + wantedSmall << setw(12) << subTotalCost << endl;
                cout << "\nTax Total: " << setw(25) << taxTotal << endl;
                cout << "Shipping: " << setw(25) << shipping << endl;
                cout << "Total Cost: " << setw(25) << totalCost << endl << endl << endl;

                orderNum++;
                // break;
            }
            else
            {
                cout << "\nWARNING: Unable to fill order of " << orderNum << " point(s). We are " << numPounds - totalInv << " pounds short. We are sorry for the inconvenience." << endl;
            }
        }
        else
        {
            cout << "\nWARNING: Input is not a valid positive integer. Command ignored." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    // }
}

int command(char& choice, int& largeInv, int& mediumInv, int& smallInv, float largePrice, float mediumPrice, float smallPrice, int& orderNum) // I created this function to avoid too much clutter in the main function
{
    if (toupper(choice) == 'F')
    {
        fillOrder(largeInv, mediumInv, smallInv, largePrice, mediumPrice, smallPrice, orderNum);
    }
    else if (toupper(choice) == 'P')
    {
        printInventory(largeInv, mediumInv, smallInv);
    }
    else if (toupper(choice) == 'O')
    {
        orderInventory(largeInv, mediumInv, smallInv);
    }
    else if (toupper(choice) == 'E')
    {
        return 0;
    }
    else // If it's not one of the 4 choices above, it is most likely an unexpected input and thus an error
    {
        cout << "\nWARNING: " << choice << " is an invalid choice. Please try again." << endl;
    }
    return 1;
}

int main()
{
    int orderNum = 1;

    int largeInv = 1500;
    int mediumInv = 1200;
    int smallInv = 7000;

    float largePrice = 41.25;
    float mediumPrice = 25.80;
    float smallPrice = 13.50;

    char validChoices[4] = {'F', 'P', 'O', 'E'}; // Array that contains all valid choices for the command function
    char choice;

    // bool loop;
    int loop = 1; // 1 is true, 0 is false (Alternative solution to creating a boolean type loop variable)

    while (loop == 1)
    {
        cout << "Chocolate Inventory\n" << "F: Fill Order\n" << "P: Print Inventory\n" << "O: Order Inventory\n" << "E: Exit\n" << "Enter your choice: ";
        cin >> choice;

        loop = command(choice, largeInv, mediumInv, smallInv, largePrice, mediumPrice, smallPrice, orderNum);

    //     if (cin >> choice)
    //     {
    //         if (find(validChoices, validChoices + 4, choice)) // Attempts to find user input value choice in array validChoices, if it doesn't find it, then it results in an error
    //         {
    //             command(choice);
    //         }
    //         else
    //         {
    //             cout << "\nWARNING: " << choice << " is an invalid choice. Please try again." << endl;
    //         }
    //     }
    //     else
    //     {
    //         cout << "\nWARNING: " << choice << " is an invalid choice. Please try again." << endl;
    //     }

    //     cout << endl;
        cout << endl;
    }

    cout << "\nThank you for using my program!" << endl;

    return 0;
}