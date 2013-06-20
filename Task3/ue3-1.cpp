#include "rodos.h"
#include <stdlib.h>
#include "random.h"


#define ENTER   0
#define LEAVE   1

static Application module01("Uebung2-1", 2000);

Semaphore x;
Semaphore y;

class TheThread: public Thread{
private:
  int random = 0;
  int last_run = 1;
public:
  
  TheThread(const char * name) : Thread(name, 25) {
  }
  
  void run() {
      PRINTF("%s & the deadlock...\n", name);

    TIME_LOOP(0, 100*MILLISECONDS){
      random = randomTT800Positive() % 2;
      if(last_run == LEAVE){
        //last run was a leave command
        switch(random){
          case 0:
            xprintf("%s entered semX\n", name);
            last_run = ENTER;
            x.enter();
          break;
          case 1:
            y.enter();
            xprintf("%s entered semY\n", name);
            last_run = ENTER;
          break;
          }
        }else{
        //last run was a enter command
        switch(random){
          case 0:
            y.leave();
            xprintf("%s left semY\n", name);
            last_run = LEAVE;
            break;
          case 1:
            x.leave();
            xprintf("%s left semX\n", name);
            last_run = LEAVE;
            break;
        }
      }     
    }
  }
};

TheThread a("A");
TheThread b("B");
TheThread c("C");

/*
a)
void run() {
    while(1){
      x.enter();
      suspendCallerUntil(NOW() + 100 * MILLISECONDS);
        y.enter();
        suspendCallerUntil(NOW() + 100 * MILLISECONDS);
        y.leave();
        suspendCallerUntil(NOW() + 100 * MILLISECONDS);
      x.leave();
      suspendCallerUntil(NOW() + 100 * MILLISECONDS);
    }
  }
*/
