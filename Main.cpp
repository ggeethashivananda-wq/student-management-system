#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    int id;
    string name;
    int age;
    string course;
};

// Function prototypes
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;
    do {
        cout << "\n==============================\n";
        cout << "   STUDENT MANAGEMENT SYSTEM  \n";
        cout << "==============================\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice, try again.\n";
        }
    } while (choice != 6);

    return 0;
}

void addStudent() {
    Student s;
    cout << "\nEnter Student ID: ";
    cin >> s.id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, s.name);
    cout << "Enter Age: ";
    cin >> s.age;
    cin.ignore();
    cout << "Enter Course: ";
    getline(cin, s.course);

    // Save to file (using comma separation)
    ofstream file("students.txt", ios::app);
    file << s.id << "," << s.name << "," << s.age << "," << s.course << "\n";
    file.close();
    cout << "Student added successfully!\n";
}

void displayStudents() {
    ifstream file("students.txt");
    if (!file.is_open()) {
        cout << "\nNo records found!\n";
        return;
    }

    string line;
    cout << "\n--- Student Records ---\n";
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, age, course;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, course, ',');

        cout << "ID: " << id << " | Name: " << name 
             << " | Age: " << age << " | Course: " << course << "\n";
    }
    file.close();
}

void searchStudent() {
    int searchId;
    cout << "\nEnter Student ID to search: ";
    cin >> searchId;

    ifstream file("students.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, age, course;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, course, ',');

        if (stoi(idStr) == searchId) {
            cout << "\nRecord Found!\n";
            cout << "ID: " << idStr << "\nName: " << name 
                 << "\nAge: " << age << "\nCourse: " << course << "\n";
            found = true;
            break;
        }
    }
    file.close();
    if (!found) cout << "Student not found!\n";
}

void updateStudent() {
    int searchId;
    cout << "\nEnter Student ID to update: ";
    cin >> searchId;

    ifstream file("students.txt");
    ofstream temp("temp.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, age, course;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, course, ',');

        if (stoi(idStr) == searchId) {
            cout << "Enter New Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter New Age: ";
            cin >> age;
            cout << "Enter New Course: ";
            cin.ignore();
            getline(cin, course);
            found = true;
        }
        temp << idStr << "," << name << "," << age << "," << course << "\n";
    }
    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) cout << "Student updated successfully!\n";
    else cout << "Student ID not found!\n";
}

void deleteStudent() {
    int searchId;
    cout << "\nEnter Student ID to delete: ";
    cin >> searchId;

    ifstream file("students.txt");
    ofstream temp("temp.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, age, course;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, course, ',');

        if (stoi(idStr) == searchId) {
            found = true;
            continue; // Skip writing this record to delete it
        }
        temp << idStr << "," << name << "," << age << "," << course << "\n";
    }
    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) cout << "Student deleted successfully!\n";
    else cout << "Student ID not found!\n";
}
