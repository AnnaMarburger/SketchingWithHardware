---
title: "08 - Das 2. Semester"
date: 2023-07-11T12:16:27+02:00
show_reading_time: true
featured_image: "/media/haus_innen_cam_offen.jpeg"
draft: false
---

## Semesterverlauf

**Geplant vs Umgesetzt**

Das Semester startete damit, dass wir nach einer Einführung eine Projektidee finden mussten, die sowohl alle vorgestellten "Must Haves", sowie mind. einem "Should Have" entsprach. Ich entschied mich dazu, ein smartes Futterhäuschen zu bauen, welches nicht nur Fotos von Vögeln machen, sondern diese auch wiegen soll, während es als Futterhäuschen für diese dient. Die Bilder und Daten plante ich per Mail an den User zu verschicken.

Nach dem Projekt-Pitch, bei welchem jeder seine Idee einschließlich Zeitplan vorstellte, begann ich meine Projektarbeit zunächst damit, eine Teileliste mit allen benötigten Bauteilen aufzustellen und entwarf einen ersten Designentwurf, wie ich mir das Häuschen vorstellte.

{{< figure src="../media/projekt/hausdesign.png" width="60%" height="60%" caption="Erster Designentwurf mit Blender">}}

Für die Planung meines Projektes, sowohl was Zeitmanagment, als auch Dateiverwaltung betrifft, verwendete ich das Tool "Notion".
Mein Zeitplan sah folgendermaßen aus:

{{< figure src="../media/projekt/zeitplan.png">}}

Dieser stellte sich über das Semester hinweg als gut einhaltbar heraus. Getauscht wurden jedoch "Server Code" und "Häuschenfertigung".

Direkt zu Beginn recherchierte ich, welche Materialien ich bedenkenlos verwenden könnte, ohne die Sicherheit / Gesundheit meiner tierischen Besucher zu gefährden. Wie ich feststellte, ist Holz hierbei die beste Wahl. Dieses sollte jedoch für Wetterbeständig- und Langlebigkeit lasiert werden. Dafür wird Lasur auf Wasserbasis empfohlen, da sie als weniger umweltbelastend gilt. Auf folgende Materialien sollte auf jeden Fall verzichtet werden: Materialien mit Zink oder Schwermetalle, die rosten. Rost, Zink und Schwermetalle sind giftig für Vögel.

Während die Bestellung der Bauteile noch unterwegs ins Lab war, änderte ich meinen Plan für das Versenden der Bilder und Daten und setzte schonmal den Server auf, an welchen mein Vogelhäuschen die Daten senden sollte, statt sie per Mail dem User zugänglich zu machen. Dabei entschied ich mich für Node.Js mit dem Framework Express aufgrund der großen Vereinfachung beim Coden, die das Framework bot.
Des Weiteren modellierte ich bereits ein 3D-Modell eines Case für den Gewichtssensor, der die Wiegefunktion des Häuschens umsetzen sollte. 

{{< figure src="../media/projekt/modell_sensorcaseunten.png"  width="60%" height="60%" caption="Unterer Teil des Sensor-Cases">}}
{{< figure src="../media/projekt/modell_waagblatt.png"  width="60%" height="60%" caption="Bewegliches Zwischenblatt">}}
{{< figure src="../media/projekt/modell_sensorcaseoben.png"  width="60%" height="60%" caption="Oberer Teil des Sensor-Cases">}}

Das Modell musste jedoch angepasst und ein Weiteres mal gedruckt werden, da eine Bohrung für eine Schraube zur Befestigung des Gewichtssensors im Case nicht an der passenden Stelle saß.

Um die ESP32-Cam, die ich als Modul für das Bildermachen wählte, möglichst stromsparend zu nutzen, plante ich, den Gewichtssensor als Interrupt-Auslöser zu verwenden und den ESP, solange der Gewichtssensor keine Schwankung in seinen Messungen feststellte, in einen light sleep zu versetzen. Als der Sensor jedoch ankam und ich ihn testen konnte, stellte ich fest, das dieser Plan nicht umzusetzen war. Da der Sensor durch seinen digitalen Output eine serielle Verbindung zum ESP aufbaut und konstant Daten sendet, wurde bei den Tests ein Interrupt nicht nur bei Schwankungen in den Messungen, sondern stattdessen durchgehend ausgelöst. Ich konnte nun zwischen zwei Alternativen wählen:
- Das Problem software-seitig lösen: Das heißt, im Code konstant überprüfen, ob das Gewicht auf dem Sensor steigt, und ab einem bestimmten Gewicht das Foto machen und an den Server senden. Nachteil: keine energie-effiziente Verwendung des ESP. Vorteil: keine zusätzlichen Bauteile nötig, einfach umzusetzen.
- Eine andere Möglichkeit finden, einen Interrupt auszulösen, wenn ein Vogel da ist, zum Beispiel mit einem weiteren Sensor.

