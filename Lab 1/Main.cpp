// Name: Vincent Yang
// Program 2 - Distance
/* Purpose:
Get 4 integers which will be the coordinates x1, y1, x2, y2,
based on either User Manual Input or Random Integer Generation,
then display the coordinates and distances each point
and which point is closest to the origin.
This sequence of actions will loop until the user indicates the loop should end.
*/

/*
Pseudocode

INPUT: 6 values (4 optional); loop, manualInput; (optional values) x1, y1, x2, y2
OUTPUT: 
Display Coordinates and Distance from Origin of each point (x,y), then tell the user which point is closer to the Origin.

main():
    WHILE (loop == 'Y')
        INPUT manualInput
        IF (manualInput == 'Y')
            THEN INPUT x1
            IF (x1 > 10 OR x1 < -10) OR NOT Numeric
                THEN WHILE (10 > x1 > -10) or NOT Numeric
                    INPUT x1
            INPUT y1
            IF (y1 > 10 OR y1 < -10) OR NOT Numeric
                THEN WHILE (10 > y1 > -10) or NOT Numeric
                    INPUT y1
            INPUT x2
            IF (x2 > 10 OR x2 < -10) OR NOT Numeric
                THEN WHILE (10 > x2 > -10) or NOT Numeric
                    INPUT x2
            INPUT y2
            IF (y2 > 10 OR y2 < -10) OR NOT Numeric
                THEN WHILE (10 > y2 > -10) or NOT Numeric
                    INPUT y2
        ELSE
            THEN x1 = randomInteger(MIN = -10, MAX = 10)
            y1 = randomInteger(MIN = -10, MAX = 10)
            x2 = randomInteger(MIN = -10, MAX = 10)
            y2 = randomInteger(MIN = -10, MAX = 10)
        
        DOUBLE point1Distance = Power(Power(x1, 2) + Power(y1, 2), 0.5)
        DOUBLE point2Distance = Power(Power(x2, 2) + Power(y2, 2), 0.5)

        PRINT Point 1: (x1, y1)
        PRINT Distance: point1Distance

        PRINT Point 2: (x2, y2)
        PRINT Distance: point2Distance

        IF (point1Distance < point2Distance)
            THEN PRINT Closest Point: point1Distance
        ELSE
            THEN PRINT Closest Point: point2Distance

        INPUT loop
*/

#include <iostream>
using namespace std;

int main()
{
    int x1, y1, x2, y2;
    char manualInput = 'Y';
    char loop = 'Y';

    cout << "Welcome to your 2nd C++ program" << endl;
    while (loop == 'Y')
    {
        cout << "Do you wish to enter the coordinates manually? If not, the program will generate random coordinates. (Enter Y if Yes)" << endl;
        cin >> manualInput;

        if (manualInput == 'Y')
        {
            cout << "Please enter the coordinates to be added (Format: x1, y1, x2, y2):" << endl;
            while (true)
            {
                if (cin >> x1 >> y1 >> x2 >> y2)
                {
                    if ((10 >= x1) && (x1 >= -10) && (10 >= y1) && (y1 >= -10) && (10 >= x2) && (x2 >= -10) && (10 >= y2) && (y2 >= -10))
                    {
                        break;
                    }
                    else
                    {
                        cout << "Invalid Input, Try Again. (Must be between 10 and -10)" << endl;
                    }
                }
                else
                {
                    cout << "Invalid Input, Try Again. (Must be Numeric)" << endl;
                    cin.clear(); // Resets the error state of cin, if this isn't set in place an infinite loop will occur
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Erases the previous input of the user, if this isn't set in place an infinite loop will occur
                }
            }
            //     if (cin >> x1)
            //     {
            //         if ((10 >= x1) && (x1 >= -10))
            //         {
            //             break;
            //         }
            //         else
            //         {
            //             cout << "Invalid Input, Try Again. (Must be between 10 and -10)" << endl;
            //         }
            //     }
            //     else
            //     {
            //         cout << "Invalid Input, Try Again. (Must be Numeric)" << endl;
            //         cin.clear();
            //         cin.ignore(numeric_limits<streamsize>::max(), '\n');
            //     }
            // }
            
            // cout << "Please enter the 1st y coordinate:" << endl;
            // while (true)
            // {
            //     if (cin >> y1)
            //     {
            //         if ((10 >= y1) && (y1 >= -10))
            //         {
            //             break;
            //         }
            //         else
            //         {
            //             cout << "Invalid Input, Try Again. (Must be between 10 and -10)" << endl;
            //         }
            //     }
            //     else
            //     {
            //         cout << "Invalid Input, Try Again. (Must be Numeric)" << endl;
            //         cin.clear();
            //         cin.ignore(numeric_limits<streamsize>::max(), '\n');
            //     }
            // }

            // cout << "Please enter the 2nd x coordinate:" << endl;
            // while (true)
            // {
            //     if (cin >> x2)
            //     {
            //         if ((10 >= x2) && (x2 >= -10))
            //         {
            //             break;
            //         }
            //         else
            //         {
            //             cout << "Invalid Input, Try Again. (Must be between 10 and -10)" << endl;
            //         }
            //     }
            //     else
            //     {
            //         cout << "Invalid Input, Try Again. (Must be Numeric)" << endl;
            //         cin.clear();
            //         cin.ignore(numeric_limits<streamsize>::max(), '\n');
            //     }
            // }

            // cout << "Please enter the 2nd y coordinate:" << endl;
            // while (true)
            // {
            //     if (cin >> y2)
            //     {
            //         if ((10 >= y2) && (y2 >= -10))
            //         {
            //             break;
            //         }
            //         else
            //         {
            //             cout << "Invalid Input, Try Again. (Must be between 10 and -10)" << endl;
            //         }
            //     }
            //     else
            //     {
            //         cout << "Invalid Input, Try Again. (Must be Numeric)" << endl;
            //         cin.clear();
            //         cin.ignore(numeric_limits<streamsize>::max(), '\n');
            //     }
            //}
        }
        else
        {
            x1 = rand() % 21 - 10;
            y1 = rand() % 21 - 10;
            x2 = rand() % 21 - 10;
            y2 = rand() % 21 - 10;
        }

        // cout << "x1: " << x1 << endl;
        // cout << "y1: " << y1 << endl;
        // cout << "x2: " << x2 << endl;
        // cout << "y2: " << y2 << endl;

        double point1Distance = pow(pow(x1, 2) + pow(y1, 2), 0.5); // Pythagorean Theorem: a^2 + b^2 = c^2; gets a^2 and b^2 then gets the square root to get c, which will be the hypotenuse/distance
        double point2Distance = pow(pow(x2, 2) + pow(y2, 2), 0.5);

        cout << "\nPoint 1: (" << x1 << ',' << y1 << ")\n" << "Distance: " << point1Distance << endl << endl;
        cout << "Point 2: (" << x2 << ',' << y2 << ")\n" << "Distance: " << point2Distance << endl << endl;

        if (point1Distance < point2Distance)
        {
            cout << "Point 1 is closer to the origin." << endl << endl;
        }
        else if (point2Distance < point1Distance)
        {
            cout << "Point 2 is closer to the origin." << endl << endl;
        }
        else
        {
            cout << "Both points are of equal distance from the origin." << endl << endl;
        }

        cout << "Again? (Enter Y if Yes)" << endl;
        cin >> loop;
    }

    return 0;
}