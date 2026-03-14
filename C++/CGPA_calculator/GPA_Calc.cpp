#include <iostream>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

// This function converts your marks into the 4.0 scale points
float getGradePoint(int m) {
    if (m >= 85) return 4.0;
    if (m >= 80) return 3.8;
    if (m >= 75) return 3.4;
    if (m >= 71) return 3.0;
    if (m >= 68) return 2.8;
    if (m >= 64) return 2.4;
    if (m >= 61) return 2.0;
    if (m >= 57) return 1.8;
    if (m >= 53) return 1.4;
    if (m >= 50) return 1.0;
    return 0.0; // Fail
}

int main() {
    int totalSubjects;
    float totalGradePoints = 0;
    int totalCreditHours = 0;

    cout << "--- Welcome to My GPA Calculator ---" << endl;
    
    // Choose how many subjects to calculate (Range 5-8)
    cout << "How many subjects do you have this semester? (5-8): ";
    cin >> totalSubjects;

    // Safety check to keep it within your 5-8 range
    if (totalSubjects < 5 || totalSubjects > 8) {
        cout << "Invalid choice! Please restart and pick between 5 and 8." << endl;
        return 0;
    }

    // Main loop to get data for each subject
    for (int i = 1; i <= totalSubjects; i++) {
        string subName;
        int marks, credits;

        cout << "\nDetails for Subject #" << i << ":" << endl;
        cout << "Name of subject: ";
        cin.ignore(); // Clears the buffer
        getline(cin, subName);
        
        cout << "Credit hours for " << subName << ": ";
        cin >> credits;
        
        cout << "Marks obtained in " << subName << ": ";
        cin >> marks;

        // Calculate GPA for this specific subject
        float subjectGPA = getGradePoint(marks);
        cout << "Current GPA for " << subName << " is: " << subjectGPA << endl;

        // Add to running totals
        totalGradePoints += (subjectGPA * credits);
        totalCreditHours += credits;
    }

    // Final Calculation
    float finalCGPA = totalGradePoints / totalCreditHours;

    cout << "\n-------------------------------------" << endl;
    cout << "Total Credit Hours: " << totalCreditHours << endl;
    cout << "YOUR FINAL CGPA IS: " << fixed << setprecision(2) << finalCGPA << endl;
    cout << "-------------------------------------" << endl;

    cout << "\nExiting in 5 seconds... Great job this semester!" << endl;
    this_thread::sleep_for(chrono::seconds(5));

    return 0;
}