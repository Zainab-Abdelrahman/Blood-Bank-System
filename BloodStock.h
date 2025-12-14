#ifndef BloodStock_h
#define BloodStock_h
#include "BloodUnit.h"
#include <unordered_map>
#include <deque>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class BloodStock
{
private:
    unordered_map<string, deque<BloodUnit>> stock;

public:
    BloodStock();

    void addBloodUnit(const string &bloodType, const BloodUnit &unit);

    bool removeOldestUnit(const string &bloodType);

    float getTotalQuantity(const string &bloodType) const;

    void displayBloodType(const string &bloodType) const;

    void displayAllStock() const;

    bool searchBatch(const string &batch_id) const;

    void saveToFile(const string &filename = "BloodStock.txt") const;

    void loadFromFile(const string &filename = "BloodStock.txt");
};

#endif