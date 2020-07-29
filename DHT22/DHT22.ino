     #include <dht.h>
    #define dataPin D2 // Defines pin number to which the sensor is connected
    dht DHT; // Creats a DHT object
    void setup() {
      Serial.begin(9600);
      pinMode(D1,OUTPUT);
      pinMode(D3,OUTPUT);
      digitalWrite(D1,HIGH);
      digitalWrite(D3,LOW);
    }
    void loop() {
      int readData = DHT.read22(dataPin); // Reads the data from the sensor
      float t = DHT.temperature; // Gets the values of the temperature
      float h = DHT.humidity; // Gets the values of the humidity
      
      // Printing the results on the serial monitor
      Serial.print("Temperature = ");
      Serial.print(t);
      Serial.print(" *C ");
      Serial.print("    Humidity = ");
      Serial.print(h);
      Serial.println(" % ");
      
      delay(2000); // Delays 2 secods, as the DHT22 sampling rate is 0.5Hz
}
