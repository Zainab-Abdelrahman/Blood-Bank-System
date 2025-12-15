#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>

#include "Donor.h"
#include "BloodStock.h"
#include "Search.h"
#include "Matching.h"
#include "Request.h"
#include "Recipient.h"

class Admin {
private:
    BloodStock stock;
    Search searchTree;

    // ===== Validation Helpers =====
    bool IsAgeValid(int age) const;
    bool IsDonationDateValid(const std::string& lastDonationDate) const;
    bool IsDiseaseSafe(const std::string& diseases) const;
    bool IsMedicationSafe(const std::string& medications) const;

public:
    Admin();

    // ================= DONOR =================
    bool ValidateDonor(const Donor& d) const;
    bool ValidateExistingDonorForDonation(const Donor& d) const;
    void AddDonor(DonorList& list, const Donor& d);
    void UpdateDonor(DonorList& list, const std::string& id, const Donor& updatedDonor);
    void DisplayAllDonors(DonorList& list);
    void DeleteDonor(DonorList& list, const std::string& id);

    // ================= BLOOD STOCK =================
    void AddBloodUnit(const std::string& type,
        float quantity,
        const std::string& donationDate,
        const std::string& expiryDate);

    void UpdateBloodUnit(const std::string& batchId,
        float newQuantity,
        const std::string& newExpiryDate);

    void RemoveBloodUnit(const std::string& type);
    void DisplayStock();
    bool SearchBatch(const string& batchId);

    // ================= RECIPIENT MANAGEMENT =================
    void AddRecipient(RecipientList& list, RecipientNode* recipient);
    void DisplayAllRecipients(RecipientList& list);
    void UpdateRecipient(RecipientList& list, const std::string& id,
        const std::string& newHospital, const std::string& newDoctor);
    void DeleteRecipient(RecipientList& list, const std::string& id);
    void SearchRecipientByEmail(RecipientList& list, const std::string& email);

    // ================= SEARCH =================
    void BuildSearchTree();
    void SearchByBloodType(const std::string& type) const;

    // ================= REQUEST =================
    void DisplayAllRequests();
    void DisplayDonationRequests();
    void UpdateRequestStatus(const std::string& requestId, const std::string& newStatus);
    void DeleteRequest(const std::string& requestId);

    // ================= MATCHING =================
    void RunMatching(DonorList& donorList);

    // ================= STATISTICS =================
    void DisplaySystemStatistics(DonorList& donorList, RecipientList& recipientList);
};

#endif

