#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

  // Found an easier solution than doing all this
//struct number
//{
//    int value;
//    string symbol;
//};
//
//string convertToSymbol(int num)
//{
//    vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36};
//    vector<string> symbols = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
//}

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

bool isValidNumber(string& numStr, int base)
{
    const string symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (char c : numStr)
    {
        c = toupper(c);
        size_t pos = symbols.find(c); // size_t is an unsigned integer data type, represents the size of objects in bytes (basically it only represents positive values or 0)
        if (pos == string::npos || pos >= base) // Checks if the character was not found in symbols, then also checks if the character/digit is less than or equal to the base number
        {
            return false;
        }
    }
    return true;
}

string baseSystemConvert(string numStr, int initialBase, int finalBase)
{
    //const int values[37] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
    const string symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //vector<int> digits;
    int remainder;
    int num = 0;
    int digit;
    string convertedNum;

    // Initial base to decimal
    for (char c : numStr) // for each character in the string
    {

        if (isdigit(c))
        {
            digit = c - '0';
        }
        else
        {
            digit = 10 + toupper(c) - 'A';
        }

        num = num * initialBase + digit;
    }

    // Decimal to final base
    while(num > 0)
    {
        remainder = num % finalBase;
        convertedNum = symbols[remainder] + convertedNum;
        num /= finalBase;
        //digits.push_back(remainder);
    }

    if (numStr == "0")
    {
        return "0";
    }

    return convertedNum;
}

//void decToBin(double num)
//{
//
//}

//void decToOct(double num)
//{
//
//}
//
//
//void decToHex(double num)
//{
//
//}
//
//
//void binToDec(double num)
//{
//
//}
//
//void octToDec(double num)
//{
//
//}
//
//void hexToDec(double num)
//{
//
//}

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

void performNumberBaseConversion(int choice)
{
    const int values[37] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
    const string symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string numStr;
    int initialBase;
    int finalBase;
    int threshold;

    while (true)
    {
        switch (choice)
        {
            case 1:
                cout << "Enter decimal number: ";
                threshold = 10;
                break;
            case 2:
                cout << "Enter decimal number: ";
                threshold = 10;
                break;
            case 3:
                cout << "Enter decimal number: ";
                threshold = 10;
                break;
            case 4:
                cout << "Enter binary number: ";
                threshold = 2;
                break;
            case 5:
                cout << "Enter octal number: ";
                threshold = 8;
                break;
            case 6:
                cout << "Enter hexadecimal number: ";
                threshold = 16;
                break;
            default:
                cout << "Enter the number to convert: ";
                threshold = 37;
                break;
        }

        if ((cin >> numStr) && (isValidNumber(numStr, threshold)))
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

    if (choice == 7)
    {
        while (true)
        {
            cout << "Enter the base number of the number inputted (2-36): ";
            if ((cin >> initialBase) && (initialBase >= 2 && initialBase <= 36 ))
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
            cout << "Enter the base number to convert to (2-36): ";
            if ((cin >> finalBase) && (finalBase >= 2 && finalBase <= 36 ))
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
    }

    switch (choice)
    {
        case 1:
            cout << "Binary Equivalent: " << baseSystemConvert(numStr, 10, 2) << endl;
            break;
        case 2:
            cout << "Octal Equivalent: " << baseSystemConvert(numStr, 10, 8) << endl;
            break;
        case 3:
            cout << "Hexadecimal Equivalent: " << baseSystemConvert(numStr, 10,16) << endl;
            break;
        case 4:
            cout << "Decimal Equivalent: " << baseSystemConvert(numStr, 2,10) << endl;
            break;
        case 5:
            cout << "Decimal Equivalent: " << baseSystemConvert(numStr, 8,10) << endl;
            break;
        case 6:
            cout << "Decimal Equivalent: " << baseSystemConvert(numStr, 16,10) << endl;
            break;
        case 7:
            cout << "Base Equivalent: " << baseSystemConvert(numStr, initialBase,finalBase) << endl;
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
            cout << "Please enter a valid input (1-5)." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

void displayNumberBaseConversionsChoices()
{
    cout << "\nNumber Base Conversions:\n1. Decimal to Binary\n2. Decimal to Octal\n3. Decimal to Hexadecimal\n4. Binary to Decimal\n5. Octal to Decimal\n6. Hexadecimal to Decimal\n7. Custom\n8. Back to Main Menu" << endl;
}

void promptNumberBaseConversions()
{
    int choice;
    char another;

    displayNumberBaseConversionsChoices();
    while (true)
    {
        cout << "Enter your choice: ";
        if ((cin >> choice) && (choice <= 8) && (choice >= 1))
        {
            if (choice == 8)
            {
                break;
            }
            performNumberBaseConversion(choice);

            while ((tolower(another) != 'y') && (tolower(another) != 'n'))
            {
                cout << "Do you want to perform another conversion? (y/n): ";
                cin >> another;
            }

            if (tolower(another) == 'n')
            {
                break;
            }

            another = 0;
            displayNumberBaseConversionsChoices();
        }
        else
        {
            cout << "Please enter a valid input (1-8)." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
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