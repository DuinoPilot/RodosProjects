#include "rodos.h"

static Application module01("Uebung2", 2000);

volatile long int cnt = 0;
Semaphore incrementCounter;

class SomeThread: public Thread{
private:
  long int callCount;
public:
  
  SomeThread(const char * name) : Thread(name, 25) {
  }
  void init(){
	callCount = 0;
  }

  void run() {
	while(1){
		
    incrementCounter.enter();
		cnt++;
    incrementCounter.leave();

		callCount++;
		xprintf("Process %s called.\n localCount*2: %ld, globalCount: %ld\n",name,callCount*2,cnt);
		FFLUSH();
	}
  }
};

SomeThread eins("1");
SomeThread zwei("2");
