# Checkers Bitboard Game

This project is a Checkers game implemented in C++ using a bitboard structure to represent the game state. It includes classes to manage the board, game logic, player interactions, and bitwise manipulations for efficient move calculations.

## Overview of Key Functions in `Board` and `CheckersGame`

### Board Class

The `Board` class is responsible for representing the game state, handling moves, and validating game rules using bitboards. Below are the most important functions:

#### `initializeBoard()`
Initializes the board by setting the initial positions of Player 1 and Player 2's pieces using predefined bit masks. Kings are not set at the beginning.

#### `movePiece(int startPosition, int endPosition, bool isPlayerOne)`
Moves a piece from `startPosition` to `endPosition`. This function also checks if the move is legal, handles captures, and checks if the piece should be promoted to a king.

- **Key sub-functions:**
  - `movePieceOnBoard()`: Updates the bitboard for the given move.
  - `capturePiece()`: Removes the opponent's piece if a capture move is performed.
  - `promoteToKing()`: Promotes a piece to a king if it reaches the last row.
  - `getJumpedPosition()`: Calculates the position of a captured piece.

#### `isLegalMove(int startPosition, int endPosition, bool isPlayerOne)`
Validates if a move from `startPosition` to `endPosition` is legal based on the current board state. It considers single-step moves and capture moves.

#### `generateSingleStepMoves(uint64_t pieces, bool isPlayerOne)`
Generates a bitboard of all possible single-step moves for the current player based on the pieces' positions and empty spaces.

#### `generateCaptureMoves(uint64_t pieces, bool isPlayerOne)`
Generates a bitboard of all possible capture moves for the current player, considering the positions of the opponent's pieces and available empty spaces.

#### `hasAnyLegalMoves(bool isPlayerOne)`
Checks if the current player has any legal moves remaining. If no moves are available, the game is over.

#### `coordinateToPosition(const std::string &coord)`
Converts standard checkers board coordinates (e.g., "E3") to a bitboard position (integer between 0 and 63).

#### `displayBoard()`
Displays the current board state in a human-readable format using standard chess/checkers notation (e.g., pieces shown with 'w', 'b' for normal pieces and 'W', 'B' for kings).

### CheckersGame Class

The `CheckersGame` class manages the overall game flow, including turn-taking, move processing, and determining the game's end.

#### `startGame()`
This is the main game loop. It alternates turns between Player 1 and Player 2, displaying the game status, accepting player moves, and handling exceptions. The game ends when one player has no legal moves left.

#### `switchPlayer()`
Switches the turn between Player 1 and Player 2 after a valid move is made.

#### `processMove(const Move& move)`
Processes the player's move by calling the `Board` class to update the board state.

#### `isGameOver()`
Checks if the game is over by verifying if the current player has any legal moves left.

#### `getPlayerMove()`
Prompts the player to input their move using standard notation (e.g., "E3 F4"). It converts the input coordinates to board positions using `Board::coordinateToPosition()`.

#### `validateMove(const Move &move)`
Validates the player's move by checking if it is legal using the `Board::isLegalMove()` function.

#### `displayGameStatus()`
Displays the current board and indicates which player's turn it is.

Some more Info Word doc: https://kennesawedu-my.sharepoint.com/:w:/g/personal/lfergu30_students_kennesaw_edu/Ed6gS38TWORBquwvyjcLJJUBlF0DawY3pXWkNjbK6MpE6w?e=AtCZOQ

Youtube Video Demonstration: https://youtu.be/qQLEAmnd3eQ


