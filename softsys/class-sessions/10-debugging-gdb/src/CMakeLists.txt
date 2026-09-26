add_executable(mystery mystery.c)

add_executable(local_sum local_sum.c)

add_executable(ticker ticker.c)

add_executable(primes primes.c)
target_link_libraries(primes PRIVATE m)
