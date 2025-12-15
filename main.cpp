#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include "Admin.h"
#include "Donor.h"
#include "Recipient.h"
#include "Request.h"
#include "BloodStock.h"
#include "Search.h"
#include "Matching.h"

// Global objects
DonorList donorList;
RecipientList recipientList;
BloodStock bloodStock;
Admin admin;
Request requestSystem;

// Function prototypes
void displayHeader();
void displayMainMenu();
void adminMode();
void donorMode();
void recipientMode();
void runMatchingSystem();
void initializeSystem();
void saveAllData();
bool authenticateAdmin();

// Main function
int main() {
    cout << "==================================================\n";
    cout << "   WELCOME TO BLOOD BANK MANAGEMENT SYSTEM\n";
    cout << "==================================================\n";
    
    initializeSystem();
    
    // Main menu loop
    int choice;
    bool exitSystem = false;
    
    while (!exitSystem) {
        displayMainMenu();
        cout << "\nEnter your choice (1-5): ";
        cin >> choice;
        
        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                adminMode();
                break;
            case 2:
                donorMode();
                break;
            case 3:
                recipientMode();
                break;
            case 4:
                runMatchingSystem();
                break;
            case 5:
                exitSystem = true;
                break;
            default:
                cout << "Invalid choice! Please enter a number between 1 and 5.\n";
        }
        
        // Pause before showing menu again
        if (!exitSystem) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
    }
    
    // Save all data before exit
    saveAllData();
    
    cout << "\nThank you for using Blood Bank Management System!\n";
    cout << "Goodbye!\n";
    
    return 0;
}

// Display system header
void displayHeader() {
    cout << "\n==================================================\n";
    cout << "           BLOOD BANK MANAGEMENT SYSTEM          \n";
    cout << "==================================================\n";
}

// Display main menu
void displayMainMenu() {
    displayHeader();
    cout << "\nMAIN MENU:\n";
    cout << "1. Admin Access\n";
    cout << "2. Donor Access\n";
    cout << "3. Recipient Access\n";
    cout << "4. Run Matching System\n";
    cout << "5. Exit\n";
}

// Initialize system data
void initializeSystem() {
    cout << "\nInitializing system...\n";
    
    // Load data from files
    donorList.LoadFromFile();
    bloodStock.loadFromFile();
    recipientList.loadFromFile("recipients.txt");
    
    // Build search tree
    admin.BuildSearchTree();
    
    cout << "System initialized successfully!\n";
    cout << "Loaded: \n";
    cout << "  - Donors data\n";
    cout << "  - Blood stock\n";
    cout << "  - Recipients data\n";
}

// Save all data to files
void saveAllData() {
    cout << "\nSaving all data...\n";
    
    donorList.SaveToFile();
    bloodStock.saveToFile();
    recipientList.saveToFile("recipients.txt");
    
    cout << "All data saved successfully!\n";
}

// Admin authentication
bool authenticateAdmin() {
    string password;
    cout << "\n=== ADMIN AUTHENTICATION ===\n";
    cout << "Enter admin password: ";
    getline(cin, password);
    
    if (password == "admin123") {
        cout << "Authentication successful!\n";
        return true;
    } else {
        cout << "Access denied! Invalid password.\n";
        return false;
    }
}

