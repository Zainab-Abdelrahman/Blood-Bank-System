#include "Matching.h"
#include "Request.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <queue>
using namespace std;

const std::map<std::string, std::vector<std::string>> Matching::compatibilityMap = {
    {"A+", {"A+", "A-", "O+", "O-"}},
    {"A-", {"A-", "O-"}},
    {"B+", {"B+", "B-", "O+", "O-"}},
    {"B-", {"B-", "O-"}},
    {"AB+", {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"}},
    {"AB-", {"AB-", "A-", "B-", "O-"}},
    {"O+", {"O+", "O-"}},
    {"O-", {"O-"}}
};

std::vector<std::string> Matching::CheckCompatibility(const std::string& recipientBloodType) {
    auto it = compatibilityMap.find(recipientBloodType);
    if (it != compatibilityMap.end()) {
        return it->second;
    }
    else {
        cerr << "ERROR: Invalid or unsupported blood type requested: " << recipientBloodType << endl;
        return {};
    }
};

void Matching::MatchDonorWithRecipient(BloodStock& stockList, DonorList& donorList) {
    vector<Request> requests = Request::LoadRequestsFromFile();
    if (requests.empty()) {
        cout << "No requests loaded. Matching process skipped." << endl;
        return;
    }
    priority_queue<Request, std::vector<Request>, CompareRequest> priorityQueue(requests.begin(), requests.end());
    cout << " Starting Matching Process (Total Requests: " << priorityQueue.size() << "\n";
    while (!priorityQueue.empty()) {
        Request highPriorityRequest = priorityQueue.top();
        priorityQueue.pop();
        string neededType = highPriorityRequest.getNeededBloodType();
        int neededQuantity = highPriorityRequest.getNeededQuantity();
        cout << " Processing Request " << highPriorityRequest.getRequestID()
            << " for " << neededType << " (Qty: " << neededQuantity << "ml) at Priority: "
            << highPriorityRequest.getPriorityLevel() << endl;
        vector<std::string> compatibleTypes = Matching::CheckCompatibility(neededType);
        bool matchFound = false;

        cout << "   - Checking Stock...\n";
        for (const string& type : compatibleTypes) {
            float availableQuantity = stockList.getTotalQuantity(type);
            if (availableQuantity >= neededQuantity) {
                cout << " Stock Match found with Type " << type << ". Fulfilling request.\n";
                if (stockList.removeOldestUnit(type)) {
                    matchFound = true;
                    break;
                }

            }
        }
        if (!matchFound) {
            cout << "Stock insufficient. Checking Donors...\n";
            for (const std::string& type : compatibleTypes) {
                vector<Donor*> availableDonors = donorList.SearchByBloodType(type);
                if (!availableDonors.empty()) {
                    cout << "Donor Match found with Type " << type << ". Contacting donor.\n";
                    matchFound = true;
                    break;
                }
            }
        }
        if (!matchFound) {
            cout << "No match found in stock or active donors. Request remains pending.\n";
        }
    }
    cout << "\n--- ✅ Matching Process Finished ---\n";
};