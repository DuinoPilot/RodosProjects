#include "rodos.h"
#include "robot_topics.h"

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
  xprintf("Dir: %c, Speed: %d\n Robot: (%ld|%ld), Target(%ld|%ld)\n", 
    dir, speed,myRobotX,myRobotY,myTargetX,myTargetY);
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

  void run(){
    TIME_LOOP(1*MILLISECONDS, 1 * MILLISECONDS){
      if(!robotIsOnTarget()){
          commandSpeed.publishConst(speed);
          // switch(dir){
          //   case 'D':
          //   diff = myTargetY - myRobotY;
          //   break;
          //   case 'U':
          //   diff = myRobotY - myTargetY;
          //   break;
          //   case 'R':
          //   diff = myTargetX - myRobotX;
          //   break;
          //   case 'L':
          //   diff = myRobotX - myTargetX;
          //   break;
          //   default:
          //   diff = 1;
          //   break;
          // }
          // if(diff >= 10){
          //   speed = 10;
          // }
          // else{
          //   speed = diff;
          // }
          // xprintf("Speed: %d, Diff: %ld", speed, diff);
          // FFLUSH();
          // commandSpeed.publishConst(speed);
      }
      // else{
      //    //stop when robot has reached target
      //   speed = 0;
      //   commandSpeed.publishConst(speed);
      //   xprintf("YEAH!");
      //  }
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