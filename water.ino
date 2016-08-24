#include <Servo.h> 

Servo miniservo;
//int inputSensor = 0;
int input_val = 1;
int pos = 0;

void setup()
{
  //Serial.begin(9600); //open serial port
  miniservo.attach(9); 
}
 
void loop(){
  
  if (input_val == 1){
    for(pos = 0; pos <= 140; pos += 1){ 
      miniservo.write(pos);               
      delay(20);
      input_val=2;     
    }delay(1000);
  }
  else if (input_val == 2){
    for(pos = 140; pos>=0; pos-=1){                                
      miniservo.write(pos);               
      delay(15);
      input_val=1;
    }      
  }
}
