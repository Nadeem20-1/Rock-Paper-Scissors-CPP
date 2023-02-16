//
// Created by Nadeem Rashid on 2023-02-04.
//

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include <vector>
#include <Windows.h>


#ifndef ASSIGNMENT1NADEEMRASHID_GAME_FUNC_H
#define ASSIGNMENT1NADEEMRASHID_GAME_FUNC_H

#endif //ASSIGNMENT1NADEEMRASHID_GAME_FUNC_H

const std::string hand[3] = { "ROCK", "PAPER", "SCISSORS" };
const std::string winnerStr[3] = { "YOU", "COMPUTER", "TIE" };

struct GamePlayer {
    std::string m_userName;
    int m_userPoints = 0,
        m_compPoints = 0,
        m_ties = 0;
};

class RandomPick {
private:
    int m_rand;
public:
    int GetRandNum();
    RandomPick();
};

class CheckWinner {
private:
    std::string m_winner;
    int m_userInp;
    int m_compInp;
    GamePlayer& m_p;
public:
    std::string Check();
    CheckWinner(int _userInp, int _compInp, GamePlayer& _player);
};

class ReadFromFile {
private:
    std::string m_username;
    GamePlayer& m_p;
public:
    void reading();
    ReadFromFile(std::string _username, GamePlayer& _player);
};

class WriteToFile {
private:
    GamePlayer& m_p;
public:
    void writing();
    WriteToFile(GamePlayer& _player);
};

bool comp(GamePlayer& a, GamePlayer& b);

void PrintLeaderboard();

void WriteToLeaderboard(std::string _username);

std::vector<std::string> ReadFromLeaderboard();