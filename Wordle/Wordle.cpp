#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int mainMenu();
int mySizeOf(const char* str);
int myChoice();
int countWords();
bool blankSpacesCheck(char* str);
bool stringsEqual(const char* str1, const char* str2);
bool usernameExists(const char* str, const char* filepath);
bool passwordExists(const char* username, const char* password, const char* filepath);
bool checkWord(char* word);
bool wordRepeats(char* word);
void rightUsersData(char* username, char* password);
void registerUser(const char* filepath);
void logInUser(const char* users);
void adminDuties(const char* usersFilepath);
void editWordList();
void wordDeletion(const char* filepath);
void wordAddition(const char* filepath);
void actionCheck(char* str);
void updateLeaderboard(const char* leaderboard, bool wonGame);
void checkLeaderboard();
bool gameplay();
char* randomWord();

const int DATA_SIZE = 16;
const int WORD_SIZE = 6;
const int ALPHABET = 26;
const int LETTER_COUNT = 2;
const char users[] = { "users.txt" };
const char words[] = { "words.txt" };
const char leaderboard[] = { "leaderboard.txt" };
const char* GREEN = "\033[32m";
const char* YELLOW = "\033[33m";
const char* RESET = "\033[0m";
const char* RED = "\033[31m";
const char* PURPLE = "\033[35m";

int main()
{
    int choice = mainMenu();


    return 0;
}

