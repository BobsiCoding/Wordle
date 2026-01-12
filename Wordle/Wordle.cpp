#include <iostream>
#include <fstream>
#include <cstdlib>

void mainMenu() {
    std::cout << "\t    Main menu "<<std::endl;
    std::cout << "Please choose one of the following options: " << std::endl;
    std::cout << "1. Sign in as an existing user" << std::endl;
    std::cout << "2. Register as a new user " << std::endl;
    std::cout << "3. Exit " << std::endl;
    std::cout << "Your choice: " << std::endl;
}

int myChoice() {
    int choice = 0;
    std::cin >> choice;
    bool validChoice = false;
    while (!validChoice) {
        if (choice < 1 || choice > 3) {
            std::cout << "Not a valid input. Try aggain: "<<std::endl;
            std::cout << "Please enter your choice: ";
            std::cin >> choice;
        }
        else {
            validChoice = true;
        }
    }
    return choice;
}

int main()
{
    mainMenu();
    int choice = myChoice();
}
