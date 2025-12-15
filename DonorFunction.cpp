#include "Donor.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include<vector>
using namespace std;

void DonorList::SaveToFile() {
    ofstream file("Donors.txt");

    Node* cur = head;
    while (cur != nullptr) {
        file << cur->data.id << ","
            << cur->data.name << ","
            << cur->data.mail << ","
            << cur->data.password << ","
            << cur->data.age << ","
            << cur->data.gender << ","
            << cur->data.bloodType << ","
            << cur->data.diseaseList << ","
            << cur->data.medications << ","
            << cur->data.latestDonationDate
            << "\n";

        cur = cur->next;
    }

    file.close();
}

void DonorList::LoadFromFile() {
    ifstream file("Donors.txt");
    if (!file.is_open())
        return;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, mail, pass, gender, blood, disease, meds, date, ageStr;
        int age;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, mail, ',');
        getline(ss, pass, ',');
        getline(ss, ageStr, ',');
        getline(ss, gender, ',');
        getline(ss, blood, ',');
        getline(ss, disease, ',');
        getline(ss, meds, ',');
        getline(ss, date, ',');

        age = stoi(ageStr);

        Donor d(id, name, mail, pass, age, gender, blood, disease, meds, date);
        InsertDonor(d);
    }

    file.close();
}




void RequestList::SaveFile() {
    ofstream file("DonationRequests.txt");
    RequestNode* cur = head;
    while (cur != nullptr) {
        file << cur->data.patientName << "," << cur->data.bloodType << ","
            << cur->data.amount << "," << cur->data.phone << "\n";
        cur = cur->next;
    }
    file.close();
}

void RequestList::LoadFile() {
    ifstream file("DonationRequests.txt");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, blood, phone, amountStr;
        int amount;
        getline(ss, name, ','); getline(ss, blood, ','); getline(ss, amountStr, ','); getline(ss, phone, ',');
        amount = stoi(amountStr);
        DonationRequest d{ name,blood,amount,phone };
        AddRequest(d);
    }
    file.close();
}



void UpdateAccount(DonorList& list, Donor* d) {
    if (!d) {
        cout << "Account Not Found!";
        return;
    }
    cin.ignore();
    cout << "Updating account for " << d->name << endl;
    cout << "New Name: "; getline(cin, d->name);
    cout << "New Age: "; cin >> d->age; cin.ignore();
    cout << "New Password: "; getline(cin, d->password);
    cout << "New Blood Type: "; getline(cin, d->bloodType);
    cout << "New Diseases: "; getline(cin, d->diseaseList);
    cout << "New Medications: "; getline(cin, d->medications);

    list.UpdateDonor(*d);
    list.SaveToFile();
    cout << "Account updated successfully!\n";
}

vector<Donor*> DonorList::SearchByBloodType(const std::string& bloodType) {
    vector<Donor*> compatibleDonors;
    Node* cur = head;
    while (cur != nullptr) {
        if (cur->data.bloodType == bloodType) {
            compatibleDonors.push_back(&cur->data);
        }
        cur = cur->next;
    }
    return compatibleDonors;
}
void DonorList::DisplayAll() {
    Node* cur = head;
    while (cur != nullptr) {
        cout << cur->data.name << " | "
            << cur->data.bloodType << " | "
            << cur->data.age << endl;
        cur = cur->next;
    }
}




/*int main() {
    DonorList donors;
    RequestList requests;
    donors.LoadFromFile();
    requests.LoadFile();

    int choice;
    do {
        cout << "\n--- Donor System ---\n";
        cout << "1- Register\n2- Login\n3- Delete Account\n4- Update Account (after login)\n";
        cout << "5- Add Donation Request\n0- Exit\n";
        cin >> choice;

        if (choice == 1) {
            Donor d;
            cin.ignore();
            cout << "ID: "; getline(cin, d.id);
            cout << "Name: "; getline(cin, d.name);
            cout << "Mail: "; getline(cin, d.mail);
            cout << "Password: "; getline(cin, d.password);
            cout << "Age: "; cin >> d.age; cin.ignore();
            cout << "Gender: "; getline(cin, d.gender);
            cout << "Blood Type: "; getline(cin, d.bloodType);
            cout << "Diseases: "; getline(cin, d.diseaseList);
            cout << "Medications: "; getline(cin, d.medications);
            cout << "Latest Donation Date: "; getline(cin, d.latestDonationDate);

            donors.InsertDonor(d);
            donors.SaveToFile();
        }

        else if (choice == 2) {
            string mail, pass;
            cout << "Mail: "; cin >> mail;
            cout << "Password: "; cin >> pass;
            Donor* d = donors.SearchByMail(mail);
            if (d && d->password == pass) {
                cout << "Login Successful\n";
                char upd;
                cout << "Update account now? (y/n): "; cin >> upd;
                if (upd == 'y' || upd == 'Y') UpdateAccount(donors, d);
            }
            else cout << "Wrong mail or password\n";
        }

        else if (choice == 3) {
            string id; cout << "Enter ID to delete: "; cin >> id;
            if (donors.DeleteDonor(id)) cout << "Deleted\n"; else cout << "Not found\n";
            donors.SaveToFile();
        }


        else if (choice == 4) {
            string mail; cout << "Enter mail to update: "; cin >> mail;
            Donor* d = donors.SearchByMail(mail);
            UpdateAccount(donors, d);
        }

        else if (choice == 5) {
            DonationRequest req;
            cin.ignore();
            cout << "Patient Name: "; getline(cin, req.patientName);
            cout << "Blood Type: "; getline(cin, req.bloodType);
            cout << "Amount in  Litres: "; cin >> req.amount; cin.ignore();
            cout << "Contact Phone: "; getline(cin, req.phone);
            requests.AddRequest(req);
            requests.SaveFile();
        }

    } while (choice != 0);

    return 0;
}*/