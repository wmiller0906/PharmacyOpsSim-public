#ifndef NOTE_H
#define NOTE_H

#include <string>

class User;

class Note {
    private:
        std::string text;
        std::string author;
        std::string dateAndTime;
        std::string digitalSignature;
        
    public:
        // Constructor
        Note();
    
        // Factory function
        static Note create_note(const std::string& input, const User& user);
        
        // Accessor
        std::string get_text() const;
        std::string get_author() const;
        std::string get_date() const;
        std::string get_digital_signature() const;
        
        // Operator overloading
        bool operator==(const Note& other) const;
};

#endif
