// Developed By M V Subrahmanyam
// Electrinics Innovation

#include <DHT.h>  // library for getting data from DHT
#include <ESP8266WiFi.h>  //Librarry connecting ESP8266 to connect with Wifi

// ***********************************************Thingspeak Credentials***************** 
String apiKey = "B8WGQKBEP2CAHC44";     //Write API key of your ThingSpeak channel
const char* server = "api.thingspeak.com";  // API for thingspeak
//****************************************************************************************

const char *ssid =  "praveen reddy";     // Wifi SSID of your Internet connection
const char *pass =  "1234554321"; // Password

#define DHTPIN D7          //pin where the DHT22 is connected 
DHT dht(DHTPIN, DHT22);    
WiFiClient client; 
void setup() 
{
       Serial.begin(9600);  // Serial monitor Baudrate
       delay(10);
       //******************PowerSupply to the Sensor**********************
       pinMode(D6, OUTPUT);
       pinMode(D8, OUTPUT);
       digitalWrite(D6,HIGH);
       digitalWrite(D8,LOW);
       delay(1000);
       //*********************************************************
       dht.begin(); 
       
       Serial.println("Trying to Connect with "); 
       Serial.println(ssid);  
       WiFi.begin(ssid, pass);   // Connecting ESP8266 with Internet enabled Wifi with above mentioned credentials
      while (WiFi.status() != WL_CONNECTED) 
     { 
           // If the connection was unsuccesfull, it will try again and again
            delay(500);
            Serial.print(".");
     }
     // Connection succesfull
      Serial.println("");
      Serial.println("WiFi connected"); 
} 
void loop() 
{ 
  
      float h = dht.readHumidity();   // Reading Temperature form DHT sensor
      float t = dht.readTemperature();      // Reading Humidity form DHT sensor 
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
                 // Connecting to the Thingspeak API and Posting DATA
              if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                  {  
                             // Format of DATA Packet "Write API Key&field1=Temperature data&field2=Humidity Data"
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
                             client.flush();
                             Serial.println(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("%.");
                             Serial.println("Data has been sussecfully sent to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting to initiate next data packet...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(6000);
}
