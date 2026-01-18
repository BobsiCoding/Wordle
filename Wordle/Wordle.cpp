#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

//Some const values that we are going to need
const int DATA_SIZE = 64;
const int WORD_SIZE = 6;
const int ALPHABET = 26;
const int LETTER_COUNT = 2;
const int USERNAME_SIZE = 15;
const int PASSWORD_SIZE = 15;
const int ACTION_SIZE = 9;
const char removal[] = { "delete" };
const char add[] = { "add" };
const char back[] = { "back" };
const char users[] = { "users.txt" };
const char words[] = { "words.txt" };
const char tempFilepath[] = { "temp.txt" };
const char leaderboard[] = { "leaderboard.txt" };
const char* GREEN = "\033[32m";
const char* YELLOW = "\033[33m";
const char* RESET = "\033[0m";
const char* RED = "\033[31m";
const char* PURPLE = "\033[35m";

//All of our functions will be initialised here and defined after the main()
int mainMenu();
int mySizeOf(const char* str);
int myChoice();
bool blankSpacesCheck(const char* str);
bool stringsEqual(const char* str1, const char* str2);
bool usernameExists(const char* username, const char* filepath);
bool passwordMatch(const char* username, const char* password, const char* filepath);
void fileConnectionErrorMessage();
void enterUsersData(char* username, char* password);
void rightUsernameCheck(char* username);
void rightPasswordCheck(char* password);
void registerUser(const char* filepath);
void logInUser(const char* users);
void adminDuties(const char* usersFilepath);
void actionCheck(char* action);
void editWordList();
bool latinLetters(const char ch);
bool checkWord(const char* word);
bool wordRepeats(const char* word);
void wordAddition(const char* filepath);
void wordDeletion(const char* filepath);
int countWords();
char* randomWord();
bool yellowLetters(char a, int matrix[ALPHABET][LETTER_COUNT]);
void matrixFill(const char* secretWord, int matrix[ALPHABET][LETTER_COUNT]);
void gameRules();
void validGuess(int currentGuess, char* guessedWord);
void letterRepsMinusGreen(char* guessedWord, char* secretWord, bool* green, int tempMatrix[ALPHABET][LETTER_COUNT]);
void colorFeedback(char* guessedWord, bool* green, int tempMatrix[ALPHABET][LETTER_COUNT]);
bool gameplay();
void updateLeaderboard(const char* username, const bool wonGame);
double calcWinrate(double gamesWon, double gamesPlayed);
void sortByGamesPlayed(Player* arr, int size);
void checkLeaderboard();
//We are going to need this for when the admin checks the leaderboard
struct Player {
	char username[DATA_SIZE];
	int gamesWon;
	int gamesPlayed;
	double winrate;
};

int main()
{
	srand(time(nullptr));
	mainMenu();

	return 0;
}

