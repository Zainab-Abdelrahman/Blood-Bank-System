#include "Search.h"
#include <iostream>
#include <set>
#include<vector>

using namespace std;

Search::Search() {}

// Build tree from stock
void Search::BuildTreeFromStock(const BloodStock& stock)
{
    tree.clear();

    // Extract all blood types from BloodStock
    // BloodStock::displayAllStock prints, but we want keys
    // solution: we rebuild types using getTotalQuantity for each known type
    // instead, we scan possible valid blood types:
    vector<string> types = {
        "A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"
    };

    for (const string& type : types)
    {
        if (stock.getTotalQuantity(type) > 0)
            tree[type] = true;
    }

    cout << "\n[Search] Tree built successfully using built-in std::map.\n";
}

void Search::SearchByBloodType(const string& bloodType, const BloodStock& stock) const
{
    if (tree.find(bloodType) == tree.end()) {
        cout << "\n[Search] Blood type not found in tree.\n";
        return;
    }

    cout << "\n[Search] Blood Type Found: " << bloodType << "\n";
    stock.displayBloodType(bloodType);
}

bool Search::CheckAvailability(const string& bloodType, int neededQty, const BloodStock& stock) const
{
    if (tree.find(bloodType) == tree.end())
        return false;

    return stock.getTotalQuantity(bloodType) >= neededQty;
}

void Search::DisplayTree(const BloodStock& stock) const
{
    if (tree.empty()) {
        cout << "\n[Search] Tree is empty.\n";
        return;
    }

    cout << "\n[Search] Blood Types (sorted automatically):\n";
    for (const auto& pair : tree) {
        cout << pair.first << " : "
            << stock.getTotalQuantity(pair.first) << " ml\n";
    }
}



/* #include <iostream>
#include "BloodUnit.h"
#include "BloodStock.h"
#include "search.h"

using namespace std;

int main() {

    BloodStock stock;

    // ---------------------------
    // 1) Add sample blood units
    // ---------------------------
    BloodUnit u1("B101", 500, "2024-01-01", "2024-03-01");
    BloodUnit u2("B102", 300, "2024-01-05", "2024-03-05");
    BloodUnit u3("O201", 450, "2024-02-01", "2024-04-01");

    stock.addBloodUnit("A+", u1);
    stock.addBloodUnit("A+", u2);
    stock.addBloodUnit("O-", u3);

    cout << "\n=== Display All Stock ===\n";
    stock.displayAllStock();

    // ---------------------------
    // 2) Build Search Tree
    // ---------------------------
    Search searchSystem;
    searchSystem.BuildTreeFromStock(stock);



    // ---------------------------
    // 3) Search for blood type
    // ---------------------------
    cout << "\n=== Test Search A+ ===\n";
    searchSystem.SearchByBloodType("A+", stock);

    cout << "\n=== Test Search B+ ===\n";
    searchSystem.SearchByBloodType("B+", stock);

    // ---------------------------
    // 4) Check availability
    // ---------------------------
    cout << "\n=== Check availability for A+ (need 600 ml) ===\n";
    if (searchSystem.CheckAvailability("A+", 600, stock))
        cout << "Enough A+ units available.\n";
    else
        cout << "Not enough A+ units available.\n";

    cout << "\n=== Check availability for O- (need 800 ml) ===\n";
    if (searchSystem.CheckAvailability("O-", 800, stock))
        cout << "Enough O- units available.\n";
    else
        cout << "Not enough O- units available.\n";

    return 0;
}*/