Ich entschied mich für letzteres und baute einen Vibrationssensor in das Häuschen mit ein, welcher auf Erschütterungen der Futterschale vor dem Häuschen reagiert, sprich, wenn zum Beispiel ein Vogel Futter von der Schale pickt.

**Fertigungsverfahren**

Beim Bau des Häuschens setzte ich verschiedene Fertigungsverfahren ein. Für die Gehäuse für die technischen Module verwendete ich den 3D-Drucker. Hierbei gefiel mir, dass auf Millimeter genau alles vermessen und angefertigt werden konnte. Mit einem guten Modell ist man nach dem Design von diesem fertig und muss es am Ende nur noch aus dem Drucker holen. Jedoch gab es zum einen in der Praxis sehr oft Probleme mit den Druckern und die Modelle kamen oft nicht so raus wie geplant. Zum Anderen war für mich ein großer Nachteil, dass die Modelle im Nachhinein kaum bearbeitbar waren. Sprich bei Planänderungen (wie zusätzlich verwendeten Schrauben, anderer Kabelführung o.Ä.) hieß dies direkt, das ganze Modell neu zu drucken. 

Das restliche Haus baute ich aus verschiedenen Holzplatten zusammen, die ich mit Band- bzw. Stichsäge auf die passenden Größen zurecht schnitt. Mit Holz zu arbeiten hat mir wesentlich besser gefallen, da auch noch im Nachhinein Stellen durch zB. Feilen angepasst werden konnten.

**Motivation und Evaluation**

Die größte Motivation für das Semester war das eigene Projekt. Dadurch, dass ich mir selbst ausgesucht habe, welches Projekt ich machen will und dieses auch nach meinen Vorstellungen umsetzen konnte, war die Motivation größer, das Projekt auch fertigzustellen.

Mit dem Kurs habe ich nicht nur festgestellt, wie viel Spaß mir nicht nur das softwareseitige Erarbeiten von Projekten macht, wie es für mich bisher im Informatik Studium der Fall war, sondern auch am Bau der Hardware beteiligt zu sein. Auch die Fertigung und Holzarbeit hat mir wesentlich mehr Spaß bereitet als gedacht und ich habe viele neue Methoden gelernt. Für mich privat nehme ich davon mit, nun auch allein dazu in der Lage zu sein, ähnliche Projekte unabhängig vom Studium in der Freizeit umzusetzen. Auch für meine berufliche Zukunft ist es sicherlich von Vorteil, diese Verknüpfung von Software und Hardware gelernt zu haben.

Das Modul und die Projektarbeit haben mir sehr gut gefallen und wir wurden angemessen betreut und unterstütz, so dass wir bei größeren Probleme nicht allein gelassen wurden und "festsaßen", sondern mit ein wenig Unterstützung weiter voran kamen.
Für zukünftige Kurse würde ich mir neue 3D-Drucker wünschen, um die Arbeit zu erleichtern. Bei den Lötkolben wurden bereits Spitzen ersetzt, was sehr geholfen hat. Außerdem würde ich mir etwas mehr Zeit wünschen, da es bei einigen trotz Zeitplan ziemlich knapp wurde und auch ich nur ein paar Tage vorher ganz fertig wurde. Man könnte zum Beispiel früher im Semester mit der Projektarbeit anfangen, der Projekt-Pitch fand bei uns erst Mitte Mai statt, einige Wochen nach Semesterstart.

{{< rawhtml >}} 
    <br>
{{< /rawhtml >}}
## Das Projekt: Bird Booth
{{< figure src="../media/projekt/Poster_AnnaMarburger.png" caption="Poster für das Streiflicht 2023 ">}}


Bird Booth sollte ein smartes Futterhäuschen werden mit der Funktion, Bilder zu machen, wenn ein Vogel an die Futterstelle kommt und diesen zu wiegen, um anschließend die Daten an einen Webserver zu senden. Das Futterhäuschen sollte sicher für Vögel, wetterbeständig und robust werden.

**Features**

{{< figure src="../media/projekt/schaltplan.png" caption="Komponenten-Schaltplan ">}}

