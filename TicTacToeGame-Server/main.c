#include <netinet/in.h>
#include <stdbool.h>
#include "TicTacToeGame.h"
#include "mysocket.h"

struct TicTacToeGame MyGame;

int serverSocketFD;
struct sockaddr_in *serverAddress;
int clientSocketFD;

int main() {
    DoServerClientProcedures(&serverSocketFD, (struct sockaddr_in *) &serverAddress, &clientSocketFD);

    StartNewGame(&MyGame);

    do {

        RunGame(&MyGame,  &clientSocketFD);

    }while(MyGame.startNewRound == true);

    return 0;
}
