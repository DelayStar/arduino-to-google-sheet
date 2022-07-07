#include <WiFiClientSecure.h>

String t;
String EC;
String PH;
String P1;
String P2;
String P3;

#define ON_Board_LED 2

const char* ssid = "Tree";
const char* password = "12345678";

const char* host = "script.google.com";
const int httpsPort = 443;

WiFiClientSecure client;

long now = millis();
long lastMeasure = 0;

String GAS_ID = "AKfycbx48zuYUFgfDNFLHOJSFIKYkR3wWsaGNxNtnb_rH6Jzf87LQM3s";

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.println("");
  
  pinMode(ON_Board_LED,OUTPUT);
  digitalWrite(ON_Board_LED, HIGH);
  
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
  }
  digitalWrite(ON_Board_LED, HIGH); 
  Serial.println("");
  
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  
  client.setInsecure();
}

void loop() {
 // now = millis();
   // if (now - lastMeasure >3000) {
   // lastMeasure = now;
    
   float t = random(45);
   float EC = random(9999);
   float PH = random(14);
   byte P1 = random(2);
   byte P2 = random(2);
   byte P3 = random(2);
   
  sendData(t,EC,PH,P1,P2,P3);
  delay(60000);
  //  }
}
void sendData(float value,float value2,float value3,float value4,float value5,float value6) {
  Serial.println("==========");
  Serial.print("connecting to ");
  Serial.println(host);
  
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  
  float string_temp = value; 
  float string_EC = value2;
  float string_PH = value3; 
  float string_P1 = value4;
  float string_P2 = value5;
  float string_P3 = value6;
  String url = "/macros/s/" + GAS_ID + "/exec?temp=" + string_temp + "&EC=" + string_EC + "&PH=" + string_PH+ "&P1=" + string_P1 + "&P2=" + string_P2 + "&P3=" + string_P3;
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");

  Serial.println("request sent");
 
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
     break;
    }
  }
  String line = client.readStringUntil('\n');
//   if (line.startsWith("{\"state\":\"success\"")) {
//    Serial.println("esp8266/Arduino CI successfull!");
//  } else {
//    Serial.println("esp8266/Arduino CI has failed");
//  }
  Serial.print("reply was : ");
  Serial.println(line);
  Serial.println("closing connection");
  Serial.println("==========");
  Serial.println();

} 
