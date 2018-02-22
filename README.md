# tanger-ArmenMotors

Test module for Tango CS for Armen motors controller


## Commands:
 - MotionLeft
 - MotionRight
 - Stop
 - PowerOn(bool) - true - on / false - off
 - bool GetEnd - return state at End motion

## Attributes:
 - number_of_motors - The controller of Armen supported 6 motors
 - speed_of_motors - This frequncy in Hz eq speed of rotation motor
 - address - Just Armen parameter for controller. Value: 81 or 82
