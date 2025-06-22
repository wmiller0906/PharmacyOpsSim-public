#include "Note.h"

#include "My_Utility.h"
#include "User.h"

// Constructor
Note::Note() : 
    text(""),
    author(""),
    dateAndTime(""),
    digitalSignature("") {}
    
// Factory function
Note Note::create_note(const std::string& input, const User& user) {
    Note n;
    
    n.text = input;
    n.author = user.get_initials();
    n.dateAndTime = get_current_time();
    n.digitalSignature = n.author + "@" + n.dateAndTime;
    
    append_log(n.digitalSignature);
    return n;
}

// Accessor
std::string Note::get_text() const {
    return text;
}

std::string Note::get_author() const {
    return author;
}


std::string Note::get_date() const {
    if(dateAndTime.length() < 10) {
        throw std::invalid_argument("dateAndTime string too short");
    }
    
    std::string year = dateAndTime.substr(0, 4);
    std::string month = dateAndTime.substr(5, 2);
    std::string day = dateAndTime.substr(8, 2);
    
    return month + "/" + day + "/" + year;
}

std::string Note::get_digital_signature() const {
    return digitalSignature;
}



// Operator overloading
bool Note::operator==(const Note& other) const {
    return text == other.text &&
           author == other.author &&
           dateAndTime == other.dateAndTime &&
           digitalSignature == other.digitalSignature;
}
