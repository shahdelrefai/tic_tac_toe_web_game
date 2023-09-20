//
// Created by Shahd El-Refai on 29/08/2023.
//

#ifndef SOCKETSERVER_TICTACTOEGAME_H
#define SOCKETSERVER_TICTACTOEGAME_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <math.h>


struct TicTacToeGame
{
    int Grid[3][3];
    enum Player{Player1, Player2, Tie} GameTurn;
    enum Player roundWinner;
    int PlayerScore[2];
    int currentMoveRow;
    int currentMoveCol;
    int tilesLeft;
    bool endRound;
    bool startNewRound;
    int numberOfRounds;
    FILE* fileP;
};

void DoServerClientProcedures();
void ConstructGrid(struct TicTacToeGame* thisGame);
void DeclareGameSettings(struct TicTacToeGame* thisGame);
bool CheckIfValidMove(int index, struct TicTacToeGame* thisGame);
void UpdateGrid(struct TicTacToeGame* thisGame);
bool CheckIfWinOrTie(struct TicTacToeGame* thisGame, char* response);
void ChangeGameTurn(struct TicTacToeGame* thisGame, char* response);
void SendGameUpdatesToClient(char* response, const int* clientSocketFD);
void StartNewGame(struct TicTacToeGame* thisGame);
void RunGame(struct TicTacToeGame* thisGame, int* clientSocketFD);
#endif //SOCKETSERVER_TICTACTOEGAME_H
