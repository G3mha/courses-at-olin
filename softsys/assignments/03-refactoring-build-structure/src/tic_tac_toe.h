/**
 * A simple tic-tac-toe library.
 */
#pragma once

#include <stdlib.h>

// Define useful constants needed in the program.
enum {
  /** Dimensions of the tic-tac-toe board. */
  BOARD_DIM = 3,
  /** Number of characters to read from user input. */
  INPUT_BUFFER_SIZE = 5,
  /** Used in strtol to convert user input to decimal ints. */
  DECIMAL_BASE = 10,
};

// C17 doesn't allow char enums, so declare the spaces/players as constants
// instead.
extern const char EMPTY_SPACE;
extern const char X_SPACE;
extern const char O_SPACE;

/** Prompt message shown when getting user input. */
extern const char INPUT_PROMPT[];

/**
 * A pair of integers representing a coordinate on a tic-tac-toe board.
 */
typedef struct {
  int row;
  int col;
} board_space;

/**
 * A tic-tac-toe board, represented by a 2-D array of characters.
 */
typedef struct {
  char spaces[BOARD_DIM][BOARD_DIM];
} tic_tac_toe_board;

/**
 * The state of a tic-tac-toe game, including current board, whose turn it is,
 * and how many moves have been made so far.
 */
typedef struct {
  tic_tac_toe_board* board;
  size_t num_moves;
  char current_turn;
} tic_tac_toe_state;

/**
 * Get the opposing player's character (X to O, or O to X).
 *
 * @param The character representing the player ('X' or 'O').
 * @return The character of the opposing player.
 */
char get_opposing_player(char player);

/**
 * Check that a set of coordinates is actually on the tic-tac-toe board.
 *
 * A space on the tic-tac-toe board is represented by a row and column index,
 * with each being 0 to 2 (inclusive) on a typical tic-tac-toe board.
 *
 * @param space A board_space (pair of ints) representing the coordinates.
 * @return 1 if space is on the board and 0 otherwise.
 */
int is_valid_space(board_space space);

/**
 * Get user input representing a pair of coordinates.
 *
 * Read a line of input from the user, generally expected to be a row and column
 * index separated by a space (e.g., "0 2"). Parse this input into a board_space
 * (pair of integers), with appropriate handling of inputs that are invalid or
 * too long. The parsed integers are placed into a premade board_space instance;
 * no new board_space is created. If the input is invalid or too long, the
 * contents of space are undefined.
 *
 * @param space The board_space instance to write the parsed ints into.
 * @return 1 if the input was successfully read and parsed and 0 otherwise.
 */
int get_user_input(board_space* space);

/**
 * Set up an empty tic-tac-toe board.
 *
 * @param board A pointer to the board to be initialized.
 */
void setup_board(tic_tac_toe_board* board);

/**
 * Check if a space on a tic-tac-toe board is empty.
 *
 * @param board The board to check.
 * @param space The board space (pair of ints) to check.
 * @return 1 if space on board is empty and 0 otherwise.
 */
int is_empty_space(const tic_tac_toe_board* board, board_space space);

/**
 * Check if every space on a tic-tac-toe board is full.
 *
 * @param board The board to check.
 * @return 1 if every space on board is full and 0 otherwise.
 */
int is_full(const tic_tac_toe_board* board);

/**
 * Check if a player has won on a board.
 *
 * A player is considered to have won on a board if they have three of their
 * character in a row.
 *
 * @param board The board to check.
 * @param player The character representing the player to check (X or O).
 * @return 1 if player has won on board and 0 otherwise.
 */
int is_win(const tic_tac_toe_board* board, char player);

/**
 * Print a text representation of the contents of a tic-tac-toe board.
 *
 * @param board The board to print.
 */
void print_board(const tic_tac_toe_board* board);

/**
 * Set up an initial game state for tic-tac-toe.
 *
 * Given a state and board instance to set up, initialize the board and make the
 * state use the board. Also set up the remainder of the state to make a new
 * game.
 *
 * @param state The game state instance to initialize.
 * @param board The board instance to initialize.
 */
void setup_state(tic_tac_toe_state* state, tic_tac_toe_board* board);

/**
 * Check if the opposing player has won a game of tic-tac-toe.
 *
 * Given a game state instance, determine if the opposing player (i.e., not the
 * current player) has won the game. The opposing player is checked because each
 * time a move is made, the current player is switched, so the winner is
 * typically the player who last moved (i.e., the one opposite the current
 * player).
 *
 * @param state The game state to check.
 * @return 1 if the opposing player has won and 0 otherwise.
 */
int player_win(const tic_tac_toe_state* state);

/**
 * Check if a game of tic-tac-toe is over.
 *
 * A game is defined as being over if one player has won, or the board is full
 * (i.e., a draw). Given a game state, check whether the game is over.
 *
 * @param state The game state to check.
 * @return 1 if the game is over and 0 otherwise.
 */
int game_over(const tic_tac_toe_state* state);

/**
 * Attempt to make a move in a tic-tac-toe game.
 *
 * Given a game state and a space, attempt to make a move by the current player
 * in that space in the game's board. The space can be invalid (e.g., outside
 * the board or already occupied), in which case the move will fail and the
 * board left unchanged. If the move is successful, the board will be changed
 * and the number of moves so far (kept in the game state) will be incremeneted.
 *
 * @param state The game state to make a move in.
 * @param space The space in the board to attempt the move in.
 * @return 1 if the move was successful and 0 otherwise.
 */
int move(tic_tac_toe_state* state, board_space space);
