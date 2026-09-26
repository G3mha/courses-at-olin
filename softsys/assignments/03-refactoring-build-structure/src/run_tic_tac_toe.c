#include <stdio.h>
#include <stdlib.h>

#include "tic_tac_toe.h"

int main(void) {
  // Ideally, the state setup would involve using malloc calls for the board and
  // overall state, but since malloc hasn't been introduced yet in this course,
  // the memory needs to be created on the stack instead.
  tic_tac_toe_board board;
  tic_tac_toe_state state;
  setup_state(&state, &board);
  while (!game_over(&state)) {
    print_board(state.board);
    printf("It is now %c's move.\n", state.current_turn);
    board_space space;
    if (get_user_input(&space) == 0 || move(&state, space) == 0) {
      puts("Invalid move, please try again.");
      continue;
    }
  }
  if (player_win(&state)) {
    printf("%c wins in %zu moves!\n", get_opposing_player(state.current_turn),
           state.num_moves);
  } else {
    // The only other way the game can end is if the board is full and nobody's
    // won, which is a draw.
    printf("It's a draw.\n");
  }
  return EXIT_SUCCESS;
}
