#include <iostream>
#include <fstream>
using namespace std;

class temp {
    string rollnum, name, Fname, Address, search;
    fstream file;
public:
    void addstu();
    void viewstu();
    void searchstu();
    void delstu();
} obj;

int main() {
    char choice;
    while (true) {
        cout << "\n------------------------------" << endl;
        cout << "1-Add Student Record" << endl;
        cout << "2-View All Student Records" << endl;
        cout << "3-Search Student Record" << endl;
        cout << "4-Dellet student record" <<endl;
        cout << "5-Exit" << endl;
        cout << "------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Clear input buffer

        switch (choice) {
            case '1':
                obj.addstu();
                break;
            case '2':
                obj.viewstu();
                break;
            case '3':
                obj.searchstu();
                break;
                case '4':
                obj.delstu();
                break;
            case '5':
                return 0;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }
}

void temp::addstu() {
    cout << "Enter Student Roll Number: ";
    getline(cin, rollnum);
    cout << "Enter Student Name: ";
    getline(cin, name);
    cout << "Enter Student Father's Name: ";
    getline(cin, Fname);
    cout << "Enter Student Address: ";
    getline(cin, Address);

    file.open("stuData.txt", ios::out | ios::app);
    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    file << rollnum << "*" << name << "*" << Fname << "*" << Address << endl;
    file.close();
    cout << "Record added successfully!\n";
}

void temp::viewstu() {
    file.open("stuData.txt", ios::in);
    if (!file) {
        cout << "Error opening file! No records found.\n";
        return;
    }

    bool hasRecords = false;
    while (getline(file, rollnum, '*') && getline(file, name, '*') &&
           getline(file, Fname, '*') && getline(file, Address, '\n')) {
        hasRecords = true;
        cout << "\n-------------------------------\n";
        cout << "Student Roll Number: " << rollnum << endl;
        cout << "Student Name: " << name << endl;
        cout << "Student Father's Name: " << Fname << endl;
        cout << "Student Address: " << Address << endl;
        cout << "-------------------------------\n";
    }
    file.close();

    if (!hasRecords) {
        cout << "No records found.\n";
    }
}

void temp::searchstu() {
    cout << "Enter Student Roll Number to Search: ";
    getline(cin, search);

    file.open("stuData.txt", ios::in);
    if (!file) {
        cout << "Error opening file! No records found.\n";
        return;
    }

    bool found = false;
    while (getline(file, rollnum, '*') && getline(file, name, '*') &&
           getline(file, Fname, '*') && getline(file, Address, '\n')) {
        if (rollnum == search) {
            found = true;
            cout << "\n-------------------------------\n";
            cout << "Student Roll Number: " << rollnum << endl;
            cout << "Student Name: " << name << endl;
            cout << "Student Father's Name: " << Fname << endl;
            cout << "Student Address: " << Address << endl;
            cout << "-------------------------------\n";
            break;  // Stop search after finding the record
        }
    }
    file.close();

    if (!found) {
        cout << "Student record not found.\n";
    }
}

void temp::delstu() {
    cout << "Enter Student Roll Number to Delete: ";
    getline(cin, search);

    file.open("stuData.txt", ios::in);
    if (!file) {
        cout << "Error opening file! No records found.\n";
        return;
    }

    fstream tempFile;
    tempFile.open("temp.txt", ios::out);

    bool found = false;
    while (getline(file, rollnum, '*') && getline(file, name, '*') &&
           getline(file, Fname, '*') && getline(file, Address, '\n')) {
        if (rollnum == search) {
            found = true;
            cout << "Student record deleted successfully!\n";
        } else {
            tempFile << rollnum << "*" << name << "*" << Fname << "*" << Address << endl;
        }
    }

    file.close();
    tempFile.close();

    if (found) {
        remove("stuData.txt");
        rename("temp.txt", "stuData.txt");
    } else {
        cout << "Student record not found.\n";
        remove("temp.txt");
    }
}