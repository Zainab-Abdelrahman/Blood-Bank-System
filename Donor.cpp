#include "Donor.h"
#include <iostream>
using namespace std;


// DonorList

DonorList::DonorList() {
    head = nullptr;
}

void DonorList::InsertDonor(Donor d) {
    Node* newNode = new Node(d);
    newNode->next = head;
    head = newNode;
}

bool DonorList::DeleteDonor(string id) {
    Node* cur = head;
    Node* prev = nullptr;

    while (cur != nullptr) {
        if (cur->data.id == id) {
            if (prev == nullptr)
                head = cur->next;
            else
                prev->next = cur->next;

            delete cur;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

Donor* DonorList::SearchByMail(string mail) {
    Node* cur = head;
    while (cur != nullptr) {
        if (cur->data.mail == mail)
            return &cur->data;
        cur = cur->next;
    }
    return nullptr;
}

void DonorList::UpdateDonor(Donor d) {
    Node* cur = head;
    while (cur != nullptr) {
        if (cur->data.id == d.id) {
            cur->data = d;
            return;
        }
        cur = cur->next;
    }
}


// RequestList
RequestList::RequestList() { head = nullptr; }

void RequestList::AddRequest(DonationRequest d) {
    RequestNode* newNode = new RequestNode(d);
    newNode->next = head;
    head = newNode;
}
