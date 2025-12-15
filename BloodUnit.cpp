#include "BloodUnit.h"
#include <iostream>
using namespace std;

BloodUnit::BloodUnit()
{
    batch_id = "";
    quantity = 0.0;
    donation_date = "";
    expiry_date = "";
}

BloodUnit::BloodUnit(string b_id, float qty, string d_date, string e_date)
{
    batch_id = b_id;
    quantity = qty;
    donation_date = d_date;
    expiry_date = e_date;
}

// Getters
string BloodUnit::getBatchID() const { return batch_id; }
float BloodUnit::getQuantity() const { return quantity; }
string BloodUnit::getDonationDate() const { return donation_date; }
string BloodUnit::getExpiryDate() const { return expiry_date; }

// Setters
void BloodUnit::setBatchID(const string& b_id) { batch_id = b_id; }
void BloodUnit::setQuantity(float qty) { quantity = qty; }
void BloodUnit::setDonationDate(const string& d_date) { donation_date = d_date; }
void BloodUnit::setExpiryDate(const string& e_date) { expiry_date = e_date; }

// Input
void BloodUnit::inputBloodUnit()
{
    cout << "\n=== Enter Blood Unit Info ===\n";

    cout << "Enter Batch ID: ";
    cin >> batch_id;

    cout << "Enter Quantity (ml): ";
    cin >> quantity;

    cout << "Enter Donation Date (YYYY-MM-DD): ";
    cin >> donation_date;

    cout << "Enter Expiry Date (YYYY-MM-DD): ";
    cin >> expiry_date;

    cout << "\nBlood unit data saved successfully.\n";
}

// Display
void BloodUnit::displayBloodUnit() const
{
    cout << "Batch ID: " << batch_id;
    cout << " | Quantity: " << quantity << " ml";
    cout << " | Donation Date: " << donation_date;
    cout << " | Expiry Date: " << expiry_date;
}