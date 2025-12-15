#include "BloodStock.h"
#include "BloodUnit.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <deque>
#include <iomanip>
#include <fstream>
using namespace std;

BloodStock::BloodStock() {}

// Add blood unit to the stock
void BloodStock::addBloodUnit(const string& bloodType, const BloodUnit& unit)
{
    stock[bloodType].push_back(unit);
    cout << "\nBlood unit added to stock successfully.\n";
}

// Remove oldest unit (FIFO)
bool BloodStock::removeOldestUnit(const string& bloodType)
{
    if (stock.find(bloodType) == stock.end() || stock[bloodType].empty())
    {
        cout << "\nNo units available to remove.\n";
        return false;
    }

    stock[bloodType].pop_front();
    saveToFile();
    cout << "\nOldest unit removed.\n";
    return true;
}


// Get total quantity of a blood type
float BloodStock::getTotalQuantity(const string& bloodType) const
{
    if (stock.find(bloodType) == stock.end())
        return 0.0;

    float total = 0;
    for (const auto& unit : stock.at(bloodType))
        total += unit.getQuantity();

    return total;
}

// Display all units of a specific blood type
void BloodStock::displayBloodType(const string& bloodType) const
{
    if (stock.find(bloodType) == stock.end() || stock.at(bloodType).empty())
    {
        cout << "\nNo stock available for blood type: " << bloodType << endl;
        return;
    }

    cout << "\n=== Blood Stock for Type " << bloodType << " ===\n";

    for (const auto& unit : stock.at(bloodType))
    {
        unit.displayBloodUnit();
        cout << endl;
    }

    cout << "\nTotal Quantity: " << getTotalQuantity(bloodType) << " ml\n";
}

// Display ENTIRE stock (all blood types)
void BloodStock::displayAllStock() const
{
    if (stock.empty())
    {
        cout << "\nNo blood stock available.\n";
        return;
    }

    cout << "\n===== ALL BLOOD STOCK =====\n";

    for (const auto& pair : stock)
    {
        cout << "\n>>> Blood Type: " << pair.first << endl;
        for (const auto& unit : pair.second)
        {
            unit.displayBloodUnit();
            cout << endl;
        }
        cout << "Total: " << getTotalQuantity(pair.first) << " ml\n";
    }
}

// Search for batch ID in all blood types
bool BloodStock::searchBatch(const string& batch_id) const
{
    for (const auto& pair : stock)
    {
        for (const auto& unit : pair.second)
        {
            if (unit.getBatchID() == batch_id)
            {
                cout << "\nBatch Found in Blood Type: " << pair.first << endl;
                unit.displayBloodUnit();
                cout << endl;
                return true;
            }
        }
    }

    cout << "\nBatch ID not found.\n";
    return false;
}

void BloodStock::saveToFile(const string& filename) const
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cout << "\nError opening file for saving.\n";
        return;
    }

    for (const auto& pair : stock)
    {
        string bloodType = pair.first;

        for (const auto& unit : pair.second)
        {
            file << bloodType << " "
                << unit.getBatchID() << " "
                << unit.getQuantity() << " "
                << unit.getDonationDate() << " "
                << unit.getExpiryDate() << "\n";
        }
    }

    file.close();
    cout << "\nStock saved successfully to file.\n";
}

void BloodStock::loadFromFile(const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "\nNo stock file found. Starting fresh.\n";
        return;
    }

    stock.clear();

    string bloodType, batch_id, donation_date, expiry_date;
    float quantity;

    while (file >> bloodType >> batch_id >> quantity >> donation_date >> expiry_date)
    {
        BloodUnit unit(batch_id, quantity, donation_date, expiry_date);
        stock[bloodType].push_back(unit);
    }

    file.close();
    cout << "\nStock loaded successfully.\n";
}


bool BloodStock::reduceQuantity(const string& type, float qty) 
{
    if (stock.find(type) == stock.end() || stock[type].empty()) return false;

    for (auto& unit : stock[type])
     {
        if (unit.getQuantity() >= qty)
         {
            unit.setQuantity(unit.getQuantity() - qty);
            if (unit.getQuantity() <= 0)
             {
                stock[type].pop_front(); 
            }
            saveToFile();
            return true;
        }
    }
    return false; 
}