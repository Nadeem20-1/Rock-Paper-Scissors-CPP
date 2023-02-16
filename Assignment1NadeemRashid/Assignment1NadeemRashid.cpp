//
// Created by Nadeem Rashid on 2023-02-05.
//

#include "game_func.h"

int main()
{
    srand(time(NULL));
    GamePlayer player;
    int userInp = 3;
    int gameEnd = false;
    char userInpStr = '5';
    char handInpStr;
    std::string username;

    std::cout << "\nWelcome to Nadeem's Rock, Paper, Scissors game!";

    while (userInpStr != '3') {
        std::cout << "\nPlease enter one of the following numbers: \n"
            "1. Play the game\n"
            "2. View the leaderboards\n"
            "3. Quit the game\n";
        std::cin >> userInpStr;
        // Using a switch-case to easily send the user off into the correct direction,
        // minimizing the errors by using 'default' if the user inputs an incorrect character.
        switch (userInpStr) {
        case '1': {

            std::cout << "\nPlease enter a username, whether it's new or it already exists (minimum 8 characters): ";
            // Taking in the username that the player will be inputting
            std::cin >> username;
            // While the username's character length is less than 8, continue the loop
            while (username.length() < 8) {
                std::cout << "Username is too short. It is " << username.length() << " characters long. Try again: ";
                std::cin >> username;
            }

            // Reading from the text file
            ReadFromFile rff(username, player);
            rff.reading();

            // While the gameEnd variable doesn't equal to true, continue the loop
            while (!gameEnd) {
                // Creating a brand-new hand for each session of the game
                RandomPick r;
                // Loop continuously until the player picks either 0, 1 or 2 as an option for their hand
                while (true) {
                    std::cout << "\nPlease pick a number from 0 - 2 inclusive (Rock = 0, Paper = 1, or Scissors = 2): ";
                    std::cin >> handInpStr;
                    // If the user's input includes a 0, 1, or 2, subtract it from the character 0, to ensure a number is given,
                    // instead of a literal character.
                    if (handInpStr == '0' || handInpStr == '1' || handInpStr == '2') {
                        userInp = handInpStr - '0';
                        break;
                    }
                    else
                        std::cout << "\nPlease input a number between 0 and 2, inclusive.\n";
                }

                // Once the user gives a valid input, check to see who's the winner, passing the computer's hand,
                // the player's hand, and the player itself. Then, call method 'Check', to retrieve the winner.
                CheckWinner checker(userInp, r.GetRandNum(), player);
                std::string winner = checker.Check();
                std::cout << "And the winner is...\n\n" << winner << "!\n\n";
                std::cout << "The computer picked " << hand[r.GetRandNum()] << ", and you picked " << hand[userInp];
                std::cout << "\n\nCurrent Score:\n" << player.m_userName << "'s Points: " << player.m_userPoints << "\nComputer's Points: "
                    << player.m_compPoints << "\nTies: " << player.m_ties;
                std::cout << "\n\nThanks for playing! If you would like to play again, enter '1'. Otherwise, press"
                    " any key to return to the main menu: ";
                std::cin >> userInpStr;
                // If the user does not input the number 1,
                if (userInpStr != '1') {
                    // Stop the loop,
                    gameEnd = true;
                    // Start writing to the file,
                    std::cout << "Returning to the main menu...";
                }
            }
        }
                break;
        case '2':
            PrintLeaderboard();
            break;
        case '3': {
            if (username != "") {
                WriteToFile wtf(player);
                wtf.writing();
                WriteToLeaderboard(username);
                std::cout << "Thanks for playing! Your game has been saved. Have a good day!";
            }else
                std::cout << "Have a good day!";
            break;
        }
        default:
            std::cout << "Please enter a proper number and try again.";
            break;
        }
    }
}

