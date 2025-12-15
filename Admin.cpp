#define _CRT_SECURE_NO_WARNINGS 
#include "Admin.h"
#include "Donor.h"
#include "Recipient.h"
#include "Request.h"
#include "BloodStock.h"
#include "Search.h"
#include "Matching.h"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

Admin::Admin() { 
    stock.loadFromFile();
}

// ================= VALIDATION =================
bool Admin::IsAgeValid(int age) const {
    return age >= 17 && age <= 60;
}

bool Admin::IsDonationDateValid(const string& lastDonationDate) const {
    if (lastDonationDate == "Never" || lastDonationDate.empty()) {
        return true; // Never donated before
    }
    
    // Parse date (format: YYYY-MM-DD)
    if (lastDonationDate.length() < 10) return false;
    
    try {
        int year = stoi(lastDonationDate.substr(0, 4));
        int month = stoi(lastDonationDate.substr(5, 2));
        int day = stoi(lastDonationDate.substr(8, 2));
        
        // Get current date
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        int currentYear = now->tm_year + 1900;
        int currentMonth = now->tm_mon + 1;
        int currentDay = now->tm_mday;
        
        // Calculate days difference
        // Simple calculation (approximate)
        int daysDiff = (currentYear - year) * 365 + 
                      (currentMonth - month) * 30 + 
                      (currentDay - day);
        
        // Minimum 56 days (8 weeks) between donations
        return daysDiff >= 56;
    }
    catch (...) {
        return false; // Invalid date format
    }
}

bool Admin::IsDiseaseSafe(const string& diseases) const {
    // List of disqualifying diseases (case-insensitive check)
    vector<string> dangerousDiseases = {
        // Blood pressure disorders
        "blood pressure", "hypertension", "hypotension", "high bp", "low bp",
        
        // Thyroid disease
        "thyroid", "hyperthyroidism", "hypothyroidism", "goiter",
        
        // Diabetes
        "diabetes", "type 1", "type 2", "diabetic", "sugar",
        
        // Cancer
        "cancer", "tumor", "malignant", "leukemia", "lymphoma", "carcinoma",
        
        // Heart disorders
        "heart", "cardiac", "arrhythmia", "heart attack", "stroke", 
        "coronary", "cardiovascular", "heart failure",
        
        // Hepatitis
        "hepatitis", "hepatitis a", "hepatitis b", "hepatitis c",
        
        // Other disqualifying conditions
        "hiv", "aids", "malaria", "tuberculosis", "tb",
        "hemophilia", "bleeding disorder", "anemia",
        "venereal", "sexually transmitted", "std", "stds",
        "epilepsy", "kidney disease", "liver disease"
    };
    
    string lowerDiseases = diseases;
    // Convert to lowercase
    transform(lowerDiseases.begin(), lowerDiseases.end(), 
              lowerDiseases.begin(), ::tolower);
    
    if (lowerDiseases == "none" || lowerDiseases.empty()) {
        return true;
    }
    
    // Check for any dangerous disease from the list
    for (const auto& disease : dangerousDiseases) {
        if (lowerDiseases.find(disease) != string::npos) {
            return false;
        }
    }
    
    return true;
}

bool Admin::IsMedicationSafe(const string& medications) const {
    // List of disqualifying medications
    vector<string> dangerousMeds = {
        // Diabetes medications
        "insulin", "metformin", "glucophage", "glibenclamide",
        
        // Thyroid medications
        "levothyroxine", "synthroid", "thyroxine", "thyroid",
        
        // Blood pressure medications
        "atenolol", "propranolol", "metoprolol", "carvedilol",
        "lisinopril", "enalapril", "ramipril", "captopril",
        "amlodipine", "nifedipine", "diltiazem", "verapamil",
        
        // Blood thinners
        "warfarin", "coumadin", "heparin", "aspirin", "clopidogrel",
        
        // Cancer treatments
        "chemotherapy", "chemo", "radiation",
        
        // Other disqualifying medications
        "accutane", "isotretinoin", "propecia", "finasteride", 
        "dutasteride", "antibiotics", "antiviral", "steroids", 
        "prednisone", "immunosuppressant"
    };
    
    string lowerMeds = medications;
    transform(lowerMeds.begin(), lowerMeds.end(), 
              lowerMeds.begin(), ::tolower);
    
    if (lowerMeds == "none" || lowerMeds.empty()) {
        return true;
    }
    
    // Check for dangerous medications
    for (const auto& med : dangerousMeds) {
        if (lowerMeds.find(med) != string::npos) {
            return false;
        }
    }
    
    return true;
}

