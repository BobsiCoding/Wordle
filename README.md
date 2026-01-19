This project is an implemantaion of the popular game WORDLE, written in c++. The goal of the game is for the player to guess a hidden 5-letter word within a limited number of attempts.
After each guess, the program provides color-coded feedback indicating how close the guess is to the secret word.
The project was developed as a course assignment and focuses on:
 - file handling;
 - dynamic memory management;
 - input validation;
 - basic algorithms;
 - user authentication and role management;
How it works:
Once the program is run, the user is presented with a main menu screen, giving him the options to either:
1. Register as a new user with unique username and a passowrd, both of which match a desired equirement, which is told to the user.
   After that the data is saved in a users.txt file.
3. Log an as an already existing user, supporting two modes:
   - enter as a player, you are shown the rules to the game, a random 5 letter word from the words.txt file is choosen
   and you must guess it by 6 attempts using the color-coded feedback after each guess as a hint.
   Once the game is finished, the results from the game are updated into a leaderboard.txt file, which stores the statistics of every user who has played the game.
 - enter as an admin, you can edit the file with words by adding new words or removing already existing from it. You can also check the leaderboard with players
   after you choose whether the data to be presented sorted by played games or by over-all winrate.
   You can go back and forth between the functionalities you are presented with and the programs ends after you choose the option quit from the main menu.
