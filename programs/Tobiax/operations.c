/*
The kernel operations like gpio control, i2c etc and power off.
*/

int initOperations()
{

}
int powerOff(int error)
{
  //clean memory, write error code and exit
}
//control led display, takes in16 args in the custom led format
int LED(int16 display)
{

}
//simple rtc commands like reading time,takes int8 as args
int RTCsimp(int8 args)
{

}
//low level rtc control, takes the i2c command exclusive memAddr
int RTCadva(char* args)
{

}
//send hid data, operation is the operation and args string of what to send
int HID(int8 operation, char* args)
{

}
//i2c data of what to send
int tiny85(char* args)
{

}
//i2c data of what to send
int tiny417(char* args)
{

}
