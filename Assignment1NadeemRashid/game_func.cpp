//
// Created by Nadeem Rashid on 2023-02-05.
//

#include "game_func.h"

// RandomPick Class
int RandomPick::GetRandNum() {
    return m_rand;
}
RandomPick::RandomPick() {
    m_rand = rand() % 3;
}

// CheckWinner Class
std::string CheckWinner::Check() {
    // Comparing the computer's input with the user's input
    switch (m_userInp) {
    case 0:
        switch (m_compInp) {
        case 0:
            m_winner = winnerStr[2];
            m_p.m_ties++;
            break;
        case 1:
            m_winner = winnerStr[1];
            m_p.m_compPoints += 3;
            break;
        case 2:
            m_winner = winnerStr[0];
            m_p.m_userPoints += 3;
            break;
        }
        break;
    case 1:
        switch (m_compInp) {
        case 0:
            m_winner = winnerStr[0];
            m_p.m_userPoints += 3;
            break;
        case 1:
            m_winner = winnerStr[2];
            m_p.m_ties++;
            break;
        case 2:
            m_winner = winnerStr[1];
            m_p.m_compPoints += 3;
            break;
        }
        break;
    case 2:
        switch (m_compInp) {
        case 0:
            m_winner = winnerStr[1];
            m_p.m_compPoints += 3;
            break;
        case 1:
            m_winner = winnerStr[0];
            m_p.m_userPoints += 3;
            break;
        case 2:
            m_winner = winnerStr[2];
            m_p.m_ties++;
            break;
        }
        break;
    }
    return m_winner;
}

CheckWinner::CheckWinner(int _userInp, int _compInp, GamePlayer& _player) :
    m_p(_player), m_userInp(_userInp), m_compInp(_compInp) {};

// ReadFromFile Class
void ReadFromFile::reading() {
    std::ifstream fileIn(m_username + ".txt");
    // If the file exists, take the contents from within and update the GamePlayer player struct with the one stored in
    // the file. Otherwise, update the username for the GamePlayer, and continue with the game either way.
    if (fileIn.good()) {
        fileIn >> m_p.m_userName >> m_p.m_userPoints >> m_p.m_compPoints >> m_p.m_ties;
        fileIn.close();
        std::cout << "\nLooks like the username " << m_username << " exists! The game will use this saved progress.\n";
    }
    else {
        m_p.m_userName = m_username;
        std::cout << "\nLooks like the username doesn't exist! This session will be saved once you exit the game at the end.\n";
    }
}

ReadFromFile::ReadFromFile(std::string _username, GamePlayer& _player) :
    m_p(_player), m_username(_username) {};

// WriteToFile Class
void WriteToFile::writing() {
    std::ofstream fileOut(m_p.m_userName + ".txt");
    // Place each variable into a new line within the file,
    fileOut << m_p.m_userName << '\n' << m_p.m_userPoints << '\n' << m_p.m_compPoints << '\n' << m_p.m_ties;
    // Close the file output stream, and the game is complete.
    fileOut.close();
}

WriteToFile::WriteToFile(GamePlayer& _player) : m_p(_player) {};

// Comparison Function
bool comp(GamePlayer& a, GamePlayer& b) {
    return a.m_userPoints > b.m_userPoints;
}

// WriteToLeaderboard Function
void WriteToLeaderboard(std::string _username) {
    std::ofstream fileOut;
    // Opening leaderboard, prepping the file to be appeneded, rather than overwritten completely
    fileOut.open("Leaderboard.txt", std::ios_base::app);
    // Appending username to the next line
    fileOut << '\n' << _username;
    fileOut.close();
}

// ReadFromLeaderboard Function
std::vector<std::string> ReadFromLeaderboard() {
    std::string name;
    std::vector<std::string> names;

    // Opening leaderboard text file
    std::ifstream fileIn("Leaderboard.txt");
    // While a line exists, put it into the string 'name', push it onto the names vector, and move on to the next line
    while (fileIn >> name)
        names.push_back(name);
    fileIn.close();

    return names;
}

// PrintLeaderboard Function
void PrintLeaderboard() {
    std::string name;
    std::vector<std::string> names = ReadFromLeaderboard();
    std::vector<GamePlayer> players;
    std::ifstream fileIn;

    // For each name in 'names' vector
    for (std::string name : names) {
        // Open the respected text file for said name, and proceed to put the GamePlayer into the 'players'
        // vector, so that it can be sorted later on.
        std::ifstream fileIn(name + ".txt");
        GamePlayer p;
        fileIn >> p.m_userName >> p.m_userPoints >> p.m_compPoints >> p.m_ties;
        players.push_back(p);
    }
    fileIn.close();

    // Sorting the players based on their points, ascending
    std::sort(players.begin(), players.end(), comp);

    std::cout << std::right << std::setw(32) << "PLAYER | POINTS\n";
    std::cout << std::right << std::setw(33) << "------------------\n";
    int counter = 1;
    // Because the 'players' vector has been sorted, all we need to do now is format and print!
    for (GamePlayer p : players) {
        if (p.m_userName != "" && p.m_userPoints > 0)
            std::cout << counter++ << ". " << std::right << std::setw(19) << p.m_userName << " | " << p.m_userPoints << "\n";
    }
    std::cout << "\nDisclaimer: Only players with a score above 0 will be shown, "
        "as they are otherwise not worthy of such pedestal.\n\n";
}