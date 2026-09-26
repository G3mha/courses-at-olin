#include "tic_tac_toe.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char EMPTY_SPACE = ' ';
const char X_SPACE = 'X';
const char O_SPACE = 'O';

const char INPUT_PROMPT[] =
    "Enter the row and column number of your desired move:\n"
    "+---+---+---+\n"
    "|0 0|0 1|0 2|\n"
    "+---+---+---+\n"
    "|1 0|1 1|1 2|\n"
    "+---+---+---+\n"
    "|2 0|2 1|2 2|\n"
    "+---+---+---+";

char get_opposing_player(char player) {
  return (char)(player == X_SPACE ? O_SPACE : X_SPACE);
}

int is_valid_space(board_space space) {
  return space.row >= 0 && space.row < BOARD_DIM && space.col >= 0 &&
         space.col < BOARD_DIM;
}

/**
 * Read the remainder of an input line and discard it.
 *
 * In some instances, a line of input read by the user is too long and the
 * unused portion needs to be flushed (discarded). The common call to
 * fflush(stdin) is not guaranteed to do this on all systems, so flush the input
 * by reading it to a buffer until a newline is encountered and do nothing with
 * it.
 */
static void flush_input_line(void) {
  // Create a dummy buffer that we won't do anything with, then repeatedly read
  // out of stdin until a newline shows up.
  char null_buffer[INPUT_BUFFER_SIZE];
  do {
    (void)fgets(null_buffer, sizeof(null_buffer), stdin);
  } while (strchr(null_buffer, '\n') == NULL);
}

int get_user_input(board_space* space) {
  puts(INPUT_PROMPT);
  char input_buffer[INPUT_BUFFER_SIZE];
  (void)fgets(input_buffer, sizeof(input_buffer), stdin);
  // If the input was too large, the newline won't be in the buffer. We already
  // know the input is invalid at this point, so stop processing.
  if (strchr(input_buffer, '\n') == NULL) {
    // Clear the rest of the input line from stdin so it doesn't affect future
    // calls.
    flush_input_line();
    return 0;
  }
  char* read_pos = input_buffer;
  space->row = (int)strtol(input_buffer, &read_pos, DECIMAL_BASE);
  // If the function did not read exactly one digit, then we already know the
  // input is invalid, so stop now.
  if (read_pos != input_buffer + 1) {
    return 0;
  }
  space->col = (int)strtol(read_pos, &read_pos, DECIMAL_BASE);
  return 1;
}

void setup_board(tic_tac_toe_board* board) {
  for (int row = 0; row < BOARD_DIM; ++row) {
    for (int col = 0; col < BOARD_DIM; ++col) {
      board->spaces[row][col] = EMPTY_SPACE;
    }
  }
}

int is_empty_space(const tic_tac_toe_board* board, board_space space) {
  return board->spaces[space.row][space.col] == EMPTY_SPACE;
}

int is_full(const tic_tac_toe_board* board) {
  for (int row = 0; row < BOARD_DIM; ++row) {
    for (int col = 0; col < BOARD_DIM; ++col) {
      if (board->spaces[row][col] == EMPTY_SPACE) {
        return 0;
      }
    }
  }
  return 1;
}

// Check if a player has won by filling a row of a board.
static int is_row_win(const tic_tac_toe_board* board, char player) {
  for (int row = 0; row < BOARD_DIM; ++row) {
    int row_win = 1;
    for (int col = 0; col < BOARD_DIM; ++col) {
      if (board->spaces[row][col] != player) {
        row_win = 0;
      }
    }
    if (row_win == 1) {
      return 1;
    }
  }
  return 0;
}

// Check if a player has won by filling a column of a board.
static int is_col_win(const tic_tac_toe_board* board, char player) {
  for (int col = 0; col < BOARD_DIM; ++col) {
    int col_win = 1;
    for (int row = 0; row < BOARD_DIM; ++row) {
      if (board->spaces[row][col] != player) {
        col_win = 0;
      }
    }
    if (col_win == 1) {
      return 1;
    }
  }
  return 0;
}

// Check if a player has won by filling a diagonal of a board.
static int is_diag_win(const tic_tac_toe_board* board, char player) {
  int trace_win = 1;
  for (int index = 0; index < BOARD_DIM; ++index) {
    if (board->spaces[index][index] != player) {
      trace_win = 0;
    }
  }
  int cross_win = 1;
  for (int index = 0; index < BOARD_DIM; ++index) {
    if (board->spaces[index][BOARD_DIM - index] != player) {
      cross_win = 0;
    }
  }
  return trace_win || cross_win;
}

int is_win(const tic_tac_toe_board* board, char player) {
  return is_row_win(board, player) || is_col_win(board, player) ||
         is_diag_win(board, player);
}

void print_board(const tic_tac_toe_board* board) {
  const char* row_divider = "+-+-+-+";
  for (int row = 0; row < BOARD_DIM; ++row) {
    printf("%s\n", row_divider);
    for (int col = 0; col < BOARD_DIM; ++col) {
      printf("|%c", board->spaces[row][col]);
    }
    printf("|\n");
  }
  printf("%s\n", row_divider);
}

void setup_state(tic_tac_toe_state* state, tic_tac_toe_board* board) {
  setup_board(board);
  state->board = board;
  state->current_turn = X_SPACE;
  state->num_moves = 0;
}

/** Switch the current player to the opposing player. */
static void next_move(tic_tac_toe_state* state) {
  if (state->current_turn == X_SPACE) {
    state->current_turn = O_SPACE;
  } else {
    state->current_turn = X_SPACE;
  }
}

int player_win(const tic_tac_toe_state* state) {
  // Checking for a win looks at the player who last moved. Since after a
  // successful move the current player switches, the opposing one is the one
  // who last moved.
  return is_win(state->board, get_opposing_player(state->current_turn));
}

int game_over(const tic_tac_toe_state* state) {
  return is_full(state->board) || is_win(state->board, X_SPACE) ||
         is_win(state->board, O_SPACE);
}

int move(tic_tac_toe_state* state, board_space space) {
  if (!is_valid_space(space) || !is_empty_space(state->board, space)) {
    return 0;
  }
  state->board->spaces[space.row][space.col] = state->current_turn;
  next_move(state);
  ++(state->num_moves);
  return 1;
}