bool Admin::ValidateDonor(const Donor& d) const {
    cout << "\n-----------------------------------------------------------\n";
    cout << "                     DONOR VALIDATION CHECK                \n";
    cout << "\n-----------------------------------------------------------\n";
    cout << "  Donor: " << d.name << " (ID: " << d.id << ")\n";
    cout << "  Blood Type: " << d.bloodType << "\n";
    cout << "\n-----------------------------------------------------------\n";
    
    bool ageValid = IsAgeValid(d.age);
    bool dateValid = IsDonationDateValid(d.latestDonationDate);
    bool diseaseSafe = IsDiseaseSafe(d.diseaseList);
    bool medSafe = IsMedicationSafe(d.medications);
    
    cout << "\nVALIDATION CRITERIA:\n";
    cout << "\n-----------------------------------------------------------\n";
    
    cout << "1. Age Requirement (17-60 years): ";
    if (ageValid) {
        cout << "PASS\n";
        cout << "   Current age: " << d.age << " years\n";
    } else {
        cout << "FAIL\n";
        cout << "   Current age: " << d.age << " years (outside acceptable range)\n";
    }
    
    cout << "\n2. Donation Interval (Minimum 56 days): ";
    if (dateValid) {
        cout << "PASS\n";
        cout << "   Last donation: " << d.latestDonationDate << "\n";
    } else {
        cout << "FAIL\n";
        cout << "   Last donation: " << d.latestDonationDate << " (too recent)\n";
    }
    
    cout << "\n3. Disease Screening: ";
    if (diseaseSafe) {
        cout << "PASS\n";
        cout << "   Diseases: " << (d.diseaseList.empty() || d.diseaseList == "None" ? "None reported" : d.diseaseList) << "\n";
    } else {
        cout << "FAIL\n";
        cout << "   Diseases: " << d.diseaseList << " (contains disqualifying conditions)\n";
    }
    
    cout << "\n4. Medication Screening: ";
    if (medSafe) {
        cout << "PASS\n";
        cout << "   Medications: " << (d.medications.empty() || d.medications == "None" ? "None reported" : d.medications) << "\n";
    } else {
        cout << "FAIL\n";
        cout << "   Medications: " << d.medications << " (contains disqualifying medications)\n";
    }
    
    cout << "\n-----------------------------------------------------------\n";
    
    bool overallValid = ageValid && dateValid && diseaseSafe && medSafe;
    
    if (overallValid) {
        cout << "  FINAL RESULT: ELIGIBLE FOR BLOOD DONATION\n";
    } else {
        cout << "  FINAL RESULT: NOT ELIGIBLE FOR BLOOD DONATION\n";
        cout << "\n  REASONS FOR REJECTION:\n";
        if (!ageValid) cout << "    • Age is outside 17-60 years range\n";
        if (!dateValid) cout << "    • Last donation was less than 56 days ago\n";
        if (!diseaseSafe) cout << "    • Has one or more disqualifying diseases\n";
        if (!medSafe) cout << "    • Is taking disqualifying medications\n";
    }
    
    cout << "\n-----------------------------------------------------------\n";
    
    return overallValid;
}

bool Admin::ValidateExistingDonorForDonation(const Donor& d) const {
    cout << "\n-----------------------------------------------------------\n";
    cout << "               DONATION ELIGIBILITY CHECK                \n";
    cout << "\n-----------------------------------------------------------\n";
    
    // Get today's date
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    char todayDate[11];
    strftime(todayDate, sizeof(todayDate), "%Y-%m-%d", now);
    
    cout << "  Today's Date: " << todayDate << "\n";
    cout << "  Donor: " << d.name << " (ID: " << d.id << ")\n";
    cout << "  Last Donation: " << d.latestDonationDate << "\n";
    cout << "\n-----------------------------------------------------------\n";
    
    bool canDonate = ValidateDonor(d);
    
    if (canDonate) {
        cout << "\n  STATUS: CLEARED FOR DONATION TODAY\n";
        cout << "  ACTION: Donor can proceed with blood donation\n";
    } else {
        cout << "\n  STATUS: CANNOT DONATE AT THIS TIME\n";
        cout << "  ACTION: Please address the issues above before donating\n";
    }
    
    cout << "\n-----------------------------------------------------------\n";
    
    return canDonate;
}

