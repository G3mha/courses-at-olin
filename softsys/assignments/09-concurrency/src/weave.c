#include "weave.h"

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

void ready(size_t thread_id) { printf("Thread %zu ready!\n", thread_id); }

void go(size_t thread_id) { printf("Thread %zu go!\n", thread_id); }

void* synchronize(void* args) {
  thread_args* my_args = (thread_args*)args;
  ready(my_args->thread_id);
  pthread_mutex_lock(my_args->lock);
  (*my_args->ready_threads)++;
  
  if (*my_args->ready_threads == my_args->total_threads) {
    for (size_t i = 0; i < my_args->total_threads; i++) {
      sem_post(my_args->go_signal);
    }
  }
  
  pthread_mutex_unlock(my_args->lock);
  sem_wait(my_args->go_signal);
  go(my_args->thread_id);

  return NULL;
}

void start_threads(size_t num_threads) {
  pthread_mutex_t lock;
  sem_t go_signal;
  size_t ready_threads = 0;
  
  pthread_mutex_init(&lock, NULL);
  sem_init(&go_signal, 0, 0);
  
  pthread_t* threads = malloc(num_threads * sizeof(pthread_t));
  thread_args* args = malloc(num_threads * sizeof(thread_args));

  for (size_t i = 0; i < num_threads; i++) {
    args[i].lock = &lock;
    args[i].go_signal = &go_signal;
    args[i].ready_threads = &ready_threads;
    args[i].thread_id = i;
    args[i].total_threads = num_threads;
    
    pthread_create(&threads[i], NULL, synchronize, &args[i]);
  }

  for (size_t i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  pthread_mutex_destroy(&lock);
  sem_destroy(&go_signal);
  free(threads);
  free(args);
}

