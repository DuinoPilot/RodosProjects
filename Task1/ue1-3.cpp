#include "rodos.h"

static Application module01("Uebung1", 2000);

  // fifo not workingggg!
  // Fifo<RingElement,8> elements;
  // int counter = 0;

class RingElement: public Thread{
private:
  RingElement *next;
public:
  static RingElement *head;
  static RingElement *tail;

  RingElement(const char * name) : Thread(name, 25) {
  }
  void init(){
    // elements[counter] = *this;
    // counter++;
    if(head == NULL){
      head = this;
      tail = this;
      this -> next = head;
    } else {
      tail -> next = this;
      tail = this;
      this -> next = head;
    }
  }

  void run() {
    while(1){
      AT(NOW()+ 1*SECONDS);

      xprintf("%s ", name);
      FFLUSH();
      
      this->next->resume();
      suspendCallerUntil(END_OF_TIME);
    }
  }
};
RingElement *RingElement::head=NULL, *RingElement::tail = NULL;
RingElement h("Holger"),g("G"),f("F"),e("E"),d("D"),c("C"),b("B"),a("A");