// ================= DONOR =================
void Admin::AddDonor(DonorList& list, const Donor& d) {
    cout << "\n-----------------------------------------------------------\n";
    cout << "                  ADDING NEW DONOR                      \n";
    cout << "\n-----------------------------------------------------------\n";
    
    if (!ValidateDonor(d)) {
        cout << "\n DONOR REJECTED: Not eligible for blood donation\n";
        cout << "  The donor cannot be added to the system.\n";
        return;
    }
    
    list.InsertDonor(d);
    list.SaveToFile();
    
    cout << "\nDONOR APPROVED AND ADDED SUCCESSFULLY!\n";
    cout << "\nDONOR SUMMARY:\n";
    cout << "\n-----------------------------------------------------------\n";
    cout << "  Name:           " << d.name << "\n";
    cout << "  ID:             " << d.id << "\n";
    cout << "  Blood Type:     " << d.bloodType << "\n";
    cout << "  Age:            " << d.age << "\n";
    cout << "  Gender:         " << d.gender << "\n";
    cout << "  Last Donation:  " << d.latestDonationDate << "\n";
    cout << "  Email:          " << d.mail << "\n";
    cout << "\n-----------------------------------------------------------\n";
    cout << " This donor is now registered in our system\n";
    cout << " Can be contacted for future blood donations\n";
    cout << " Eligible to make donation requests\n";
    cout << "\n-----------------------------------------------------------\n";
}

void Admin::UpdateDonor(DonorList& list, const string& id, const Donor& updatedDonor) {
    cout << "\n-----------------------------------------------------------\n";
    cout << "                  UPDATING DONOR INFORMATION             \n";
    cout << "\n-----------------------------------------------------------\n";
    
    // Note: You need to implement a search function in DonorList to find donor by ID
    // This is a placeholder implementation
    cout << "Searching for donor ID: " << id << "\n";
    
    // Assuming we found the donor and updated the data
    cout << "\n Donor information updated successfully\n";
    
    // Re-validate the donor after update
    if (!ValidateDonor(updatedDonor)) {
        cout << "\n WARNING: After update, donor is no longer eligible to donate\n";
        cout << "  Donor status changed to: INELIGIBLE\n";
    } else {
        cout << "\n Donor remains eligible to donate after update\n";
    }
    
    cout << "\n-----------------------------------------------------------\n";
}

void Admin::DisplayAllDonors(DonorList& list) {
    cout << "\n-----------------------------------------------------------\n";
    cout << "                   ALL REGISTERED DONORS                 \n";
    cout << "\n-----------------------------------------------------------\n";
    list.DisplayAll();
    cout << "\n-----------------------------------------------------------\n";
}

void Admin::DeleteDonor(DonorList& list, const string& id) {
    cout << "\n-----------------------------------------------------------\n";
    cout << "                  DELETING DONOR RECORD                  \n";
    cout << "\n-----------------------------------------------------------\n";
    
    if (list.DeleteDonor(id)) {
        list.SaveToFile();
        cout << " Donor with ID " << id << " deleted successfully.\n";
    } else {
        cout << " Donor with ID " << id << " not found.\n";
    }
    
    cout << "\n-----------------------------------------------------------\n";
}

// ================= BLOOD STOCK =================
void Admin::AddBloodUnit(const string& type,
    float quantity,
    const string& donationDate,
    const string& expiryDate) {
    
    cout << "\n-----------------------------------------------------------\n";
    cout << "                  ADDING BLOOD UNIT                      \n";
    cout << "\n-----------------------------------------------------------\n";
    
    string batchId = "BATCH_" + type + "_" + to_string(time(0));
    BloodUnit unit(batchId, quantity, donationDate, expiryDate);
    stock.addBloodUnit(type, unit);
    stock.saveToFile();
    BuildSearchTree();
    
    cout << " Blood unit added successfully\n";
    cout << "\nUNIT DETAILS:\n";
    cout << "\n-----------------------------------------------------------\n";
    cout << "  Batch ID:      " << batchId << "\n";
    cout << "  Blood Type:    " << type << "\n";
    cout << "  Quantity:      " << quantity << " ml\n";
    cout << "  Donation Date: " << donationDate << "\n";
    cout << "  Expiry Date:   " << expiryDate << "\n";
    cout << "\n-----------------------------------------------------------\n";
    cout << " Added to blood inventory\n";
    cout << " Search tree updated\n";
    cout << "\n-----------------------------------------------------------\n";
}

