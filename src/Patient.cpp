#include "Patient.h"

#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <utility>
#include <vector>

#include "My_Utility.h"

// Constructor
Patient::Patient() : sex('U'), textAlerts('N'), ninetyDaySupply('N') {}




// Accessors
std::string Patient::get_first_name() const { return name.first; }

std::string Patient::get_last_name() const { return name.second; }

std::string Patient::get_full_name() const {
    return name.first + " " + name.second;
}

std::string Patient::get_middle_initial() const { return middleInitial; }

std::string Patient::get_date_of_birth() const { return dateOfBirth.print(); }

char Patient::get_sex() const { return sex; }

std::string Patient::get_address_street() const { return address.get_street(); }

std::string Patient::get_address_full() const { return address.get_address(); }

std::string Patient::get_phone_number_1() const {
    if (phoneNumbers.size() < 1) { return ""; }
    else { return phoneNumbers.at(0); }
}

std::string Patient::get_phone_number_2() const { 
    if (phoneNumbers.size() < 2) { return ""; }
    else { return phoneNumbers.at(1); }
}
        
std::string Patient::get_phone_number_3() const {
    if (phoneNumbers.size() < 3) { return ""; }
    else { return phoneNumbers.at(2); }
}

const std::vector<std::string>& Patient::get_allergies() const { return allergies; }

const std::vector<std::string>& Patient::get_medical_conditions() const { return medicalConditions; }

const std::vector<Note>& Patient::get_notes() const { return notes; }

std::string Patient::get_primary_language() const { return primaryLanguage; }

char Patient::get_text_alerts() const { return textAlerts; }

char Patient::get_ninety_day_supply() const { return ninetyDaySupply; }

void Patient::print() const {
    std::cout << "\n--- Patient Information ---\n";
    std::cout << "Name: " << get_first_name();
    if (!middleInitial.empty()) std::cout << " " << middleInitial << ". ";
    std::cout << get_last_name();
    std::cout << "\nDOB: " << get_date_of_birth();
    std::cout << "\nSex: " << sex;
    std::cout << "\n\n--- Address ---\n" << get_address_full();

    std::cout << "\n\n--- Phone Numbers ---\n";
    std::cout << "Primary: " << get_phone_number_1() << "\n";
    std::cout << "Secondary: " << get_phone_number_2() << "\n";
    std::cout << "Tertiary: " << get_phone_number_3();

    std::cout << "\n\n--- Allergies ---\n";
    for (const auto& a : allergies) std::cout << "- " << a << "\n";
    if (allergies.empty()) std::cout << "None\n";

    std::cout << "\n--- Medical Conditions ---\n";
    for (const auto& m : medicalConditions) std::cout << "- " << m << "\n";
    if (medicalConditions.empty()) std::cout << "None\n";

    std::cout << "\n--- Notes ---\n";
    for (const auto& n : notes) std::cout << "- " << n.get_text() << " : " << n.get_digital_signature() << "\n";
    if (notes.empty()) std::cout << "None\n";

    std::cout << "\nPrimary Language: " << primaryLanguage;
    std::cout << "\nText Alerts: " << textAlerts;
    std::cout << "\n90-Day Supply: " << ninetyDaySupply << "\n";
}





// Mutators
void Patient::set_first_name(const std::string& first) {
    name.first = first;
}

void Patient::set_last_name(const std::string& last) {
    name.second = last;
}

void Patient::set_middle_initial(const std::string& initial) {
    if (initial.size() != 1) {
        throw std::invalid_argument("Multi-character input used on set_middle_initial()");
    } else if (!is_alpha(initial)) {
        throw std::invalid_argument("Non-alpha input used on set_middle_initial()");
    } else {
        middleInitial = initial[0];
    }
}

void Patient::set_date_of_birth(const std::string& dob) {
    dateOfBirth = Date(dob);
}

void Patient::set_sex(const char& x) {
    char temp = toupper(x);
    if(temp != 'M' && temp != 'F') throw std::invalid_argument("Sex must be M or F.");
    sex = temp;
}

void Patient::set_address(const Address& x) {
    address = x;
}

void Patient::add_phone_number(const std::string& x) {
    auto it = std::find(phoneNumbers.begin(), phoneNumbers.end(), x);
    
    if (it != phoneNumbers.end()) {
        throw std::invalid_argument("Duplicate phone numbers are not allowed.");
    } else if (phoneNumbers.size() >= 3) {
        throw std::length_error("Max phone numbers reached. Please remove one before adding another.");
    } else {
        phoneNumbers.push_back(x);
    }
}

void Patient::remove_phone_number(const std::string& x) {
    auto it = std::find(phoneNumbers.begin(), phoneNumbers.end(), x);
    if (it != phoneNumbers.end()) {
        phoneNumbers.erase(it);
        
    } else {
        throw std::invalid_argument("Phone number to delete could not be found.");
    }
}

void Patient::set_primary_phone_number(const std::string& x) {
    auto it = std::find(phoneNumbers.begin(), phoneNumbers.end(), x);
    if (it == phoneNumbers.end()) {
        throw std::invalid_argument("Phone number being set to primary has not been added yet.");
    } else {
        phoneNumbers.erase(it);
        phoneNumbers.insert(phoneNumbers.begin(), x);
    }
}

void Patient::add_allergy(const std::string& x) {
    auto it = std::find(allergies.begin(), allergies.end(), x);
    if (it != allergies.end()) throw std::invalid_argument("Duplicate allergies are not allowed.");
    allergies.push_back(x);
}

void Patient::remove_allergy(const std::string& x) {
    auto it = std::find(allergies.begin(), allergies.end(), x);
    if (it != allergies.end()) {
        allergies.erase(it);
        
    } else {
        throw std::invalid_argument("Allergy to delete could not be found.");
    }
}

void Patient::add_medical_condition(const std::string& x) {
    auto it = std::find(medicalConditions.begin(), medicalConditions.end(), x);
    if (it != medicalConditions.end()) throw std::invalid_argument("Duplicate medical conditions not allowed.");
    medicalConditions.push_back(x);
}

void Patient::remove_medical_condition(const std::string& x) {
    auto it = std::find(medicalConditions.begin(), medicalConditions.end(), x);
    if (it != medicalConditions.end()) {
        medicalConditions.erase(it);
        
    } else {
        throw std::invalid_argument("Medical condition to delete could not be found.");
    }
}

void Patient::add_note(const Note& x) {
    notes.push_back(x);
}

void Patient::remove_note(const Note& x) {
    auto it = std::find(notes.begin(), notes.end(), x);
    if (it != notes.end()) {
        notes.erase(it);
        
    } else {
        throw std::invalid_argument("Note to delete could not be found.");
    }
}

void Patient::set_primary_language(const std::string& x) {
    primaryLanguage = x;    // Will use dropdown menu for selecting language
}

void Patient::set_text_alerts(const char& x) {
    char temp = toupper(x);
    if(temp != 'Y' && temp != 'N') throw std::invalid_argument("Must use Y or N.");
    textAlerts = temp;
}

void Patient::set_ninety_day_supply(const char& x) {
    char temp = toupper(x);
    if(temp != 'Y' && temp != 'N') throw std::invalid_argument("Must use Y or N.");
    ninetyDaySupply = temp;
}