// Admin mode - USING ADMIN CLASS FUNCTIONS
void adminMode() {
    if (!authenticateAdmin()) {
        return;
    }
    
    int adminChoice;
    bool backToMain = false;
    
    while (!backToMain) {
        displayHeader();
        cout << "\nADMIN PANEL:\n";
        cout << "1. Manage Donors\n";
        cout << "2. Manage Blood Stock\n";
        cout << "3. Manage Requests\n";
        cout << "4. System Statistics\n";
        cout << "5. Back to Main Menu\n";
        cout << "\nEnter your choice (1-5): ";
        cin >> adminChoice;
        cin.ignore();
        
        switch (adminChoice) {
            case 1: { // Manage Donors
                int donorMgmtChoice;
                do {
                    cout << "\n--- DONOR MANAGEMENT ---\n";
                    cout << "1. Add New Donor\n";
                    cout << "2. View All Donors\n";
                    cout << "3. Delete Donor\n";
                    cout << "4. Search Donor by Email\n";
                    cout << "5. Back to Admin Menu\n";
                    cout << "Choice: ";
                    cin >> donorMgmtChoice;
                    cin.ignore();
                    
                    switch (donorMgmtChoice) {
                        case 1: {
                            Donor d;
                            cout << "\n--- Add New Donor ---\n";
                            cout << "ID: "; getline(cin, d.id);
                            cout << "Name: "; getline(cin, d.name);
                            cout << "Email: "; getline(cin, d.mail);
                            cout << "Password: "; getline(cin, d.password);
                            cout << "Age: "; cin >> d.age; cin.ignore();
                            cout << "Gender: "; getline(cin, d.gender);
                            cout << "Blood Type: "; getline(cin, d.bloodType);
                            cout << "Diseases (None if none): "; getline(cin, d.diseaseList);
                            cout << "Medications (None if none): "; getline(cin, d.medications);
                            cout << "Last Donation Date (YYYY-MM-DD): "; getline(cin, d.latestDonationDate);
                            
                            // Using Admin class function
                            admin.AddDonor(donorList, d);
                            break;
                        }
                        case 2:
                            // Using Admin class function
                            admin.DisplayAllDonors(donorList);
                            break;
                        case 3: {
                            string id;
                            cout << "Enter Donor ID to delete: ";
                            getline(cin, id);
                            // Using Admin class function
                            admin.DeleteDonor(donorList, id);
                            break;
                        }
                        case 4: {
                            string mail;
                            cout << "Enter donor email: ";
                            getline(cin, mail);
                            Donor* donor = donorList.SearchByMail(mail);
                            if (donor) {
                                cout << "\nDonor Found:\n";
                                cout << "Name: " << donor->name << "\n";
                                cout << "Blood Type: " << donor->bloodType << "\n";
                                cout << "Age: " << donor->age << "\n";
                                cout << "Last Donation: " << donor->latestDonationDate << "\n";
                            } else {
                                cout << "Donor not found.\n";
                            }
                            break;
                        }
                    }
                } while (donorMgmtChoice != 5);
                break;
            }
            
            case 2: { // Manage Blood Stock
                int stockMgmtChoice;
                do {
                    cout << "\n--- BLOOD STOCK MANAGEMENT ---\n";
                    cout << "1. Add Blood Unit\n";
                    cout << "2. Remove Oldest Blood Unit\n";
                    cout << "3. View All Stock\n";
                    cout << "4. Search Batch ID\n";
                    cout << "5. Back to Admin Menu\n";
                    cout << "Choice: ";
                    cin >> stockMgmtChoice;
                    cin.ignore();
                    
                    switch (stockMgmtChoice) {
                        case 1: {
                            string type, donationDate, expiryDate;
                            float quantity;
                            cout << "\n--- Add Blood Unit ---\n";
                            cout << "Blood Type (A+, B+, etc.): "; getline(cin, type);
                            cout << "Quantity (ml): "; cin >> quantity; cin.ignore();
                            cout << "Donation Date (YYYY-MM-DD): "; getline(cin, donationDate);
                            cout << "Expiry Date (YYYY-MM-DD): "; getline(cin, expiryDate);
                            
                            // Using Admin class function
                            admin.AddBloodUnit(type, quantity, donationDate, expiryDate);
                            break;
                        }
                        case 2: {
                            string type;
                            cout << "Enter blood type to remove oldest unit from: ";
                            getline(cin, type);
                            // Using Admin class function
                            admin.RemoveBloodUnit(type);
                            break;
                        }
                        case 3:
                            // Using Admin class function
                            admin.DisplayStock();
                            break;
                        case 4: {
                            string batchId;
                            cout << "Enter Batch ID to search: ";
                            getline(cin, batchId);

                            admin.SearchBatch(batchId); 
                            break;
                        }
                    }
                } while (stockMgmtChoice != 5);
                break;
            }
            
            case 3: { // Manage Requests
                int requestChoice;
                do {
                    cout << "\n--- REQUEST MANAGEMENT ---\n";
                    cout << "1. View All Blood Requests\n";
                    cout << "2. View Donation Requests\n";
                    cout << "3. Back to Admin Menu\n";
                    cout << "Choice: ";
                    cin >> requestChoice;
                    cin.ignore();
                    
                    switch (requestChoice) {
                        case 1:
                            // Using Admin class function
                            admin.DisplayAllRequests();
                            break;
                        case 2:
                            // Using Admin class function
                            admin.DisplayDonationRequests();
                            break;
                    }
                } while (requestChoice != 3);
                break;
            }
            
            case 4: { // System Statistics
                // Using Admin class function
                admin.DisplaySystemStatistics(donorList, recipientList);
                break;
            }
            
            case 5:
                backToMain = true;
                cout << "Returning to main menu...\n";
                break;
                
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

// Donor mode
void donorMode() {
    int donorChoice;
    bool backToMain = false;
    
    while (!backToMain) {
        displayHeader();
        cout << "\nDONOR MENU:\n";
        cout << "1. Register as New Donor\n";
        cout << "2. Login\n";
        cout << "3. View Blood Requests\n";
        cout << "4. Back to Main Menu\n";
        cout << "\nEnter your choice (1-4): ";
        cin >> donorChoice;
        cin.ignore();
        
        switch (donorChoice) {
            case 1: { // Register
                Donor d;
                cout << "\n--- NEW DONOR REGISTRATION ---\n";
                cout << "ID: "; getline(cin, d.id);
                cout << "Name: "; getline(cin, d.name);
                cout << "Email: "; getline(cin, d.mail);
                cout << "Password: "; getline(cin, d.password);
                cout << "Age: "; cin >> d.age; cin.ignore();
                cout << "Gender: "; getline(cin, d.gender);
                cout << "Blood Type: "; getline(cin, d.bloodType);
                cout << "Diseases (if any): "; getline(cin, d.diseaseList);
                cout << "Medications (if any): "; getline(cin, d.medications);
                cout << "Last Donation Date (YYYY-MM-DD or 'Never'): "; getline(cin, d.latestDonationDate);
                
                donorList.InsertDonor(d);
                donorList.SaveToFile();
                cout << "\nRegistration successful! Thank you for registering.\n";
                break;
            }
            
            case 2: { // Login
                string email, password;
                cout << "\n--- DONOR LOGIN ---\n";
                cout << "Email: "; getline(cin, email);
                cout << "Password: "; getline(cin, password);
                
                Donor* donor = donorList.SearchByMail(email);
                if (donor && donor->password == password) {
                    cout << "\nLogin successful! Welcome " << donor->name << "!\n";
                    
                    int loggedInChoice;
                    do {
                        cout << "\n--- DONOR DASHBOARD ---\n";
                        cout << "1. View My Information\n";
                        cout << "2. Update Account Information\n";
                        cout << "3. Delete My Account\n";
                        cout << "4. Make Donation Request\n";
                        cout << "5. View Blood Requests\n";
                        cout << "6. Logout\n";
                        cout << "Choice: ";
                        cin >> loggedInChoice;
                        cin.ignore();
                        
                        switch (loggedInChoice) {
                            case 1: // View Info
                                cout << "\nYour Information:\n";
                                cout << "Name: " << donor->name << "\n";
                                cout << "Blood Type: " << donor->bloodType << "\n";
                                cout << "Age: " << donor->age << "\n";
                                cout << "Last Donation: " << donor->latestDonationDate << "\n";
                                cout << "Email: " << donor->mail << "\n";
                                break;
                                
                            case 2: { // Update Account Information
                                cout << "\n--- UPDATE ACCOUNT INFORMATION ---\n";
                                cout << "What would you like to update?\n";
                                cout << "1. Personal Information\n";
                                cout << "2. Medical Information\n";
                                cout << "3. Password\n";
                                cout << "4. Cancel\n";
                                cout << "Choice: ";
                                int updateChoice;
                                cin >> updateChoice;
                                cin.ignore();
                                
                                switch (updateChoice) {
                                    case 1: { // Personal Information
                                        cout << "\nUpdate Personal Information:\n";
                                        cout << "New Name: "; getline(cin, donor->name);
                                        cout << "New Age: "; cin >> donor->age; cin.ignore();
                                        cout << "New Gender: "; getline(cin, donor->gender);
                                        cout << "New Email: "; getline(cin, donor->mail);
                                        donorList.UpdateDonor(*donor);
                                        donorList.SaveToFile();
                                        cout << "Personal information updated successfully!\n";
                                        break;
                                    }
                                    case 2: { // Medical Information
                                        cout << "\nUpdate Medical Information:\n";
                                        cout << "New Blood Type: "; getline(cin, donor->bloodType);
                                        cout << "Diseases (if any, 'None' for none): "; getline(cin, donor->diseaseList);
                                        cout << "Medications (if any, 'None' for none): "; getline(cin, donor->medications);
                                        cout << "Last Donation Date (YYYY-MM-DD or 'Never'): "; getline(cin, donor->latestDonationDate);
                                        donorList.UpdateDonor(*donor);
                                        donorList.SaveToFile();
                                        cout << "Medical information updated successfully!\n";
                                        break;
                                    }
                                    case 3: { // Password
                                        cout << "\nUpdate Password:\n";
                                        string currentPass;
                                        cout << "Enter current password: ";
                                        getline(cin, currentPass);
                                        
                                        if (currentPass == donor->password) {
                                            cout << "Enter new password: ";
                                            getline(cin, donor->password);
                                            donorList.UpdateDonor(*donor);
                                            donorList.SaveToFile();
                                            cout << "Password updated successfully!\n";
                                        } else {
                                            cout << "Incorrect current password. Update failed.\n";
                                        }
                                        break;
                                    }
                                    case 4:
                                        cout << "Update cancelled.\n";
                                        break;
                                    default:
                                        cout << "Invalid choice!\n";
                                }
                                break;
                            }
                            
                            case 3: { // Delete My Account
                                char confirm;
                                cout << "\n--- DELETE MY ACCOUNT ---\n";
                                cout << "WARNING: This action cannot be undone!\n";
                                cout << "All your data will be permanently deleted.\n";
                                cout << "Are you sure you want to delete your account? (y/n): ";
                                cin >> confirm;
                                cin.ignore();
                                
                                if (confirm == 'y' || confirm == 'Y') {
                                    string passConfirm;
                                    cout << "Enter your password to confirm deletion: ";
                                    getline(cin, passConfirm);
                                    
                                    if (passConfirm == donor->password) {
                                        if (donorList.DeleteDonor(donor->id)) {
                                            donorList.SaveToFile();
                                            cout << "\nAccount deleted successfully!\n";
                                            cout << "Thank you for being a donor. You can always register again.\n";
                                            loggedInChoice = 6; // Logout
                                        } else {
                                            cout << "Failed to delete account.\n";
                                        }
                                    } else {
                                        cout << "Incorrect password. Account deletion cancelled.\n";
                                    }
                                } else {
                                    cout << "Account deletion cancelled.\n";
                                }
                                break;
                            }
                            
                            case 4: { // Make Donation Request
                                cout << "\n--- MAKE DONATION REQUEST ---\n";
                                
                                // Check donation eligibility using Admin class
                                cout << "Checking your eligibility...\n";
                                if (!admin.ValidateExistingDonorForDonation(*donor)) {
                                    cout << "\n You are not eligible to donate at this time.\n";
                                    cout << "Please check the validation results above.\n";
                                    break;
                                }
                                
                                // Generate a unique request ID
                                string requestId = "DONOR_" + donor->id + "_" + to_string(time(0));
                                
                                // Get donation details
                                int quantity;
                                string hospital, date;
                                
                                cout << "\nDonation Details:\n";
                                cout << "Hospital/Clinic for donation: ";
                                getline(cin, hospital);
                                cout << "Available donation date (YYYY-MM-DD): ";
                                getline(cin, date);
                                cout << "Quantity you wish to donate (ml, typically 470ml): ";
                                cin >> quantity;
                                cin.ignore();
                                
                                // Validate quantity
                                if (quantity < 250 || quantity > 500) {
                                    cout << " Note: Typical donation is 470ml. You entered " << quantity << "ml.\n";
                                    char proceed;
                                    cout << "Proceed anyway? (y/n): ";
                                    cin >> proceed;
                                    cin.ignore();
                                    if (proceed != 'y' && proceed != 'Y') {
                                        cout << "Donation request cancelled.\n";
                                        break;
                                    }
                                }
                                
                                // Create donation request file
                                ofstream donationFile("DonationRequests.txt", ios::app);
                                if (donationFile.is_open()) {
                                    donationFile << requestId << ","
                                                 << donor->id << ","
                                                 << donor->name << ","
                                                 << donor->bloodType << ","
                                                 << quantity << ","
                                                 << hospital << ","
                                                 << date << ","
                                                 << "PENDING" << "\n";
                                    donationFile.close();
                                    
                                    cout << "\n✓ Donation request submitted successfully!\n";
                                    cout << "===============================\n";
                                    cout << "Request ID: " << requestId << "\n";
                                    cout << "Donor: " << donor->name << "\n";
                                    cout << "Blood Type: " << donor->bloodType << "\n";
                                    cout << "Quantity: " << quantity << "ml\n";
                                    cout << "Hospital: " << hospital << "\n";
                                    cout << "Date: " << date << "\n";
                                    cout << "Status: PENDING\n";
                                    cout << "===============================\n";
                                    cout << "You will be contacted by the blood bank for confirmation.\n";
                                    cout << "Please keep your Request ID for reference.\n";
                                    
                                    // Update donor's last donation date
                                    donor->latestDonationDate = date;
                                    donorList.UpdateDonor(*donor);
                                    donorList.SaveToFile();
                                } else {
                                    cout << "Error: Could not save donation request.\n";
                                }
                                break;
                            }
                            
                            case 5: // View Blood Requests
                                cout << "\n--- BLOOD REQUESTS ---\n";
                                // Using Admin class function to show requests
                                admin.DisplayAllRequests();
                                break;
                                
                            case 6: // Logout
                                cout << "Logging out...\n";
                                break;
                                
                            default:
                                cout << "Invalid choice!\n";
                        }
                    } while (loggedInChoice != 6);
                } else {
                    cout << "Invalid email or password!\n";
                }
                break;
            }
            
            case 3: // View Requests (without login)
                cout << "\n--- BLOOD REQUESTS ---\n";
                // Using Admin class function
                admin.DisplayAllRequests();
                break;
                
            case 4: // Back to Main Menu
                backToMain = true;
                cout << "Returning to main menu...\n";
                break;
                
            default:
                cout << "Invalid choice!\n";
        }
    }
}

// Recipient mode
void recipientMode() {
    int recipientChoice;
    bool backToMain = false;
    
    while (!backToMain) {
        displayHeader();
        cout << "\nRECIPIENT MENU:\n";
        cout << "1. Register as New Recipient\n";
        cout << "2. Login\n";
        cout << "3. Back to Main Menu\n";
        cout << "\nEnter your choice (1-3): ";
        cin >> recipientChoice;
        cin.ignore();
        
        switch (recipientChoice) {
            case 1: { // Register
                string id, name, mail, pass, gender, bloodType, hospital, doctor;
                int age;
                
                cout << "\n--- NEW RECIPIENT REGISTRATION ---\n";
                cout << "ID: "; getline(cin, id);
                cout << "Name: "; getline(cin, name);
                cout << "Email: "; getline(cin, mail);
                cout << "Password: "; getline(cin, pass);
                cout << "Age: "; cin >> age; cin.ignore();
                cout << "Gender: "; getline(cin, gender);
                cout << "Blood Type: "; getline(cin, bloodType);
                cout << "Hospital: "; getline(cin, hospital);
                cout << "Doctor: "; getline(cin, doctor);
                
                RecipientNode* newNode = new RecipientNode(id, name, mail, pass, age, gender, bloodType, hospital, doctor);
                recipientList.insertTail(newNode);
                recipientList.saveToFile("recipients.txt");
                cout << "Registration successful!\n";
                break;
            }
            
            case 2: { // Login
                string email, password;
                cout << "\n--- RECIPIENT LOGIN ---\n";
                cout << "Email: "; getline(cin, email);
                cout << "Password: "; getline(cin, password);
                
                // Search for recipient by email
                RecipientNode* recipient = recipientList.findByemail(email);
                
                if (recipient && recipient->password == password) {
                    cout << "\nLogin successful! Welcome " << recipient->name << "!\n";
                    
                    int loggedInChoice;
                    do {
                        cout << "\n--- RECIPIENT DASHBOARD ---\n";
                        cout << "1. Request Blood\n";
                        cout << "2. View My Requests\n";
                        cout << "3. Search Blood Type Availability\n";
                        cout << "4. Logout\n";
                        cout << "Choice: ";
                        cin >> loggedInChoice;
                        cin.ignore();
                        
                        switch (loggedInChoice) {
                            case 1: { // Request Blood
                                cout << "\n--- CREATE BLOOD REQUEST ---\n";
                                
                                string bloodType, hospital;
                                float quantity;
                                int priority;
                                
                                cout << "Blood Type Needed (e.g., A+, O-): ";
                                getline(cin, bloodType);
                                
                                cout << "Quantity needed (ml): ";
                                cin >> quantity;
                                cin.ignore();
                                
                                cout << "Hospital name: ";
                                getline(cin, hospital);
                                
                                cout << "Priority (1=Lowest, 10=Highest): ";
                                cin >> priority;
                                cin.ignore();
                                
                                // Validate priority
                                if (priority < 1) priority = 1;
                                if (priority > 10) priority = 10;
                                
                                // Generate request ID
                                string requestId = "REQ_" + recipient->id + "_" + to_string(time(0));
                                
                                // Save to file
                                ofstream outFile("Requests.txt", ios::app);
                                if (outFile.is_open()) {
                                    outFile << requestId << ","
                                            << recipient->id << ","
                                            << bloodType << ","
                                            << quantity << ","
                                            << hospital << ","
                                            << priority << "\n";
                                    outFile.close();
                                    
                                    cout << "\n✓ BLOOD REQUEST CREATED SUCCESSFULLY!\n";
                                    cout << "\n-----------------------------------------------------------\n";
                                    cout << "Request ID:     " << requestId << "\n";
                                    cout << "Recipient:      " << recipient->name << "\n";
                                    cout << "Blood Type:     " << bloodType << "\n";
                                    cout << "Quantity:       " << quantity << " ml\n";
                                    cout << "Hospital:       " << hospital << "\n";
                                    cout << "Priority:       " << priority << "/10\n";
                                    cout << "\n-----------------------------------------------------------\n";
                                    cout << "Status:         PENDING\n";
                                    cout << "Your request will be processed by the blood bank.\n";
                                    
                                    // If high priority, run matching
                                    if (priority >= 8) {
                                        cout << "\n⚠ HIGH PRIORITY REQUEST - Running matching system...\n";
                                        runMatchingSystem();
                                    }
                                } else {
                                    cout << "Error: Could not save request to file.\n";
                                }
                                break;
                            }
                            
                            case 2: { // View My Requests
                                cout << "\n--- YOUR BLOOD REQUESTS ---\n";
                                vector<Request> requests = Request::LoadRequestsFromFile();
                                
                                if (requests.empty()) {
                                    cout << "No requests found.\n";
                                } else {
                                    bool hasRequests = false;
                                    for (const auto& req : requests) {
                                        if (req.getRecipientID() == recipient->id) {
                                            cout << "Request ID: " << req.getRequestID()
                                                 << " | Blood: " << req.getNeededBloodType()
                                                 << " | Qty: " << req.getNeededQuantity() << "ml"
                                                 << " | Priority: " << req.getPriorityLevel()
                                                 << " | Hospital: " << req.getPatientHospital() << "\n";
                                            hasRequests = true;
                                        }
                                    }
                                    if (!hasRequests) {
                                        cout << "You have no blood requests.\n";
                                    }
                                }
                                break;
                            }
                            
                            case 3: { // Search Blood Type Availability
                                string bloodType;
                                cout << "\n--- SEARCH BLOOD TYPE AVAILABILITY ---\n";
                                cout << "Enter blood type to search (e.g., A+, O-): ";
                                getline(cin, bloodType);
                                
                                // Using Admin class function
                                admin.SearchByBloodType(bloodType);
                                
                                // Check availability using Search class
                                Search searchSystem;
                                searchSystem.BuildTreeFromStock(bloodStock);
                                
                                // Check availability for different quantities
                                cout << "\n--- AVAILABILITY CHECK ---\n";
                                cout << "Checking different quantities:\n";
                                
                                vector<int> quantities = {100, 250, 500, 1000};
                                vector<string> descriptions = {"Small", "Medium", "Standard", "Large"};
                                
                                for (size_t i = 0; i < quantities.size(); i++) {
                                    if (searchSystem.CheckAvailability(bloodType, quantities[i], bloodStock)) {
                                        cout << "✓ " << descriptions[i] << " request (" << quantities[i] << "ml): AVAILABLE\n";
                                    } else {
                                        cout << "✗ " << descriptions[i] << " request (" << quantities[i] << "ml): NOT AVAILABLE\n";
                                    }
                                }
                                
                                // Show compatibility information
                                cout << "\n--- COMPATIBILITY INFORMATION ---\n";
                                cout << "For blood type " << bloodType << ":\n";
                                
                                if (bloodType == "O-") {
                                    cout << "  - Can receive from: O- only\n";
                                    cout << "  - Universal donor (can donate to all types)\n";
                                } else if (bloodType == "O+") {
                                    cout << "  - Can receive from: O+, O-\n";
                                    cout << "  - Can donate to: O+, A+, B+, AB+\n";
                                } else if (bloodType == "A-") {
                                    cout << "  - Can receive from: A-, O-\n";
                                    cout << "  - Can donate to: A+, A-, AB+, AB-\n";
                                } else if (bloodType == "A+") {
                                    cout << "  - Can receive from: A+, A-, O+, O-\n";
                                    cout << "  Can donate to: A+, AB+\n";
                                } else if (bloodType == "B-") {
                                    cout << "  - Can receive from: B-, O-\n";
                                    cout << "  - Can donate to: B+, B-, AB+, AB-\n";
                                } else if (bloodType == "B+") {
                                    cout << "  - Can receive from: B+, B-, O+, O-\n";
                                    cout << "  - Can donate to: B+, AB+\n";
                                } else if (bloodType == "AB-") {
                                    cout << "  - Can receive from: AB-, A-, B-, O-\n";
                                    cout << "  - Can donate to: AB+, AB-\n";
                                } else if (bloodType == "AB+") {
                                    cout << "  - Can receive from: ALL blood types\n";
                                    cout << "  - Universal recipient\n";
                                    cout << "  - Can donate to: AB+ only\n";
                                } else {
                                    cout << "  - Invalid or unknown blood type\n";
                                }
                                
                                // Recommendation based on availability
                                cout << "\n--- RECOMMENDATION ---\n";
                                if (searchSystem.CheckAvailability(bloodType, 500, bloodStock)) {
                                    cout << "✓ Your blood type is available for immediate use.\n";
                                    cout << "  You can proceed with a blood request.\n";
                                } else {
                                    cout << "✗ Your blood type is currently low in stock.\n";
                                    cout << "  Consider:\n";
                                    cout << "  1. Checking back later\n";
                                    cout << "  2. Looking for alternative compatible types\n";
                                    cout << "  3. Contacting the blood bank directly\n";
                                }
                                break;
                            }
                            
                            case 4: // Logout
                                cout << "Logging out...\n";
                                break;
                                
                            default:
                                cout << "Invalid choice!\n";
                        }
                    } while (loggedInChoice != 4);
                } else {
                    cout << "Invalid email or password!\n";
                }
                break;
            }
            
            case 3:
                backToMain = true;
                cout << "Returning to main menu...\n";
                break;
                
            default:
                cout << "Invalid choice!\n";
        }
    }
}

// Run matching system
void runMatchingSystem() {
    cout << "\n=== RUNNING MATCHING SYSTEM ===\n";
    // Using Admin class function
    admin.RunMatching(donorList);
}