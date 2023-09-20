#include "TicTacToeGame.h"


void ConstructGrid(struct TicTacToeGame* thisGame)
{
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            (*thisGame).Grid[i][j] = -1;
}

void DeclareGameSettings(struct TicTacToeGame* thisGame)
{
    ConstructGrid(thisGame);
    (*thisGame).GameTurn = Player1;

    (*thisGame).numberOfRounds += 1;
    (*thisGame).tilesLeft = 9;
    (*thisGame).endRound = false;
    (*thisGame).startNewRound = false;
}

bool CheckIfValidMove(int index, struct TicTacToeGame* thisGame)
{
    int row = floor(index/3);
    int col = index%3;

    (*thisGame).currentMoveRow = row;
    (*thisGame).currentMoveCol = col;

    if((*thisGame).Grid[row][col] == -1)
    {
        (*thisGame).tilesLeft -= 1;
        return true;
    }
    return false;
}

void UpdateGrid(struct TicTacToeGame* thisGame)
{
    int row = (*thisGame).currentMoveRow;
    int col = (*thisGame).currentMoveCol;

    (*thisGame).Grid[row][col] = (*thisGame).GameTurn;

    fprintf((*thisGame).fileP, "index played by player %d : [%d][%d]\n", (*thisGame).GameTurn+1, row, col);
    fflush((*thisGame).fileP);
}

bool CheckIfWinOrTie(struct TicTacToeGame* thisGame, char* response)
{
    int row = (*thisGame).currentMoveRow, col = (*thisGame).currentMoveCol;
    int rowCount = 0, colCount = 0, diagonalChains[2] = {0,0};
    bool isDiagonal = row%2 == 0 && col%2 == 0;

    for(int i = 0; i < 3; i++)
    {
        if((*thisGame).Grid[row][i] == (*thisGame).GameTurn)   rowCount += 1;

        if((*thisGame).Grid[i][col] == (*thisGame).GameTurn)   colCount += 1;

        if(isDiagonal && i%2 == 0)
        {
            for(int j = 0; j < 3; j+=2)
                if((*thisGame).Grid[i][j] == (*thisGame).GameTurn)
                {
                    if (i == j) diagonalChains[0] += 1;
                    else diagonalChains[1] += 1;
                }
        }
        else if(isDiagonal && i == 1)
        {
            if((*thisGame).Grid[1][1] == (*thisGame).GameTurn)
            {
                diagonalChains[0] += 1;
                diagonalChains[1] += 1;
            }
        }
    }

    if(rowCount == 3 || colCount == 3 || diagonalChains[0] == 3 || diagonalChains[1] == 3)
    {
        (*thisGame).roundWinner = (*thisGame).GameTurn;
        (*thisGame).PlayerScore[(*thisGame).roundWinner] += 1;
        *response = (*thisGame).roundWinner == 0 ? '0' : '1';
        fprintf((*thisGame).fileP, "Round number %d was Won by player %d\n", (*thisGame).numberOfRounds - 1, (*thisGame).roundWinner + 1);
        fflush((*thisGame).fileP);
        return true;
    }


    if(!(*thisGame).tilesLeft)
    {
        (*thisGame).roundWinner = Tie;
        *response = 't';
        fprintf((*thisGame).fileP, "Round number %d was a Tie\n", (*thisGame).numberOfRounds-1);
        fflush((*thisGame).fileP);
        return true;
    }

    *response = 'c';
    return false;
}

void ChangeGameTurn(struct TicTacToeGame* thisGame, char* response)
{
    if((*thisGame).GameTurn == Player1) (*thisGame).GameTurn = Player2;
    else (*thisGame).GameTurn = Player1;

    *response = *response = (*thisGame).GameTurn == 0 ? '0' : '1';
}

void SendGameUpdatesToClient(char* response, const int* clientSocketFD)
{
    printf("Response : %s\n", response);
    send(*clientSocketFD, response, 3, 0);
}

void StartNewGame(struct TicTacToeGame* thisGame)
{
    printf("New Game\n");
    (*thisGame).numberOfRounds = 0;
    (*thisGame).PlayerScore[Player1] = 0;
    (*thisGame).PlayerScore[Player2] = 0;

    (*thisGame).fileP = fopen("gamelog.txt", "w");
    if ((*thisGame).fileP == NULL) {
        printf("Error opening the file");
    }
    fputs("", (*thisGame).fileP);
    fprintf((*thisGame).fileP, "New Game\n");
    fflush((*thisGame).fileP);
}

void RunGame(struct TicTacToeGame* thisGame, int* clientSocketFD)
{
    if((*thisGame).numberOfRounds > 0)
    {
        printf("New Round\n");
        fprintf((*thisGame).fileP, "New Round\n");
        fflush((*thisGame).fileP);
    }

    DeclareGameSettings(thisGame);

    while((*thisGame).endRound == false)
    {
        char received;
        recv(*clientSocketFD, &received, 1, 0);

        printf("Move received from client : %c\n", received);

        char response[4];
        response[3] = '\0';

        if(CheckIfValidMove((int)(received - '0'), thisGame))
        {
            response[0] = 'v';

            UpdateGrid(thisGame);

            if(CheckIfWinOrTie(thisGame,&response[1]))
            {
                (*thisGame).endRound = true;
                (*thisGame).startNewRound = true;
            }

            ChangeGameTurn(thisGame, &response[2]);
        }
        else
        {
            if(received == 'r')
            {
                (*thisGame).startNewRound = true;
                (*thisGame).endRound = true;
            }

            response[0] = 'n';
            response[1] = 'n';
            response[2] = 'n';
        }

        SendGameUpdatesToClient(response, clientSocketFD);
    }
}
