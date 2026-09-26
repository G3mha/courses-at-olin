#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>

#include "../src/tic_tac_toe.h"

// The player opposite X should be O.
Test(get_opposing_player, x_to_o) {
  cr_assert(eq(chr, get_opposing_player(X_SPACE), O_SPACE));
}

// The player opposite O should be X.
Test(get_opposing_player, o_to_x) {
  cr_assert(eq(chr, get_opposing_player(O_SPACE), X_SPACE));
}

// The upper-left corner (row 0, column 0) should always be in the board.
Test(is_valid_space, ul_corner) {
  board_space space = {0, 0};
  cr_assert(eq(int, is_valid_space(space), 1));
}

// The upper-right corner should always be in the board.
Test(is_valid_space, ur_corner) {
  board_space space = {0, BOARD_DIM - 1};
  cr_assert(eq(int, is_valid_space(space), 1));
}

// The lower-left corner should always be in the board.
Test(is_valid_space, ll_corner) {
  board_space space = {BOARD_DIM - 1, 0};
  cr_assert(eq(int, is_valid_space(space), 1));
}

// The lower-right corner should always be in the board.
Test(is_valid_space, lr_corner) {
  board_space space = {BOARD_DIM - 1, BOARD_DIM - 1};
  cr_assert(eq(int, is_valid_space(space), 1));
}

// A coordinate off the left side of the board (negative column) should not be
// in the board.
Test(is_valid_space, too_far_left) {
  board_space space = {0, -1};
  cr_assert(zero(int, is_valid_space(space)));
}

// A coordinate off the right side of the board (column is BOARD_DIM) should not
// be in the board.
Test(is_valid_space, too_far_right) {
  board_space space = {0, BOARD_DIM};
  cr_assert(zero(int, is_valid_space(space)));
}

// A coordinate off the upper side of the board (negative row) should not be
// in the board.
Test(is_valid_space, too_far_up) {
  board_space space = {-1, 0};
  cr_assert(zero(int, is_valid_space(space)));
}

// A coordinate off the bottom side of the board (row is BOARD_DIM) should not
// be in the board.
Test(is_valid_space, too_far_down) {
  board_space space = {BOARD_DIM, 0};
  cr_assert(zero(int, is_valid_space(space)));
}

// Reading a valid input should indicate success.
Test(get_user_input, valid_input_success) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file, "0 0\n");
  (void)fclose(stdin_file);
  board_space space;
  cr_assert(eq(int, get_user_input(&space), 1));
}

// Reading a valid input should correctly update the output space.
Test(get_user_input, valid_input_update_space) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file, "1 2\n");
  (void)fclose(stdin_file);
  board_space space;
  (void)get_user_input(&space);
  cr_assert(eq(int, space.row, 1));
  cr_assert(eq(int, space.col, 2));
}

// Reading a valid, but too long input (due to trailing characters) should
// indicate failure.
Test(get_user_input, too_long_input_failure) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file, "0 0 \n");
  (void)fclose(stdin_file);
  board_space space;
  cr_assert(zero(int, get_user_input(&space), 0));
}

// Reading an input that is too long should indicate failure.
Test(get_user_input, way_too_long_input_failure) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file, "1111111111111111 0\n");
  (void)fclose(stdin_file);
  board_space space;
  cr_assert(zero(int, get_user_input(&space), 0));
}

// Reading input that is not parseable as ints should indicate failure.
Test(get_user_input, invalid_input_failure) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file, "x y\n");
  (void)fclose(stdin_file);
  board_space space;
  cr_assert(zero(int, get_user_input(&space), 0));
}

// A new board's spaces should all be empty.
Test(setup_board, new_board) {
  tic_tac_toe_board board;
  setup_board(&board);
  for (int i = 0; i < BOARD_DIM; ++i) {
    for (int j = 0; j < BOARD_DIM; ++j) {
      cr_assert(eq(chr, board.spaces[i][j], EMPTY_SPACE));
    }
  }
}

// is_empty_space should report a new board's spaces as all empty.
Test(is_empty_space, new_board) {
  tic_tac_toe_board board;
  setup_board(&board);
  for (int i = 0; i < BOARD_DIM; ++i) {
    for (int j = 0; j < BOARD_DIM; ++j) {
      board_space space = {i, j};
      cr_assert(eq(int, is_empty_space(&board, space), 1));
    }
  }
}

// is_empty_space should report a space occupied by X as not empty.
Test(is_empty_space, x_not_empty) {
  tic_tac_toe_board board;
  setup_board(&board);
  board.spaces[0][0] = X_SPACE;
  board_space space = {0, 0};
  cr_assert(eq(int, is_empty_space(&board, space), 0));
}

