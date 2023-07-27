---
title: "09 - Nachbauanleitung: Bird Booth"
date: 2023-07-11T12:28:26+02:00
show_reading_time: true
featured_image: "/media/haus_drawing.png"
draft: false
---

## Einleitung

Das Projekt Bird Booth entstand aus der Idee, auch viel beschäftigten Vogelliebhabern die Möglichkeit zu bieten, ihre Besucher zu sehen, und nicht nur das langsam verschwindende Futter über die Zeit zu beobachten. Das smarte Futterhäuschen liefert Bilder und Gewicht von alle Vögeln, die sich an dem Futter bedienen. Das Gewicht liefert einen zusätzlichen Wiedererkennungswert und lässt Beobachter zum Beispiel auch Rückschlüsse auf Gesundheit und Zustand der tierischen Besucher ziehen.
Bird Booth soll ein langlebiges und umweltfreundliches Vogelhäuschen sein.

{{< rawhtml >}} 
    <br>
{{< /rawhtml >}}
### Materialien und Zubehör

##### Technik
-  ESP32 CAM 2,4 GHz WiFi mit OV2640 Kamera Modul
-  Elektronischer Gewicht Sensor (3kg)
-  HX711 LoadCell Amplifier
-  Vibrationssensor SW420
-  Batterie-Case mit 3x AAA-Batterien(1,5V)

##### Zusätzliches Material
- 2 Lochraster-Platinen
- Kleines Scharnier einschließlich Schrauben
- Holzlasur auf Wasserbasis
- Holz nach Wahl (5 Platten mit 1cm Dicke für Wände und Boden, 4 Platten mit 3mm für das Dach, Zwischenboden und Futterplatte)
- Dachpappe
- 2 kleine Plexiglasplatten
- 2 kleine Magnete
- 2x Schrauben (Maße: Durchmesser  5mm, Kopfdurchmesser max. 9mm, Länge ca 25mm), einschließlich 2 passenden Muttern
- Eine Schraube (Maße: Durchmesser 5mm, Kopfdurchmesser max. 9mm, Länge 15-25mm), einschließlich passender Mutter (Für Sensor-Case unten)
- Eine Schrauben (Maße: Durchmesser 4mm, Kopfhöhe max. 4.5mm, Länge 15-25mm), einschließlich passender Muttern (Für Sensor-Case Innen)
- 8 kleine Nägel
- Holzstab Durchmesser 10mm, Länge 105mm

##### Zubehör
- FTDI232 Adapter (USB auf Serielles TTL) und USB Kabel
- 3D-Drucker mit PLA Filament
- Bandsäge und Stichsäge
- Akku-/Bohrschrauber
- Holzleim, 2-Komponenten-Kleber, Heißkleber
- Kabel, Lötzubehör, Schrumpfschläuche

##### Zum Testen
- Steckplatine
- Jumperkabel

##### Optional
- weiße Acrylfarbe
- kleine, platte Holzstäbchen für die Fensterrahmen
- Makramee-Fäden

