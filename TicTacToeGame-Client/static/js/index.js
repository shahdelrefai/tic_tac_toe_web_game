window.addEventListener('DOMContentLoaded', () => {
    const tiles = Array.from(document.querySelectorAll('.tile'));
    const playerDisplay = document.querySelector('.display-player');
    const resetButton = document.querySelector('#reset');
    const announcer = document.querySelector('.announcer');
    const player1score = document.querySelector('.player1-score');
    const player2score = document.querySelector('.player2-score');
    var score1 = 0;
    var score2 = 0;

    let board = ['', '', '', '', '', '', '', '', ''];
    let currentPlayer = 'X';
    let isGameActive = true;

    const PLAYERX_WON = 'PLAYERX_WON';
    const PLAYERO_WON = 'PLAYERO_WON';
    const TIE = 'TIE';

    function handleResultValidation(state) {
        if(state == "c") return;

        if(state == "0") announce(PLAYERX_WON);
        else if(state == "1") announce(PLAYERO_WON);
        else if(state == "t") announce(TIE);

        isGameActive = false;

    }

    const announce = (type) => {
        switch(type){
            case PLAYERO_WON:
                announcer.innerHTML = 'Player <span class="playerO">O</span> Won';
                score2 += 1;
                player2score.innerText = score2;
                break;
            case PLAYERX_WON:
                announcer.innerHTML = 'Player <span class="playerX">X</span> Won';
                score1 += 1;
                player1score.innerText = score1;
                break;
            case TIE:
                announcer.innerText = 'Tie';
        }
        announcer.classList.remove('hide');
    };

    const updateBoard =  (index) => {
        board[index] = currentPlayer;
    }

    const changePlayer = (playerTurn) => {
        playerDisplay.classList.remove(`player${currentPlayer}`);
        if(playerTurn == "0") currentPlayer = 'X';
        else currentPlayer = 'O';
        playerDisplay.innerText = currentPlayer;
        playerDisplay.classList.add(`player${currentPlayer}`);
    }

    const userAction = (tile, index, data) => {
        if(data[0] == "v" && isGameActive) {
            tile.innerText = currentPlayer;
            tile.classList.add(`player${currentPlayer}`);
            updateBoard(index);
            handleResultValidation(data[1]);
            changePlayer(data[2]);
        }
    }

    const SendMove = (tile, index) => {
        fetch('/api/make_move', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(index)
        })
        .then(response => response.json())
        .then(data => {
            console.log(data);
            userAction(tile, index, data);
        })
    .   catch(error => {
            console.error('Error:', error);
        });
    }

    const resetBoard = () => {
        if(isGameActive == true) SendMove('tile', 'r');
        board = ['', '', '', '', '', '', '', '', ''];
        isGameActive = true;
        announcer.classList.add('hide');

        changePlayer("0");

        tiles.forEach(tile => {
            tile.innerText = '';
            tile.classList.remove('playerX');
            tile.classList.remove('playerO');
        });
    }

    tiles.forEach( (tile, index) => {
        tile.addEventListener('click', () => SendMove(tile, index));
    });

    resetButton.addEventListener('click', resetBoard);
});