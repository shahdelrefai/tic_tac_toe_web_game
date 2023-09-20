# Tic Tac Toe Web Game
The Tic Tac Toe web game project consists of both front-end using HTML, CSS, and JavaScript and back-end components using C and Python (Flask).

## Communication Flow:
   - ### The front-end (HTML, CSS, JavaScript) handles user interactions and sends game-related requests to the Python server.
       
   - ### The Python server (Flask) receives these requests, and forwards them to the C server via the established TCP connection.
  
   - ### The C server processes the game inputs, updates the game state, and sends game updates back to the Python server.

   - ### The Python server (Flask) receives these requests, and forwards them to the C server via the established TCP connection.
