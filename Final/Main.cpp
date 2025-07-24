// Name: Vincent Yang
// Final Program
/* Purpose:

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
using namespace std;

int main() {
    auto* inputFilePtr = new ifstream("quiz_data.txt");
    auto* outputFilePtr = new ofstream("quiz_results.txt");
    if (!inputFilePtr->is_open()) {
        cerr << "Error: Could not open quiz_data.txt" << endl;
        delete inputFilePtr;
        return 1;
    }

    if (!outputFilePtr->is_open()) {
        cerr << "Error: Could not open quiz_results.txt" << endl;
        delete outputFilePtr;
        return 1;
    }

    auto* correctAnswersPtr = new string();
    if (getline(*inputFilePtr, *correctAnswersPtr)) {
    }
    else {
        cerr << "Error: Could not read correct answers from student.txt" << endl;
        inputFilePtr->close();
        delete inputFilePtr;
        delete correctAnswersPtr;
        return 1;
    }

    *outputFilePtr << "Quiz Grading Report:\n";
    *outputFilePtr << "--------------------\n";
    *outputFilePtr << left << setw(15) << "Student ID"
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