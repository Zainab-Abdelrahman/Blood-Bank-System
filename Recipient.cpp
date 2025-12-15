#include "Recipient.h"
#include<fstream>
#include<iostream>
#include <sstream>
#include <string>
using namespace std;


// Node Constructor
RecipientNode::RecipientNode(const string& _id, const string& _name, const string& _mail,
    const string& _password, int _age, const string& _gender,
    const string& _bloodType, const string& _hospital, const string& _doctor)
{
    id = _id;
    name = _name;
    mail = _mail;
    password = _password;
    age = _age;
    gender = _gender;
    bloodType = _bloodType;
    hospital = _hospital;
    doctor = _doctor;
    next = nullptr;
}



// RecipientList Functions
RecipientList::RecipientList() : head(nullptr) {}

RecipientList::~RecipientList() { clear(); }

RecipientNode* RecipientList::getHead() const { return head; }

void RecipientList::clear() {
    RecipientNode* cur = head;
    while (cur) {
        RecipientNode* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    head = nullptr;
}

void RecipientList::insertTail(RecipientNode* node) {
    if (!head) {
        head = node;
        node->next = nullptr;
        return;
    }
    RecipientNode* cur = head;
    while (cur->next) cur = cur->next;
    cur->next = node;
    node->next = nullptr;
}

RecipientNode* RecipientList::findByemail(const string& mail) const {
    RecipientNode* cur = head;
    while (cur) {
        if (cur->mail == mail) return cur;
        cur = cur->next;
    }
    return nullptr;
}

bool RecipientList::removeByID(const string& id) {
    if (!head) return false;
    if (head->id == id) {
        RecipientNode* d = head;
        head = head->next;
        delete d;
        return true;
    }
    RecipientNode* prev = head;
    RecipientNode* cur = head->next;

    while (cur) {
        if (cur->id == id) {
            prev->next = cur->next;
            delete cur;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

bool RecipientList::saveToFile(const string& filename) const {
    ofstream out(filename, ios::trunc);
    if (!out) return false;

    RecipientNode* cur = head;
    while (cur) {
        out << cur->id << "|"
            << cur->name << "|"
            << cur->mail << "|"
            << cur->password << "|"
            << cur->age << "|"
            << cur->gender << "|"
            << cur->bloodType << "|"
            << cur->hospital << "|"
            << cur->doctor << "\n";

        cur = cur->next;
    }

    out.close();
    return true;
}

bool RecipientList::loadFromFile(const string& filename) {
    ifstream in(filename);
    if (!in) return false;

    clear();
    string line;

    while (getline(in, line)) {
        if (line.empty()) continue;

        vector<string> p;
        stringstream ss(line);
        string temp;

        while (getline(ss, temp, '|')) p.push_back(temp);

        if (p.size() != 9) continue;

        RecipientNode* node = new RecipientNode(
            p[0], p[1], p[2], p[3], stoi(p[4]),
            p[5], p[6], p[7], p[8]
        );

        insertTail(node);
    }
    in.close();
    return true;
}



// Hash Table Functions
RecipientHash::ChainNode::ChainNode(RecipientNode* d) : data(d), next(nullptr) {}

RecipientHash::RecipientHash(size_t cap) : capacity(cap), chains(cap, nullptr) {}

RecipientHash::~RecipientHash() {
    for (auto& c : chains) {
        while (c) {
            ChainNode* nxt = c->next;
            delete c;
            c = nxt;
        }
    }
}

size_t RecipientHash::hashFunc(const string& key) const {
    return hash<string>{}(key) % capacity;
}

void RecipientHash::insert(RecipientNode* node) {
    size_t idx = hashFunc(node->mail);
    ChainNode* cn = new ChainNode(node);
    cn->next = chains[idx];
    chains[idx] = cn;
}

bool RecipientHash::removeByMail(const string& mail) {
    size_t idx = hashFunc(mail);
    ChainNode* cur = chains[idx];
    ChainNode* prev = nullptr;

    while (cur) {
        if (cur->data->mail == mail) {
            if (prev) prev->next = cur->next;
            else chains[idx] = cur->next;
            delete cur;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

RecipientNode* RecipientHash::findByMail(const string& mail) const {
    size_t idx = hashFunc(mail);
    ChainNode* cur = chains[idx];

    while (cur) {
        if (cur->data->mail == mail) return cur->data;
        cur = cur->next;
    }
    return nullptr;
}

void RecipientHash::rebuildFromList(const RecipientList& list) {
    for (auto& c : chains) {
        while (c) {
            ChainNode* nxt = c->next;
            delete c;
            c = nxt;
        }
    }
    fill(chains.begin(), chains.end(), nullptr);

    RecipientNode* cur = list.getHead();
    while (cur) {
        insert(cur);
        cur = cur->next;
    }
}