// is_empty_space should report a space occupied by O as not empty.
Test(is_empty_space, o_not_empty) {
  tic_tac_toe_board board;
  setup_board(&board);
  board.spaces[0][0] = O_SPACE;
  board_space space = {0, 0};
  cr_assert(eq(int, is_empty_space(&board, space), 0));
}

// An empty board should not be considered full.
Test(is_full, empty_board_not_full) {
  tic_tac_toe_board board;
  setup_board(&board);
  cr_assert(zero(int, is_full(&board)));
}

// A partially filled board should not be considered full.
Test(is_full, partial_board_not_full) {
  tic_tac_toe_board board;
  setup_board(&board);
  board.spaces[0][0] = O_SPACE;
  board.spaces[1][1] = X_SPACE;
  cr_assert(zero(int, is_full(&board)));
}

// A full board should be considered full.
Test(is_full, full_board) {
  tic_tac_toe_board board;
  setup_board(&board);
  for (int i = 0; i < BOARD_DIM; ++i) {
    for (int j = 0; j < BOARD_DIM; ++j) {
      board.spaces[i][j] = X_SPACE;
    }
  }
  cr_assert(eq(int, is_full(&board), 1));
}

// Check a no-win case.
Test(is_win, no_win_empty) {
  tic_tac_toe_board board;
  setup_board(&board);
  cr_assert(zero(int, is_win(&board, X_SPACE)));
}

// A full, but drawn game is not considered a win.
Test(is_win, no_win_draw) {
  tic_tac_toe_board board;
  board.spaces[0][0] = X_SPACE;
  board.spaces[0][1] = X_SPACE;
  board.spaces[0][2] = O_SPACE;
  board.spaces[1][0] = O_SPACE;
  board.spaces[1][1] = X_SPACE;
  board.spaces[1][2] = X_SPACE;
  board.spaces[2][0] = X_SPACE;
  board.spaces[2][1] = O_SPACE;
  board.spaces[2][2] = O_SPACE;
  cr_assert(zero(int, is_win(&board, X_SPACE)));
}

// A row win is considered a win.
Test(is_win, row_win) {
  tic_tac_toe_board board;
  setup_board(&board);
  for (int col = 0; col < BOARD_DIM; ++col) {
    board.spaces[0][col] = X_SPACE;
  }
  cr_assert(eq(int, is_win(&board, X_SPACE), 1));
}

// A column win is considered a win.
Test(is_win, col_win) {
  tic_tac_toe_board board;
  setup_board(&board);
  for (int row = 0; row < BOARD_DIM; ++row) {
    board.spaces[row][0] = X_SPACE;
  }
  cr_assert(eq(int, is_win(&board, X_SPACE), 1));
}

// A diagonal win is considered a win.
Test(is_win, diag_win) {
  tic_tac_toe_board board;
  setup_board(&board);
  for (int index = 0; index < BOARD_DIM; ++index) {
    board.spaces[index][index] = X_SPACE;
  }
  cr_assert(eq(int, is_win(&board, X_SPACE), 1));
}

// Check that an empty board prints correctly.
Test(print_board, empty_board, .init = cr_redirect_stdout) {
  tic_tac_toe_board board;
  setup_board(&board);
  print_board(&board);
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str(
      "+-+-+-+\n"
      "| | | |\n"
      "+-+-+-+\n"
      "| | | |\n"
      "+-+-+-+\n"
      "| | | |\n"
      "+-+-+-+\n");
}

// Check that an X move prints correctly.
Test(print_board, x_move, .init = cr_redirect_stdout) {
  tic_tac_toe_board board;
  setup_board(&board);
  board.spaces[0][0] = X_SPACE;
  print_board(&board);
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str(
      "+-+-+-+\n"
      "|X| | |\n"
      "+-+-+-+\n"
      "| | | |\n"
      "+-+-+-+\n"
      "| | | |\n"
      "+-+-+-+\n");
}

// Check that an O move prints correctly.
Test(print_board, o_move, .init = cr_redirect_stdout) {
  tic_tac_toe_board board;
  setup_board(&board);
  board.spaces[0][0] = O_SPACE;
  print_board(&board);
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str(
      "+-+-+-+\n"
      "|O| | |\n"
      "+-+-+-+\n"
      "| | | |\n"
      "+-+-+-+\n"
      "| | | |\n"
      "+-+-+-+\n");
}

// Setting up a state should initialize the board.
Test(setup_state, setup_empty_board) {
  tic_tac_toe_board board;
  tic_tac_toe_state state;
  setup_state(&state, &board);
  for (int i = 0; i < BOARD_DIM; ++i) {
    for (int j = 0; j < BOARD_DIM; ++j) {
      cr_assert(eq(chr, board.spaces[i][j], EMPTY_SPACE));
    }
  }
}