int mainMenu() {
    std::cout << PURPLE << "\t    Main menu " << RESET << std::endl;
    std::cout << "Please choose one of the following options: " << std::endl;
    std::cout << "1. Sign in as an existing user" << std::endl;
    std::cout << "2. Register as a new user " << std::endl;
    std::cout << "3. Exit " << std::endl;
    std::cout << "Your choice: " << std::endl;
    int user_choice = myChoice();
    char users[] = { "users.txt" };
    if (user_choice == 1) {
        logInUser(users);
    }
    else if (user_choice == 2) {
        registerUser(users);
    }
    return user_choice;
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
            std::cout << RED << "Not a valid input. Enter 1, 2 or 3. Try again! " << RESET << std::endl;
            std::cout << "Please, enter your choice: ";
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
    if (str1 == nullptr || str2 == nullptr) {
        std::cout << "Nullpointer error. \n";
        return 0;
    }

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
        std::cout << RED << "A connection with the database could not be established." << std::endl;
        std::cout << "Please close the program and try again." << RESET;
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

bool passwordExists(const char* username, const char* password, const char* filepath) {
    if (password == nullptr || filepath == nullptr || username == nullptr) {
        std::cout << "Nullpointer error.";
        return 0;
    }
    std::ifstream ifs(filepath);
    if (!ifs.is_open()) {
        std::cout << RED << "A connection with the database could not be established." << std::endl;
        std::cout << "Please close the program and try again." << RESET;
        return 0;
    }

    char u[DATA_SIZE];
    char p[DATA_SIZE];

    while (ifs >> u >> p) {
        if (stringsEqual(u,username) && stringsEqual(p, password)) {

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
        if (mySizeOf(username) > 15 || mySizeOf(username) == 0) {
            std::cout << RED << "The username must be under 16 characters." << RESET << std::endl;
            std::cout << "Username:";
            std::cin.getline(username, DATA_SIZE);
            std::cout << std::endl;
            continue;
        }

        if (!(blankSpacesCheck(username))) {
            std::cout << RED << "The username must not contain blank spaces." << RESET << std::endl;
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
            std::cout << RED << "The password must be under 16 characters." << RESET << std::endl;
            std::cout << "Password: ";
            std::cin.getline(password, DATA_SIZE);
            std::cout << std::endl;
            continue;
        }

        if (!(blankSpacesCheck(password))) {
            std::cout << RED << "The password must not contain blank spaces." << RESET << std::endl;
            std::cout << "Password: ";
            std::cin.getline(password, DATA_SIZE);
            std::cout << std::endl;
            continue;
        }
        rightPassword = true;
    }
    std::cout << "Your username: " << username << " and password: " << password << std::endl;
    std::cout << std::endl;
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
        std::cout << RED << "This username is taken. Please choose a different one." << RESET << std::endl;
        rightUsersData(username, password);
    }

    std::ofstream ofs(filepath, std::ios::app);

    if (!ofs.is_open()) {
        std::cout << RED << "A connection with the database could not be established." << RESET << std::endl;
        std::cout << "Please close the program and try again.";
        return;
    }

    ofs << username << " " << password << std::endl;
    ofs.close();

    std::cout << GREEN << "Registration successful!" << RESET << std::endl;

    mainMenu();
}

void logInUser(const char* users) {
    if (users == nullptr) {
        std::cout << "Nullpointer error.";
        return;
    }

    const char adminUser[] = { "Boyan" };
    const char adminPass[] = { "1234" };

    char username[DATA_SIZE], password[DATA_SIZE];
    rightUsersData(username, password);
    if (stringsEqual(username, adminUser) && stringsEqual(password, adminPass)) {
        adminDuties(users);
    }
    else {
        std::ifstream ifs(users);

        if (!ifs.is_open()) {
            std::cout << RED << "A connection with the database could not be established." << RESET << std::endl;
            std::cout << "Please close the program and try again.";
            return;
        }
        if (passwordExists(username, password, users)) {
            bool wonGame = gameplay();
            updateLeaderboard(username, wonGame);
            ifs.close();
            mainMenu();
        }

        std::cout << RED << "No such user was found. Check your login and password information. \n" << RESET;
        ifs.close();
        mainMenu();
    }
}

void adminDuties(const char* usersFilepath) {
    if (usersFilepath == nullptr) {
        std::cout << "Nullpointer error.";
        return;
    }

    std::cout << YELLOW << "You are now logged in as an admin \n" << RESET;
    std::cout << "You can either: \n";
    std::cout << "1. Check the leaderboard \n";
    std::cout << "2. Edit the word list \n";
    std::cout << "3. Return to the main menu \n";
    std::cout << "Please select your decision: ";
    int decision = myChoice();
    if (decision == 1) {
        checkLeaderboard();
    }
    else if (decision == 2) {
        editWordList();
    }
    else {
        mainMenu();
    }
}

void actionCheck(char* str) {
    if (str == nullptr) {
        std::cout << "Nullpointer error.";
        return;
    }

    bool rightStr = false;

    while (!rightStr) {
        if (mySizeOf(str) > 15 || mySizeOf(str) == 0) {
            std::cout <<RED<< "The action must be 'add', 'delete' or 'back'." <<RESET<< std::endl;
            std::cout << "Action:";
            std::cin.getline(str, DATA_SIZE);
            std::cout << std::endl;
            continue;
        }

        if (!(blankSpacesCheck(str))) {
            std::cout <<RED<< "The action must not contain blank spaces." <<RESET<< std::endl;
            std::cout << "Action:";
            std::cin.getline(str, DATA_SIZE);
            std::cout << std::endl;
            continue;
        }
        rightStr = true;
    }
}

void editWordList() {
    std::cout << "What would you like to do? \n";
    std::cout << "Enter 'delete' to remove words from the list, 'add' to include or 'back'. \n";
    std::cout << "Action: ";
    char removal[] = { "delete" };
    char add[] = { "add" };
    char back[] = {"back"};
    char action[DATA_SIZE];
    std::cin>>std::ws;
    std::cin.getline(action, DATA_SIZE);

    if (stringsEqual(action, removal)) {
        wordDeletion(words);
    }
    else if (stringsEqual(action, add)) {
        wordAddition(words);
    }
    else if(stringsEqual(action, back)){
        adminDuties(users);
    }else {
        std::cout << RED << "The action must be 'add', 'delete' or 'back'." << RESET << std::endl;
        actionCheck(action);
        editWordList();
    }
}

bool checkWord(char* word) {
    if (word == nullptr) {
        std::cout << "Nullpointer error. \n";
        return 0;
    }
    int cnt = 0;
    while (*word != '\0') {
        if (!(*word >= 'a' && *word <= 'z')) {
            return false;
        }
        word++;
        cnt++;
    }
    if (cnt != 5)
        return false;
    return true;
}

bool wordRepeats(char* word) {
    if (word == nullptr) {
        std::cout << "Nullpointer error. \n";
        return 0;
    }
    std::ofstream ofs(words, std::ios::app);
    if (!ofs.is_open()) {
        std::cout << RED << "A connection with the database could not be established." << RESET << std::endl;
        std::cout << "Please close the program and try again." << std::endl;
        return 0;
    }
    ofs.close();

    std::ifstream ifs(words);
    if (!ifs.is_open()) {
        std::cout << RED << "A connection with the database could not be established." << RESET << std::endl;
        std::cout << "Please close the program and try again." << std::endl;
        return 0;
    }
    char currentWord[WORD_SIZE];
    while (ifs >> currentWord) {
        if (stringsEqual(currentWord, word)) {
            std::cout << RED << "This word already exists in the file. \n" << RESET;
            ifs.close();
            return 0;
        }
    }
    ifs.close();
    return 1;
}

void wordAddition(const char* filepath) {
    if (filepath == nullptr) {
        std::cout << "Nullpointer error. \n";
        return;
    }

    char newWord[WORD_SIZE];
    std::cout << "Enter the new word: ";
    std::cin.getline(newWord, WORD_SIZE);

    if (checkWord(newWord) && wordRepeats(newWord)) {

        std::ofstream ofs(filepath, std::ios::app);

        if (!ofs.is_open()) {
            std::cout << RED << "A connection with the database could not be established." << RESET << std::endl;
            std::cout << "Please close the program and try again.";
            return;
        }

        ofs << newWord << std::endl;

        ofs.close();
        std::cout << GREEN << "Word added successfully. \n" << RESET;
        editWordList();

    }
    else {
        std::cout << RED << "The words must be made up of 5 small Latin letters and must not already exist in the file. \n" << RESET;
        std::cout << "Try again. \n";
        wordAddition(filepath);
    }

}

void wordDeletion(const char* filepath) {
    if (filepath == nullptr) {
        std::cout << "Nullpointer error. \n";
        return;
    }
    char wordToRemove[WORD_SIZE];
    std::cout << "Enter the word you want to delete: ";
    std::cin.getline(wordToRemove, WORD_SIZE);

    if (checkWord(wordToRemove) && !wordRepeats(wordToRemove)) {

        std::ofstream createFile(filepath, std::ios::app);
        createFile.close();

        std::ifstream ifs(filepath);

        if (!ifs.is_open()) {
            std::cout << RED << "A connection with the database could not be established." << RESET << std::endl;
            std::cout << "Please close the program and try again.";
            return;
        }

        char temp[] = { "temp.txt" };
        std::ofstream ofs(temp);

        if (!ofs.is_open()) {
            std::cout << RED << "Could not create a temporary file." << RESET << std::endl;
            std::cout << "Please close the program and try again.";
            ifs.close();
            return;
        }

        char currentWord[WORD_SIZE];
        bool found = false;

        while (ifs >> currentWord) {
            if (!stringsEqual(currentWord, wordToRemove)) {
                ofs << currentWord << std::endl;
            }
            else {
                found = true;
            }
        }
        ifs.close();
        ofs.close();

        if (!found) {
            std::cout << RED <<"The word was not found. \n" << RESET;
            remove(temp);
            return;
        }

        remove(filepath);
        rename(temp, filepath);

        std::cout << GREEN << "Word removed successfully. \n" << RESET;
        editWordList();

    }
    else {
        std::cout <<RED<< "The words must be made up of 5 small Latin letters and already be in the file. \n";
        std::cout <<RESET<< "Try again. \n";
        wordDeletion(filepath);
    }
}

int countWords() {
    std::ifstream ifs(words);
    if (!ifs.is_open()) {
        std::cout <<RED<< "A connection with the database could not be established." <<RESET<< std::endl;
        std::cout << "Please close the program and try again.";
        return 0;
    }

    int count = 0;
    char currentWord[WORD_SIZE];

    while (ifs >> currentWord) {
        count++;
    }
    ifs.close();
    return count;
}

char* randomWord() {
    int totalWords = countWords();
    if (totalWords == 0) {
        std::cout << RED << "There are no words to play with. \n" << RESET;
        std::cout << "Please wait till the admin updates the list. \n";
        return nullptr;
    }
    srand(time(nullptr));
    int randomIndex = rand() % countWords();

    std::ifstream ifs(words);
    if (!ifs.is_open()) {
        std::cout << RED << "A connection with the database could not be established." << RESET << std::endl;
        std::cout << "Please close the program and try again.";
        return nullptr;
    }
    char currentWord[WORD_SIZE];
    int currentIndex = 0;
    while (ifs >> currentWord) {
        if (currentIndex == randomIndex) {
            char* randomWord = new char[WORD_SIZE];
            int i = 0;
            while (currentWord[i] != '\0') {
                randomWord[i] = currentWord[i];
                i++;
            }
            randomWord[i] = '\0';
            ifs.close();
            return randomWord;
        }
        currentIndex++;
    }
    ifs.close();
    return nullptr;
}

bool yellowLetters(char a, int matrix[ALPHABET][LETTER_COUNT]) {
    if (matrix == nullptr) {
        std::cout << "Nullpointer error. \n";
        return 0;
    }

    int index = a - 'a';
    if (matrix[index][1] != 0) {
        matrix[index][1]--;
        return 1;
    }
    return 0;
}

void matrixFill(char* secretWord, int matrix[ALPHABET][LETTER_COUNT]) {
    if (secretWord == nullptr || matrix == nullptr) {
        std::cout << "Nullpointer error. \n";
        return;
    }

    int k = 0;
    for (int i = 0; i < ALPHABET; i++) {
        matrix[i][0] = 'a' + i;
        matrix[i][1] = 0;
    }
    while (secretWord[k] != '\0') {
        int index = secretWord[k] - 'a';
        matrix[index][1]++;
        k++;

    }
}

bool gameplay() {
    char* secretWord;
    secretWord = randomWord();;

    int matrix[ALPHABET][LETTER_COUNT];
    matrixFill(secretWord, matrix);

    const int GUESSES = 6;
    int currentGuess = 1;
    char guessedWord[WORD_SIZE];

    while (currentGuess <= GUESSES) {
        int tempMatrix[ALPHABET][LETTER_COUNT];
        for (int i = 0; i < ALPHABET; i++) {
            tempMatrix[i][1] = matrix[i][1];
        }

        std::cout << currentGuess << ". guess: ";
        std::cin >> guessedWord;
        std::cout << std::endl;

        if (!checkWord(guessedWord)) {
            std::cout << RED << "Invalid word. Must be 5 small latin letters. \n" << RESET;
            continue;
        }
        char w[WORD_SIZE];
        bool exists = false;
        std::ifstream ifs(words);
        while (ifs >> w) {
            if (stringsEqual(guessedWord, w)) {
                exists = true;
            }
        }
        if (!exists) {
            std::cout << RED << "Not in word list. \n" << RESET;
            continue;
        }
        ifs.close();
        int i = 0;
        bool green[WORD_SIZE] = { false };
        while (guessedWord[i] != '\0') {
            if (guessedWord[i] == secretWord[i])
            {
                int index = guessedWord[i] - 'a';
                green[i] = true;
                tempMatrix[index][1]--;
            }
            i++;
        }
        i = 0;
        while (guessedWord[i] != '\0') {
            if (green[i])
            {
                std::cout << GREEN << guessedWord[i] << RESET;
            }
            else if (yellowLetters(guessedWord[i], tempMatrix)) {
                std::cout << YELLOW << guessedWord[i] << RESET;
            }
            else {
                std::cout << guessedWord[i];
            }
            i++;
        }

        if (stringsEqual(guessedWord, secretWord)) {
            std::cout << std::endl;
            std::cout << PURPLE << "You won \n" << RESET;
            delete[] secretWord;
            return 1;
        }

        currentGuess++;
        std::cout << std::endl;
    }

    delete[] secretWord;
    std::cout << RED << "You could not guess the word in 6 guesses. \n" << RESET;
    std::cout << YELLOW << "Better luck next time. \n" << RESET;
    return 0;
}

void updateLeaderboard(const char* username, bool wonGame) {
    if (username == nullptr) {
        std::cout << "Nullpointer error. \n";
        return;
    }
    std::ofstream ofs(leaderboard, std::ios::app);

    if (!ofs.is_open()) {
        std::cout << RED << "A connection with the database could not be established." << RESET << std::endl;
        std::cout << "Please close the program and try again.";
        return;
    }
    ofs.close();

    const char tempFilepath[] = { "temp.txt" };
    std::ifstream ifs(leaderboard);
    std::ofstream temp(tempFilepath);
    if (!temp.is_open() || !ifs.is_open()) {
        std::cout << RED << "A connection with the database could not be established." << RESET << std::endl;
        std::cout << "Please close the program and try again.";
        return;
    }

    
    char checkExistence[DATA_SIZE];
    int gamesWon = 0;
    int gamesPlayed = 0;
    bool exists = false;

    while (ifs >> checkExistence >> gamesWon >> gamesPlayed) {
        if (stringsEqual(checkExistence, username)) {
            gamesPlayed++;
            if (wonGame) {
                gamesWon++;
            }
            exists = true;
        }
        temp << checkExistence << " " << gamesWon << " " << gamesPlayed << std::endl;
    }

    
    if (!exists) {
        temp << username << " " << (wonGame ? 1 : 0) <<" " << 1 << std::endl;
    }
    ifs.close();
    temp.close();
    
    remove(leaderboard);
    rename(tempFilepath, leaderboard);

}

void checkLeaderboard() {
    
}