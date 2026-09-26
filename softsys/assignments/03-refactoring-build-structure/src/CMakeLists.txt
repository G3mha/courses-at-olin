add_library(tic_tac_toe tic_tac_toe.c tic_tac_toe.h)

add_executable(run_tic_tac_toe run_tic_tac_toe.c)
target_link_libraries(run_tic_tac_toe tic_tac_toe)
