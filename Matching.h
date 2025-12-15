#pragma once
#ifndef MATCHING_H
#define MATCHING_H

#include <string>
#include <vector>
#include <map>
#include "Request.h"
#include "BloodStock.h"
#include "Donor.h"      
using namespace std;

class Matching {
private:
    static const map<string, vector<string>> compatibilityMap;

public:
    static vector<string> CheckCompatibility(const string& recipientBloodType);
   static void MatchDonorWithRecipient(BloodStock& stockList, DonorList& donorList);
};

#endif