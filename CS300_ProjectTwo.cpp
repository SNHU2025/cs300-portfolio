//============================================================================
// ProjectTwo.cpp
// Author      : Khem Raj Khatiwada
// Course      : CS 300
// Description : ABCU Advising Assistance Program
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

//============================================================================
// Course structure
//============================================================================
struct Course {
    string courseId;
    string title;
    vector<string> prerequisites;
};

// Global data structure
map<string, Course> courseMap;

//============================================================================
// Function declarations
//============================================================================
void loadDataStructure(string fileName);
void printCourseList();
void printCourse(string courseId);
void displayMenu();

//============================================================================
// Main
//============================================================================
int main() {
    string fileName;
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        displayMenu();
        cout << "What would you like to do? ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input." << endl;
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter the file name: ";
            cin >> fileName;
            loadDataStructure(fileName);
            break;

        case 2:
            printCourseList();
            break;

        case 3: {
            string courseId;
            cout << "What course do you want to know about? ";
            cin >> courseId;
            transform(courseId.begin(), courseId.end(), courseId.begin(), ::toupper);
            printCourse(courseId);
            break;
        }

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}

//============================================================================
// Display Menu
//============================================================================
void displayMenu() {
    cout << endl;
    cout << " 1. Load Data Structure." << endl;
    cout << " 2. Print Course List." << endl;
    cout << " 3. Print Course." << endl;
    cout << " 9. Exit" << endl;
    cout << endl;
}

//============================================================================
// Load CSV File into Data Structure
//============================================================================
void loadDataStructure(string fileName) {
    ifstream file;
    file.open(fileName);

    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    courseMap.clear();
    string line;

    while (getline(file, line)) {
        Course course;
        string token;
        stringstream ss(line);

        getline(ss, course.courseId, ',');
        getline(ss, course.title, ',');

        while (getline(ss, token, ',')) {
            if (!token.empty()) {
                course.prerequisites.push_back(token);
            }
        }

        courseMap[course.courseId] = course;
    }

    file.close();
    cout << "File loaded successfully." << endl;
}

//============================================================================
// Print Alphanumeric Course List
//============================================================================
void printCourseList() {
    if (courseMap.empty()) {
        cout << "No courses loaded." << endl;
        return;
    }

    cout << endl;
    cout << "Here is a sample schedule:" << endl;

    for (auto const& pair : courseMap) {
        cout << pair.second.courseId << ", "
            << pair.second.title << endl;
    }
}

//============================================================================
// Print Individual Course Information
//============================================================================
void printCourse(string courseId) {
    if (courseMap.find(courseId) == courseMap.end()) {
        cout << "Course not found." << endl;
        return;
    }

    Course course = courseMap[courseId];

    cout << course.courseId << ", " << course.title << endl;

    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); i++) {
            string prereqId = course.prerequisites[i];
            cout << prereqId;

            if (courseMap.find(prereqId) != courseMap.end()) {
                cout << " (" << courseMap[prereqId].title << ")";
            }

            if (i != course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}
