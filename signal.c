#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int trigger = 0;
int alarmcount = 0;

time_t start, stop;

void thehandler1(int signum)
{ //signal handler
  printf("Hello World!\n");
  sleep(1);
  
  trigger = 1;
  
  alarmcount++;
  
  //exit(1); //exit after printing
}
void thehandler2(int signum){ 
  
  int totalalarms;
  stop = time(NULL);
  
  totalalarms = stop - start;
  
  printf("\nNumber of alarm: %d\n in seconds %d\n", alarmcount, totalalarms);
}
int main(int argc, char * argv[])
{
  signal(SIGALRM,thehandler1); //register handler to handle SIGALRM
  signal(SIGINT,thehandler2); //register handler to handle SIGINT
  
  start = time(NULL);
  
  while(1){
    trigger = 0;
    alarm(1); //Schedule a SIGALRM for 1 second
    
    while(!trigger);//busy wait for signal to be delivered
    
    printf("Turing was right!\n");
  }
  
 
  return 0; //never reached
}