#include "rodos.h"
#include "random.h"
#include <vector>

using std::vector;

static Application module("semaphordeadlocknomore",2000);

vector<char> enteredRequester;
int requesterCount = 0;

int indexOfCharInVector(char id, vector<char> vector){
    for(int i = 0; i < vector.size(); i++){
        if(vector[i] == id){
            return i;
        }
    }
    return -1;
}

void printVector(vector<char> vector){
    xprintf("######################\n");
    xprintf("# ACTIVE REQUESTERS  #\n");
    for(int i = 0; i < vector.size();i++){
        xprintf("# %d. r%c              #\n", i + 1, vector[i]);
    }
    xprintf("# ReqCount: %d        #\n", vector.size());
    xprintf("######################\n");
}

bool isDeadlock(vector<char> v1, vector<char> v2){
    //check if two or more threads are in both semaphores
    int doubleSemCount = 0;
    for(int i=0;i < v1.size(); i++){
        for(int j=0; j < v2.size(); j++){
            if(v1[i] == v2[j]){
                doubleSemCount++;
            }
        }
    }
    return doubleSemCount >= 2;
}

class SecureSemaphore : public Semaphore {
    int id;
public:
    vector<char> enteredRequester;

    SecureSemaphore(int name){
        id = name;
    }
    void secure_enter(char reqName){
        enteredRequester.push_back(reqName);
        xprintf("%c -> Semaphore s%d secure enter\n", reqName, id);
        enter();
    }
    void secure_leave(char reqName){
        int index = indexOfCharInVector(reqName, enteredRequester);
        if(index != -1){
            enteredRequester.erase(enteredRequester.begin() + index);
        }
        xprintf("%c <- Semaphore s%d secure leave\n",reqName, id);
        leave();
    }

};

SecureSemaphore s1(1);
SecureSemaphore s2(2);

class Requester : public Thread {
    char id;
public:
    Requester(char name) {
        id = name;
    }

    void run() {
        bool s1Lock = false;
        bool s2Lock = false;

        TIME_LOOP(0, 100*MILLISECONDS) {
            int action = randomTT800Positive() % 4;
            switch (action) {
            case 0:
                if (s1Lock) break;
                PRINTF("%c secure_enter s1 \n", id);
                s1.secure_enter(id);
                s1Lock = true;
                break;

            case 1:
                if (s2Lock) break;
                PRINTF("%c secure_enter s2 \n", id);
                s2.secure_enter(id);
                s2Lock = true;
                break;

            case 2:
                if (!s1Lock) break;
                PRINTF("%c secure_leave s1 \n", id);
                s1.secure_leave(id);
                s1Lock = false;
                break;

            case 3:
                if (!s2Lock) break;
                PRINTF("%c secure_leave s2 \n", id);
                s2.secure_leave(id);
                s2Lock = false;
                break;


            }
        }
    }
};

class Printer : public Thread{
    char id;
public:
    Printer(char name){
        id = name;
    }
    void run(){
        xprintf("Starting PRINTER %c\n", id);
        xprintf("Max Size of Vector %d\n", enteredRequester.max_size());
        TIME_LOOP(0, 1000*MILLISECONDS) {  
                if(isDeadlock(s1.enteredRequester, s2.enteredRequester)){
                    xprintf("Deadlock occured!\n");
                    xprintf("Semaphore 1:\n");
                    printVector(s1.enteredRequester);
                    xprintf("Semaphore 2:\n");
                    printVector(s2.enteredRequester);  
                    FFLUSH();
                    suspendCallerUntil(END_OF_TIME);
                }
        }
    }
};

Printer printer('P');

Requester r1('A');
Requester r2('B');
Requester r3('C');
