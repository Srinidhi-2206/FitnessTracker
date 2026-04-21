/*
 ============================================================
   FITNESS TRACKER - C++ Console Application
   A menu-driven program to record and monitor daily
   fitness activities using file handling and structures.
 ============================================================
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

// ─────────────────────────────────────────────
//  Data Structure
// ─────────────────────────────────────────────
struct FitnessData {
    char date[12];       // e.g. 21-04-2026
    int  steps;          // steps taken
    float calories;      // calories burned
    int  duration;       // exercise duration in minutes
};

const char* FILE_NAME = "fitness_records.dat";

// ─────────────────────────────────────────────
//  Utility: Display a separator line
// ─────────────────────────────────────────────
void printLine(char ch = '-', int len = 50) {
    for (int i = 0; i < len; i++) cout << ch;
    cout << endl;
}

// ─────────────────────────────────────────────
//  Display the main menu
// ─────────────────────────────────────────────
void displayMenu() {
    cout << endl;
    printLine('=');
    cout << "       FITNESS TRACKER  |  C++ Project" << endl;
    printLine('=');
    cout << "  1. Add Daily Fitness Record" << endl;
    cout << "  2. View All Records" << endl;
    cout << "  3. Search Record by Date" << endl;
    cout << "  4. Exit" << endl;
    printLine('=');
    cout << "  Enter your choice: ";
}

// ─────────────────────────────────────────────
//  Display a single fitness record
// ─────────────────────────────────────────────
void displayRecord(const FitnessData& fd) {
    printLine();
    cout << "  Date          : " << fd.date     << endl;
    cout << "  Steps Taken   : " << fd.steps    << " steps" << endl;
    cout << "  Calories Burnt: " << fixed << setprecision(1)
         << fd.calories << " kcal" << endl;
    cout << "  Duration      : " << fd.duration << " minutes" << endl;
    printLine();
}

// ─────────────────────────────────────────────
//  1. Add a new fitness record
// ─────────────────────────────────────────────
void addRecord() {
    FitnessData fd;

    cout << endl;
    printLine('*');
    cout << "        ADD DAILY FITNESS RECORD" << endl;
    printLine('*');

    cout << "  Enter Date (DD-MM-YYYY) : ";
    cin >> fd.date;

    cout << "  Enter Steps Taken       : ";
    cin >> fd.steps;

    cout << "  Enter Calories Burned   : ";
    cin >> fd.calories;

    cout << "  Enter Duration (mins)   : ";
    cin >> fd.duration;

    // Open file in append + binary mode
    fstream file;
    file.open(FILE_NAME, ios::out | ios::app | ios::binary);

    if (!file) {
        cout << "\n  [ERROR] Could not open file for writing!" << endl;
        return;
    }

    file.write(reinterpret_cast<char*>(&fd), sizeof(fd));
    file.close();

    cout << endl;
    printLine();
    cout << "  [SUCCESS] Record saved successfully!" << endl;
    printLine();
}

// ─────────────────────────────────────────────
//  2. View all stored records
// ─────────────────────────────────────────────
void viewAllRecords() {
    FitnessData fd;
    int count = 0;

    fstream file;
    file.open(FILE_NAME, ios::in | ios::binary);

    if (!file) {
        cout << "\n  [INFO] No records found. Add some data first!" << endl;
        return;
    }

    cout << endl;
    printLine('*');
    cout << "          ALL FITNESS RECORDS" << endl;
    printLine('*');

    while (file.read(reinterpret_cast<char*>(&fd), sizeof(fd))) {
        cout << "  Record #" << ++count << endl;
        displayRecord(fd);
    }

    file.close();

    if (count == 0) {
        cout << "  [INFO] No records found in file." << endl;
    } else {
        cout << "\n  Total Records: " << count << endl;
    }
}

// ─────────────────────────────────────────────
//  3. Search a record by date
// ─────────────────────────────────────────────
void searchByDate() {
    char target[12];
    FitnessData fd;
    bool found = false;

    cout << endl;
    printLine('*');
    cout << "         SEARCH RECORD BY DATE" << endl;
    printLine('*');
    cout << "  Enter Date to Search (DD-MM-YYYY): ";
    cin >> target;

    fstream file;
    file.open(FILE_NAME, ios::in | ios::binary);

    if (!file) {
        cout << "\n  [INFO] No records file found. Add data first!" << endl;
        return;
    }

    while (file.read(reinterpret_cast<char*>(&fd), sizeof(fd))) {
        if (strcmp(fd.date, target) == 0) {
            cout << "\n  [FOUND] Record for date: " << target << endl;
            displayRecord(fd);
            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\n  [NOT FOUND] No record found for date: " << target << endl;
    }
}

// ─────────────────────────────────────────────
//  Main Function
// ─────────────────────────────────────────────
int main() {
    int choice;

    cout << endl;
    printLine('=');
    cout << "   Welcome to Fitness Tracker - C++ Project" << endl;
    printLine('=');

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                viewAllRecords();
                break;
            case 3:
                searchByDate();
                break;
            case 4:
                cout << endl;
                printLine('=');
                cout << "  Thank you for using Fitness Tracker!" << endl;
                cout << "  Stay fit and healthy. Goodbye!" << endl;
                printLine('=');
                break;
            default:
                cout << "\n  [ERROR] Invalid choice! Please enter 1-4." << endl;
        }

    } while (choice != 4);

    return 0;
}
