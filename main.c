#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

//Question1 Explain what pthread is doing in this program. Be specific.
//pthread is creating a new thread based off the child template at the beginning of the program. It also waiting for the user to hit "ENTER" to terminate the child thread which infinitely loops while we wait on that input.

//Question2 Explain how the sleeping thread is able to send out messages periodically.
//The sleeping thread is able to send out its messages periodically because all threads from the same process share resources that other threads performing different tasks also have access to.

//Template for the child thread
static void *child(void *ignored){
  //Infinite loop that will repeat the print statement below unless
  //killed in main thead
  while (1){
   sleep(3);
   printf("Child is done sleeping 3 seconds.\n");
  }
   return NULL;
}

//Actual setup of main parent thread and child thread
int main(int argc, char *argv[]){
   pthread_t child_thread;
   //Command/line to setup the child thread
   pthread_create(&child_thread, NULL, child, NULL);
   int code;
   //Setting up flags/chars for infinite loop to wait for user input
   //of "ENTER" to kill the child thread
   bool flag = true;
   char ch;
   while(flag==true){
     ch = getchar();
     code = child_thread;
     //"Enter" input is equivilent to 0x0A
     if(ch=0x0A){
       flag = false;
       pthread_cancel(child_thread);
     }
     else if (code){
       fprintf(stderr,"pthread_create failed with code %d\n", code);
     }
   }
   //Statement to notify child thread is dead + closing
   printf("Child thread is asleep forever.\n");
   sleep(5);
   printf("Parent is done sleeping 5 seconds.\n");
   return 0;
}