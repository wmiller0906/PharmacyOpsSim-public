#include <iostream>
#include <sodium.h>
#include <string>
#include "Address.h"
#include "My_Utility.h"
#include "User.h"

using namespace std;


// FUNCTION DECLARATIONS
void setup();
void test_user_base_features(User& x);
void test_user_password(User& x);

int main() {
    setup();
    
    // TEST USER
    User me(true);
    //test_user_base_features(me);
    //test_user_password(me);
    
    return 0;
}

// Setup function to initialize any objects needed
void setup() {
    if (sodium_init() < 0) throw std::runtime_error("libsodium initialization failed");
}


/*----------------
    GUI TESTS
----------------*/
// VERIFIED
void test_user_base_features(User& x) {
    // Test accessors
    cout << x.get_name().first << " " << x.get_name().second << endl;
    cout << x.get_initials() << endl;
    cout << x.get_id() << endl;
    cout << x.get_title() << endl;
    cout << x.get_access_code() << endl;
    
    // Test mutators
    x.set_name("xxxxx", "xxxxx");
    x.set_initials("x");
    x.set_id("1111111");
    x.set_title("Certified Technician");
    
    // Verify mutators
    x.print_info();
}

// VERIFIED
void test_user_password(User& x) {
    // TEST get_password();
    cout << x.get_password() << endl;
    
    // TEST authenticate();
    string password;
    cout << "Testing login with authenticate()" << endl;
    cout << "Enter password: ";
    cin >> password;
    password = to_uppercase(password);
    if(x.authenticate(password)) { cout << "Successfully authenticated." << endl; }
    else { cout << "Failed to authenticate." << endl; }
}
