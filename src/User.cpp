#include "User.h"

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include "My_Utility.h"
#include "Password.h"


// HELPERS
void User::gather_name() {
    std::string temp;
    
    // First name
    std::cout << "Enter first name: ";
    std::cin >> temp;
    
    while (true) {
        bool isAlpha = std::all_of(temp.begin(), temp.end(), ::isalpha);
        if (isAlpha && temp.length() <= 20) break;
        std::cout << (isAlpha ? "Name must be 20 characters or fewer. Please try again: "
                              : "Name must be alphabetic characters. Please try again: ");
        std::cin >> temp;
    }
    name.first = capitalize(temp);
    
    // Last name
    std::cout << "Enter last name: ";
    std::cin >> temp;
    
    while (true) {
        bool isAlpha = std::all_of(temp.begin(), temp.end(), ::isalpha);
        if (isAlpha && temp.length() <= 30) break;
        std::cout << (isAlpha ? "Name must be 30 characters or fewer. Please try again: "
                              : "Name must be alphabetic characters. Please try again: ");
        std::cin >> temp;
    }
    name.second = capitalize(temp);
}

void User::gather_initials() {
    std::string middle = "";
    std::cout << "Enter middle initial: ";
    std::cin >> middle;
    while(middle.size() != 1 || !std::isalpha(middle[0])) { // Catch for incorrect entry
        std::cout << "Middle initial must be 1 alphabetic character. Please try again: ";
        std::cin >> middle;
    }
    userInitials = to_uppercase(
        std::string(1, name.first[0]) + middle + std::string(1, name.second[0])
    );
    username = userInitials;
}

void User::gather_id() {
    std::string temp;
    std::cout << "Enter employee ID: ";
    std::cin >> temp;
    while(temp.length() > 7 || !std::all_of(temp.begin(), temp.end(), ::isdigit)) { // Catch for incorrect entry
        std::cout << "Employee ID must be 7 digits or fewer. Please try again: ";
        std::cin >> temp;
    }
    employeeID = temp;
}

void User::gather_title() {
    std::cout << "\n1. Standard Technician\n2. Certified Technician\n3. Senior Technician\n4. Lead Technician\n5. Staff Pharmacist\n6. Pharmacy Manager" << std::endl;
    switch(get_valid_int("Please select a number from the above options to set the user's title: ", 1, 6)) {
        case 1:
            title = "Pharmacy Technician";
            accessCode = "PhT";
            break;
        case 2:
            title = "Certified Pharmacy Technician";
            accessCode = "CPhT";
            break;
        case 3:
            title = "Senior Pharmacy Technician";
            accessCode = "SPhT";
            break;
        case 4:
            title = "Lead Pharmacy Technician";
            accessCode = "LPhT";
            break;
        case 5:
            title = "Staff Pharmacist";
            accessCode = "RPh";
            break;
        case 6:
            title = "Pharmacy Manager";
            accessCode = "RPhM";
            break;
    }
}


/* This function exists for CLI testing. Will not be incorporated into GUI. */
void User::create() {
        // Gather name
        gather_name();
        
        //Gather userInitials
        gather_initials();
        
        // Gather employeeID
        gather_id();
        
        // Gather title
        gather_title();
        
        // Verify entry correct
        print_info();
        char answer = get_valid_char("Is the above correct? (Y/N): ");
        if(answer == 'N') {
            while(answer == 'N') {
                /* 1. name
                   2. userInitials
                   3. employeeID
                   4. title
                */
                int retry = get_valid_int("Enter the number of the field you wish to update: ", 1, 4);
                if (retry == 1) { gather_name(); }
                else if (retry == 2) { gather_initials(); }
                else if (retry == 3) { gather_id(); }
                else if (retry == 4) { gather_title(); }
                else {
                    throw std::invalid_argument("get_valid_int() failed.");
                }
                
                // Check again for correctness
                print_info();
                answer = get_valid_char("Is the above correct? (Y/N): ");
            }
        }
        
        std::cout << "User profile successfully created." << std::endl;
        generate_password();
}

void User::assign_id(const std::string& pos) {
    if(pos == "Pharmacy Technician") { accessCode = "PhT"; }
    else if(pos == "Certified Technician") { accessCode = "CPhT"; }
    else if(pos == "Senior Technician") { accessCode = "SPhT"; }
    else if(pos == "Lead Technician") { accessCode = "LPhT"; }
    else if(pos == "Staff Pharmacist") { accessCode = "RPh"; }
    else if(pos == "Pharmacy Manager") { accessCode = "RPhM"; }
    else {
        throw std::invalid_argument("Invalid title passed to assign_id(): '" + pos + "'");
    }
}

void User::generate_password() {
    std::string rawPassword = Password::generate();
    passwordHash = Password::hash(rawPassword);
    std::cout << "Password: " << rawPassword << std::endl;
    std::cout << "Please remember this as it will not be shown again." << std::endl;
}


// CONSTRUCTORS
User::User() :
    name("", ""),
    userInitials(""),
    employeeID(""),
    title(""),
    accessCode(""),
    username(""),
    passwordHash("") {}

User::User(bool CLI) {
    if(CLI) {
        create();
    }
    else {
        std::cout << "Did you mean to auto-create user profile?" << std::endl;
    }
}

// ACCESSORS
std::pair<std::string, std::string> User::get_name() const { return name; }     // NOTE: This return pair<string, string>

std::string User::get_initials() const { return userInitials; }

std::string User::get_id() const { return employeeID; }

std::string User::get_title() const { return title; }

std::string User::get_access_code() const { return accessCode; }

std::string User::get_username() const { return username; }

std::string User::get_password() const { return passwordHash; }

// Used for CLI
void User::print_info() {
    std::cout  << "1. Name: " << name.first << " " << name.second << std::endl;
    std::cout << "2. Initials: " << userInitials << std::endl;
    std::cout << "3. Employee ID: " << employeeID << std::endl;
    std::cout << "4. Title: " << title << std::endl;
}


// MUTATORS
void User::set_name(const std::string& first, const std::string& last) {
    if(!std::all_of(first.begin(), first.end(), ::isalpha)) {
        throw std::invalid_argument("First name had numeric characters.");
    }
    if(!std::all_of(last.begin(), last.end(), ::isalpha)) {
        throw std::invalid_argument("Last name had numeric characters.");
    }
    name.first = capitalize(first);
    name.second = capitalize(last);
}

void User::set_initials(const std::string& middleInitial) {
    if (middleInitial.length() != 1 || !std::isalpha(middleInitial[0])) {
        throw std::invalid_argument("Middle initial must be a single alphabetic character.");
    }
    
    userInitials = to_uppercase(
        std::string(1, name.first[0]) + middleInitial + std::string(1, name.second[0])
    );
    username = userInitials;
}

void User::set_id(const std::string& id) {
    if (id.length() > 7 || !std::all_of(id.begin(), id.end(), ::isdigit))
        throw std::invalid_argument("Employee ID must be 7 characters or fewer.");
    employeeID = id;
}

void User::set_title(const std::string& pos) {
    title = pos;
    assign_id(pos);
}

void User::reset_password() {
    std::cout << "Please confirm password reset. Once completed, old password cannot be recovered." << std::endl;
    char choice = get_valid_char("(Y/N): ");
    if(choice == 'Y') { generate_password(); }
}

bool User::authenticate(const std::string& password) const {
    return Password::verify(passwordHash, password);
}
