#include <ESP8266WiFi.h>

// ten wifi va mat khau wifi
const char* ssid     = "Wifi Xin Xo";
const char* password = "d19cqcn02";
WiFiServer server(80);
String header;
String trang_thai_led1 = "tat";
String trang_thai_led2 = "tat";
String trang_thai_led3 = "tat";
String trang_thai_led4 = "tat";
// chan su dung
const int led1 = 5;
const int led2 = 4;
const int led3 = 0;
const int led4 = 2;

void setup() {
  Serial.begin(9600);
  // cai dat cong output
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);

  Serial.print("Dang ket noi voi mang wifi ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
  Serial.print("");
  Serial.print("Da ket noi wifi thanh cong");
  Serial.print("Dia chi IP cua thiet bi la : ");
  Serial.print(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // lang nghe xem co client nao dang ket noi den thiet bi khong

  if (client) {                             
    // Serial.print("New Client.");    
    String currentLine = "";                
    while (client.connected()) {            
      if (client.available()) {             
        char c = client.read();             
        // Serial.write(c);   
                     
        header += c;
        
        if (c == 'n') {                    
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Bat tat 4 led
            if (header.indexOf("GET /1/bat") >= 0) {
              Serial.print("Led 1 bat");
              trang_thai_led1 = "bat";
              digitalWrite(led1, HIGH);
            } else if (header.indexOf("GET /1/tat") >= 0) {
              Serial.print("Led 1 tat");
              trang_thai_led1 = "tat";
              digitalWrite(led1, LOW);
            }
              else if (header.indexOf("GET /2/bat") >= 0) {
              Serial.print("Led 2 bat");
              trang_thai_led2 = "bat";
              digitalWrite(led2, HIGH);
            } else if (header.indexOf("GET /2/tat") >= 0) {
              Serial.print("Led 2 tat");
              trang_thai_led2  = "tat";
              digitalWrite(led2, LOW);
            }
              else if (header.indexOf("GET /3/bat") >= 0) {
              Serial.print("Led 3 bat");
              trang_thai_led3 = "bat";
              digitalWrite(led3, HIGH);
            } else if (header.indexOf("GET /3/tat") >= 0) {
              Serial.print("Led 3 tat");
              trang_thai_led3  = "tat";
              digitalWrite(led3, LOW);
            }            
              else if (header.indexOf("GET /4/bat") >= 0) {
              Serial.print("Led 4 bat");
              trang_thai_led4 = "bat";
              digitalWrite(led4, HIGH);
            } else if (header.indexOf("GET /4/tat") >= 0) {
              Serial.print("Led 4 tat");
              trang_thai_led4  = "tat";
              digitalWrite(led4, LOW);
            }            
            // Hien thi trang web HTML
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<meta charset=\"utf-8\"/>");
           // client.println("<meta http-equiv="refresh" content="1″> "); // tu reload lai web html
            client.println("<link rel=\"icon\" href=\"data:,\">");
           // code CSS tao button
           client.println("<style>html { background-color: #000000; font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
           client.println(".button { display: inline-block;outline: none;cursor: pointer;text-align: center;text-decoration: none;");
           client.println("font: 30px/100% Arial, Helvetica, sans-serif;padding: 0.5em 2em .55em;text-shadow: 0 1px 1px rgba(0,0,0,.3);");
           client.println("-webkit-border-radius: 1em; -moz-border-radius: 1em;border-radius: 1em;-webkit-box-shadow: 0 1px 2px rgba(0,0,0,.2);");
           client.println("-moz-box-shadow: 0 1px 2px rgba(0,0,0,.2); box-shadow: 0 1px 2px rgba(0,0,0,.2);}");
           client.println(".button:hover {text-decoration: none;}");
           client.println(".button:active {position: relative;top: 1px;}");
           // button mau xanh
           client.println(".red {color: #faddde;border: solid 1px #980c10;background: #d81b21;background: -webkit-gradient(linear, left top, left bottom, from(#ed1c24), to(#aa1317));");
           client.println("background: -moz-linear-gradient(top,  #ed1c24,  #aa1317);filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#ed1c24′, endColorstr='#aa1317′);}");
           client.println(".red:hover {background: #b61318;background: -webkit-gradient(linear, left top, left bottom, from(#c9151b), to(#a11115));");
           client.println("background: -moz-linear-gradient(top,  #c9151b,  #a11115);filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#c9151b', endColorstr='#a11115′);}");
           client.println(".red:active {color: #de898c;background: -webkit-gradient(linear, left top, left bottom, from(#aa1317), to(#ed1c24));");
           client.println("background: -moz-linear-gradient(top,  #aa1317,  #ed1c24);filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#aa1317′, endColorstr='#ed1c24′);}");
           // button mau xanh
           client.println(".blue {color: #d9eef7;border: solid 1px #0076a3;background: #0095cd;background: -webkit-gradient(linear, left top, left bottom, from(#00adee), to(#0078a5));");
           client.println("background: -moz-linear-gradient(top,  #00adee,  #0078a5);filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#00adee', endColorstr='#0078a5′);}");
           client.println(".blue:hover {background: #007ead;background: -webkit-gradient(linear, left top, left bottom, from(#0095cc), to(#00678e));");
           client.println("background: -moz-linear-gradient(top,  #0095cc,  #00678e);filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#0095cc', endColorstr='#00678e');}");
           client.println(".blue:active {color: #80bed6;background: -webkit-gradient(linear, left top, left bottom, from(#0078a5), to(#00adee));");
           client.println("background: -moz-linear-gradient(top,  #0078a5,  #00adee);filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#0078a5′, endColorstr='#00adee');} ");

           client.println("</style></head>");
           client.println("<body><h1><font color=\"white\">Điều Khiển 4 LED Qua Websever Trên ESP8266</font></h1>");
           client.println("<body><h2><font color=\"white\">Blog thachdt.com</font></h2>");
           if (trang_thai_led1=="tat") {
              client.println("<p><a href=\"/1/bat\"><button class=\"button blue\">Bật Bóng Đèn 1</button></blue></p>");
            } 
           else {
              client.println("<p><a href=\"/1/tat\"><button class=\"button button red\">Tắt Bóng Đèn 1</button></red</p>");
            }               
           if (trang_thai_led2=="tat") {
              client.println("<p><a href=\"/2/bat\"><button class=\"button blue\">Bật Bóng Đèn 2</button></blue></p>");
            } 
           else {
              client.println("<p><a href=\"/2/tat\"><button class=\"button button red\">Tắt Bóng Đèn 2</button></red></p>");
            }
           if (trang_thai_led3=="tat") {
              client.println("<p><a href=\"/3/bat\"><button class=\"button blue\">Bật Bóng Đèn 3</button></blue></p>");
            } 
           else {
              client.println("<p><a href=\"/3/tat\"><button class=\"button button red\">Tắt Bóng Đèn 3</button></red></p>");
            }
           if (trang_thai_led4=="tat") {
              client.println("<p><a href=\"/4/bat\"><button class=\"button blue\">Bật Bóng Đèn 4</button></blue></p>");
            } 
           else {
              client.println("<p><a href=\"/4/tat\"><button class=\"button button red\">Tắt Bóng Đèn 4</button></red></p>");
            }
  
            client.println("</body></html>");    
            client.println();
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != 'r') {  
          currentLine += c;      
        }
      }
    } 
    header = "";
    client.stop();// ngat ket noi
    
      }

}
