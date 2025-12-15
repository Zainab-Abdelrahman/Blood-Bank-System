🩸 Blood Bank Management System – Recipient Module

📌 Overview

This project represents the Recipient Management Module in a Blood Bank Management System.
It allows recipients to register, login, update their data, delete accounts, search by email, and store data permanently in a file.

The system is implemented in C++ using:

Linked List

Hash Table

File Handling


The goal is to ensure fast searching, easy insertion/deletion, and persistent storage.


---

🧱 System Components

1️⃣ RecipientNode (Linked List Node)

Represents a single recipient.

Attributes:

id → Unique recipient ID

name → Recipient name

mail → Email (used as hash key)

password → Login password

age → Recipient age

gender → Gender

bloodType → Blood group

hospital → Hospital name

doctor → Doctor name

next → Pointer to next node


Purpose:
Used to store recipient data inside a linked list.


---

2️⃣ RecipientList (Singly Linked List)

Used for data storage and file operations.

Main Functions:

insertTail() → Add recipient at the end

findByID() → Search by ID

removeByID() → Delete recipient

saveToFile() → Save all data to file

loadFromFile() → Load data from file

clear() → Free memory


Why Linked List?

Easy insertion and deletion

No fixed size

Efficient memory usage



---

3️⃣ RecipientHash (Hash Table with Chaining)

Used for fast searching by email.

Key Points:

Uses std::hash<string> for hashing

Collision handling using Separate Chaining

Each bucket contains a linked list (ChainNode)


Main Functions:

insert() → Insert recipient using email as key

findByMail() → Fast search (O(1) average)

removeByMail() → Delete from hash table

rebuildFromList() → Sync hash table with linked list


Why Hash Table?

Very fast searching compared to linked list

Email is a perfect unique key



---

💾 File Handling

Recipient data is stored in a text file:

Recipient.txt

Format:

ID|Name|Email|Password|Age|Gender|BloodType|Hospital|Doctor

Example:

R1001|Ahmed Ali|ahmed@gmail.com|1234|25|Male|A+|Tanta Hospital|Dr.Samir

Benefits:

Data is not lost when program closes

Easy to read and edit

Simple parsing using stringstream



---

🖥 Main Program Features

📋 Menu Options

1. Login


2. Register


3. Update Recipient Data


4. Delete Account


5. Search by Email


6. Display All Recipients


7. Exit




---

🔐 Login

Uses Hash Table for fast email search

Verifies password



---

📝 Register

Generates unique ID automatically

Prevents duplicate emails

Saves data to linked list, hash table, and file



---

✏ Update Data

Requires correct email and password

Updates name, age, hospital, doctor

Changes saved to file



---

❌ Delete Account

Removes recipient from:

Hash Table

Linked List

File




---

🔍 Search by Email

O(1) average time using hash table

Displays recipient info



---

🛠 Technologies & Concepts Used

C++

Object-Oriented Programming (OOP)

Singly Linked List

Hash Table (Separate Chaining)

File Handling (ifstream / ofstream)

Dynamic Memory Allocation

Data Structures Optimization



---

✅ Advantages of the Design

✔ Fast searching using hash table
✔ Easy insert/delete using linked list
✔ Persistent data storage
✔ Clean separation between data storage and searching
✔ Scalable and easy to extend


---

🚀 Future Improvements

Password encryption

Admin module

GUI interface

Validation for input data

Sorting recipients by blood type



---

👩‍💻 Author

Basmala Shalaby
Computer Science Student
Blood Bank Management System Project
