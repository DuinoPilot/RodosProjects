#include "rodos.h"
#include "robot_topics.h"


/** READ-ONLY topics
 *  Please do not assign new values. You will confuse the robot :) !!!
 */
// robot to commander
Topic<int>    robotX(-1, "robotX");
Topic<int> robotY(-1, "robotY");
Topic<char> robotDir(-1, "robotDir");

// target position
Topic<int> targetX(-1, "targetX");
Topic<int> targetY(-1, "targetY");


/** READ-WRITE topics
 *  Assign new values to control the robot and lead it to the traget.
 */ 
// commander to robot
Topic<char> commandDir(-1, "commandDir");  // valid values: "L"eft, "R"ight, "U"p and "D"own 
Topic<int> commandSpeed(-1, "commandSpeed"); // valid values: 0 to 10

//Topic<Position>  position(-1, "position");
