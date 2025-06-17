#include <iostream>
using namespace std;

void orderInventory(int& largeInv, int& mediumInv, int& smallInv)
{
    int increment;
    char type;
    string typeAsString;

    cout << "Enter the number of bars needed: ";
    cin >> increment;

    cout << "Enter the type (L, M, S): ";
    cin >> type;

    if (type == 'L')
    {
        typeAsString = "Large";
    }
    else if (type == 'M')
    {
        typeAsString = "Medium";
    }
    else if (type == 'S')
    {
        typeAsString = "Small";
    }
    // else
    // {
    //     typeAsString = ""
    // }

    cout << "An additional " << increment << ' ' << typeAsString << " bars ordered. New total of " << typeAsString << " bars = " << increment << endl;
}

void command(char& choice) // I created this function to avoid too much clutter in the main function
{
    if (choice == 'F')
    {

    }
    else if (choice == 'P')
    {
        
    }
    else if (choice == 'O')
    {
        
    }
    else if (choice == 'E')
    {
        
    }
    else // If it's not one of the 4 choices above, it is most likely an unexpected input and thus an error
    {
        cout << "WARNING: " << choice << " is an invalid choice. Please try again." << endl;
    }
}

int main()
{
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
        
        if (cin >> choice)
        {
            if (find(validChoices, validChoices + 4, choice)) // Attempts to find user input value choice in array validChoices, if it doesn't find it, then it results in an error
            {
                command(choice);
            }
            else
            {
                cout << "WARNING: " << choice << " is an invalid choice. Please try again." << endl;
            }
        }
        else
        {
            cout << "WARNING: " << choice << " is an invalid choice. Please try again." << endl;
        }

        cout << endl;
    }

    return 0;
}