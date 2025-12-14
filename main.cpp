#include "Recipient.h"
#include<iostream>
#include<fstream>
using namespace std;

string trim(const string& s) {
    size_t a = s.find_first_not_of(" \t\n\r");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\n\r");
    return s.substr(a, b - a + 1);
}

string readLineNonEmpty(const string& msg) {
    string s;
    do {
        cout << msg;
        getline(cin, s);
    } while (s.empty());
    return s;
}

string genID() {
    static int x = 1000;
    return "R" + to_string(x++);
}

int main() {
    const string FILE = "C:/Users/XPRISTO/OneDrive/Desktop/Blood Bank Management System/Recipient.txt";

    RecipientList list;
    list.loadFromFile(FILE);

    RecipientHash hash;
    hash.rebuildFromList(list);
    cout << "*****Welcome****\n";
    cout << "*** Recipient Management System ***\n";

    while (true) {
        cout << "\n1 --> Login\n";
        cout << "2 --> Register\n";
        cout << "3 --> Update Data\n";
        cout << "4 --> Delete Account\n";
        cout << "5 --> Search by Email\n";
        cout << "6 --> Display All\n";
        cout << "7 --> Exit\n";

        cout << "Choice: ";
        string ch;
        getline(cin, ch);
        int c = stoi(ch);

        // choice
        if (c == 1) {
            string email, pass;
            cout << "Email: "; getline(cin, email);
            cout << "Password: "; getline(cin, pass);

            RecipientNode* r = hash.findByMail(trim(email));

            if (r && r->password == pass)
                cout << "Login success. Welcome " << r->name << "\n";
            else
                cout << "Login failed.\n";
        }

        // another choice
        else if (c == 2) {
            cout << "-- Register --\n";

            string id = genID();
            string name = readLineNonEmpty("Name: ");
            string mail = readLineNonEmpty("Email: ");

            if (hash.findByMail(mail)) {
                cout << "Email already exists.\n";
                continue;
            }

            string pass = readLineNonEmpty("Password: ");
            int age = stoi(readLineNonEmpty("Age: "));
            string gender = readLineNonEmpty("Gender: ");
            string blood = readLineNonEmpty("Blood Type: ");
            string hospital = readLineNonEmpty("Hospital: ");
            string doctor = readLineNonEmpty("Doctor: ");

            RecipientNode* node =
                new RecipientNode(id, name, mail, pass, age, gender, blood, hospital, doctor);

            list.insertTail(node);
            hash.insert(node);

            list.saveToFile(FILE);

            cout << "Registered successfully. ID = " << id << "\n";
        }

        // another choice
        else if (c == 3) {
            cout << "-- Update--\n";

            string email, pass;
            cout << "Email: "; getline(cin, email);
            cout << "Password: "; getline(cin, pass);

            RecipientNode* r = hash.findByMail(trim(email));

            if (!r || r->password != pass) {
                cout << "Updated failed.\n";
                continue;
            }

            cout << "New name [" << r->name << "]: ";
            string t; getline(cin, t); if (!t.empty()) r->name = t;

            cout << "New age [" << r->age << "]: ";
            getline(cin, t); if (!t.empty()) r->age = stoi(t);

            cout << "New hospital [" << r->hospital << "]: ";
            getline(cin, t); if (!t.empty()) r->hospital = t;

            cout << "New doctor [" << r->doctor << "]: ";
            getline(cin, t); if (!t.empty()) r->doctor = t;

            list.saveToFile(FILE);
            cout << "Updated.\n";
        }

        // another choice
        else if (c == 4) {
            cout << "-- Delete --\n";

            string email, pass;
            cout << "Email: "; getline(cin, email);
            cout << "Password: "; getline(cin, pass);

            RecipientNode* r = hash.findByMail(trim(email));

            if (!r || r->password != pass) {
                cout << "Deleted failed.\n";
                continue;
            }

            hash.removeByMail(r->mail);
            list.removeByID(r->id);
            list.saveToFile(FILE);

            cout << "Account deleted.\n";
        }

        // another choice
        else if (c == 5) {
            string email;
            cout << "Email: ";
            getline(cin, email);

            RecipientNode* r = hash.findByMail(trim(email));

            if (!r) cout << "Not found.\n";
            else {
                cout << "Found: " << r->name
                    << " | Blood: " << r->bloodType
                    << " | Hospital: " << r->hospital << "\n";
            }
        }

        // another choice
        else if (c == 6) {
            RecipientNode* show = list.getHead();
            if (!show) cout << "Empty.\n";
            while (show) {
                cout << show->id << " | " << show->name << " | " << show->mail
                    << " | " << show->bloodType << show->age << " | " << show->doctor << " | " << show->hospital << "\n";
                show = show->next;
            }
        }

        // another choice
        else if (c == 7) {
            cout << "Goodbye (^_^) \n";
            break;
        }
        else cout << "Invalid choice.\n";
    }

    return 0;
}