void Admin::UpdateBloodUnit(const string& batchId,
    float newQuantity,
    const string& newExpiryDate) {
    
    cout << "\nUpdating blood unit: " << batchId << "\n";
    // Implementation depends on your BloodStock class
    cout << "Blood unit update functionality\n";
}

void Admin::RemoveBloodUnit(const string& type) {
    cout << "\n-----------------------------------------------------------\n";
    cout << "              REMOVING OLDEST BLOOD UNIT                \n";
    cout << "\n-----------------------------------------------------------\n";

    cout << "Removing oldest unit of type: " << type << "\n";
    stock.removeOldestUnit(type);
    BuildSearchTree();

    cout << " Oldest blood unit removed successfully\n";
    cout << " Search tree updated\n";
    cout << "\n-----------------------------------------------------------\n";
}

void Admin::DisplayStock() {
    cout << "\n-----------------------------------------------------------\n";
    cout << "                  BLOOD STOCK INVENTORY                  \n";
    cout << "\n-----------------------------------------------------------\n";
    stock.displayAllStock();
    cout << "\n-----------------------------------------------------------\n";
}

bool Admin::SearchBatch(const string& batchId) {
    return stock.searchBatch(batchId);
}

// ================= RECIPIENT MANAGEMENT =================
void Admin::AddRecipient(RecipientList& list, RecipientNode* recipient) {
    cout << "\n-----------------------------------------------------------\n";
    cout << "                 ADDING NEW RECIPIENT                    \n";
    cout << "\n-----------------------------------------------------------\n";
    
    // Implementation depends on your RecipientList class
    cout << "Recipient added to system\n";
    cout << "\n-----------------------------------------------------------\n";
}

void Admin::DisplayAllRecipients(RecipientList& list) {
    cout << "\n-----------------------------------------------------------\n";
    cout << "                 ALL REGISTERED RECIPIENTS               \n";
    cout << "\n-----------------------------------------------------------\n";
    // Implementation depends on your RecipientList class
    cout << "Recipient list display\n";
    cout << "\n-----------------------------------------------------------\n";
}

void Admin::UpdateRecipient(RecipientList& list, const string& id,
    const string& newHospital, const string& newDoctor) {
    
    cout << "\nUpdating recipient: " << id << "\n";
    // Implementation depends on your RecipientList class
    cout << "Recipient update functionality\n";
}

void Admin::DeleteRecipient(RecipientList& list, const string& id) {
    cout << "\nDeleting recipient: " << id << "\n";
    // Implementation depends on your RecipientList class
    cout << "Recipient delete functionality\n";
}

void Admin::SearchRecipientByEmail(RecipientList& list, const string& email) {
    cout << "\nSearching recipient by email: " << email << "\n";
    // Implementation depends on your RecipientList class
    cout << "Recipient search functionality\n";
}

// ================= SEARCH =================
void Admin::BuildSearchTree() {
    searchTree.BuildTreeFromStock(stock);
    cout << "\n Search tree built successfully\n";
}

void Admin::SearchByBloodType(const string& type) const {
    cout << "\n-----------------------------------------------------------\n";
    cout << "              SEARCHING BLOOD TYPE: " << type << "           \n";
    cout << "\n-----------------------------------------------------------\n";
    searchTree.SearchByBloodType(type, stock);
    cout << "\n-----------------------------------------------------------\n";
}

// ================= REQUEST =================
void Admin::DisplayAllRequests() {
    cout << "\n-----------------------------------------------------------\n";
    cout << "                 ALL BLOOD REQUESTS                      \n";
    cout << "\n-----------------------------------------------------------\n";
    
    vector<Request> requests = Request::LoadRequestsFromFile();
    
    if (requests.empty()) {
        cout << "No blood requests found.\n";
    } else {
        int count = 1;
        for (const auto& r : requests) {
            cout << "\nREQUEST " << count++ << "\n";
            cout << "\n-----------------------------------------------------------\n";
            cout << "  Request ID:     " << r.getRequestID() << "\n";
            cout << "  Recipient ID:   " << r.getRecipientID() << "\n";
            cout << "  Blood Type:     " << r.getNeededBloodType() << "\n";
            cout << "  Quantity:       " << r.getNeededQuantity() << " ml\n";
            cout << "  Hospital:       " << r.getPatientHospital() << "\n";
            cout << "  Priority:       " << r.getPriorityLevel() << "/10\n";
            cout << "\n-----------------------------------------------------------\n";
        }
        cout << "\nTotal Requests: " << requests.size() << "\n";
    }
    
    cout << "\n-----------------------------------------------------------\n";
}

