#ifndef REQUESTS_H
#define REQUESTS_H

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include "Recipient.h"
using namespace std;

class Request {
private:
    string RequestID;
    string RecipientID;
    string NeededBloodType;
    int NeededQuantity;
    string HospitalName;
    int PriorityLevel;

public:
    Request();
    Request(string r, string b, int q, string h, int priority);
    void CreateRequest(RecipientNode& r);
    bool ConfirmHospital(const string hospitalName);
    void SaveRequestsToFile(const Request& req);
    static vector<Request> LoadRequestsFromFile();
    void DeleteRequest(const string& requestID);
    int getPriorityLevel() const { return PriorityLevel; };
    string getRequestID() const { return RequestID; };
    string getRecipientID() const { return RecipientID; };
    string getNeededBloodType() const { return NeededBloodType; };
    int getNeededQuantity() const { return NeededQuantity; };
    string getPatientHospital() const { return HospitalName; };
};

struct CompareRequest {
    bool operator()(const Request a, const Request b) {
        return a.getPriorityLevel() < b.getPriorityLevel();
    }
};

#endif
