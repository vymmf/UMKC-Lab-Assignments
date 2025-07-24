// Name: Vincent Yang
// Final Program
/* Purpose:
Grading students quiz scores using pointers.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
using namespace std;

int main() {
    // Creates pointers for an input file (stream) and an output file (stream) // streams being where data is passed through, similar to cout displaying data/info using the console and cin getting user input
    auto* inputFilePtr = new ifstream("quiz_data.txt");
    auto* outputFilePtr = new ofstream("quiz_results.txt");

    // Attempts to open the input file, if it fails an error message is shown and the pointer is deleted (saves memory), also makes process finish with exit code 1
    if (!inputFilePtr->is_open()) {
        cerr << "Error: Could not open quiz_data.txt" << endl;
        delete inputFilePtr;
        return 1;
    }

    // Attempts to open the output file, if it fails an error message is shown and the pointer is deleted (saves memory), also makes process finish with exit code 1
    if (!outputFilePtr->is_open()) {
        cerr << "Error: Could not open quiz_results.txt" << endl;
        delete outputFilePtr;
        return 1;
    }

    // Creates a pointer for a string (memory allocation to a slot where only string values should be stored)
    auto* correctAnswersPtr = new string();

    // getline function which has the parameters of what file it wants to get a line/data/text from, and where to store that line/data/text to. Since this is the first instance of getting a line, it will only get the first line.
    // this also checks if it is able to read and get the line from the file it wants to read from, and if it can't then it'll display an error message.
    if (getline(*inputFilePtr, *correctAnswersPtr)) {
    }
    else {
        // closes the file and deletes the pointer for the file/file stream. also deletes the string pointer for the correctAnswers (Which should be ABCDE if things go correctly)
        cerr << "Error: Could not read correct answers from student.txt" << endl;
        inputFilePtr->close();
        delete inputFilePtr;
        delete correctAnswersPtr;
        return 1;
    }

    // Fancy text formatting to make the grading report look nice
    // setw() sets the width based on the integer that is passed in
    // left sets the alignment of the string/text
    // *outputFilePtr is passed through instead of cout because we are writing to the quiz_results.txt file, not to the console display
    *outputFilePtr << "Quiz Grading Report:\n";
    *outputFilePtr << "------------------------\n";
    *outputFilePtr << left << setw(15) << "Student ID"
         << left << setw(10) << "Correct" << endl;
    *outputFilePtr << "------------------------\n";
    // Creates 3 new string pointers, which will be used to get the current line, the student's id, and the answers the student got
    auto* linePtr = new string();
    auto* studentIdStrPtr = new string();
    auto* studentAnswersPtr = new string();
    // This while loop attempts to get the next line in the file and puts it in the line string pointer, which will be used to read the student's id and answers
    while (getline(*inputFilePtr, *linePtr)) {
// Finds the first space in the line, which will the divider between the student id and their answers. (spacePos is the position of the space)
        size_t spacePos = linePtr->find(' ');
        // If a space is found within the line (thus there is no position aka npos) then it creates a substring where the student id is from index 0 to the index position of the space, and then anything after the space is the student's answers
        if (spacePos != string::npos) {
            *studentIdStrPtr = linePtr->substr(0, spacePos);
            *studentAnswersPtr = linePtr->substr(spacePos + 1);
        }

        int correct = 0;
// Creates pointers for the characters in the string pointers for student answers and correct answers
        const char* studentAnsChar = studentAnswersPtr->c_str();
        const char* correctAnsChar = correctAnswersPtr->c_str();
        // loops 5 times because there are only 5 multiple choice questions/answers to be checked for each student
        for (int i = 0; i < 5; ++i) {
                if (*(studentAnsChar + i) == *(correctAnsChar + i)) {
                    correct += 1; // Correct answer
                }
        }
        // More fancy text formatting, this time it will write the student ids and their number of correct answers into the quiz_results.txt file
        *outputFilePtr << left << setw(15) << *studentIdStrPtr
             << left << setw(10) << correct << endl;
    }
// Closes both input and output file streams using the data that the pointers are pointing to (in this case the file streams)
    inputFilePtr->close();
    outputFilePtr->close();
    // Deletes all allocated memory slots for pointers that were used in the program
    delete inputFilePtr;
    delete outputFilePtr;
    delete correctAnswersPtr;
    delete linePtr;
    delete studentIdStrPtr;
    delete studentAnswersPtr;
    cout << "\nGrading complete.\n";
    return 0;
}