#ifndef BloodUnit_h
#define BloodUnit_h
#include <unordered_map> //HashMap O(1) access
#include <deque> //Double-ended queue for FIFO
#include <string>
#include <iostream>
using namespace std;

class BloodUnit
{
private:
    string batch_id;
    float quantity;
    string donation_date;
    string expiry_date;

public:
    // Constructors
    BloodUnit();
    BloodUnit(string b_id, float qty, string d_date, string e_date);

    // Getters
    string getBatchID() const;
    float getQuantity() const;
    string getDonationDate() const;
    string getExpiryDate() const;

    // Setters
    void setBatchID(const string &b_id);
    void setQuantity(float qty);
    void setDonationDate(const string &d_date);
    void setExpiryDate(const string &e_date);

    // Input
    void inputBloodUnit();

    // Display
    void displayBloodUnit() const;
};

#endif