#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <utility>
#include <vector>

#include "Address.h"
#include "Date.h"
#include "Note.h"


class Patient {
    private:
        std::pair<std::string, std::string> name;
        std::string middleInitial;
        Date dateOfBirth;   // MM/DD/YYYY
        char sex;   // M/F
        Address address;
        std::vector<std::string> phoneNumbers;  // Up to 3
        std::vector<std::string> allergies;
        std::vector<std::string> medicalConditions;
        // Medication history (future class)
        std::vector<Note> notes;
        // Provider pcp;
        std::string primaryLanguage;
        char textAlerts;            // Y or N
        char ninetyDaySupply;       // Y or N
        
    public:
        // Constructors
        Patient();
        
        // Accessors
        std::string get_first_name() const;
        std::string get_last_name() const;
        std::string get_full_name() const;
        std::string get_middle_initial() const;
        std::string get_date_of_birth() const;
        char get_sex() const;
        std::string get_address_street() const;
        std::string get_address_full() const;
        std::string get_phone_number_1() const;
        std::string get_phone_number_2() const;
        std::string get_phone_number_3() const;
        const std::vector<std::string>& get_allergies() const;
        const std::vector<std::string>& get_medical_conditions() const;
        const std::vector<Note>& get_notes() const;
        std::string get_primary_language() const;
        char get_text_alerts() const;
        char get_ninety_day_supply() const;
        void print() const;     // CLI Debugging
        
        // Mutators
        void set_first_name(const std::string& first);
        void set_last_name(const std::string& last);
        void set_middle_initial(const std::string& initial);
        void set_date_of_birth(const std::string& dob);
        void set_sex(const char& x);
        void set_address(const Address& x);     // Consider use of Address struct
        void add_phone_number(const std::string& x); // Consider num 1, 2, or 3
        void remove_phone_number(const std::string& x);
        void set_primary_phone_number(const std::string& x);
        void add_allergy(const std::string& x);
        void remove_allergy(const std::string& x);
        void add_medical_condition(const std::string& x);
        void remove_medical_condition(const std::string& x);
        void add_note(const Note& x);
        void remove_note(const Note& x);
        void set_primary_language(const std::string& x);
        void set_text_alerts(const char& x);
        void set_ninety_day_supply(const char& x);
};

#endif