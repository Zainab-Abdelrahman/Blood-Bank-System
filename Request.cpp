#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib> 
#include <ctime>   
#include "Request.h"
#include "Recipient.h"
using namespace std;

Request::Request() : RecipientID(""), NeededBloodType(""), NeededQuantity(0), HospitalName(""), PriorityLevel(0) {
    srand(time(0));
    RequestID = "REQ" + to_string(rand() % 100000);
}

Request::Request(string r, string b, int q, string h, int priority) : RecipientID(r),
NeededBloodType(b), NeededQuantity(q), HospitalName(h), PriorityLevel(priority) {
    srand(time(0));
    RequestID = "REQ" + to_string(rand() % 100000);
}

void Request::SaveRequestsToFile(const Request& req) {
    ofstream file("Requests.txt", ios::app);
    if (file.is_open()) {
        file << req.getRequestID() << ","
            << req.getRecipientID() << ","
            << req.getNeededBloodType() << ","
            << req.getNeededQuantity() << ","
            << req.getPatientHospital() << ","
            << req.getPriorityLevel() << "\n";
        file.close();
        cout << req.getRequestID() << " - Request has been saved successfully\n";
    }
    else {
        cerr << "ERROR : Cannot open Requests.txt\n";
    }
}

bool Request::ConfirmHospital(std::string hospitalName) {
    if (hospitalName.empty()) {
        return false;
    }
    HospitalName = hospitalName;
    return true;
}

void Request::CreateRequest(RecipientNode& r) {
    RecipientID = r.id;
    NeededBloodType = r.bloodType;
    cout << "Confirming and processing new donation request\n";
    cout << "Enter Needed Quantity (ml): ";
    cin >> NeededQuantity;
    cout << "Enter Priority Level (1-10, 10 is highest): ";
    cin >> PriorityLevel;
    if (!ConfirmHospital(r.hospital)) {
        cerr << "ERROR : Enter a Hospital Name\n";
        return;
    }
    SaveRequestsToFile(*this);
    cout << "Matching system will start processing request with priority: " << PriorityLevel << ".\n";
}

vector<Request> Request::LoadRequestsFromFile() {
    vector<Request> requests;
    ifstream file("Requests.txt");
    if (!file.is_open()) {
        cerr << " ERROR: Could not open Requests.txt for reading.\n";
        return requests;
    }
    string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> seglist;
        while (std::getline(ss, segment, ',')) {
            seglist.push_back(segment);
        }
        if (seglist.size() == 6) {
            try {
                int quantity = std::stoi(seglist[3]);
                int priority = std::stoi(seglist[5]);
                Request loadedRequest(seglist[1], seglist[2], quantity, seglist[4], priority);
                loadedRequest.RequestID = seglist[0]; // Preserve original ID
                requests.push_back(loadedRequest);
            }
            catch (const std::exception& e) {
                cerr << " Warning: Data conversion failed (std::stoi) in line: " << line << ". Skipping. Error: " << e.what() << endl;
            }
        }
        else {
            cerr << " Warning: Incorrect number of fields in line: " << line << ". Skipping." << endl;
        }
    }
    file.close();
    cout << " Successfully loaded " << requests.size() << " requests from Requests.txt." << endl;
    return requests;
}

// إضافة دالة لحذف الطلبات
void Request::DeleteRequest(const string& requestID) {
    vector<Request> requests = LoadRequestsFromFile();
    ofstream file("Requests.txt", ios::trunc);
    
    if (!file.is_open()) {
        cerr << "ERROR: Cannot open Requests.txt for writing.\n";
        return;
    }
    
    bool found = false;
    for (const auto& req : requests) {
        if (req.getRequestID() != requestID) {
            file << req.getRequestID() << ","
                 << req.getRecipientID() << ","
                 << req.getNeededBloodType() << ","
                 << req.getNeededQuantity() << ","
                 << req.getPatientHospital() << ","
                 << req.getPriorityLevel() << "\n";
        } else {
            found = true;
        }
    }
    
    file.close();
    if (found) {
        cout << "Request " << requestID << " deleted successfully.\n";
    } else {
        cout << "Request " << requestID << " not found.\n";
    }
}