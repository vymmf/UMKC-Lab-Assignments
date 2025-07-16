// Name: Vincent Yang
// Program 6 - Grading Using Pointers
/* Purpose:
Automate the process of grading answers of students for a multiple choice quiz.
*/

// student.txt, error.txt, and report.txt are in the cmake-build-debug/Lab 5 folder

// The source of this code was from https://umsystem.instructure.com/courses/312246/files/folder/Labs/Grading

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype> // For isdigit

using namespace std;

// Function to check if a string contains only digits using a pointer
bool isNumeric(const string* strPtr) {
// Check if the pointer is null before dereferencing
    if (strPtr == nullptr) {
        return false;
    }
// Iterate through the string using a pointer to characters
    for (const char* cPtr = strPtr->c_str(); *cPtr != '\0'; ++cPtr) {
        if (!isdigit(*cPtr)) {
            return false;
        }
    }
    return true;
}
// Function to trim whitespace from a string using pointers
void trimWhitespace(string* strPtr) {
    if (strPtr == nullptr) {
        return;
    }
// Trim leading whitespace
    size_t first = strPtr->find_first_not_of(" \t\n\r\f\v");
    if (string::npos == first) {
// String is all whitespace or empty
        strPtr->clear();
        return;
    }
    strPtr->erase(0, first);
// Trim trailing whitespace
    size_t last = strPtr->find_last_not_of(" \t\n\r\f\v");
    strPtr->erase(last + 1);
}
int main() {
// Using pointers for file streams
    ifstream* inputFilePtr = new ifstream("student.txt");
    ofstream* errorFilePtr = new ofstream("error.txt");
    if (!inputFilePtr->is_open()) {
        cerr << "Error: Could not open student.txt" << endl;
// Clean up dynamically allocated memory before exiting
        delete inputFilePtr;
        delete errorFilePtr; // Even if not opened, try to delete to be safe
        return 1;
    }
    if (!errorFilePtr->is_open()) {
        cerr << "Error: Could not open error.txt" << endl;
// Clean up dynamically allocated memory before exiting
        inputFilePtr->close(); // Close the input file before deleting
        delete inputFilePtr;
        delete errorFilePtr;
        return 1;
    }
    string* correctAnswersPtr = new string();
    if (getline(*inputFilePtr, *correctAnswersPtr)) {
// Trim any leading/trailing whitespace from correctAnswers using the helper function
        trimWhitespace(correctAnswersPtr);
    }
    else {
        cerr << "Error: Could not read correct answers from student.txt" << endl;
// Clean up dynamically allocated memory
        inputFilePtr->close();
        errorFilePtr->close();
        delete inputFilePtr;
        delete errorFilePtr;
        delete correctAnswersPtr;
        return 1;
    }
    cout << "Quiz Grading Report:\n";
    cout << "--------------------\n";
    cout << left << setw(15) << "Student ID"
         << left << setw(10) << "Score"
         << left << setw(10) << "Percentage"
         << left << "Grade" << endl;
    cout << "----------------------------\n";
    string* linePtr = new string();
    string* studentIdStrPtr = new string();
    string* studentAnswersPtr = new string();
    while (getline(*inputFilePtr, *linePtr)) {
// Find the first space to separate ID and answers
        size_t spacePos = linePtr->find(' ');
        if (spacePos != string::npos) {
            *studentIdStrPtr = linePtr->substr(0, spacePos);
// Get answers, handling potential leading spaces before answers
            *studentAnswersPtr = linePtr->substr(spacePos + 1);
            trimWhitespace(studentAnswersPtr); // Trim leading whitespace from answers
        }
        else {
// If no space, assume the whole line is potentially an ID or malformed
            *studentIdStrPtr = *linePtr;
            studentAnswersPtr->clear(); // No answers provided if no space
        }
// Trim any leading/trailing whitespace from studentIdStr
        trimWhitespace(studentIdStrPtr);
// Pass the address of the string to isNumeric
        if (!isNumeric(studentIdStrPtr) || studentIdStrPtr->empty()) {
            *errorFilePtr << "Rejected Record: Invalid Student ID '" <<
                          *studentIdStrPtr << "' in line: " << *linePtr << endl;
            continue; // Skip to the next line
        }
        int score = 0;
// Iterate using pointers to characters for comparison (optional but demonstrates pointer usage)
        const char* studentAnsChar = studentAnswersPtr->c_str();
        const char* correctAnsChar = correctAnswersPtr->c_str();
        for (int i = 0; i < 20; ++i) {
            if (i < studentAnswersPtr->length() && i < correctAnswersPtr->length())
            {
                if (*(studentAnsChar + i) == *(correctAnsChar + i)) {
                    score += 2; // Correct answer
                }
                else if (*(studentAnsChar + i) != ' ') { // Incorrect (and not blank)
                    score += 1; // Incorrect answer
                }
// If studentAnswers[i] is ' ', it's a blank, score remains 0 for that question
            }
        }
        double percentage = (static_cast<double>(score) / 40.0) * 100.0;
        char grade;
        if (percentage >= 90.0) {
            grade = 'A';
        }
        else if (percentage >= 80.0) {
            grade = 'B';
        }
        else if (percentage >= 70.0) {
            grade = 'C';
        }
        else if (percentage >= 60.0) {
            grade = 'D';
        }
        else {
            grade = 'F';
        }
        cout << left << setw(15) << *studentIdStrPtr
             << left << setw(10) << score
             << left << setw(10) << fixed << setprecision(2) << percentage
             << left << grade << endl;
    }
// Close and delete dynamically allocated file streams
    inputFilePtr->close();
    errorFilePtr->close();
    delete inputFilePtr;
    delete errorFilePtr;
// Delete dynamically allocated strings
    delete correctAnswersPtr;
    delete linePtr;
    delete studentIdStrPtr;
    delete studentAnswersPtr;
    cout << "\nGrading complete. Invalid student IDs (if any) have been written to error.txt.\n";
    return 0;
}