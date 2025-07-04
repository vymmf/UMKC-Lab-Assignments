// Name: Vincent Yang
// Program 1 - Numbers
/* Purpose:
Continuiously display the largest, smallest, average, increasing order, and
decreasing order of the 4 numbers inputted by the user for each iteration 
of the loop until the user indicates the loop should end
*/

/*
Pseudocode

INPUT: 5 values; loop, a,b,c,d
OUTPUT: 
Largest of the 4 values, Smallest of the 4 values, Average of the 4 values, 
4 values in Increasing Order, 4 values in Decreasing Order

main():
    WHILE (loop == 'Y')
        INPUT a,b,c,d
        IF a > b
            THEN swap a & b
        IF b > c
            THEN swap b & c
        IF c > d
            THEN swap c & d
        IF a > b
            THEN swap a & b
        IF b > c
            THEN swap b & c
        IF a > b
            THEN swap a & b
        
        sum = a + b + c + d
        avg = sum/4

        PRINT largest: d
        PRINT smallest: a
        PRINT average: avg
        PRINT increasing order: a b c d
        PRINT decreasing order: d c b a

        INPUT loop
*/

#include <iostream>
using namespace std;

int main()
{
    int number1, number2, number3, number4; // I want number1 to be the smallest number and number 4 to be the largest number; order will be from smallest to largest
    int storedNum; // Used to store the larger number when comparing 2 numbers
    int sum = 0;
    char loop = 'Y';

    cout << "Welcome to your 1st C++ program \n";
    while (loop == 'Y')
    {
        cout << "Please enter numbers to be added:\n";
    
        cin >> number1 >> number2 >> number3 >> number4;
        
        if (number1 > number2)
        {
            storedNum = number1;
            number1 = number2;
            number2 = storedNum;
        }

        if (number2 > number3)
        {
            storedNum = number2;
            number2 = number3;
            number3 = storedNum;
        }

        if (number3 > number4)
        {
            storedNum = number3;
            number3 = number4;
            number4 = storedNum;
        }

        if (number1 > number2)
        {
            storedNum = number1;
            number1 = number2;
            number2 = storedNum;
        }

        if (number2 > number3)
        {
            storedNum = number2;
            number2 = number3;
            number3 = storedNum;
        }

        if (number1 > number2)
        {
            storedNum = number1;
            number1 = number2;
            number2 = storedNum;
        }

        cout << "Largest of the four numbers is " << number4 << endl;
        cout << "Smallest of the four numbers is " << number1 << endl;

        sum = number1 + number2 + number3 + number4;
        float avg = sum/static_cast<double>(4); // Converts the value type of 4 into a double
        cout << "Average of the four numbers is " << avg << endl;

        cout << "Numbers in Increasing Order is " << number1 << ' ' << number2 << ' ' << number3 << ' ' << number4 << endl;
        cout << "Numbers in Decreasing Order is " << number4 << ' ' << number3 << ' ' << number2 << ' ' << number1 << endl;

        cout << "\nAgain?\n";
        cin >> loop;
    }

    return 0;
}