// Setting up a state should set the number of moves to zero.
Test(setup_state, no_moves) {
  tic_tac_toe_board board;
  tic_tac_toe_state state;
  setup_state(&state, &board);
  cr_assert(zero(sz, state.num_moves));
}

// Setting up a state should have X going first.
Test(setup_state, x_starts) {
  tic_tac_toe_board board;
  tic_tac_toe_state state;
  setup_state(&state, &board);
  cr_assert(eq(chr, state.current_turn, X_SPACE));
}

// In an empty board, neither player is winning.
Test(player_win, new_state_no_win) {
  tic_tac_toe_state state;
  tic_tac_toe_board board;
  setup_state(&state, &board);
  cr_assert(zero(int, player_win(&state)));
  state.current_turn = O_SPACE;
  cr_assert(zero(int, player_win(&state)));
}

// If the current player is winning, the state shouldn't report a win.
Test(player_win, current_player_win) {
  tic_tac_toe_state state;
  tic_tac_toe_board board;
  setup_state(&state, &board);
  for (int col = 0; col < BOARD_DIM; ++col) {
    board.spaces[0][col] = X_SPACE;
  }
  cr_assert(zero(int, player_win(&state)));
}

// If the opposing player is winning, the state should report a win.
Test(player_win, opposing_player_win) {
  tic_tac_toe_state state;
  tic_tac_toe_board board;
  setup_state(&state, &board);
  for (int col = 0; col < BOARD_DIM; ++col) {
    board.spaces[0][col] = O_SPACE;
  }
  cr_assert(eq(int, player_win(&state), 1));
}

// A new game should not be over.
Test(game_over, new_game_not_over) {
  tic_tac_toe_state state;
  tic_tac_toe_board board;
  setup_state(&state, &board);
  cr_assert(zero(int, game_over(&state)));
}

// The game should be over when the board is full.
Test(game_over, board_full) {
  tic_tac_toe_state state;
  tic_tac_toe_board board;
  setup_state(&state, &board);
  board.spaces[0][0] = X_SPACE;
  board.spaces[0][1] = X_SPACE;
  board.spaces[0][2] = O_SPACE;
  board.spaces[1][0] = O_SPACE;
  board.spaces[1][1] = X_SPACE;
  board.spaces[1][2] = X_SPACE;
  board.spaces[2][0] = X_SPACE;
  board.spaces[2][1] = O_SPACE;
  board.spaces[2][2] = O_SPACE;
  cr_assert(eq(int, game_over(&state), 1));
}

// The game should be over when a player has won.
Test(game_over, player_won) {
  tic_tac_toe_state state;
  tic_tac_toe_board board;
  setup_state(&state, &board);
  for (int col = 0; col < BOARD_DIM; ++col) {
    board.spaces[0][col] = O_SPACE;
  }
  cr_assert(eq(int, game_over(&state), 1));
}

// A successful move should update that space on the board.
Test(move, update_board) {
  tic_tac_toe_state state;
  tic_tac_toe_board board;
  setup_state(&state, &board);
  board_space space = {0, 0};
  (void)move(&state, space);
  cr_assert(eq(chr, board.spaces[0][0], X_SPACE));
}

// A successful move should return 1 to indicate success.
Test(move, return_success) {
  tic_tac_toe_state state;
  tic_tac_toe_board board;
  setup_state(&state, &board);
  board_space space = {0, 0};
  cr_assert(eq(int, move(&state, space), 1));
}

// A move that fails due to being outside the board should indicate failure.
Test(move, invalid_space_failure) {
  tic_tac_toe_state state;
  tic_tac_toe_board board;
  setup_state(&state, &board);
  board_space space = {-1, 0};
  cr_assert(zero(int, move(&state, space)));
}

// A move that fails due to being outside the board should not change the board.
Test(move, invalid_space_unchanged) {
  tic_tac_toe_state state;
  tic_tac_toe_board board;
  setup_state(&state, &board);
  board_space space = {-1, 0};
  (void)move(&state, space);
  for (int i = 0; i < BOARD_DIM; ++i) {
    for (int j = 0; j < BOARD_DIM; ++j) {
      cr_assert(eq(chr, board.spaces[i][j], EMPTY_SPACE));
    }
  }
}

// A move that fails due to the space being full should indicate failure.
Test(move, space_full_failure) {
  tic_tac_toe_state state;
  tic_tac_toe_board board;
  setup_state(&state, &board);
  board_space space = {0, 0};
  (void)move(&state, space);
  cr_assert(zero(int, move(&state, space)));
}

// A move that fails due to the space being full should not change the space.
Test(move, space_full_unchanged) {
  tic_tac_toe_state state;
  tic_tac_toe_board board;
  setup_state(&state, &board);
  board_space space = {0, 0};
  (void)move(&state, space);
  (void)move(&state, space);
  cr_assert(eq(chr, board.spaces[0][0], X_SPACE));
}
