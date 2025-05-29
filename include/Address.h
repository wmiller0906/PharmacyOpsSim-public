#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

class Address {
    private:
        std::string street1;
        std::string street2;
        std::string city;
        std::string state;
        std::string zipCode;
    public:
        // Constructors
        Address();
        Address(std::string s1, std::string c, std::string s, std::string z);
        Address(std::string s1, std::string s2, std::string c, std::string s, std::string z);
    
        // Accessors
        std::string get_address() const;
        std::string get_street() const;
        std::string get_city() const;
        std::string get_state() const;
        std::string get_zip() const;
        
        // Mutators
        void change_street1(const std::string& s);
        void change_street2(const std::string& s);
        void change_city(const std::string& s);
        void change_state(const std::string& s);
        void change_zip(const std::string& z);
};

#endif