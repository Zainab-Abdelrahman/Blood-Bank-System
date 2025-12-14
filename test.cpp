#include <iostream>
#include <string>
#include <unordered_map>
#include <deque>
#include <fstream>
using namespace std;

// ---------------- BloodUnit Class ----------------
class BloodUnit
{
private:
    string batch_id;
    float quantity;
    string donation_date;
    string expiry_date;

public:
    BloodUnit()
    {
        batch_id = "";
        quantity = 0.0;
        donation_date = "";
        expiry_date = "";
    }

    BloodUnit(string b_id, float qty, string d_date, string e_date)
    {
        batch_id = b_id;
        quantity = qty;
        donation_date = d_date;
        expiry_date = e_date;
    }

    // Getters
    string getBatchID() const { return batch_id; }
    float getQuantity() const { return quantity; }
    string getDonationDate() const { return donation_date; }
    string getExpiryDate() const { return expiry_date; }

    // Setters
    void setBatchID(const string &b_id) { batch_id = b_id; }
    void setQuantity(float qty) { quantity = qty; }
    void setDonationDate(const string &d_date) { donation_date = d_date; }
    void setExpiryDate(const string &e_date) { expiry_date = e_date; }

    // Input
    void inputBloodUnit()
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
    void displayBloodUnit() const
    {
        cout << "Batch ID: " << batch_id
             << " | Quantity: " << quantity << " ml"
             << " | Donation Date: " << donation_date
             << " | Expiry Date: " << expiry_date;
    }
};

// ---------------- BloodStock Class ----------------
class BloodStock
{
private:
    unordered_map<string, deque<BloodUnit>> stock;

public:
    BloodStock() {}

    void addBloodUnit(const string &bloodType, const BloodUnit &unit)
    {
        stock[bloodType].push_back(unit);
        cout << "\nBlood unit added to stock successfully.\n";
    }

    bool removeOldestUnit(const string &bloodType)
    {
        if (stock.find(bloodType) == stock.end() || stock[bloodType].empty())
        {
            cout << "\nNo units available to remove.\n";
            return false;
        }
        stock[bloodType].pop_front();
        cout << "\nOldest unit removed.\n";
        return true;
    }

    float getTotalQuantity(const string &bloodType) const
    {
        if (stock.find(bloodType) == stock.end())
            return 0.0;
        float total = 0;
        for (const auto &unit : stock.at(bloodType))
            total += unit.getQuantity();
        return total;
    }

    void displayBloodType(const string &bloodType) const
    {
        if (stock.find(bloodType) == stock.end() || stock.at(bloodType).empty())
        {
            cout << "\nNo stock available for blood type: " << bloodType << endl;
            return;
        }
        cout << "\n=== Blood Stock for Type " << bloodType << " ===\n";
        for (const auto &unit : stock.at(bloodType))
        {
            unit.displayBloodUnit();
            cout << endl;
        }
        cout << "Total Quantity: " << getTotalQuantity(bloodType) << " ml\n";
    }

    void displayAllStock() const
    {
        if (stock.empty())
        {
            cout << "\nNo blood stock available.\n";
            return;
        }
        cout << "\n===== ALL BLOOD STOCK =====\n";
        for (const auto &pair : stock)
        {
            cout << "\n>>> Blood Type: " << pair.first << endl;
            for (const auto &unit : pair.second)
            {
                unit.displayBloodUnit();
                cout << endl;
            }
            cout << "Total: " << getTotalQuantity(pair.first) << " ml\n";
        }
    }

    bool searchBatch(const string &batch_id) const
    {
        for (const auto &pair : stock)
        {
            for (const auto &unit : pair.second)
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

    void saveToFile(const string &filename = "BloodStock.txt") const
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cout << "\nError opening file for saving.\n";
            return;
        }
        for (const auto &pair : stock)
        {
            for (const auto &unit : pair.second)
            {
                file << pair.first << " "
                     << unit.getBatchID() << " "
                     << unit.getQuantity() << " "
                     << unit.getDonationDate() << " "
                     << unit.getExpiryDate() << "\n";
            }
        }
        file.close();
        cout << "\nStock saved successfully to file.\n";
    }

    void loadFromFile(const string &filename = "BloodStock.txt")
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
};

// ---------------- Main for Testing ----------------
int main()
{
    BloodStock myStock;
    myStock.loadFromFile();

    int choice;
    do
    {
        cout << "\n--- Blood Stock Menu ---\n";
        cout << "1. Add Blood Unit\n";
        cout << "2. Display Blood Type\n";
        cout << "3. Display All Stock\n";
        cout << "4. Search Batch ID\n";
        cout << "5. Remove Oldest Unit\n";
        cout << "6. Save & Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string bloodType;
            cout << "Enter Blood Type (e.g., A+, O-): ";
            cin >> bloodType;
            BloodUnit unit;
            unit.inputBloodUnit();
            myStock.addBloodUnit(bloodType, unit);
            break;
        }
        case 2:
        {
            string bloodType;
            cout << "Enter Blood Type to Display: ";
            cin >> bloodType;
            myStock.displayBloodType(bloodType);
            break;
        }
        case 3:
            myStock.displayAllStock();
            break;
        case 4:
        {
            string batch;
            cout << "Enter Batch ID to Search: ";
            cin >> batch;
            myStock.searchBatch(batch);
            break;
        }
        case 5:
        {
            string bloodType;
            cout << "Enter Blood Type to Remove Oldest Unit: ";
            cin >> bloodType;
            myStock.removeOldestUnit(bloodType);
            break;
        }
        case 6:
            myStock.saveToFile();
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}