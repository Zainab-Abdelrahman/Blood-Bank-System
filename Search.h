#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <map>
#include "BloodStock.h"

class Search {
private:
    // map uses a built-in balanced BST
    std::map<std::string, bool> tree;

public:
    Search();

    // Build BST automatically from BloodStock object
    void BuildTreeFromStock(const BloodStock& stock);

    // Search for a specific blood type
    void SearchByBloodType(const std::string& bloodType, const BloodStock& stock) const;

    // Check availability
    bool CheckAvailability(const std::string& bloodType, int neededQty, const BloodStock& stock) const;

    // Display BST in sorted order
    void DisplayTree(const BloodStock& stock) const;
};

#endif