//This will be the initial message, letting the player choose his first action
int mainMenu() {
	int user_choice;
	do {
		std::cout << PURPLE << "\t    Main menu " << RESET << std::endl;
		std::cout << "Please choose one of the following options: " << std::endl;
		std::cout << "1. Sign in as an existing user" << std::endl;
		std::cout << "2. Register as a new user " << std::endl;
		std::cout << "3. Exit " << std::endl;
		std::cout << "Your choice: " << std::endl;
		user_choice = myChoice();
		if (user_choice == 1) {
			logInUser(users);
		}
		else if (user_choice == 2) {
			registerUser(users);
		}
	} while (user_choice != 3);

	return user_choice;
}
//A function which gets the size of a string
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
//Making sure the input for choice is valid
int myChoice() {
	const int INPUTSIZE = 16;
	char choice[INPUTSIZE];
	std::cin >> std::ws;
	std::cin.getline(choice, INPUTSIZE);
	bool validChoice = false;
	while (!validChoice) {
		if (*choice < '1' || *choice > '3' || mySizeOf(choice) > 1) {
			std::cout << RED << "Not a valid input. Enter 1, 2 or 3. Try again! " << RESET << std::endl;
			std::cout << "Please, enter your choice: ";
			std::cin.getline(choice, INPUTSIZE);
		}
		else {
			validChoice = true;
		}
	}
	return *choice - '0';
}
//Making sure there are no blank spaces in the string because they are not allowed
bool blankSpacesCheck(const char* str) {
	if (str == nullptr) {
		std::cout << "Nullpointer error.";
		return false;
	}
	while (*str != '\0') {
		if (*str == ' ' || *str == '\t')
			return false;
		str++;
	}
	return true;

}
//Comparing two strings
bool stringsEqual(const char* str1, const char* str2) {
	if (str1 == nullptr || str2 == nullptr) {
		std::cout << "Nullpointer error. \n";
		return false;
	}

	do {
		if (*str1 != *str2)
			return false;
		str1++;
		str2++;
	} while (*str1 != '\0' || *str2 != '\0');
		
	return true;
}
//Checking whether a username is in the database   
bool usernameExists(const char* username, const char* filepath) {
	if (username == nullptr || filepath == nullptr) {
		std::cout << "Nullpointer error.";
		return false;
	}
	std::ifstream ifs(filepath);
	if (!ifs.is_open()) {
		fileConnectionErrorMessage();
		return false;
	}

	char user[DATA_SIZE];
	char pass[DATA_SIZE];

	while (ifs >> user >> pass) {
		if (stringsEqual(user, username)) {
			ifs.close();
			return true;
		}
	}
	ifs.close();
	return false;
}
//Checking whether a password and username matches with the one in the database
bool passwordMatch(const char* username, const char* password, const char* filepath) {
	if (password == nullptr || filepath == nullptr || username == nullptr) {
		std::cout << "Nullpointer error.";
		return false;
	}
	std::ifstream ifs(filepath);
	if (!ifs.is_open()) {
		fileConnectionErrorMessage();
		return false;
	}

	char user[DATA_SIZE];
	char pass[DATA_SIZE];

	while (ifs >> user >> pass) {
		if (stringsEqual(user, username) && stringsEqual(pass, password)) {
			ifs.close();
			return true;
		}
	}
	ifs.close();
	return false;
}
//This error message is used multiple times, so it is better if we make it its own funciton
void fileConnectionErrorMessage() {
	std::cout << "A connection with the database could not be established. \n";
	std::cout << "Please, close the program and try again. \n";
}
//Makes sure the user enters a valid username and password
void enterUsersData(char* username, char* password) {
	if (username == nullptr || password == nullptr) {
		std::cout << "Nullpointer error.";
		return;
	}

	std::cout << "Username: ";
	std::cin >> std::ws;
	std::cin.getline(username, DATA_SIZE);
	std::cout << std::endl;
	
	rightUsernameCheck(username);

	std::cout << "Password: ";
	std::cin.getline(password, DATA_SIZE);
	std::cout << std::endl;

	rightPasswordCheck(password);
	
	std::cout << "Your username: " << username << " and password: " << password << std::endl;
	std::cout << std::endl;
}
//Specifically for the username
void rightUsernameCheck(char* username) {
	if (username == nullptr) {
		std::cout << "Nullpointer error.";
		return;
	}
	bool rightUsername = false;

	while (!rightUsername) {
		if (mySizeOf(username) > USERNAME_SIZE || mySizeOf(username) == 0) {
			std::cout << RED << "The username must be under 16 characters." << RESET << std::endl;
			std::cout << "Username:";
			std::cin.getline(username, DATA_SIZE);
			std::cout << std::endl;
			continue;
		}

		if (!blankSpacesCheck(username)) {
			std::cout << RED << "The username must not contain blank spaces." << RESET << std::endl;
			std::cout << "Username:";
			std::cin.getline(username, DATA_SIZE);
			std::cout << std::endl;
			continue;
		}
		rightUsername = true;
	}

	return;
}
//Specifically for the password
void rightPasswordCheck(char* password) {
	if (password == nullptr) {
		std::cout << "Nullpointer error.";
		return;
	}

	bool rightPassword = false;

	while (!rightPassword) {
		if (mySizeOf(password) > PASSWORD_SIZE || mySizeOf(password) == 0) {
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
	return;
}
//Registering a user in the database
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

	enterUsersData(username, password);

	while (usernameExists(username, filepath)) {
		std::cout << RED << "This username is taken. Please choose a different one." << RESET << std::endl;
		enterUsersData(username, password);
	}

	std::ofstream ofs(filepath, std::ios::app);

	if (!ofs.is_open()) {
		fileConnectionErrorMessage();
		return;
	}

	ofs << username << " " << password << std::endl;
	ofs.close();

	std::cout << GREEN << "Registration successful!" << RESET << std::endl;

}
//Logging in option and separating into user nd admin profile
void logInUser(const char* users) {
	if (users == nullptr) {
		std::cout << "Nullpointer error.";
		return;
	}

	const char adminUser[] = { "Admin" };
	const char adminPass[] = { "1234" };

	char username[DATA_SIZE], password[DATA_SIZE];
	enterUsersData(username, password);
	if (stringsEqual(username, adminUser) && stringsEqual(password, adminPass)) {
		adminDuties(users);
	}
	else {
		if (passwordMatch(username, password, users)) {
			bool wonGame = gameplay();
			updateLeaderboard(username, wonGame);
			return;
		}

		std::cout << RED << "No such user was found. Check your login and password information. \n" << RESET;
	}
}
//Possible admin oppportunities
void adminDuties(const char* usersFilepath) {
	if (usersFilepath == nullptr) {
		std::cout << "Nullpointer error.";
		return;
	}

	std::cout << YELLOW << "You are now logged in as an admin \n" << RESET;

	int decision;

	do {
		std::cout << "You can either: \n";
		std::cout << "1. Check the leaderboard \n";
		std::cout << "2. Edit the word list \n";
		std::cout << "3. Return to the main menu \n";
		std::cout << "Please select your decision: ";

		decision = myChoice();

		if (decision == 1) {
			checkLeaderboard();
		}
		else if (decision == 2) {
			editWordList();
		}
		
	} while (decision != 3);
}
//Function making sure the admin enters a vslid action when edditing the word list
void actionCheck(char* action) {
	if (action == nullptr) {
		std::cout << "Nullpointer error.";
		return;
	}
	std::cin >> std::ws;
	std::cin.getline(action, DATA_SIZE);

	bool rightAction = false;

	while (!rightAction) {
		if (mySizeOf(action) > ACTION_SIZE || mySizeOf(action) == 0) {
			std::cout << RED << "The action must be 'add', 'delete' or 'back'." << RESET << std::endl;
			std::cout << "Action:";
			std::cin.getline(action, DATA_SIZE);
			std::cout << std::endl;
			continue;
		}

		if (!blankSpacesCheck(action)) {
			std::cout << RED << "The action must not contain blank spaces." << RESET << std::endl;
			std::cout << "Action:";
			std::cin.getline(action, DATA_SIZE);
			std::cout << std::endl;
			continue;
		}
		rightAction = true;
	}
}
//Possible actions when edditing the word list
void editWordList() {

	char action[DATA_SIZE];
	
	do {
		std::cout << "What would you like to do? \n";
		std::cout << "Enter 'delete' to remove words from the list, 'add' to include or 'back' to leave. \n";
		std::cout << "Action: ";

		actionCheck(action);

		if (stringsEqual(action, removal)) {
			wordDeletion(words);
		}
		else if (stringsEqual(action, add)) {
			wordAddition(words);
		}
	} while (!stringsEqual(action, back));

}
//Check to see if a char is a small latin letter
bool latinLetters(const char ch) {
	if (ch >= 'a' && ch <= 'z')
		return true;
	return false;
}
//Checking whether the word meets our criteria - 5 small latin letter words
bool checkWord(const char* word) {
	if (word == nullptr) {
		std::cout << "Nullpointer error. \n";
		return false;
	}
	int cnt = 0;
	for (int i = 0; word[i] != '\0'; i++) {
		if (!latinLetters(word[i])) {
			return false;
		}
		cnt++;
	}
	if (cnt != 5)
		return false;
	return true;
}
//Check to see if the word already exists in the word file to avoid repetitions
bool wordRepeats(const char* word) {
	if (word == nullptr) {
		std::cout << "Nullpointer error. \n";
		return false;
	}

	std::ifstream ifs(words, std::ios::app);
	if (!ifs.is_open()) {
		fileConnectionErrorMessage();
		return false;
	}

	char currentWord[WORD_SIZE];
	while (ifs.getline(currentWord, WORD_SIZE)) {
		if (stringsEqual(currentWord, word)) {
			ifs.close();
			return true;
		}
	}
	ifs.close();
	return false;
}
//Function to add words in the word file
void wordAddition(const char* filepath) {
	if (filepath == nullptr) {
		std::cout << "Nullpointer error. \n";
		return;
	}

	char newWord[WORD_SIZE];
	bool additionSuccessful = false;

	do {
		std::cout << "Enter the new word: ";
		std::cin.getline(newWord, WORD_SIZE);
		if (checkWord(newWord) && !wordRepeats(newWord)) {

			std::ofstream ofs(filepath, std::ios::app);
			if (!ofs.is_open()) {
				fileConnectionErrorMessage();
				return;
			}

			ofs << newWord << std::endl;

			ofs.close();
			std::cout << GREEN << "Word added successfully. \n" << RESET;
			additionSuccessful = true;
		}
		else {
			std::cout << RED << "The words must be made up of 5 small Latin letters";
			std::cout << " and must not already exist in the file. \n" << RESET;
			std::cout << "Try again. \n";
		}
	} while (!additionSuccessful);
	return;
}
//Functions to remove words from the wrod file
void wordDeletion(const char* filepath) {
	if (filepath == nullptr) {
		std::cout << "Nullpointer error. \n";
		return;
	}
	char wordToRemove[WORD_SIZE];
	bool ramovalSuccessful = false;
	do {
		std::cout << "Enter the word you want to delete: ";
		std::cin.getline(wordToRemove, WORD_SIZE);

		if (checkWord(wordToRemove) && wordRepeats(wordToRemove)) {

			std::ifstream ifs(filepath);
			if (!ifs.is_open()) {
				fileConnectionErrorMessage();
				return;
			}
			//We are creating temporary file in which we are going
			//to rewrite the words from the original one without the removed
			//Than we delete the ogriginal and rename the temporary.
			std::ofstream ofs(tempFilepath);
			if (!ofs.is_open()) {
				fileConnectionErrorMessage();
				ifs.close();
				return;
			}

			char currentWord[WORD_SIZE];
			bool found = false;

			while (ifs.getline(currentWord, WORD_SIZE)) {
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
				std::cout << RED << "The word was not found. \n" << RESET;
				remove(tempFilepath);
				return;
			}

			remove(filepath);
			rename(tempFilepath, filepath);

			std::cout << GREEN << "Word removed successfully. \n" << RESET;
			ramovalSuccessful = true;
		}
		else {
			std::cout << RED << "The words must be made up of 5 small latin letters";
			std::cout<< " and already be in the file. \n";
			std::cout << RESET << "Try again. \n";
		}
	} while (!ramovalSuccessful);
}
//Functions to count the words in the word file
int countWords() {
	std::ifstream ifs(words);
	if (!ifs.is_open()) {
		fileConnectionErrorMessage();
		return 0;
	}

	int count = 0;
	char currentWord[WORD_SIZE];

	while (ifs.getline(currentWord, WORD_SIZE)) {
		count++;
	}
	ifs.close();
	return count;
}
//Function to choose a random word from the word file
char* randomWord() {
	int totalWords = countWords();
	if (totalWords == 0) {
		fileConnectionErrorMessage();
		return nullptr;
	}
	int randomIndex = rand() % totalWords;

	std::ifstream ifs(words);
	if (!ifs.is_open()) {
		fileConnectionErrorMessage();
		return nullptr;
	}
	char currentWord[WORD_SIZE];
	int currentIndex = 0;
	while (ifs >> currentWord) {
		if (currentIndex == randomIndex) {
			char* randomWord = new char[WORD_SIZE];
			int i;
			for (i = 0; currentWord[i] != '\0'; i ++) {
				randomWord[i] = currentWord[i];
			}
			randomWord[i] = '\0';
			ifs.close();
			return randomWord;
		}
		currentIndex++;
	}
	return nullptr;
}
//Function to determine whether a letter's feedback should be yellow
bool yellowLetters(char a, int matrix[ALPHABET][LETTER_COUNT]) {
	if (matrix == nullptr) {
		std::cout << "Nullpointer error. \n";
		return false;
	}

	int index = a - 'a';
	if (matrix[index][1] != 0) {
		matrix[index][1]--;
		return true;
	}
	return false;
}
//A function to fill a two dimansional array with how many times a letter is found in the secret word
void matrixFill(const char* secretWord, int matrix[ALPHABET][LETTER_COUNT]) {
	if (secretWord == nullptr || matrix == nullptr) {
		std::cout << "Nullpointer error. \n";
		return;
	}

	int k = 0;
	for (int i = 0; i < ALPHABET; i++) {
		matrix[i][0] = i;
		matrix[i][1] = 0;
	}
	while (secretWord[k] != '\0') {
		int index = secretWord[k] - 'a';
		matrix[index][1]++;
		k++;

	}
}
//The rules of the game
void gameRules() {
	std::cout << PURPLE << "You are about to play WORDLE! \n";
	std::cout << RESET << "The rules of the game are: \n";
	std::cout << "You must guess a randomly selected 5 letter word from our database in 6 guesses. \n";
	std::cout << "You will get a colour-coded feedback after every guess: \n";
	std::cout << GREEN << "Green" << RESET << " - the letter is in the correct spot in the secret word \n";
	std::cout << YELLOW << "Yellow" << RESET << " - the letter is correct, but in the wrong spot. \n";
	std::cout << "Good luck! \n";
}
//Makes sure a guess is valid
void validGuess(int currentGuess, char* guessedWord) {
	if (guessedWord == nullptr) {
		std::cout << "Nullpointer error";
		return;
	}
	bool valid = false;
	while (!valid) {
		std::cout << currentGuess << ". guess: ";
		std::cin.getline(guessedWord, WORD_SIZE);
		std::cout << std::endl;

		if (!checkWord(guessedWord)) {
			std::cout << RED << "Invalid word. Must be 5 small latin letters. \n" << RESET;
			continue;
		}
		bool existsInList = wordRepeats(guessedWord);
		if (!existsInList) {
			std::cout << RED << "Not in word list. \n" << RESET;
			continue;
		}
		valid = true;
	}
}
//Making sure that yellow and green letters dont oppose each other.
void letterRepsMinusGreen(char* guessedWord, char* secretWord,bool* green, int tempMatrix[ALPHABET][LETTER_COUNT]) {
	if (guessedWord == nullptr || secretWord == nullptr || green == nullptr || tempMatrix == nullptr) {
		std::cout << "Nullpointer error" << std::endl;
		return;
	}
	for (int i = 0; guessedWord[i] != '\0'; i++) {
		if (guessedWord[i] == secretWord[i])
		{
			int index = guessedWord[i] - 'a';
			green[i] = true;
			tempMatrix[index][1]--;
		}
	}
}
//Color feedback
void colorFeedback(char* guessedWord, bool* green, int tempMatrix[ALPHABET][LETTER_COUNT]) {
	for (int i = 0; guessedWord[i] != '\0';i++) {
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
	}
}
//The actual game
bool gameplay() {
	char* secretWord;
	secretWord = randomWord();

	int matrix[ALPHABET][LETTER_COUNT];
	matrixFill(secretWord, matrix);

	const int GUESSES = 6;
	int currentGuess = 1;
	char guessedWord[WORD_SIZE];

	gameRules();
	
	while (currentGuess <= GUESSES) {
		int tempMatrix[ALPHABET][LETTER_COUNT];
		for (int i = 0; i < ALPHABET; i++) {
			tempMatrix[i][1] = matrix[i][1];
		}

		validGuess(currentGuess,guessedWord);
		
		bool green[WORD_SIZE] = { false };

		letterRepsMinusGreen(guessedWord, secretWord, green, tempMatrix);

		colorFeedback(guessedWord, green, tempMatrix);

		if (stringsEqual(guessedWord, secretWord)) {
			std::cout << std::endl;
			std::cout << PURPLE << "\t \t  You won \n \n" << RESET;
			delete[] secretWord;
			return true;
		}

		currentGuess++;
		std::cout << std::endl;
	}

	std::cout << RED << "You could not guess the word " << GREEN << secretWord;
	std::cout<< RED << " in 6 guesses. \n" << RESET;
	std::cout << YELLOW << "Better luck next time. \n" << RESET;
	delete[] secretWord;

	return false;
}
//Function which updates the leaderboard file after a game
void updateLeaderboard(const char* username,const bool wonGame) {
	if (username == nullptr) {
		std::cout << "Nullpointer error. \n";
		return;
	}
	std::ofstream ofs(leaderboard, std::ios::app);
	ofs.close();
	std::ifstream ifs(leaderboard);
	std::ofstream temp(tempFilepath);
	if (!temp.is_open() || !ifs.is_open()) {
		fileConnectionErrorMessage();
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
		temp << username << " " << (wonGame ? 1 : 0) << " " << 1 << std::endl;
	}
	ifs.close();
	temp.close();

	remove(leaderboard);
	rename(tempFilepath, leaderboard);

}
//Calculates the winrate of a player in decimal value
double calcWinrate(double gamesWon, double gamesPlayed) {
	if (gamesPlayed == 0)
		return 0.0;
	double winrate = (gamesWon / gamesPlayed);
	return winrate;
}

void sortByGamesPlayed(Player* arr, int size) {

}

void checkLeaderboard() {

}