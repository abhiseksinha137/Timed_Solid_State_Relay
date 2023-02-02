long current_time=0;
struct SSR {
  int id;
  int status;   // 1 for on; 0 for off
  long timeSince_stateChanged;
  long on_time;
  long off_time;
};
//long checkSwitch(SSR, long);
SSR switch1,switch2,switch3;

void setup() {
  // put your setup code here, to run once:
  switch1={1,0,0,5000,10000}; 
  switch2={2,0,0,5000,5000};  
  switch3={3,1,0,1000,2000};
Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  current_time = millis();
  checkSwitch(&switch1, current_time);
  checkSwitch(&switch2, current_time);
  checkSwitch(&switch3, current_time);
  // if (checkSwitch(switch1, current_time))
  // {

  // }
  
  //Serial.println(switch1.status);
  //Serial.println(current_time);
  
}

long checkSwitch(SSR *sw, long current_time)
{
  if (sw->status==1) // If the switch is already on
  {
    if((current_time-sw->timeSince_stateChanged)>=sw->on_time)
    {
        // Turn off SSR
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



