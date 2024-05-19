# Tetris Finite State Machine

The Tetris game is modeled as a finite state machine (FSM), which consists of a set of states and transitions between them. 
The FSM allows the game to respond to user input and game events in a consistent and predictable manner.

![FSM](./misc/images/FSM.png)
The following states and transitions are defined in the Tetris FSM:

## States

- **START**: The initial state of the game. The game is not running and the user is presented with a start screen.
- **SPAWN**: The state in which a new Tetrimino is spawned at the top of the game field.
- **SHIFTING**: The state in which the user can shift the Tetrimino left or right using the arrow keys.
- **MOVING**: The state in which the Tetrimino is moving down the game field automatically.
- **PAUSE**: The state in which the game is paused and the user is presented with a pause screen.
- **ATTACHING**: The state in which the Tetrimino is attached to the game field and the user is awarded points for any completed lines.
- **GAME_OVER**: The state in which the game is over and the user is presented with a game over screen.
