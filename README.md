# Checkers Bitboard Game

A C++ implementation of Checkers that uses a 64-bit bitboard to efficiently represent the board, track piece locations (including kings), and compute legal moves. This structure significantly reduces memory overhead and leverages fast bitwise operations to handle move generation and captures.

---

## Key Features

- **Bitboard Representation**  
  Each 64-bit integer bitboard encodes a player’s pieces and potential king positions. Bits are set or cleared using efficient bitwise operations, enabling constant-time checks for moves and captures.

- **Board and Game Logic**  
  - **Board**  
    - Maintains separate bitboards for Player 1 pieces, Player 2 pieces, and kinged pieces.  
    - Handles movement, captures, and promotion logic (king creation).  
    - Enforces boundaries using edge masks (LEFT_EDGE, RIGHT_EDGE) to prevent wrapping.  

  - **CheckersGame**  
    - Manages turn order, validates moves, and checks for game termination.  
    - Provides user input handling (coordinate-based moves, e.g. `E3 F4`).  
    - Automatically detects when a player has no legal moves (resulting in game over).

- **Move Generation**  
  - **generateSingleStepMoves**: Computes single-step diagonals for normal pieces and additional directions for kings.  
  - **generateCaptureMoves**: Checks diagonals for opponent pieces and empty landing squares.  
  - **hasAnyLegalMoves**: Globally checks if the current player can move at all, indicating a potential win/lose condition.

- **Bitwise Utilities**  
  Utility functions (e.g., `setBit`, `clearBit`, `toggleBit`) provide a lower-level interface for toggling and reading bits, as well as supplemental operations like bitwise addition/multiplication.


## Sample Usage

When running the game, you will be prompted for moves in coordinate format such as `E3 F4`. For a piece at E3 moving diagonally to F4, enter:
```
Enter your move (e.g., E3 F4): E3 F4
```
The board will update, and the next player’s turn begins.

![screenshot](https://github.com/18leaf/BitBoardCheckers/blob/master/checkersbitboardimage.png)

---

## Additional Resources

- **Word Doc** with design details and implementation notes:  
  [Project Report](https://kennesawedu-my.sharepoint.com/:w:/g/personal/lfergu30_students_kennesaw_edu/Ed6gS38TWORBquwvyjcLJJUBlF0DawY3pXWkNjbK6MpE6w?e=AtCZOQ)

- **YouTube Video Demonstration**:  
  [Checkers Bitboard in Action](https://youtu.be/qQLEAmnd3eQ)