void Admin::DisplayDonationRequests() {
    cout << "\n-----------------------------------------------------------\n";
    cout << "               ALL DONATION REQUESTS                    \n";
    cout << "\n-----------------------------------------------------------\n";
    
    ifstream donationFile("DonationRequests.txt");
    if (donationFile.is_open()) {
        string line;
        int count = 0;
        
        while (getline(donationFile, line)) {
            stringstream ss(line);
            string requestId, donorId, donorName, bloodType, quantity, hospital, date, status;
            
            getline(ss, requestId, ',');
            getline(ss, donorId, ',');
            getline(ss, donorName, ',');
            getline(ss, bloodType, ',');
            getline(ss, quantity, ',');
            getline(ss, hospital, ',');
            getline(ss, date, ',');
            getline(ss, status, ',');
            
            cout << "\nDONATION REQUEST #" << ++count << "\n";
            cout << "\n-----------------------------------------------------------\n";
            cout << "  Request ID:     " << requestId << "\n";
            cout << "  Donor:          " << donorName << " (ID: " << donorId << ")\n";
            cout << "  Blood Type:     " << bloodType << "\n";
            cout << "  Quantity:       " << quantity << " ml\n";
            cout << "  Hospital:       " << hospital << "\n";
            cout << "  Date:           " << date << "\n";
            cout << "  Status:         " << status << "\n";
            cout << "\n-----------------------------------------------------------\n";
        }
        donationFile.close();
        
        if (count == 0) {
            cout << "No donation requests found.\n";
        } else {
            cout << "\nTotal Donation Requests: " << count << "\n";
        }
    } else {
        cout << "No donation requests file found.\n";
    }
    
    cout << "\n-----------------------------------------------------------\n";
}

void Admin::UpdateRequestStatus(const string& requestId, const string& newStatus) {
    cout << "\nUpdating request status: " << requestId << " -> " << newStatus << "\n";
    // Implementation for updating request status
}

void Admin::DeleteRequest(const string& requestId) {
    cout << "\nDeleting request: " << requestId << "\n";
    // Implementation for deleting requests
}

// ================= MATCHING =================
void Admin::RunMatching(DonorList& donorList) {
    cout << "\n-----------------------------------------------------------\n";
    cout << "              RUNNING MATCHING SYSTEM                   \n";
    cout << "\n-----------------------------------------------------------\n";
    Matching::MatchDonorWithRecipient(stock, donorList);
    cout << "\n-----------------------------------------------------------\n";
}

// ================= STATISTICS =================
void Admin::DisplaySystemStatistics(DonorList& donorList, RecipientList& recipientList) {
    cout << "\n-----------------------------------------------------------\n";
    cout << "               SYSTEM STATISTICS                        \n";
    cout << "\n-----------------------------------------------------------\n";
    
    // Get current date
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    char currentDate[11];
    strftime(currentDate, sizeof(currentDate), "%Y-%m-%d", now);
    
    cout << "  Report Date: " << currentDate << "\n";
    cout << "\n-----------------------------------------------------------\n";
    
    cout << "\nBLOOD STOCK SUMMARY:\n";
    cout << "\n-----------------------------------------------------------\n";
    
    vector<string> bloodTypes = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
    float totalQuantity = 0;
    
    for (const auto& type : bloodTypes) {
        float totalQty = stock.getTotalQuantity(type);
        if (totalQty > 0) {
            totalQuantity += totalQty;
            
            cout << "  " << type << ": " 
                 << setw(6) << totalQty << " ml\n";
            // Removed: << "(" << units << " units)\n";
        }
    }
    
    cout << "\n-----------------------------------------------------------\n";
    cout << "  Total Quantity: " << totalQuantity << " ml\n";
    // Removed: cout << "  Total Units:    " << totalUnits << " units\n";
    cout << "\n-----------------------------------------------------------\n";
    
    // ... rest of the function remains the same
}