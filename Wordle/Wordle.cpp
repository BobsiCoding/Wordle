#include <iostream>
#include <fstream>
#include <cstdlib>

void mainMenu();
int mySizeOf(const char* str);
int myChoice();
bool blankSpacesCheck(char* str);
bool stringsEqual(const char* a, const char* b);
bool usernameExists(const char* str, const char* filepath);
void rightUsersData(char* username, char* password);
void registerUser(const char* filepath);

const int DATA_SIZE = 16;

int main()
{
    mainMenu();
    int user_choice = myChoice();
    char filepath[] = { "users.txt" };
    if (user_choice == 1) {

    }
    else if (user_choice == 2) {
        registerUser(filepath);
    }

}

void mainMenu() {
    std::cout << "\t    Main menu "<<std::endl;
    std::cout << "Please choose one of the following options: " << std::endl;
    std::cout << "1. Sign in as an existing user" << std::endl;
    std::cout << "2. Register as a new user " << std::endl;
    std::cout << "3. Exit " << std::endl;
    std::cout << "Your choice: " << std::endl;
}

int mySizeOf(const char* str) {
    if (str == nullptr) {
        std::cout << "Nullpointer error.";
        return 0;
    }
    int cnt = 0;
    while (*str != '\0') {
        cnt++;
        str++;
    }
    return cnt;
}

int myChoice() {
    const int INPUTSIZE = 16;
    char choice[INPUTSIZE];
    std::cin >> choice;
    bool validChoice = false;
    while (!validChoice) {
        if (*choice < '1' || *choice > '3' || mySizeOf(choice) > 1) {
            std::cout << "Not a valid input. Try aggain: "<<std::endl;
            std::cout << "Please enter your choice: ";
            std::cin >> choice;
        }
        else {
            validChoice = true;
        }
    }
    return *choice - '0';
}

bool blankSpacesCheck(char* str) {
    if (str == nullptr) {
        std::cout << "Nullpointer error.";
        return 0;
    }
    while (*str != '\0') {
        if (*str == ' ' || *str == '\t')
            return 0;
        str++;
    }
    return 1;

}

bool stringsEqual(const char* str1, const char* str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2)
            return false;
        str1++;
        str2++;
    }
    if (mySizeOf(str1) != mySizeOf(str2))
        return false;
    return true;
}
    
bool usernameExists(const char* username, const char* filepath) {
    if (username == nullptr || filepath == nullptr) {
        std::cout << "Nullpointer error.";
        return 0;
    }
    std::ifstream ifs(filepath);
    if (!ifs.is_open()) {
        std::cout << "A connection with the database could not be established." << std::endl;
        std::cout << "Please close the program and try again.";
        return 0;
    }

    char u[DATA_SIZE];
    char p[DATA_SIZE];

    while (ifs >> u >> p) {
        if (stringsEqual(u, username)) {

            ifs.close();
            return true;
        }
    }
    ifs.close();
    return false;
}

void rightUsersData(char* username, char* password) {
    if (username == nullptr || password == nullptr) {
        std::cout << "Nullpointer error.";
        return;
    }
    
    std::cout << "Username: ";
    std::cin >> std::ws;
    std::cin.getline(username, DATA_SIZE);
    std::cout << std::endl;
    bool rightUsername = false;

    while (!rightUsername) {
        if (mySizeOf(username) > 15 || mySizeOf(username) == 0 ) {
            std::cout << "The username must be under 16 characters." << std::endl;
            std::cout << "Username:";
            std::cin.getline(username, DATA_SIZE);
            std::cout << std::endl;
            continue;
        }

        if (!(blankSpacesCheck(username))) {
            std::cout << "The username must not contain blank spaces." << std::endl;
            std::cout << "Username:";
            std::cin.getline(username, DATA_SIZE);
            std::cout << std::endl;
            continue;
        }
        rightUsername = true;
    }

    std::cout << "Password: ";
    std::cin.getline(password, DATA_SIZE);
    std::cout << std::endl;

    bool rightPassword = false;

    while (!rightPassword) {
        if (mySizeOf(password) > 15 || mySizeOf(password) == 0) {
            std::cout << "The password must be under 16 characters." << std::endl;
            std::cout << "Password: ";
            std::cin.getline(password, DATA_SIZE);
            std::cout << std::endl;
            continue;
        }

        if (!(blankSpacesCheck(password))) {
            std::cout << "The password must not contain blank spaces." << std::endl;
            std::cout << "Password: ";
            std::cin.getline(password, DATA_SIZE);
            std::cout << std::endl;
            continue;
        }
        rightPassword = true;
    }
    std::cout << "Your username: " << username << " and password: " << password << std::endl;
}

void registerUser(const char* filepath) {
    if (filepath == nullptr) {
        std::cout << "Nullpointer error.";
        return;
    }

    char username[DATA_SIZE];
    char password[DATA_SIZE];

    std::cout << "Please enter your username and password." << std::endl;
    std::cout << "They must be under under 16 characters long. ";
    std::cout << "They must not contain blank spaces. " << std::endl;

    rightUsersData(username, password);


    while (usernameExists(username, filepath)) {
        std::cout << "This username is taken. Please choose a different one." << std::endl;
        rightUsersData(username, password);
    }

    std::ofstream ofs(filepath, std::ios::app);

    if (!ofs.is_open()) {
        std::cout << "A connection with the database could not be established." << std::endl;
        std::cout << "Please close the program and try again.";
        return;
    }

    ofs << username << " " << password << std::endl;
    ofs.close();

    std::cout << "Registration successful!" << std :: endl;

}

