#include <SoftwareSerial.h>

#include "DHT.h"
#define DHTPIN 2    
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

SoftwareSerial debug( 4, 5 ); // RX, TX
//*-- IoT Information
#define SSID "SSID"
#define PASS "PASSWORD"
#define IP "SERVER IP" 

void setup() {
    Serial.begin( 115200 ); //wifi的baudrate
    debug.begin( 115200 );
    //sendDebug("AT");
    //Loding("sent AT");
    connectWiFi();
}
void loop() {
    delay(5000);
    //SentOnCloud( String(6), String("fuck"));
    GetHumidTemp();
    //SentOnCloud( 100, 8);
}
boolean connectWiFi()
{
    //CWMODE=1:網卡模式
    debug.println("AT+CWMODE=1");
    //Wifi_connect();
    
    String cmd="AT+CWJAP=\"";
    cmd+=SSID;
    cmd+="\",\"";
    cmd+=PASS;
    cmd+="\"";
    //sendDebug("AT+CWMODE=1");
    sendDebug(cmd);
    Loding("Wifi_connect");
}
void GetHumidTemp()
{
  Serial.begin(9600);
  //Serial.println("DHT11 test!");
  dht.begin();

  float Humid = dht.readHumidity();
  float Temp = dht.readTemperature();
  //float f = dht.readTemperature(true); //華氏溫度
  //if (isnan(h) || isnan(t) || isnan(f)) { //開啟華氏溫度用這行
  if (isnan(Humid) || isnan(Temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
    }
   Serial.println(Humid);
   Serial.println(Temp);
   SentOnCloud(Humid,Temp);
}
void SentOnCloud( float H, float T )
{
    // 設定 ESP8266 作為 Client 端
    String cmd = "AT+CIPSTART=\"TCP\",\"";
    cmd += IP;
    cmd += "\",8080";
    sendDebug(cmd);
    if( debug.find("Error"))
    {
        Serial.print("RECEIVED: IP Error\n" );
        return;
    }
    cmd = "GET /insert.php?Temporature=" + String(T) + "&humiduty=" + String(H) + "\r\n";
    debug.print( "AT+CIPSEND=" );
    debug.println( cmd.length());
    if(debug.find( ">"))
    {
        Serial.print(">");
        Serial.print(cmd);
        debug.print(cmd);
    }
    else
    {
        debug.print( "AT+CIPCLOSE" );
    }
    if( debug.find("OK"))
    {
        Serial.println( "RECEIVED: OK" );
    }
    else
    {
        Serial.println( "RECEIVED: SendError\n" );
    }
}

void Loding(String state){
    for (int timeout=0 ; timeout<10 ; timeout++)
    {
      if(debug.find("OK"))
      {
          Serial.println("RECEIVED: WIFI OK");
          break;
      }
      else if(timeout==9){
        Serial.print( state );
        Serial.println("Wifi fail...\n");
      }
      else
      {
        Serial.print("Wifi Loading...");
        delay(500);
      }
    }
}
void sendDebug(String cmd)
{
    Serial.print("SEND: ");
    Serial.println(cmd);
    debug.println(cmd);
} 
