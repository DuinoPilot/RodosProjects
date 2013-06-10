#include "rodos.h"
#include "robot_topics.h"
#include <stdlib.h>  

int speed = 10;
char dir;
long diff;

static Application myReceiver("ReciverThread", 2000);

long myRobotX, myRobotY, myTargetX, myTargetY;
char myRobotDir;

void saveRobotX(long& val){
  myRobotX = val;
}

void saveRobotY(long& val){
  myRobotY = val;
}

void saveTargetX(long& val){
  myTargetX = val;
}

void saveTargetY(long& val){
  myTargetY = val;
}

void saveRobotDir(long& val){
  myRobotDir = (char)val;
}

bool robotIsOnTarget(){
  bool val = myTargetY == myRobotY && myTargetX == myRobotX;
  return val;
}

void printRobotStatus(){
  xprintf("\t\t\t\t\t\t\t\t\tDir: %c, Speed: %d, Robot: (%ld|%ld), Target(%ld|%ld)\n", 
    dir, speed,myRobotX,myRobotY,myTargetX,myTargetY);
}

int calcDist(){
  return abs(myRobotX - myTargetX) * abs(myRobotY - myTargetY);
}

class DirectionPublisher : public Thread {
public:
  DirectionPublisher() : Thread("DirectionPublisher") {
  }

  void run () {
    TIME_LOOP(1*MILLISECONDS, 1 * MILLISECONDS){
      if(!robotIsOnTarget()){
        if(myRobotY < myTargetY){
          //turn down
          dir = 'D';
        }else if(myRobotY > myTargetY){
          //turn up
          dir = 'U';
        }else if(myRobotX < myTargetX){
          //turn right
          dir = 'R';
        }else if(myRobotX > myTargetX){
          dir = 'L';
        }
        commandDir.publish(dir);
      }
    }
  }
};


class SpeedPublisher : public Thread{
public:
  SpeedPublisher() : Thread("SpeedPublisher"){
  }
  void init(){
    commandSpeed.publishConst(speed);
  }

  void run(){
    TIME_LOOP(55 * MILLISECONDS, 55 * MILLISECONDS){
      if(!robotIsOnTarget()){
          if(calcDist() <= 2){
            speed = 3;
            commandSpeed.publishConst(speed);
          }else if(speed != 10){
            speed = 10;
            commandSpeed.publishConst(speed);
          }
      }else{
        speed = 0;
        commandSpeed.publishConst(speed);
      }
      //printRobotStatus();
    }
  }
};

SubscriberReceiver<long> robotXSubscriber(robotX, saveRobotX, "RobotX");
SubscriberReceiver<long> robotYSubscriber(robotY, saveRobotY, "RobotY");
SubscriberReceiver<long> robotDirSubscriber(robotDir, saveRobotDir, "RobotDir");
SubscriberReceiver<long> targetYSubscriber(targetX, saveTargetX, "TargetX");
SubscriberReceiver<long> targetXSubscriber(targetY, saveTargetY, "TargetY");

DirectionPublisher directionPublisher;
SpeedPublisher speedPublisher;
