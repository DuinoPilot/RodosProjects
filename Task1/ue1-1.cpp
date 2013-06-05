#include "rodos.h"

static Application module01("Uebung1", 2000);

class HelloWorldThread: public Thread{
public:
  HelloWorldThread(const char * name) : Thread(name, 25) { 
  }


  void run() {
      xprintf("Message: HelloWorld! - ");
      xprintf("ThreadName: %s\n", name);
      FFLUSH();
      suspendCallerUntil(END_OF_TIME);
  }
};

HelloWorldThread helloWorldThread("HelloWorldThread");
HelloWorldThread frenchWorldThread("BonjourThread");
HelloWorldThread spanishWorldThread("¡Hola!Thread");
