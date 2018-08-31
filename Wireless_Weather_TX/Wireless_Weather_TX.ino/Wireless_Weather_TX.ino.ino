/*
 * Arduino Wireless Weather Station
 * Transmitter Code
 *
 * 
 * by Niyas Thalappil
 * 
 * www.youtube.com/c/NiyasThalappil
 * Niyzmuahmmed@gmail.com
 *
 */


#include <VirtualWire.h>                            
#include "DHT.h"                                 


#define DHTPIN  4                                 
#define DHTTYPE DHT11                              


const int led_pin = 13;                            
const int transmit_pin = 12;                       


struct package                                      
{
  float temperature ;                            
  float humidity ;                                 
};


typedef struct package Package;                    
Package data;                                      

DHT dht(DHTPIN, DHTTYPE);                       


void setup()
{
    
    vw_set_tx_pin(transmit_pin);                    
    vw_set_ptt_inverted(true);                     
    vw_setup(500);                                 
    pinMode(led_pin, OUTPUT);                       
}

void loop()
{
  digitalWrite(led_pin, HIGH);                     
  readSensor();                                     
  vw_send((uint8_t *)&data, sizeof(data));         
  vw_wait_tx();                                    
  digitalWrite(led_pin, LOW);                      
  delay(2000);                                     

void readSensor()                                  
{
 dht.begin();                                      
 delay(1000);                                       
 data.humidity = dht.readHumidity();               
 data.temperature = dht.readTemperature();         
}

