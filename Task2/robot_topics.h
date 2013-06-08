#ifndef _ROBOT_TOPICS_H_
#define _ROBOT_TOPICS_H_

#include "rodos.h"

/** READ-ONLY topics
 *  Please do not assign new values. You will confuse the robot :) !!!
 */
// robot to commander
extern Topic<int> robotX;
extern Topic<int> robotY;
extern Topic<char> robotDir;

// target position
extern Topic<int> targetX;
extern Topic<int> targetY;


/** READ-WRITE topics
 *  Assign new values to control the robot and lead it to the traget.
 */ 
// commander to robot
extern Topic<char> commandDir;  // valid values: "L"eft, "R"ight, "U"p and "D"own 
extern Topic<int> commandSpeed; // valid values: 0 to 10

#endif
