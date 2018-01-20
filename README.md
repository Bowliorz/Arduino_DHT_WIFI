# Arduino_DHT_WIFI
Arduino搭配wifi晶片加溫溼度感應器

溫溼度使用DHT11，如下圖
http://modtronix.com/images/detailed/1/mod-dht11.jpg
須將函式庫整個資料夾放至C:\Program Files (x86)\Arduino\libraries

wifi晶片使用ESP8266 (ESP-01S)

程式碼為自動將溫溼度讀取後透過wifi晶片連網並存至資料庫

線路接法
--------
DHT：    
    - → GND
