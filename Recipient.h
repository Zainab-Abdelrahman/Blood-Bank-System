#ifndef RECIPIENT_H
#define RECIPIENT_H

#include <string>
#include <vector>
using namespace std;


// Recipient Node (Linked List) ==> good inserting and deleteing
struct RecipientNode {
    string id;
    string name;
    string mail;
    string password;
    int age;
    string gender;
    string bloodType;
    string hospital;
    string doctor;

    RecipientNode* next;

    RecipientNode(const string& _id, const string& _name, const string& _mail,
        const string& _password, int _age, const string& _gender,
        const string& _bloodType, const string& _hospital, const string& _doctor);
};


// Linked List Class  ==> functions
class RecipientList {
private:
    RecipientNode* head;

public:
    RecipientList();
    ~RecipientList();

    RecipientNode* getHead() const;

    void clear();
    void insertTail(RecipientNode* node);
    RecipientNode* findByID(const string& id) const;
    bool removeByID(const string& id);

    bool saveToFile(const string& filename) const;
    bool loadFromFile(const string& filename);
};


// Hash Table Structure ==> good searching
class RecipientHash {

private:
    size_t capacity;

    struct ChainNode {
        RecipientNode* data;
        ChainNode* next;
        ChainNode(RecipientNode* d);
    };

    vector<ChainNode*> chains;

    size_t hashFunc(const string& key) const;

public:
    RecipientHash(size_t cap = 211);
    ~RecipientHash();

    void insert(RecipientNode* node);
    bool removeByMail(const string& mail);
    RecipientNode* findByMail(const string& mail) const;
    void rebuildFromList(const RecipientList& list);
};

#endif

























