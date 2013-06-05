#include "rodos.h"

static Application module01("Uebung1", 2000);

class TimeThread: public Thread{
private:
  int periodTime;
  long long int callCount = 0;
public:
  TimeThread(const char * name, const int timeParam) : Thread(name, 25) {
    periodTime = timeParam;
  }
  void init(){
    xprintf("initTime with %d",periodTime);
  }

  void run() {
    while(1){
      xprintf("%lld by Thread: %s, called %lld times\n", NOW(),name,callCount);
      FFLUSH();
      callCount++;
      suspendCallerUntil(NOW()+periodTime*SECONDS);
    }
  }
};
//a
TimeThread secondThread("SecondThread", 1);
TimeThread twoSecondThread("TwoSecondThread", 2);
TimeThread fiveSecondhread("FiveSecondThread", 5);
TimeThread elevenSecondThread("ElevenSecondThread", 11);
//b
TimeThread thirtySecondThread("ThirtySecondThread", 30);