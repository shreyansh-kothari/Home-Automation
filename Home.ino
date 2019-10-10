#include <SoftwareSerial.h>
#define RELAY1  6                        
#define RELAY2  7                        
#define RELAY3  8                        
#define RELAY4  9

String in;   //will store the msg received 
SoftwareSerial mySerial(0,1);  // for TX, RX (transmission and receving)

void setup()
{
  pinMode(RELAY1, OUTPUT);       //setting the states for relays
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  digitalWrite(RELAY1,HIGH);   // in arduino HIGH means low signal and vice-versa
  digitalWrite(RELAY2,HIGH);
  digitalWrite(RELAY3,HIGH);
  digitalWrite(RELAY4,HIGH);
  mySerial.begin(19200);    //baud rate for monitor screen. Change and check which works
  Serial.begin(19200);
  delay(100);
  Serial.println("AT+CMGD=1,4");
  delay(2000);
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
}
void sendsms(String g)      // function to send notification
{
   mySerial.println("AT+CMGF=1");    
  delay(1000);  
  mySerial.println("AT+CMGS=\"+919827584323\"\r");  //setting number to which the notification will be sent
  delay(1000);
  mySerial.println(g);
  delay(100);
   mySerial.println((char)26);
  delay(1000);
}
void OnRelay1()     //called when relay 2 is to be switched on
{
  digitalWrite(RELAY1,LOW);    //set LOW which sends high signal
    sendsms("Relay 1 on");    //can alter the notification to be sent when appliance at relay one is switched on
 in="";                       //resetting the msg string
}

//all the settings can altered in all functions

void OffRelay1()      //called when relay 1 is to be switched off
{
  digitalWrite(RELAY1,HIGH);
  sendsms("Relay 1 off");
}
void OnRelay2()    //called when relay 2 is to be switched on
{
  digitalWrite(RELAY2,LOW);   
  in="";
  sendsms("Relay 2 on");
}
void OffRelay2()          //called when relay 1 is to be switched off
{
  digitalWrite(RELAY2,HIGH);
  sendsms("Relay 2 off");
}
void OnRelay3()       //called when relay 3 is to be switched on
{
  digitalWrite(RELAY3,LOW);
  sendsms("Relay 3 on");
    in="";
}
void OffRelay3()                //called when relay 1 is to be switched off
{
  digitalWrite(RELAY3,HIGH);
  sendsms("Relay 3 off");
  in="";
}
void OnRelay4()          //called when relay 4 is to be switched on
{
  analogWrite(RELAY4,LOW);
    in="";
    sendsms("Fan Switched On");
}
void OffRelay4()               //called when relay 1 is to be switched off
{
  digitalWrite(RELAY4,HIGH);
  sendsms("Fan Switched Off");
  in="";
}
void AllRelayOff()             //called when all relays are to be switched off
{
  digitalWrite(RELAY1,HIGH);
  digitalWrite(RELAY2,HIGH);
  digitalWrite(RELAY3,HIGH);
  digitalWrite(RELAY4,HIGH);
  in="";
  sendsms("All Relays Off");
}

void error()   //called if the msg is not recognized
{
  in="";
  Serial.print("Error");
}

//main loop
void loop()
{

   if (mySerial.available()>0)   //checking for msg
   {
    in=mySerial.readString();    //reading the string
    Serial.print(in);
   //Serial.write(mySerial.read());
   delay(10);
   }
   in.toLowerCase();          //to remove the lower upper case issues by converting msg to lower case
  if(in.indexOf("off1")>=0)   //checking for the msg to trigger functions. Can be altered for all the functions depending on the usage
    {
      OffRelay1();
    }
    
 else if(in.indexOf("off2")>=0)
    {
      OffRelay2();
    }
    
  else if(in.indexOf("off3")>=0)
    {
      OffRelay3();
    }
    
else if(in.indexOf("fan off")>=0 || in.indexOf("off fan")>=0)
    {
      OffRelay4();
    }
else if(in.indexOf("on1")>=0)
    {
      OnRelay1();
    }
    
else if(in.indexOf("on2")>=0)
    {
      OnRelay2();
    }
    
else if(in.indexOf("on3")>=0)
    {
      OnRelay3();
    }
else if(in.indexOf("fan on")>=0 || in.indexOf("on fan")>=0)   //ex for using for fan
    {
      OnRelay4();
    }
else if(in.indexOf("all off")>=0)
{
AllRelayOff();
}
}
  
