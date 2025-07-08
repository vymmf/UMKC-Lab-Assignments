#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

double add(double num1, double num2)
{
    return num1 + num2;
}

double subtract(double num1, double num2)
{
    return num1 - num2;
}

double multiply(double num1, double num2)
{
    return num1 * num2;
}

double divide(double num1, double num2)
{
    return num1 / num2;
}

void performArithmetic(int choice)
{
    double num1;
    double num2;

    while (true)
    {
        cout << "Enter first number: ";
        if (cin >> num1)
        {
            break;
        }
        else
        {
            cout << "Please enter a valid number" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    while (true)
    {
        cout << "Enter second number: ";
        if (cin >> num2)
        {
            break;
        }
        else
        {
            cout << "Please enter a valid number" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    //cout << "Choice is equal to " << choice <<endl<<endl;
    switch (choice)
    {
        case 1:
            cout << "Result: " << add(num1, num2) << endl;
            break;
        case 2:
            cout << "Result: " << subtract(num1, num2) << endl;
            break;
        case 3:
            cout << "Result: " << multiply(num1, num2) << endl;
            break;
        case 4:
            cout << "Result: " << divide(num1, num2) << endl;
            break;
        default:
            cout << "This wasn't supposed to happen" << endl;
            break;
    }
}

void displayArithmeticOperationChoices()
{
    cout << "\nArithmetic Operations:\n1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n5. Back to Main Menu" << endl;
}

void promptArithmeticOperations()
{
    int choice;
    char another;

    displayArithmeticOperationChoices();

    while (true)
    {
        cout << "Enter your choice: ";
        if ((cin >> choice) && (choice <= 5) && (choice >= 1))
        {
            if (choice == 5)
            {
                break;
            }
            performArithmetic(choice);

            while ((tolower(another) != 'y') && (tolower(another) != 'n'))
            {
                cout << "Do you want to perform another arithmetic operation? (y/n): ";
                cin >> another;
            }

            if (tolower(another) == 'n')
            {
                break;
            }

            another = 0;
            displayArithmeticOperationChoices();
        }
        else
        {
            cout << "Please enter a valid input (1, 2, 3, 4, 5)." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

void promptNumberBaseConversions()
{
    cout << "Number Base Conversions:\n";
}

void displayIntro()
{
    cout << "Welcome to the C++ Calculator!" << endl << "Main Main:" << endl << "1. Arithmetic Operations" << endl << "2. Number Base Conversions" << endl << "3. Exit" << endl;
}

void displayOutro()
{
    cout << "Thank you for using the C++ Calculator! See you later!" << endl;
}

int promptMainMenu()
{
    int choice;
    while (true)
    {
        cout << "Enter your choice: ";
        if (cin >> choice)
        {
            switch (choice)
            {
                case 1:
                    promptArithmeticOperations();
                    return 0;
                case 2:
                    promptNumberBaseConversions();
                    return 0;
                case 3:
                    return 1;
                default:
                    cout << "Please enter a valid input (1, 2, 3)." << endl;
            }
        }
        else
        {
            cout << "Please enter a valid input (1, 2, 3)." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

int main()
{
    int loop = 0;
    while (loop == 0)
    {
        displayIntro();
        loop = promptMainMenu();
    }
    displayOutro();

    return 0;
}