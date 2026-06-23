/**
* Program to write a string (writestr) to a file (writefile) 
*/

#include <unistd.h>  
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>

/* ssize_t write (int fd, const void *buf, size_t count); */  

int creat (const char *name, mode_t mode); 
ssize_t write (int fd, const void *buf, size_t count);

int writer(char *writefile, char *writestr) {  
  syslog(LOG_DEBUG, "Writing %s to %s\n",writestr,writefile); 
  size_t count; 
  ssize_t nr; 
  int fd; 

  fd = creat (writefile, 0644); 

  if (fd == 1) {  
    printf("error during file creation");
    syslog(LOG_ERR, "Assignment 2, error during file creation\n"); 
    return 1; } 
  count = strlen(writestr);
  nr = write (fd, writestr, count); 
  if (nr == -1) {  
          fd = 1;
          syslog(LOG_ERR, "Assignment 2, error during file write\n"); 
          return 1;  
  } else if (nr != count) {
          fd = count;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  openlog("AESD: karlmickelson", 0, LOG_USER); 
  if (argc != 3) {
     syslog(LOG_ERR, "Assignment 2, number of arguments for writer must be 2\n");   
     return 1; }  
  syslog(LOG_USER, "Assignment 2, running write.c\n"); 
  syslog(LOG_USER, "Main: Writing %s to %s\n",argv[2],argv[1]); 
  writer(argv[1],argv[2]);  
  closelog(); 
  return 0;
}