{{< rawhtml >}} 
    <br>
{{< /rawhtml >}}
### Dateien-Bibliothek
#### Code
- [Server Code ](https://github.com/AnnaMarburger/smartesfutterhaus)
- [ESP Code ](https://github.com/AnnaMarburger/swh/blob/main/birdbooth_files/esp_code.ino)

#### 3D-Druck-Modelle (.stl)
- [Sensor-Case Deckel ](https://github.com/AnnaMarburger/swh/blob/main/birdbooth_files/sensorcase_deckel.stl)
- [Sensor-Case Zwischenblatt](https://github.com/AnnaMarburger/swh/blob/main/birdbooth_files/sensorcase_zwischenblatt.stl)
- [Sensor-Case Unterteil](https://github.com/AnnaMarburger/swh/blob/main/birdbooth_files/sensorcase_unten.stl)
- [Futterschale Unterteil](https://github.com/AnnaMarburger/swh/blob/main/birdbooth_files/futterschale_unten.stl)
- [Kamera-Case](https://github.com/AnnaMarburger/swh/blob/main/birdbooth_files/cam-case.stl)


{{< rawhtml >}} 
    <br>
{{< /rawhtml >}}
## Schritt-für-Schritt Anleitung

### 1. Website programmieren, Server aufsetzen und hosten

{{< figure src="../media/projekt/server_desktop.png" >}}


#### 1.1 Projekt aufsetzen, Umgebungen installieren

Um später die Bilder der Futterhaus-Kamera zusammen mit den Gewichtsdaten von überall einsehen zu können, setzen wir einen Server auf. Dieser soll zum einen POST-Requests mit den Daten, die wir später von dem Kamera Modul senden, annehmen und in einer Datenbank speichern können. Zum anderen soll er Webclients, die unsere Website aufrufen, eine HTML mit den aufgearbeiteten Daten (Bildern) zurückgeben.

Um den Server zu realisieren verwende ich die Laufzeitumgebung [Node Js](https://nodejs.org/de). Ist diese noch nicht installiert, sollte dies zuerst geschehen. 

Nun legen wir ein Verzeichnis an, in welchem wir unsere Anwendung aufbauen. Mit `npm init` wird eine neue package.json Datei erstellt. In dieser können wir unter anderem den Namen unserer Anwendung festlegen, sowie unter “main” den Namen unsere Hauptdatei, die für das Starten des Servers verantwortlich ist. Bevor wir genau diese Datei anlegen, in meinem Fall “app.js”, fügen wir der package.json Datei ein weiteres Attribut hinzu: `“type”:module`. 

Um das Coden einfacher zu  gestalten, verwende ich das Framework  [Express Js](https://expressjs.com)  . Dieses lässt sich mit dem Package Manager npm durch `npm install express` installieren. Dabei ist wichtig, dass wir uns im Verzeichnis unserer Anwendung befinden. Mit `node app.js` kann der Server lokal getestet werden. Hierzu ist zudem das Programm [Postman](https://www.postman.com) hilfreich, das über eine einfache Benutzeroberfläche Server Requests verschicken lässt 

  {{< figure src="../media/projekt/postman_request.png" caption="Screenshot POST-request in Postman">}}

(Achtung: Für Anfragen an lokale Server wird hierbei die Desktop App benötigt).



#### 1.2 Datenspeicherung mit Firebase

Für die Datenspeicherung verwende ich Firebase. Um das Projekt dort anzulegen, wird ein Konto benötigt. Anschließend kann über “Projekt hinzufügen”, ein neues Projekt erstellt werden. Ist dies getan, öffnet sich die Konsole für das Projekt. Dort sollte die App dem Projekt hinzugefügt werden. Da wir eine Webanwendung bauen, wählen wir dort “Web” aus und geben den Namen unseres Servers ein. Über Firebase kann der Server später auch gehostet werden, dann sollte der Haken bei dieser Option gesetzt werden. Ich habe dafür jedoch einen anderen (kostenlosen) Anbieter gewählt: [Render](https://render.com/). Anschließend muss firebase in unserem Projekt installiert werden: `npm install firebase`. Firebase zeigt nun einen Codeblock an:

```jsx
// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";

// Your web app's Firebase configuration
const firebaseConfig = {
  apiKey: "...",
  ...
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
```

Wichtig hier ist die Firebase Configuration für unsere Anwendung, da diese für jedes angelegte Firebase Projekt individuell ist. Dieser Teil muss also kopiert und in unserer Hauptdatei *app.js* entsprechend ersetzt werden. Nun müssen wir in der Firebase Konsole nur noch unseren Speicher einrichten. Unter “Entwickeln” im Seitenmenü wählen wir “Storage” aus und drücken auf der Seite auf “Jetzt Starten”.  Die Sicherheitsregeln setzen wir (zum Entwickeln) auf öffentlich. In diesem Speicherbucket können wir nun einen Ordner “images” erstellen. Hier lädt unser Server alle einkommenden Bilder hoch. 

  {{< figure src="../media/projekt/screen_firebase.png" caption="Screenshot des Firebase-Storage">}}

Außerdem muss die Datei *data.json* in diesem Storage von Hand erstmals hochgeladen werden, da der Server versucht, diese herunterzuladen, sobald er eine “GET” Request von einem Clienten erhält. Beim allerersten Serverstart würde dieser dementsprechend einen Fehler werfen, wenn er dort keine *data.json* Datei findet.

#### 1.3 Hosting

Für das Hosten des Servers auf Render wird lediglich ein GitHub Repository mit dem Servercode benötigt. Der Anbieter deployed mit jedem Commit den Server erneut. Außerdem gibt es eine Konsole, in der Ausgaben des Servers eingesehen werden können (Hilfreich zum Debuggen). Render selbst führt gut verständlich durch den Hosting Prozess.


#### 1.4 **Aufbau des Servers:**

Der gesamte Code für den Server ist auf folgendem Repo zu finden: 

https://github.com/AnnaMarburger/smartesfutterhaus

1. Die *app.js* Datei, auch die Hauptdatei, die für das eigentliche Erstellen des Servers verantwortlich ist. In dieser Datei werden “POST”, “GET” und “DELETE” Anfragen gehändelt. Einkommende POST Anfragen werden auf Richtigkeit geprüft und anschließend bearbeitet. Bilder werden direkt mit einem eindeutigen Namen (durch Datum+Uhrzeit) im Firebase Storage gesichert. 

2. Die *index.html* Datei ist die Datei, welche an Clienten bei GET Requests geschickt wird. In ihr werden die Buttons zum Filtern und Sortieren definiert. Außerdem sind in ihr die Dateien *gallery.js* und *style.css* verlinkt.

Im *Public Ordner*, welchen wir als solchen in *app.js* deklarieren (dies ist wichtig, um Clienten den Zugriff auf benötigte Dateien wie z.B. stylesheets möglich zu machen, die wir nicht per se mitschicken):

3. *gallery.js* ist die JavaScript Datei, die sich um das dynamische Anzeigen der Daten auf der Website kümmert. Sie liest aus der “data.json” jeweils Bildname, zugehöriges Gewicht und Datum aus und zeigt diese Daten für jeden Eintrag als Galerie-Item auf der Website an. Des Weiteren händelt sie die Filter- und Sortierungs-Optionen, die durch die Buttons auf der Seite getriggert werden. 

4. In der Datei *style.css* wird das Aussehen der Website entsprechend festgelegt.

5. Die bereits erwähnte *data.json* Datei verwaltet die Metadaten zu jedem Bild, das den Server erreicht. Dazu gehören Name der Bilddatei, sodass sie in den Files gefunden werden kann, das gemessene Gewicht des zugehörigen Vogels sowie einen Datumsstempel, der beim Empfangen des Bildes hinzugefügt wurde.

Der *Uploads Ordner* enthält die Bilddateien zum Anzeigen nach Herunterladen aus dem Firebase Speicher.

{{< rawhtml >}} 
    <br>
{{< /rawhtml >}}
### 2. Kameramodul

#### 2.1 Schaltplan

Unsere Kamera-Komponente besteht aus zwei Teilen: Zum einen die ESP32-Cam, die mit einem ESP32 Microchip arbeitet, zum anderen das OV2640 Kameramodul, sprich die Kamera selbst. Werden beide Teile getrennt geliefert, so muss der längliche Klipser auf der ESP32-Cam vorsichtig aufgemacht und das Kameramodul so reingeschoben werden, dass die Kamera nach vorne zeigt und sicher hält.

Da die ESP32-Cam keinen USB-Anschluss mitbringt, benötigen wir, um sie zu programmieren, einen USB-to-TTL Adapter, wie zum Beispiel den FTDI. Diesen können wir mithilfe eines Breadbords anschließen:

  {{< figure src="../media/projekt/steckplatine.jpeg" width="60%"  caption="ESP+FTDI auf Steckplatine">}}

Dabei sollten wir darauf achten, dass auf dem Adapter die Bridge zu 5V gesetzt ist. Zwar läuft der Esp laut Dokumentation auch mit 3.3V, jedoch wurden hierbei zahlreiche Probleme in Online Foren reported. Zusätzlich müssen wir die ESP32-Cam, um Code hochladen zu können, in den “Flashing Mode” setzen. Dies machen wir, indem wir die Pins GPIO0 und GND verbinden. Der Schaltplan sieht demnach folgendermaßen aus:

  {{< figure src="../media/projekt/schaltplan_esp.jpeg" caption="Schaltplan ESP+FTDI">}}

#### 2.2 Programmieren

 Um den ESP-32 Microchip programmieren zu können, müssen wir das Board in der Arduino IDE installieren. Dazu fügen wir in den Einstellungen folgenden Link dem Feld “Additional boards manager URLs” hinzu und speichern:

https://dl.espressif.com/dl/package_esp32_index.json 

Im Boards Manager können wir nun nach “esp32” suchen und installieren. Anschließend sollten wir unter Tools>Board>esp32 die “AI Thinker Esp32 Cam” auswählen können. Unter Port wählen wir den entsprechenden USB Port aus, an welchem wir den Adapter eingesteckt haben.

  {{< figure src="../media/projekt/select_AIThinkerCam.png" caption="Screenshot Board-Auswahl">}}


Unter File > Examples gibt es verschiedene Beispielprogramme, um den ESP zu testen, so auch zum Beispiel auch ein Programm, dass auf einem lokalen Server einen Livestream der Kamera startet und die verschiedensten Einstellungen treffen lässt. Der Code findet sich unter File > Examples > ESP32 > Camera > CameraWebServer. 

Während dem Upload des Codes, wenn auf der Konsole “Connecting…” erscheint, muss das Board einmal resettet werden. Auf der Rückseite gibt es dazu einen kleinen Reset-Knopf. Da man daran aber schlecht herankommt, wenn man ein Breadboard verwendet, kann man alternativ das Kabel zu 5V am Board kurz aus- und wieder einstecken.

Nun sollten wir dazu bereit sein, unseren eigentlichen Code für die ESP32-Cam zu schreiben. Wir erstellen eine neue Arduino Datei. Zunächst brauchen wir folgende Libraries:

```cpp
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "esp_camera.h"
```

Anschließend legen wir folgende Variablen für die WiFi Connection fest:
```cpp
//WIFI
const char* ssid = "INSERT_YOUR_SSID";
const char* password = "INSERT_PASSWORD_FOR_SSID";
String serverName = "INSERT_SERVER_URL"; //for me: smartesfutterhaus.onrender.com
String serverPath = "/"; 
const int serverPort = 443; //server port for HTTPS
WiFiClientSecure client;
```

Hierbei müssen SSID und Passwort natürlich mit den eigenen Werten gefüllt werden, sprich mit Name und Passwort der WLAN-Verbindung. Auch die Server-URL muss individuell eingetragen werden. 

Um die AI-Thinker Camera vom ESP32 zu verwenden, müssen wir folgende Pins definieren:
```cpp
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
```

Nun konfigurieren wir in der setup Methode zum einen die WiFi-Verbindung (wir verwenden den STA Modus), zum anderen die Kamera (diese ist durch das Modell erneut vorgegeben).
Zuletzt versuchen wir, die Cam zu initialisieren. Tritt hierbei ein Fehler auf, soll eine Fehlermeldung ausgegeben werden und nach einem kurzen Delay ein Neustart des ESP hervorgerufen werden. 
```cpp
//SETUP
void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //BROWN OUT DETECTOR
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
  
  // CAM init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    delay(1000);
    ESP.restart();
  }
}
```

In einer zusätzlichen Methode schreiben wir folgenden Code, um uns mit dem WiFi zu verbinden:
```cpp
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
}
```
Diesen werden wir später jedes Mal aufrufen, wenn wir den ESP aus seinem sleep modus aufwecken. 

Außerdem schreiben wir eine Methode, die für das tatsächliche Versenden des Fotos verantwortlich ist. Dabei holen wir uns zuerst einen Pointer zum Kamera Frame-Buffer (und starten den ESP neu, falls dies fehlschlagen sollte). Anschließend bauen wir eine Verbindung zu unserem Server auf. Schließlich schreiben wir die Request, senden sie ab und warten auf die Antwort des Servers (dies ist hauptsächlich für Debugging-Zwecke nötig und kann letztendlich weggelassen werden, da wir die Antwort nicht weiter verarbeiten. Alternativ kann bei einer Fehlerausgabe ein erneutes Versenden ausgelöst werden; Darauf habe ich, um die Code Komplexität zu verringern, verzichtet).

```cpp
void sendPhoto() {
  String getAll;
  String getBody;
	
  //get Camera Capture
  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();
  if(!fb) {
    Serial.println("Camera capture failed");
    delay(1000);
    ESP.restart();
  }
  
  Serial.println("Connecting to server: " + serverName);
  
  client.setInsecure(); //skip certificate validation
  if (client.connect(serverName.c_str(), serverPort)) {

    Serial.println("Connection successful!");  

    //send request           
    String head1 = "--XXX\r\nContent-Disposition: form-data; name=\"password\"\r\n\r\nSWH2023\r\n--XXX\r\nContent-Disposition: form-data; name=\"weight\"\r\n\r\n";
    String head2 = head1 + weight;
    String head = head2 + "\r\n--XXX\r\nContent-Disposition: form-data; name=\"img\"; filename=\"esp32-cam.jpg\"\r\nContent-Type: image/jpeg\r\n\r\n";
    String tail = "\r\n--XXX--\r\n";
    
    uint32_t imageLen = fb->len;
    uint32_t extraLen = head.length() + tail.length();
    uint32_t totalLen = imageLen + extraLen;
  
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
```

Achtung: Um den Code zu testen, muss "weight" durch eine beliebige Zahl ersetzt werden. Diese Variable haben wir bisher noch nicht definiert. Dies werden wir in Abschnitt 4 tun, wenn es um den Gewichtssensor geht.
Um beim Testen das Output des Programms sehen zu können, öffnen wir unter Tools > Serial Monitor den Serial Monitor und beachten dabei, dass er auf die richtige BAUD Rate (hier 115200) eingestellt ist.

**Troubleshooting**: Beim Hochladen von Code auf den ESP kommt es gerne mal zu Problemen, oftmals liegt es an manelhafter Stromversorgung. Hier hilft Google weiter. Eine für mich hilfreiche Seite war: [espressif docs](https://docs.espressif.com/projects/arduino-esp32/en/latest/troubleshooting.html).

{{< rawhtml >}} 
    <br>
{{< /rawhtml >}}
### 3. Weckfunktion mit Vibrationssensor

Damit der ESP in den light sleep geschickt werden kann, während keine Vögel zu Besuch sind, wird ein Vibrationssensor benötigt, um den ESP auch wieder aufwecken zu können. Dazu ergänzen wir unseren Code folgendermaßen:

- Wir ergänzen in der setup Methode am Ende: 
    ```cpp
    //lightsleep init
    pinMode(15, INPUT);
    gpio_wakeup_enable(GPIO_NUM_15, GPIO_INTR_HIGH_LEVEL);
    esp_sleep_enable_gpio_wakeup();
    WiFi.disconnect(true);
    Serial.println("Gleich schlafen"); //debug output
    Serial.flush(); 
    delay(100);
    esp_light_sleep_start();
    delay(10);
    ```
    Hierbei ist Pin 15 der Pin, an den wir den Vibrationssensor anschließen. Wir legen diesen als WakeUp-Pin fest und trennen anschließend die WiFi-Verbindung. Dies ist nötig, um sie nach Erwachen aus dem sleep modus fehlerfrei wiederherstellen zu können. Anschließend starten wir direkt in den light sleep. Wenn der ESP durch ein Signal des Vibrationssensor geweckt wird, läuft der Code einfach weiter.

- Wir schreiben eine Methode, die mit jedem Erwachen aus dem sleep modus ausgeführt wird, unsere sogenannte WakeUp-Routine:
    ```cpp
    void wakeUpRoutine(){
        //reconnect to wifi and send image to server
        connectWiFi();
        sendPhoto();

        //back to sleep
        WiFi.disconnect(true);
        Serial.flush();
        delay(100);
        esp_light_sleep_start();
        delay(10);
        }
    ```
    Nach Senden des Fotos müssen wir, wie oben bereits erklärt, die WiFi Verbindung wieder trennen, bevor wir den ESP wieder in den sleep modus schicken.

- Nun können wir die loop-Methode schreiben, die sich so lange wiederholt, wie der ESP mit Strom versorgt wird:
    ```cpp
    void loop() {
        Serial.println("......... Woke Up ..................."); //debugging print
        wakeUpRoutine();
        delay(100);
    }
    ```
    In dieser brauchen wir nun lediglich unsere WakeUp-Routine aufzurufen. Ein loop-Durchgang entspricht also einem “Aufwachen”, da der ESP am Ende der WakeUp-Routine in den sleep modus versetzt wird.


{{< rawhtml >}} 
    <br>
{{< /rawhtml >}}
### 4. All about “Gewichtssensor”
Um mit den Daten des Gewichtssensors etwas anfangen zu können, brauchen wir ein Amplifier Modul (HX711). Der Schaltplan für diese beiden Komponenten sieht folgendermaßen aus:

{{< figure src="../media/projekt/schaltplan_loadcell.png" caption="Schaltplan Gewichtssensor">}}

Hierbei entsprechen die Farben der Kabel des Sensors auf dem Bild den Farben in echt und sollten dementsprechend verlötet werden. Um sicherzugehen ist es aber ratsam, in die Dokumentation der eigenen Teile zu schauen, falls Abweichungen auftreten. 

Das Schaubild zeigt außerdem, wie wir den Gewichtssensor montieren. Dazu brauchen wir folgende Bauteile:

{{< figure src="../media/projekt/bauteile_gewichtssensor.jpeg" width="60%"  caption="Gewichtssensor Bauteile">}}

- 3D-Modelle: Sensor-Case Deckel, Unterteil und Zwischenblatt
- Gewichtssensor mit Amplifier Modul
- 2 Schrauben einschließlich passender Muttern
- Holzstange

Die beiden Muttern dienen dabei als Spacer zwischen dem Gewichtssensor und dem unteren Teil des Cases, bzw. dem Waagblatt, das die Sitzstange hält und zwischen oberen Teil des Cases und Gewichtssensor liegt. Dies ist wichtig, damit der Sensor genug Platz hat, um bei Belastung nach unten gebeugt zu werden.

{{< figure src="../media/projekt/assemble_gewichtssensor.jpeg" width="60%"  caption="Gewichtssensor zusammenbauen">}}

Ist das Gehäuse zusammengesetzt, werden in die Holzstange (nachdem sie ebenfalls lasiert wurde) zwei Löcher mit 3mm Durchmesser gebort, so dass sie auf die beiden herausschauenden Stäbe gesteckt werden kann. Damit sie sicher hebt, habe ich sie mit 2-Komponenten-Kleber festgeklebt, dies sollte jedoch erst geschehen, wenn der Gewichtssensor zuverlässig funktioniert und das Case nicht mehr geöffnet werden muss. Das Case an sich habe ich nicht verklebt, da es durch den Steck-Mechanismus bereits ausreichend stabile Haftung vorwies.

{{< figure src="../media/projekt/gewichtssensor.jpeg" width="60%"  caption="Gewichtssensor fertig">}}

Um mit jedem Bild auch das aktuell gemessene Gewicht an den Server zu übermitteln, ergänzen wir den bisherigen Code für unseren ESP folgendermaßen:
- Das HX711 Modul benötigt eine Library, die wir inkludieren müssen:
    ```cpp
    #include "HX711.h"
    ```
    
- Des Weiteren definieren wir folgende Variablen, noch vor der setup-Methode:
    ```cpp
    //LOADCELL
    const int LOADCELL_DOUT_PIN = 13;
    const int LOADCELL_SCK_PIN = 12;
    const int calibrationfaktor = 380; //insert your own!
    long weight;
    HX711 scale;
    ```
    Die zwei Pins für DOUT und SCK entsprechen den Pins, die wir am ESP für den Sensor auswählen, ich habe hier Pin 12 und 13 gewählt.
    WICHTIG: Der Calibration-Factor ist für jeden Sensor ein anderer. Um diesen herauszufinden, müssen einige Objekte mit bekanntem Gewicht mit dem Sensor gewogen werden. Der Faktor berechnet sich dann folgendermaßen: 
    
    Calibration-Factor = Gemessenes Gewicht / Bekanntes Gewicht. 
    
    Es empfiehlt sich, dies mit einer gewissen Anzahl an Objekten zu machen und anschließen den Mittelwert der erhaltenen Faktoren zu nehmen, um am Ende möglichst genaue Daten zu erhalten.

- In der setup-Methode müssen wir nun unsere Waage initialisieren
    ```cpp
    //LOADCELL init
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    scale.set_scale(calibrationfaktor);
    scale.tare(5);
    ```
    Mit `scale.tare()` setzen wir die Waage auf Null. Wenn diese Methode aufgerufen wird, sollte sich also kein Gewicht auf dem Sensor befinden.

- Nun passen wir noch die WakeUp-Routine des ESP’s an, indem wir vor dem Senden des Fotos zunächst das Gewicht messen, und anschließend das Senden an den Server nur durchführen, wenn das Gewicht einen bestimmten Schwelle überschreitet. Dies verhindert, dass Fotos gesendet werden, wenn der Vibrationssensor fehlerhaft ausgelöst wurde (zum Beispiel durch ein fallendes Blatt oÄ.). Ich habe als Schwellwert 3 Gramm gewählt.
    ```cpp
    void wakeUpRoutine(){
        //get weight
        if (scale.is_ready()) { 
            weight = scale.get_units(20); //get the average of 20 readings
            Serial.print("Gewicht: "); //debug output
            Serial.println(weight);
        } else {
            Serial.println("HX711 not found.");
            weight = 0;
        }

        //check if an object is actually there or if scale empty
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
    ```

{{< rawhtml >}} 
    <br>
{{< /rawhtml >}}
### 5. Finaler Schaltplan, Stromversorgung

Um die bisher einzelnen Komponenten zusammenzuführen, soll folgender Schaltplan verwendet werden.

{{< figure src="../media/projekt/schaltplan.png" caption="Vollständiger Schaltplan aller Komponenten">}}

Als Stromversorgung verwenden wir ein Batterie-Case, dass Platz für 3 AAA Batterien beinhaltet. Da die AAA Batterien jeweils 1.5V liefern, erhalten wir so insgesamt 4.5V. Da alle Komponenten mit 3.3-5V arbeiten, brauchen wir so keine zusätzlichen Widerstände und versorgen gleichzeitig alle Komponenten mit genügend Strom.

Tabelle der Verknüpfungen: 

| HX711 \|  | ESP32-Cam \| | SW420  |
| --- | --- | --- |
| DT | GPIO13 | - |
| SCK | GPIO12 | - |
| - | GPIO15 | DO |

Ich habe jeweils Vibrationssensor und Amplifier Modul auf eine Platine sowie den ESP auf eine eigene Platine verlötet. Dies ist der Verteilung der Komponenten im Häuschen verschuldet. Während Vibrationssensor und Amplifier unter die Futterschale gehören, muss die ESP-Cam gegenüber der Sitzstange im Häuschen-Inneren angebracht werden. Es empfiehlt sich, die Cam erst später während dem Häuschenfertigungsprozess final zu verlöten, da erst dann abgeschätzt werden kann, wie lang die Drähte ins Häuschen-Innere sein müssen.

{{< rawhtml >}} 
    <br>
{{< /rawhtml >}}
### 6. Häuschenfertigung

Das Gehäuse für den Gewichtssensor wurde bereits angesprochen. So bleibt noch die Futterschale und das Häuschen selber.

Für die Futterschale habe ich den unteren Teil, in den dann Vibrationssensor und Amplifier Modul gelegt werden, 3D gedruckt. Da das Gehäuse des Gewichtssensors keinen Platz für Schrauben bietet und es nicht nötig ist, dass der untere Teil der Futterschale abnehmbar ist, wird er mit 2-Komponenten-Kleber an den unteren Teil des Gewichtssensor-Gehäuses geklebt, so dass beide Teile nach unten bündig abschließen.

{{< figure src="../media/projekt/futterschale_untererTeil.jpeg" width="60%"  caption="Futterschale und Sensor-Case">}}

Die  beiden kleinen Schraubenlöcher auf der Oberseite waren ursprünglich dazu da, um eine Platte von oben drauf zu schrauben, um so die Technik zu schützen. Wird diese Variante präferiert, können diese beibehalten werden, ansonsten sind sie überflüssig und können auch aus dem 3D Modell entfernt werden.

Um das Häuschen selbst zu bauen, sollen aus beliebigen Holz je nach gewünschter Größe des Hauses passende Wände sowie ein Boden ausgesägt werden. Zwei Wände müssen hierbei mit spitzer Oberseite zugesägt werden. Eine von diesen soll die Vorderseite werden, die andere die Rückseite. In die Vorderseite müssen folgende Ausschnitte:

- Zwei Löcher auf Höhe der Schrauben der Futterschale (siehe oben), Durchmesser 5mm
- Ein rechteckiges Fenster auf Höhe der oberen Seite der Futterschale (Dabei muss bedacht werden, dass ein Deckel später dazugehört, die Schale wird nicht offen bleiben). Durch dieses soll später das Futter in die Futterschale gelangen.
- Ein weiteres Loch, etwas unterhalb der Futteröffnung, um die Kabel ins Häuschen-Innere zu führen.
- Ein weiteres Fenster oberhalb des vorherigen, durch welches später die ESP-Cam fotografiert.

Dazu habe ich eine Stichsäge verwendet, während ich zum Aussägen der Platten selber eine Bandsäge benutzt habe.

{{< figure src="../media/projekt/haus_vorne.jpeg" width="60%" caption="Vorderseite des Häuschens">}}

Vor dem Verkleben sollte das Holz wetterfest gemacht werden. Hierbei habe ich einen wasserbasierte Acryllasur (in der Farbe Nussbaum) verwendet. Die Lasur sollte für die Sicherheit der Vögel eine giftigen Inhaltsstoffe enthalten. Die Ränder der Fenster können optional mit mit kleinen, zurechtgeschnittenen Holzstäbchen versehen werden, um die Kanten zu verstecken. Dadurch entstehen die oben zu sehenden Fensterrahmen. An das obere Fenster wird von innen eine kleine Plexiglasplatte geklebt, um die Cam zu schützen. Hierzu habe ich ebenfalls 2-Komponenten-Kleber verwendet. Bei der Holzplatte für die Rückseite des Häuschens hab ich das Prozedere für das obere Fenster wiederholt, jedoch in ein bisschen größer in vertikaler Hinsicht. Somit ist später von Außen zu sehen, wie viel Futter noch im Häuschen vorhanden ist.

{{< figure src="../media/projekt/haus_rueckseite.jpeg" width="60%" caption="Fenster in der Rückseite des Häuschens">}}

Um später das Batterie-Case aus dem “Keller” herausnehmen zu können, wird eine kleine Seitentür auf eine Seite des Hauses gebaut. Dazu Sägen wir ein Rechteck in eine der Seitenwände und verschrauben ein kleines Scharnier mit dem ausgeschnittenen Holzstück und der Seitenwand.

{{< figure src="../media/projekt/keller.jpeg" width="60%" caption="Seitentür für den Keller">}}


Beide Seitenwände, Boden und Rückseite können nun in diesem Stadium bereits mit Holzleim zusammengeklebt werden. Dabei sollte auf genug Ruhezeit geachtet werden, um den Leim trocknen zu lassen. Es empfehlen sich außerdem Klammern, die die Komponenten während dem Trocknen zusammenhalten. Für den Zwischenboden im Häuschen, der den “Keller”, in dem später das Batteriecase verstaut wird, vom oberen Teil des Häuschens trennt, werden vier Holzstückchen an die Innenwände auf Höhe der Futteröffnung. Es macht durchaus Sinn, den Zwischenboden ein wenig schräg (hinten höher als vorne) anzubringen, damit das Futter später leichter herausrutscht. Dabei muss, wie auf dem Bild zu sehen, eine Kuhle für die Kabel auf einer Seite gefeilt werden.

{{< figure src="../media/projekt/haus_innen_zwischenboden.jpeg" width="60%" caption="Haus von Innen, Zwischenboden">}}

Als nächstes drucken wir das Gehäuse für die ESP-Cam. Das Gehäuse hat an den Innenwänden zwei Schienen. So kann mit Hilfe eines kleinen Holzstäbchens, an dem dann der ESP befestigt wird, die Cam beliebig nach vorne und hinten verstellt werden. Dies ermöglicht ein passgenaues Einstellen der Cam, um möglichst gute Bilder im Endeffekt zu erhalten. Das Case wird mit 2-Komponenten-Kleber auf der Innenseite des Fensters festgeklebt. Die genaue Höhe sollte vorher durch Testbilder ermittelt werden.

{{< figure src="../media/projekt/haus_innen_cam_offen.jpeg" width="60%" caption="Kamera Case und ESP">}}

Die Futterschale wird mit zwei Schrauben und zwei Muttern an der Häuschenvorderseite festgeschraubt und die Kabel von Gewichts- und Vibrationssensor durch die entsprechende Öffnung geführt. Es empfiehlt sich, diese vorher mit einem Schrumpfschlauch zu umhüllen, um zusätzlichen Schutz zu bieten. Auf die Unterseite des Cam-Case  hab ich eine kleine Holzplatte geklebt, die ein kleines bisschen weiter ins Innere des Häuschens ragt.Damit schließt die spätere,abnehmbaare Rückwand des Cases bündig mit dem Boden ab. Für meine Cam stellte sich heraus, dass 30 mm Abstand zur Vorderwand eine gute Einstellung für das Sichtfeld der Kamera ist. Ist die Kamera befestigt, so wird noch ein Magnet an einem Holzstäbchen davor geklebt. Um die Technik am ESP zu schützen, habe ich den Magnet zusätzlich mit Isolierband umwickelt.


{{< figure src="../media/projekt/haus_innen_cam.jpeg" width="60%" caption="Kamera Case fertig">}}

So können wir auf einer weiteren kleinen Holzplatte in Größe der Öffnung des Kamera-Cases einen weiteren Magnet befestigen und somit einen abnehmbaren Deckel für das Case bauen, so dass der ESP zugänglich bleibt.

{{< figure src="../media/projekt/haus_innen_kabel.jpeg" width="60%" caption="Kabelführung ESP">}}

Schließlich werden zwei weitere lasierte Holzplatten benötigt, um das Dach des Häuschens zu bauen. Dabei ist darauf zu achten, dass diese lang genug sind, um die Futterschale und Sitzstange vor dem Häuschen zu schützen. Mit ein wenig Dachpappe werden diese nochmal extra vor Witterung geschützt. Mit jeweils vier Nägeln, einen für jede Ecke, wird die Pappe auf die Holzplatte genagelt. Eine Seite des Daches habe ich mit Holzleim festgeklebt und von Innen kleine, durch Unregelmäßigkeiten entstandene Lücken, mit Heißkleber abgedichtet. Auf diese Seite des Daches habe ich auch einen kleinen Schornstein eingebaut, einschließlich eines Deckels. Durch den Schornstein kann Futter nachgefüllt werden, ohne das Dach des Häuschens abnehmen zu müssen.

{{< figure src="../media/projekt/dach.jpeg" width="60%" caption="Dach von Innen">}}

Auf der anderen Dachseite werden in einem Rechteck so vier Holzstücke geklebt, dass sich das Dach passgenau auf das Häuschen setzen lässt. Dabei muss in das Holzstück, dass an der oberen Seite des Daches sitzt, eine Auskerbung gesägt werden, um den Schornstein freizuhalten (siehe Bild).

{{< figure src="../media/projekt/dachplatte.jpeg" width="60%" caption="Abnehmbare Dachplatte">}}

Zuletzt soll die Futterschale vervollständigt werden. Zwischen Hausvorderwand und oberen Teil des Gewichtssensor-Case kleben wir auf beiden Seiten zwei Holzstücke auf solcher Höhe, dass zwischen ihnen und dem unteren, 3D gedruckten Teil der Futterschale eine kleine Holzplatte passt. Diese sägen wir uns zurecht und können sie nun als herausschiebbaren Boden für die Futterschale verwenden.

{{< figure src="../media/projekt/Futterschale_boden.jpeg" width="60%" caption="Futterschale">}}

Da bei mir das Loch für die Kabelführung etwas zu hoch war, habe ich ein weiteres Holzstück an die Hauswand geklebt, um die Kabel zu verstecken.

Zuletzt habe ich ein paar Makramee-Fäden verwendet, um kleine Gardinen an das vordere Fenster zu kleben.


{{< figure src="../media/projekt/fertigeshaus.jpg" width="60%" caption="fertiges Häuschen">}}


{{< rawhtml >}} 
    <br>
{{< /rawhtml >}}
## Lizensierung
{{< rawhtml >}} 
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.
{{< /rawhtml >}}