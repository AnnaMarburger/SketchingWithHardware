---
title: "06 - Additive Fertigung"
date: 2023-02-12T14:08:27+01:00
featured_image: "/media/lab4_qboydruck.jpeg"
show_reading_time: true
draft: false
---

Im Gegensatz zur subtraktiven Fertigung, die Thema des letzten Labors war, werden bei der additiven Fertigung durch Hinzufügen von Material Teile hergestellt. Dies kann beispielsweise durch einen 3D-Drucker geschehen. Hierbei gibt es verschiedene Arten an Druckern:
- SLA: Stereolithography
- FDM: Fused Deposition Modeling
- SLS:  Selective Laser Sintering
- SPD:  Selective-Powder-Deposition

In unserem Labor stehen FDM Drucker zur Verfügung. Bei diesen Druckern wird Material erhitzt und aus einer Nozzle am Druckkopf gepresst, um so Schicht für Schicht das gewünschte Modell auf einer Platte aufzubauen. Es gibt zwei gängige Architekturen bei Druckern dieser Art:
- "Bowden tube extrusion system": Der Extruder befindet sich gesondert von Druckkopf und Nozzle. Vorteile: schneller und genauer, da der Druckkopf nicht durch den Extruder beschwert wird
- "Direct-Drive-Extruder": Der Extruder sitzt direkt am Druckkopf. Vorteile: Einfacher Materialwechsel, kann flexible Materialien drucken (da sich diese nur "ziehen" und nicht "schieben" lassen).

Als Material kann zwischen verschiedenen Plastikarten wie PLA, PETG, ABS, TPU und PVE gewählt werden, je nach gewünschten Eigenschaften (zB. flexibel vs. stabil). Je nach Material muss eine unterschiedliche Temperatur bei Druckbett und Extruder gewählt werden. 

#### Software

Zum Erstellen eines 3D-Objekts kann sowohl CAD Software, wie Autodesk Fusion 360, aber auch Mesh-Bearbeitungssoftware wie zum Beispiel Blender genutzt werden. Mit ersterem lassen sich 3D-Modelle auf exakte Maßangaben hin durch geometrische Modellierung erstellen und drucken. Es wird dabei direkt mit 3D-Körpern gearbeitet und nicht mit Meshes, wie es bei Software wie Blender o.Ä. der Fall ist. Letzteres eignet sich demnach für komplexere Objekte mit freien Formen.
Im Lab bekamen wir die Aufgabe, eine Papierhalterung zu designen:

{{< figure src="../media/infoschild.png" >}}


Anschließend muss erstelltes 3D-Objekt, exportiert als ".stl"-Datei, gesliced werden. Dies passiert durch eine weitere Software, in unserem Fall "UltiMaker Cura". Beim slicen wird entsprechendes Objekt in Anweisungen für den 3D-Drucker übersetzt. Außerdem können Einstellungen wie
- Extrusionsbreite, 
- Geschwindigkeit, 
- Supportstrukturen und 
- Füllung 

beeinflusst werden. Die "geslicte" Datei wird anschließend dem 3D-Drucker übergeben und das 3D-Objekt gedruckt.

#### Typische Fehler beim 3D-Druck:
- Unglatter Druck, klar sichtbare Linien. Grund: Billiges Material, oder auch zu hohe Layer Höhe / Temperatur.
- Stringing, der Drucker zieht ungewollte Fäden. Grund: Zu hohe Temperatur, zu geringer Rückzugabstand / Druckgeschwindigkeit, aber auch bestimmte Materialien.
- Wölben des Materials an Ecken. Grund: Zu hohe Drucktemperatur, zu wenig Kühlung während des Drucks.


