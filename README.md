# 🩸 Blood Bank System — Blood Stock Module

## 📌 Member 3 — Blood Stock

This module is responsible for managing the blood inventory in the Blood Bank System.

---

## 📂 Files Included
- BloodUnit.h
- BloodUnit.cpp
- BloodStock.h
- BloodStock.cpp
- BloodStock.txt

---

## 🧱 Classes

### 1️⃣ BloodUnit
Represents a single blood batch stored in the blood bank.

*Attributes:*
- BatchID
- BloodType
- Quantity
- DonationDate 
- ExpiryDate
  
---

### 2️⃣ BloodStock
Manages all blood units and overall inventory.

*Responsibilities:*
- Add new blood units
- Display available blood stock
- Update quantities
- Load data from file
- Save data to file

---

## 🧠 Data Structures Used
- *Deque* → storing blood units by insertion order
- *Hash Map* → quick access by blood type
- *Priority Queue* → handling expiry dates (soonest first)
- *Linked List* → internal management where required

---

## 📄 Storage
All blood stock data is saved in:

