
/***************************************************
  Adafruit CC3000 Breakout/Shield TCP Echo Server
    
  This is a simple implementation of the echo 
  protocol, RFC 862 http://tools.ietf.org/html/rfc862 , 
  for the Arduino platform and Adafruit CC3000 breakout
  or shield.  This sketch will create a TCP server that 
  listens by default on port 7 and echos back any data
  received.  Up to 3 clients can be connected concurrently
  to the server.  This sketch is meant as an example of how 
  to write a simple server with the Arduino and CC3000.

  See the CC3000 tutorial on Adafruit's learning system
  for more information on setting up and using the
  CC3000:
    http://learn.adafruit.com/adafruit-cc3000-wifi  
    
  Requirements:
  
  This sketch requires the Adafruit CC3000 library.  You can
  download the library from:
    https://github.com/adafruit/Adafruit_CC3000_Library
  
  For information on installing libraries in the Arduino IDE
  see this page:
    http://arduino.cc/en/Guide/Libraries
  
  Usage:
    
  Update the SSID and, if necessary, the CC3000 hardware pin 
  information below, then run the sketch and check the 
  output of the serial port.  After connecting to the 
  wireless network successfully the sketch will output 
  the IP address of the server and start listening for 
  connections.  Once listening for connections, connect
  to the server from your computer  using a telnet client
  on port 7.  
           
  For example on Linux or Mac OSX, if your CC3000 has an
  IP address 192.168.1.100 you would execute in a command
  window:
  
    telnet 192.168.1.100 7
           
  After connecting, notice that as you type input and 
  press enter to send it the CC3000 will echo back exactly
  what you typed.  Press ctrl-] and type quit at the prompt 
  to close the telnet session.
           
  On Windows you'll need to download a telnet client.  PuTTY 
  is a good, free GUI client: 
    http://www.chiark.greenend.org.uk/~sgtatham/putty/
  
  License:
 
  This example is copyright (c) 2013 Tony DiCola (tony@tonydicola.com)
  and is released under an open source MIT license.  See details at:
    http://opensource.org/licenses/MIT
  
  This code was adapted from Adafruit CC3000 library example 
  code which has the following license:
  
  Designed specifically to work with the Adafruit WiFi products:
  ----> https://www.adafruit.com/products/1469

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution      
 ****************************************************/
#include <Adafruit_CC3000.h>
#include <SPI.h>
#include "utility/debug.h"
#include "utility/socket.h"
#include <EEPROM.h>

// These are the interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   3  // MUST be an interrupt pin!
// These can be any two pins
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIVIDER); // you can change this clock speed

#define WLAN_SSID       "Connectify-sd"           // cannot be longer than 32 characters!
#define WLAN_PASS       "madushan"
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2

#define LISTEN_PORT           7    // What TCP port to listen on for connections.  The echo protocol uses port 7.
# define k 22

Adafruit_CC3000_Server echoServer(LISTEN_PORT);




void p13() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(8);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(8);              // wait for a second
}

 void forward(){
  digitalWrite(k, HIGH);
  digitalWrite(k+1, HIGH);
  digitalWrite(k+2, HIGH);
  digitalWrite(k+3, HIGH);

  digitalWrite(k+4,LOW);
  digitalWrite(k+5,LOW);
  digitalWrite(k+6,LOW);
  digitalWrite(k+7,LOW);
  delay(50);
}

 void backward(){
  digitalWrite(k,LOW );
  digitalWrite(k+1, LOW);
  digitalWrite(k+2, LOW);
  digitalWrite(k+3, LOW);

  digitalWrite(k+4,HIGH);
  digitalWrite(k+5,HIGH);
  digitalWrite(k+6,HIGH);
  digitalWrite(k+7,HIGH);
  delay(50);
  
}

void left(){
 
  digitalWrite(k+1, HIGH);
  digitalWrite(k+5,LOW);
  digitalWrite(k+2, LOW);
  digitalWrite(k+6,HIGH);
  delay(50);
  
  }
  
void right(){
 
  digitalWrite(k+1, LOW);
  digitalWrite(k+5,HIGH);
  digitalWrite(k+2, HIGH);
  digitalWrite(k+6,LOW);
  delay(50);
  
  }

  void sleep(){
    
  digitalWrite(k,LOW );
  digitalWrite(k+1, LOW);
  digitalWrite(k+2, LOW);
  digitalWrite(k+3, LOW);

  digitalWrite(k+4,LOW);
  digitalWrite(k+5,LOW);
  digitalWrite(k+6,LOW);
  digitalWrite(k+7,LOW);
  
    
  }


  void up(){
  int val = EEPROM.read(50);

  if(val != 1){
  digitalWrite(38, HIGH);
  digitalWrite(37, LOW);// turn the LED on (HIGH is the voltage level)
  EEPROM.write(50, 1);
  delay(3250);              // wait for a second
   digitalWrite(38, LOW);
  }

  }

  void down(){ 
  int val = EEPROM.read(50);
  if(val == 1){
  digitalWrite(38, LOW); 
  digitalWrite(37, HIGH);// turn the LED off by making the voltage LOW
  EEPROM.write(50, 0);
  delay(3250); 
  digitalWrite(37,LOW);// wait for a second
  }
 }


void setup(void)
{

  pinMode(38, OUTPUT);
  pinMode(37, OUTPUT);

  
   pinMode(k, OUTPUT);
   pinMode(k+1, OUTPUT);
   pinMode(k+2, OUTPUT);
   pinMode(k+3, OUTPUT);
   pinMode(k+4, OUTPUT);
   pinMode(k+5, OUTPUT);
   pinMode(k+6, OUTPUT);
   pinMode(k+7, OUTPUT);
   
  Serial.begin(9600);
   pinMode(13, OUTPUT);
  Serial.println(F("Hello, CC3000!\n")); 

  Serial.print("Free RAM: "); Serial.println(getFreeRam(), DEC);
  
  /* Initialise the module */
  Serial.println(F("\nInitializing..."));
  if (!cc3000.begin())
  {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    while(1);
  }
  
  Serial.print(F("\nAttempting to connect to ")); Serial.println(WLAN_SSID);
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1);
  }
   
  Serial.println(F("Connected!"));
  
  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }  

  /* Display the IP address DNS, Gateway, etc. */  
  while (! displayConnectionDetails()) {
    delay(1000);
  }

  /*********************************************************/
  /* You can safely remove this to save some flash memory! */
  /*********************************************************/
  Serial.println(F("\r\nNOTE: This sketch may cause problems with other sketches"));
  Serial.println(F("since the .disconnect() function is never called, so the"));
  Serial.println(F("AP may refuse connection requests from the CC3000 until a"));
  Serial.println(F("timeout period passes.  This is normal behaviour since"));
  Serial.println(F("there isn't an obvious moment to disconnect with a server.\r\n"));
  
  // Start listening for connections
  echoServer.begin();
  
  Serial.println(F("Listening for connections..."));
}

void loop(void)
{
  // Try to get a client which is connected.
  Adafruit_CC3000_ClientRef client = echoServer.available();
  if (client) {
     // Check if there is data available to read.
     if (client.available() > 0) {
       // Read a byte and write it to all clients.
       char ch = client.read();
        switch ( ch ) {
case 'u':
  forward();
 // sleep();
  break;
case 'd':
  backward();
 // sleep();
  break;
case 'l':
  left();
 // sleep();
  break;
case 'r':
  right();
 // sleep();
  break;
case 'p':
  up();
 // sleep();
  break;
case 'o':
  down();
 // sleep();
  break;
 default:
 sleep();
 break;
}
sleep();
      // client.write(ch);
     }
  }
}

/**************************************************************************/
/*!
    @brief  Tries to read the IP address and other connection details
*/
/**************************************************************************/
bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
  
  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    Serial.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    Serial.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    Serial.print(F("\nNetmask: ")); cc3000.printIPdotsRev(netmask);
    Serial.print(F("\nGateway: ")); cc3000.printIPdotsRev(gateway);
    Serial.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
    Serial.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
    Serial.println();
    return true;
  }
}
