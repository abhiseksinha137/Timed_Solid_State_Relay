long current_time=0;
int flagMsg;
String readString;
#define SSR_ON LOW
#define SSR_OFF HIGH
struct SSR {
  int id;
  int status;   // 1 for on; 0 for off
  long timeSince_stateChanged;
  long on_time;
  long off_time;
  int pin;
};
//long checkSwitch(SSR, long);
SSR switch1,switch2;

void setup() {
  // put your setup code here, to run once:
  switch1={1,0,0,1000,1000,13}; //ID,initial_status, 0, on_time, off_time, pin
  switch2={2,1,0,3000,2000,6};  
  
  pinMode(switch1.pin, OUTPUT);
  pinMode(switch2.pin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  // Check Serial for Commands
  flagMsg=0;
   while (Serial.available()) {
      char c = Serial.read();  //gets one byte from serial buffer
      readString += c; //makes the string readString
      delay(50);
   }
   if (readString.length() >0) {
      //Serial.print(readString);  //so you can see the captured string
      setSwitch();
   }
   readString=""; //empty for next input
  
  
  
  // put your main code here, to run repeatedly:
  current_time = millis();
  checkSwitch(&switch1, current_time);
  checkSwitch(&switch2, current_time);
}

long checkSwitch(SSR *sw, long current_time)
{
  if (sw->status==1) // If the switch is already on
  {
    if((current_time-sw->timeSince_stateChanged)>=sw->on_time)
    {
        // Turn off SSR
        digitalWrite(sw->pin,SSR_OFF);
        Serial.print("Turning Switch No. ");
        Serial.print(sw->id);
        Serial.print(" OFF at: ");
        Serial.println(current_time);
        
        sw->timeSince_stateChanged=current_time;
        sw->status=0;
    }
  }
  else   // If the switch is already Off
  {
      if((current_time-sw->timeSince_stateChanged)>=sw->off_time)
    {
        // Turn On SSR
        digitalWrite(sw->pin,SSR_ON);        
        Serial.print("Turning Switch No. ");
        Serial.print(sw->id);
        Serial.print(" ON at: ");
        Serial.println(current_time);
        
        sw->timeSince_stateChanged=current_time;
        sw->status=1;
    }
  }
  return -1;   // State not changed
}



void setSwitch()
{
    //command :
    if (readString.indexOf("get") != -1){
        char buffer[200];
        int length = 0;
        length +=sprintf(buffer+length , "%d,%d,%ld,%ld,%ld,%d;", switch1.id,switch1.status,switch1.timeSince_stateChanged,switch1.on_time, switch1.off_time, switch1.pin
         ); //ID,initial_status, 0, on_time, off_time, pin
        length +=sprintf(buffer+length , "%d,%d,%ld,%ld,%ld,%d", switch2.id,switch2.status,switch2.timeSince_stateChanged,switch2.on_time, switch2.off_time, switch2.pin
        ); //ID,initial_status, 0, on_time, off_time, pin
        Serial.println(buffer);
    }
    else
    {
      int commaIndex  = readString.indexOf(',');


      //  Search for the next comma just after the first
      int secondCommaIndex = readString.indexOf(',', commaIndex + 1);
      int thirdCommaIndex = readString.indexOf(',', commaIndex + 2);
      int fourthCommaIndex = readString.indexOf(',', commaIndex + 3);
      int fifthCommaIndex = readString.indexOf(',', commaIndex + 4);
      //int sixthCommaIndex = readString.indexOf(',', commaIndex + 5);
      //ID,initial_status, 0, on_time, off_time, pin
      String firstValue = readString.substring(0, commaIndex);
      String secondValue = readString.substring(commaIndex+1, secondCommaIndex);
      String thirdValue = readString.substring(secondCommaIndex+1, thirdCommaIndex);
      String fourthValue = readString.substring(thirdCommaIndex+1, fourthCommaIndex);
      String fifthValue = readString.substring(fourthCommaIndex+1, fifthCommaIndex);
      String sixthValue = readString.substring(fifthCommaIndex+1);
     
      //ID,initial_status, 0, on_time, off_time, pin
      int ID=firstValue.toInt();
      int status=secondValue.toInt();
      int on_time=fourthValue.toInt();
      int off_time=fifthValue.toInt();
      int pin=sixthValue.toInt();
      Serial.println(ID);
      Serial.println(status);
      Serial.println(on_time);
      Serial.println(off_time);
      Serial.println(pin);
    }

}
