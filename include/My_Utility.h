#ifndef MY_UTILITY_H
#define MY_UTILITY_H

#include <algorithm>
#include <cctype>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

/* ENTRIES
1. to_uppercase()
2. get_valid_int()
3. get_valid_char()
4. capitalize()
5. get_current_time()
6. append_log()
*/

// 1. Converts a string input to uppercase. Used for clarity when reading sensitive info (PT address, prescription directions, etc)
inline std::string to_uppercase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}


// 2. Used for menu selection. Ensures that the input always fits within the range for the menu and repeats until the user complies. Returns the menu selection int.
inline int get_valid_int(const std::string& prompt, int min, int max) {
    int value;
    std::cout << prompt;
    std::cin >> value;

    while (std::cin.fail() || value < min || value > max) {
        std::cin.clear(); // reset stream
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush invalid input
        std::cout << "Invalid input. " << prompt;
        std::cin >> value;
    }

    return value;
}


// 3. Used to gather Y or N for decisions. Verifies that y, Y, n, or N was entered and repeats until the user complies. Always returns uppercase.
inline char get_valid_char(const std::string& prompt) {
    char input;
    std::cout << prompt;
    std::cin >> input;

    while (std::cin.fail() || (std::toupper(input) != 'Y' && std::toupper(input) != 'N')) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. " << prompt;
        std::cin >> input;
    }

    return std::toupper(input);
}


// 4. Used to capitalize the first letter of a word and lowercase the rest
inline std::string capitalize(const std::string& input) {
    if (input.empty()) { return input; }
    std::string result = input;
    result[0] = std::toupper(result[0]);
    for (size_t i = 1; i < result.length(); ++i) {
        result[i] = std::tolower(result[i]);
    }
    return result;
}


// 5. Acquires current time for signatures and record keeping
inline std::string get_current_time() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
    
#ifdef _WIN32
    localtime_s(&tm, &time); // Windows-specific
#else
    tm = *std::localtime(&time);
#endif

    
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}


// 6. Appends digital signature to a write-only log
inline void append_log(const std::string& entry) {
    std::ofstream logFile("DigSigLog.txt", std::ios::app); // append mode
    if (!logFile) throw std::runtime_error("Cannot open log file.");
    logFile << entry << "\n";
    logFile.close();
}


#endif
