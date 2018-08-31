/*
 * Arduino Wireless Weather Station
 * Receiver Code
 *
 * 
 * by Niyas Thalappil
 * 
 * www.youtube.com/c/NiyasThalappil
 * Niyzmuahmmed@gmail.com
 *
 */


#include <VirtualWire.h>

const int led=13;
const int receive_pin = 12;
char temperatureChar[10];
char humidityChar[10];



typedef struct package Package;                     
Package data;                                      

void setup()
{
    
Serial.begin(9600);                                 
    
    pinMode(led,OUTPUT);                           
    vw_set_rx_pin(receive_pin);                     
    vw_setup(500);                                  
    vw_rx_start();                                 
}

void loop()
{
    uint8_t buf[sizeof(data)];                      
    uint8_t buflen = sizeof(data);                 

if (vw_have_message())                              
  {
    digitalWrite(led,HIGH);                         
    vw_get_message(buf, &buflen);                 
    memcpy(&data,&buf,buflen);                      

    Serial.print("Temp     ");                      
    Serial.print((data.temperature*1.8)+32);       
    Serial.println("F");                           
    
    
    Serial.print("Humidity ");                      
    Serial.print(data.humidity);                    
    Serial.println("%");                            
    delay(100);                                     
    digitalWrite(led,LOW);                        
  }
}


