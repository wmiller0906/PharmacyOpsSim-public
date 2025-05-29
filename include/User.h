#ifndef USER_H
#define USER_H

#include <string>
#include <utility>

/*
  This is the profile of the user.
  Contains relevant information such as name, initials, employeeID, title, and access level. 
  Used to record who made certain actions and determine program access.
*/
class User {
    private:
        std::pair<std::string, std::string> name;
        std::string userInitials;   // Functions as a signature and login username
        std::string employeeID;     // Up to 7 digits
        std::string title;          // The formal name for the selected title
        std::string accessCode;     // Title code used for access in operations management software
        std::string username;       // Required for HIPAA compliance of digital signatures
        std::string passwordHash;
        
        // Helper functions
        void gather_name();         // CLI
        void gather_initials();     // CLI
        void gather_id();           // CLI
        void gather_title();        // CLI
        void create();              // CLI
        void assign_id(const std::string& pos);
        void generate_password();
        
    public:
        // Constructor
        User(); // Default for GUI
        User(bool CLI); // CLI
        
        // Accessors
        std::pair<std::string, std::string> get_name() const;
        std::string get_initials() const;
        std::string get_id() const;
        std::string get_title() const;
        std::string get_access_code() const;
        std::string get_username() const;
        std::string get_password() const;
        void print_info();  // CLI
        
        // Mutators
        void set_name(const std::string& first, const std::string& last);
        void set_initials(const std::string& middleInitial);
        void set_id(const std::string& id);
        void set_title(const std::string& pos);
        void reset_password();
        
        // Authentication
        bool authenticate(const std::string& password) const;
};

#endif
