 #include "threading.h"
#include <unistd.h>
#include <syslog.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdarg.h>
// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)
//#define MAX_NUM_THREADS (10)
void *threadfunc(void *thread_param)
{
    thread_data *thread_func_args = (thread_data *)thread_param;
    int wait_lock, wait_unlock;
    wait_lock = 1000*thread_func_args->wait_to_obtain_ms;
    usleep(wait_lock);
    // obtain mutex
    pthread_mutex_lock(thread_func_args->mutex);
    wait_unlock = 1000*thread_func_args->wait_to_release_ms;
    usleep(wait_unlock);
    // release mutex
    pthread_mutex_unlock(thread_func_args->mutex);
    printf("Karl, Thread is finished.\n");
    thread_func_args->thread_complete_success = true;
    return NULL;
}
bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    thread_data *thread_func_args = malloc(sizeof(thread_data));
    if (thread_func_args == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }
    
    pthread_mutex_init(thread_func_args->mutex, NULL);
    //pthread_t threadID;  // Declare a pthread thread descriptor
    //int index; 
    thread_func_args->threadID = thread;
    thread_func_args->mutex = mutex;
    thread_func_args->wait_to_obtain_ms = wait_to_obtain_ms;
    thread_func_args->wait_to_release_ms = wait_to_release_ms;
    thread_func_args->thread_complete_success = false;
    index = 0;
    // Create a new thread
    syslog(LOG_USER, "Assignment 4,  doing pthread_create");
    printf("Karl, Creating new thread\n");
    int threadfunctreturn = pthread_create(&threadID,   // pointer to thread descriptor
                            NULL,                       // use SPECIFIC SECHED_FIFO attributes
                            threadfunc,                 // thread function entry point
                            (void *)&(thread_func_args));   // parameters to pass in
    if (threadfunctreturn != 0) {
        printf("Error creating thread\n");
        return 1;
    }
    pthread_mutex_destroy(thread_func_args->mutex);
    // Wait for the thread to finish
    pthread_join(threadID, NULL);
    printf("Karl, whole thing has finished.\n");
    if (threadfunctreturn == threadID) return true;
    else return false;
    
}  
