#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "esp_camera.h"
#include "HX711.h"

//WIFI
const char* ssid = "welcome";
const char* password = "";
String serverName = "smartesfutterhaus.onrender.com";
String serverPath = "/"; 
const int serverPort = 443; //server port for HTTPS
WiFiClientSecure client;


// CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22


//LOADCELL
const int LOADCELL_DOUT_PIN = 13;
const int LOADCELL_SCK_PIN = 12;
const int calibrationfaktor = 380;
long weight;
HX711 scale;


//SETUP
void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); 
  Serial.begin(115200); //BAUD RATE

  //WIFI setup
  WiFi.enableSTA(true);
  WiFi.mode(WIFI_STA);

  //CAM config
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  // init with high specs to pre-allocate larger buffers
  if(psramFound()){
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 10;  //0-63 lower number means higher quality
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_CIF;
    config.jpeg_quality = 12;  //0-63 lower number means higher quality
    config.fb_count = 1;
  }
  
  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    delay(1000);
    ESP.restart();
  }

  //loadcell init
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibrationfaktor);
  scale.tare(5);

  //lightsleep init
  pinMode(15, INPUT);
  gpio_wakeup_enable(GPIO_NUM_15, GPIO_INTR_HIGH_LEVEL);
  esp_sleep_enable_gpio_wakeup();
  WiFi.disconnect(true);
  Serial.println("Gleich schlafen");
  Serial.flush();
  delay( 100 );
  esp_light_sleep_start();
  delay(10);
}



void loop() {
    Serial.println("......... Woke Up ...................");
    wakeUpRoutine();
    delay(100);
}


void connectWiFi(){
  WiFi.enableSTA(true);
  WiFi.mode(WIFI_STA);
  delay(10);
  WiFi.begin(ssid, password);
  int counter = 0;

  while( WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi.. > status : " + String(WiFi.status()));
    counter++;
    if(counter >= 25){
      WiFi.begin(ssid, password);
      counter = 0;
    }
  }

  delay( 10 );
}


void wakeUpRoutine(){

  //get weight
  if (scale.is_ready()) { 
    weight = scale.get_units(20);
    Serial.print("Gewicht: ");
    Serial.println(weight);
  } else {
    Serial.println("HX711 not found.");
    weight = 0;
  }

  //take photo and send data
  if(weight > 3){
    //reconnect to wifi and send image to server
    connectWiFi();
    sendPhoto();
  }

  //back to sleep
  WiFi.disconnect(true);
  Serial.flush();
  delay(100);
  esp_light_sleep_start();
  delay(10);
}



void sendPhoto() {
  String getAll;
  String getBody;

  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get(); //get cam frame buffer
  if(!fb) {
    Serial.println("Camera capture failed");
    delay(1000);
    ESP.restart();
  }
  
  Serial.println("Connecting to server: " + serverName);
  
  client.setInsecure(); //skip certificate validation
  if (client.connect(serverName.c_str(), serverPort)) {

    Serial.println("Connection successful!");  

    //define request           
    String head1 = "--XXX\r\nContent-Disposition: form-data; name=\"password\"\r\n\r\nSWH2023\r\n--XXX\r\nContent-Disposition: form-data; name=\"weight\"\r\n\r\n";
    String head2 = head1 + weight;
    String head = head2 + "\r\n--XXX\r\nContent-Disposition: form-data; name=\"img\"; filename=\"esp32-cam.jpg\"\r\nContent-Type: image/jpeg\r\n\r\n";
    String tail = "\r\n--XXX--\r\n";
    
    uint32_t imgLen = fb->len;
    uint32_t requestLen = head.length() + tail.length();
    uint32_t totalLen = imgLen + requestLen;
  
    //send request
    client.println("POST " + serverPath + " HTTP/1.1");
    client.println("Host: " + serverName);
    client.println("Content-Length: " + String(totalLen));
    client.println("Content-Type: multipart/form-data; boundary=XXX\r\n\r\n");
    client.print(head);
  
    //send img
    uint8_t *fbBuf = fb->buf;
    size_t fbLen = fb->len;
    for (size_t n=0; n<fbLen; n=n+1024) {
      if (n+1024 < fbLen) {
        client.write(fbBuf, 1024);
        fbBuf += 1024;
      }
      else if (fbLen%1024>0) {
        size_t remainder = fbLen%1024;
        client.write(fbBuf, remainder);
      }
    }   
    client.print(tail);
    
    esp_camera_fb_return(fb);
    
    int timoutTimer = 180000;
    long startTimer = millis();
    boolean state = false;
    
    //read answer
    while ((startTimer + timoutTimer) > millis()) {
      Serial.print(".");
      delay(500);      
      while (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (getAll.length()==0) { state=true; }
          getAll = "";
        }
        else if (c != '\r') { getAll += String(c); }
        if (state==true) { getBody += String(c); }
        startTimer = millis();
      }
      if (getBody.length()>0) { break; }
    }
    Serial.println();
    client.stop();
    Serial.println(getBody);
  }
  else {
    Serial.println("Connection to " + serverName +  " failed.");
  }
}



