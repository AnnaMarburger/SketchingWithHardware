---
title: "03 - Microcontroller Labor"
date: 2022-12-04T18:42:03+01:00
featured_image: "/media/lab2_ledmatrix.jpeg"
show_reading_time: true
draft: false
---

Es fanden drei Microcontroller Labortage statt, von denen ich an einem aufgrund von Krankheit nicht teilnehmen konnte.

### Tag 1
Am ersten Tag erhielten wir zunächst eine Kiste mit verschiedenen Bauteilen. In der Runde besprachen wir verschiedene Sensoren, wie zum Beispiel für Luftfeuchtigkeit oder Temperatur. 
Anschließend programmierten wir unseren ersten Arduino mit dem Beispielprogramm "Blink" der Arduino IDE. 

Nachdem die eingebaute Mini-LED im Arduino erfolgreich blinkte, schlossen wir mit Hilfe einer Steckplatine externe LED's an und passten auch dementsprechend das Skript für den Arduino an. 

{{< figure src="../media/lab2_ledblinken.mp4"  width="60%" height="60%">}}

Anschließend durften wir mit den verschiedenen Sensoren herumbasteln. 
Mit einem Touchsensor probierte ich, eine LED durch diesen zum Leuchten zu bringen, bzw. wieder auszuschalten. Leider reagierte der Sensor nicht besonders gut und wurde deshalb schnell durch einen normalen Button ersetzt. Danach funktionierte das Skript einwandfrei.

Des Weiteren entschlossen wir zu Zweit, mit einem Motor ein Ventilatorähnliches Bauteil zum Drehen zu bringen. Nachdem es zuerst zwei Mal kaputt ging, da die Drähte sich lösten, und gelötet werden musste, verkabelten wir es mit einem Arduino. Leider bedachten wir nicht, dass der Arduino nicht in der Lage dazu war genügend Strom für dieses Bauteil zu liefern. So beendeten wir dieses Projekt nicht erfolgreich, da am Ende für die etwas kompliziertere Lösung die Zeit fehlte.


### Tag 2

An diesem Tag verpasste ich leider das Labor und konnte so an keinem Miniprojekt weiterarbeiten. In der Vorlesung wurden am diesen Tag unter anderem das Schema der serielle Kommunikation besprochen.


### Tag 3

Nach einer einführenden Vorlesung,in der unser Wissen vor allem zu Output abgerundet wurde, durften wir wieder mit den verschiedenen Bauteilen basteln. Ich entschied mich dazu, mehrere LED Matrizzen aneiander zu schließen. Mit einer Bibliothek versuchte ich verschiedene Textausgaben darstellen zu lassen. Dies funktionierte jedoch nicht, auf den Matrizzen war kein Text zu sehen. Zudem störte ein massiver Wackelkontakt etweder bei den Kabeln oder bei den LED Matrizzen das Ergebnis. Das eigentliche Ziel war, animierten Text darzustellen, z.B. ein Wort, dass die Matrix einmal quer "durchläuft". 

{{< figure src="../media/lab2_ledmatrix.jpeg"  width="60%" height="60%">}}

Ohne die Bibliothek war dies mit meinen Fähigkeiten leider nicht möglich und so beschränkte sich das Ergebnis auf ein paar hardgecodete leuchtende LED's der Matrix.

### Interrupts und Sleep-Modi

Um einen Arduino Stromsparend zu verwenden, gibt es verschieden Sleep Modi und Interrupts, um z.B. eine möglichst lange Akkulaufzeitt zu bekommen.

##### Interrupts
 Ein Interrupt ist ein Mechanismus der zur Überwachung von Echtzeitevents genutzt wird. Dabei funktioniert er folgendermaßen:
 Wird ein bestimmtes Signal festgestellt, unterbricht der Interrupt die aktuelle Handlung des Prozessors und führt für diesen Fall zuvor festgelegten Code aus. Anschließend kehrt der Prozessor zum vorherigen Punkt zurück und setzt seine unterbrochene Handlung fort.
 Ein großer Vorteilist folglich, dass aktives Warten des Prozessors vermieden wird, gleichzeitig aber auf Events in Echtzeit reagiert werden kann.

 Um dies im Code umzusetzen, gibt es folgende Methode

 ``` arduino
    void setup() {
        // Attach an interrupt to the ISR vector
        attachInterrupt(0, interruptMethod, CHANGE);
    }

    void interruptMethod() {
        //do interrupt action here
    }
```

Die attachInterrupt() nimmt drei Parameter:
- Den Interrupt Vektor, der festlegt, von welchem Pin ein Interrupt generiert werden kann. Jedoch ist dies hier nicht die Nummer des Pins selbst, sondern eine Referenz auf eine Stelle im Speicher. Für Arduinos ist der Vektor 0 für Pin 2 und Vektor 1 für Pin 3 (Anmerkung: Es können nicht alle Pins Interrupts auslösen).
- Der Name der Methode, die bei einem Interrupt ausgeführt werden soll.
- Der Interrupt Modus. Er bestimmt, welche Pin-Aktion einen Interrupt auslöst. Es gibt dabei die Modi 'RISING, FALLING, CHANGE, LOW' (Funktion dem Name entsprechend)

In obigem Beispiel wird also Pin 2 auf jede Wertänderung überwacht, um bei eintreffendem Interrupt die Methode interruptMethod() aufzurufen.


##### Sleep Modi

Während Interrupts also aktives Warten vermeiden lassen, können Sleep Modi dazu dienen, den Prozessosr bzw. Teile davon in einen inaktiven Zustand zu versetzen.

Um den Sleep Modus ein- bzw. auszuschalten gibt es folgende Funktionen:

``` arduino
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable(); // sleep mode einschalten
    sleep_mode(); // in den sleep mode gehen
    sleep_disable(); // sleep mode ausschalten nach Erwachen
```