- **Kamera:** Das Häuschen hat eine eingebaute Minikamera im Inneren, die auslöst, wenn eine Erschütterung auf der Futterschale wahrgenommen wird. Letzteres geschieht durch einen Vibrationssensor. Die Kamera wird durch eine ESP32-Cam implementiert. Der Microchip wartet also auf ein Signal des Vibrationssensor und sendet, sobald dieses eintrifft ein Foto an einen Server.
- **Waage:** Nicht nur ein Bild wird an den Server geschickt, sondern auch das Gewicht, dass der Gewichtssensor unter der Sitzstange des Häuschens misst. Die Mechanik im Gewichtssensor-Case erlaubt eine sensible Messung: Setzt sich ein Vogel auf die Sitzstange, so überträgt diese das Gewicht auf das Zwischenblatt im Case. Dieses widerum leitet das Gewicht auf die nicht befestigte Seite des Gewichtssensors weiter. Dadurch dehnt sich dieser minimal nach unten. Um die gemessenen Daten lesen zu können, da der Gewichtssensor das Gewicht über sogenannte Dehnungsmessstreifen wahrnimmt und dadurch sehr kleine Messungen zurückgibt, wird ein Amplifier benötigt.
- **Mobilität:** Damit das Häuschen draußen montiert werden kann, wird eine mobile Stromversorgung in Form von 3x AAA-Batterien verwendet. Das Batterie-Case befindet sich im “Keller” des Häuschens, geschützt von äußeren Einflüssen.
- **Webserver:** Um die Bilder und Gewichtsdaten einsehen zu können, steht ein eigener Server bereit. Dieser verwendet Firebase Storage als Datenbank zum Speichern der Daten. So kann der User von überall und von allen Geräten auf die Daten zugreifen. Der Server wurde mit Node.js Express geschrieben. Das Framework ermöglicht unkomplizierten Code und kann so mit relativ wenig Vorwissen ebenfalls angepasst werden. Über den Server können die Bilder auch heruntergeladen oder wieder gelöscht werden. Auch können die Bilder nach gemessenem Gewicht sortiert und die Ansicht auf Bilder, die “heute” oder auch “diese Woche” entstanden sind, eingeschränkt werden.
- **Zugänglichkeit:** die technischen Komponenten sind leicht zugänglich und so können Anpassungen bzw. das Ersetzen von Modulen leicht durchgeführt werden.
- **Stromsparend:** Damit die Batterien möglichst lange durchhalten und nicht so oft gewechselt werden müssen, wurde der Code für das ESP-Modul so geschrieben, dass er in einem stromsparenden sleep-modus fällt, wenn keine Vögel detektiert werden. Im sogenannten “light-sleep” kappt der ESP beispielsweise WLAN-Verbindungen. Der größte Teil des RAM und der CPUs werden jedoch taktgesichert und können nach dem aufwachen ihren Betrieb wieder aufnehmen, da ihr innerer Zustand erhalten bleibt.

Folgendes Diagramm veranschaulicht die Funktion / Ablauf des Futterhäuschens:

{{< figure src="../media/projekt/ablaufdiagramm.png" caption="Ablaufdiagramm">}}

Alle Features waren zum Zeitpunkt der Abschlusspräsentation bereits geplant und ebenso voll funktionsfähig. Nach der Präsentation wurde nichts mehr an dem Projekt verändert.

{{< rawhtml >}} 
    <br>
{{< /rawhtml >}}
## Gallerie

**Häuschen**
  \
  \
{{< rawhtml >}} 
    <video width=80% controls autplay >
        <source src="../media/projekt/haus.mp4" type="video/mp4">
        Your browser does not support the video tag.  
    </video>
{{< /rawhtml >}}
  \
  \
{{< rawhtml >}} 
    <video width=80% controls autplay >
        <source src="../media/projekt/haus_zugaenglichkeit.mp4" type="video/mp4">
        Your browser does not support the video tag.  
    </video>
{{< /rawhtml >}}
  \
  \
{{< figure src="../media/projekt/fertigeshaus.jpg" caption="Fertiges Häuschen von Vorne">}}
  \
{{< figure src="../media/projekt/keller.jpeg" caption="Kellerfach und Futterschale">}}
  \
{{< figure src="../media/projekt/gewichtssensor.jpeg" caption="Gewichtssensor-Case mit Sitzstange">}}
  \
{{< figure src="../media/projekt/dach.jpeg" caption="Schornstein / Dach von Innen ">}}
  \
{{< figure src="../media/projekt/haus_innen_cam.jpeg" caption="Haus von Innen (Sicht auf ESP)">}}
  \
  \
**Server**
  \
{{< figure src="../media/projekt/server_desktop.png" caption="Screenshot Desktopansicht">}}
  \
{{< figure src="../media/projekt/server_iphone.png"  width="60%" height="60%" caption="Screenshot IPhone X">}}