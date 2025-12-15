#ifndef DONOR_H
#define DONOR_H

#include <string>
#include <vector>
using namespace std;

class Donor {
public:   
    string id;
    string name;
    string mail;
    string password;
    int age;
    string gender;
    string bloodType;
    string diseaseList;
    string medications;
    string latestDonationDate;

    Donor() {};
    Donor(string _id, string _name, string _mail, string _password,
        int _age, string _gender, string _bloodType,
        string _diseaseList, string _medications, string _latestDonationDate)
    {
        id = _id;
        name = _name;
        mail = _mail;
        password = _password;
        age = _age;
        gender = _gender;
        bloodType = _bloodType;
        diseaseList = _diseaseList;
        medications = _medications;
        latestDonationDate = _latestDonationDate;
    }
    
    

};

// Linked List Node
struct Node {
    Donor data;
    Node* next;
    Node(Donor d) : data(d), next(nullptr) {}
};

// Linked List class
class DonorList {
private:
    Node* head;

public:
    DonorList();
    void InsertDonor(Donor d);
    bool DeleteDonor(string id);
    Donor* SearchByMail(string mail);
    void UpdateDonor(Donor d);
    vector<Donor*> SearchByBloodType(const string& bloodType);

    void SaveToFile();
    void LoadFromFile();
    void DisplayAll();

};

// Donation Request
struct DonationRequest {
    string patientName;
    string bloodType;
    int amount;
    string phone;
};

// Linked List Node for requests
struct RequestNode {
    DonationRequest data;
    RequestNode* next;
    RequestNode(DonationRequest d) : data(d), next(nullptr) {}
};

class RequestList {
private:
    RequestNode* head;
public:
    RequestList();
    void AddRequest(DonationRequest d);

    void LoadFile();
    void SaveFile();
};

#endif  
