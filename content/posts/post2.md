---
title: "02 -  E-Technik Labor"
date: 2022-11-11T18:15:06+01:00
draft: false
---

Nach einer einführenden Vorlesung zu Elektrotechnik, in der unser Wissen zu Strom, Spannung und Widerstand aufgefrischt wurde, bildete der erste Versuch des heutigen Labs das Löten.

## Versuch 1: Löten

In Zweierteams wurden uns Lötkolben, Lötzinn, Entlötlitze und Flussmittel bereitgestellt, sowie eine Leiterplatte und verschiedene Widerstände. 

{{< figure src="../media/lab1_loeten_zubehoer.png" caption="Lötzubehör" width="60%" height="60%">}}

Letzere sollten also auf der Platte festgelötet werden. Zunächst musste dafür das Flussmittel auf die zu lötende Stelle aufgetragen werden. Anschließend wurde die Stelle mit dem Lötkolben erhitzt und der Lötzinn daran gehalten, bis dieser flüssig wurde. Nach dem Erhärten war die Stelle auch schon erfolgreich verlötet.

{{< figure src="../media/lab1_loeten_vorgang.png" caption="Prozess"  width="60%" height="60%">}}

Da ich bisher noch keine Erfahrungen mit Löten sammeln konnte, war der Start zunächst holprig - nach zwei, drei Mal löten klappte es jedoch bereits gut.

{{< figure src="../media/lab1_loeten_ergebnis.png" caption="Ergebnis" width="60%" height="60%">}}


## Versuch 2: Messgeräte im Labor

### 2.1 Einführende Aufgaben

Um das Wissen aus der vorangegangenen Vorlesung zu festigen und auf den folgenden Versuch zu Messgeräten im Labor vorzubereiten, beschäftigten wir uns als nächstes mit ein paar Aufgaben zum Ohmschen Gesetz, Kennlinien und zur Leistung. So sollten wir Widerstände berechnen, von Kennlinien ablesen und Zusammenhänge zwischen Strom- und Widerstandgrößen bzw der Leistungsabgabe verstehen.

### 2.2 Messen mit dem Multimeter

Vorbereitung: Anschließen eines Widerstandes an das Labornetzteil nach folgendem Schema:

 {{< figure src="../media/lab1_messen_schema.png" caption="" width="60%" height="60%">}}

Vorgehen: Ein Multimeter schlossen wir parallel zum Widerstand an, um die Spannung zu messen, sowie ein weiteres in Reihe, um den Strom zu messen. Letzteres war nötig, da die Stromangaben des Labornetzteils etwas ungenau waren. 

Ergebnisse: Es wurden 10 Strom- bzw. Spannungswerte gemessen, die wir in folgende Tabelle vermerkten.

{{< figure src="../media/lab1_messtabelle.png" caption=""  width="60%" height="60%">}}

Dies ergab folgende Kennlinie für den Widerstand:

{{< figure src="../media/lab1_kennlinie.png" caption=""  width="65%" height="65%">}}

Bei die Berechnung des Widerstands fallen die Messungenauigkeiten und -fehler des Versuchs durch die leichten Schwankungen der Angaben auf.

In der Schule behandelte der Physikunterricht das Messen mit dem Multimeter, so war dies für mich zwar nicht neu; Da die letzte Physikstunde jedoch schon eine ganze Weile her ist, frischte dieser Versuch mein Wissen dazu deutlich auf.

### 2.3 Widerstand mit dem Spannungsteiler bestimmen

Der letzte Versuch bildete das Messen eines Widerstands mit einem Spannungsteiler.

Vorgehen: Zunächst musste dafür ein Spannungsteiler gebaut werden, dies realisierten wir mit Hilfe einer Steckplatte.

{{< figure src="../media/lab1_stromteiler_aufbau.png" caption="Spannungsteiler Versuchsaufbau"  width="60%" height="60%">}}

Anschließend nahmen wir die Werte der Spannung des zweiten Widerstandes ($U_{R_2}$) bzw. der gesamten Spannung ($U_{ges}$). Zudem maßen wir den Wert des zweiten Widerstandes ($R_2$). Durch Umstellen der Formel

$$U_{R_2}=U_{ges}*\frac{R_2}{R_1+R_2}$$  

aus der Vorlesung nach  ${R_1}$ :

$$R_1=\frac{U_{ges}*R_2}{U_{R_2}}+R_2$$

Ergebnis: Mit den Messwerten eingesetzt, ergab dies

$$R_1=\frac{2V*221\Omega}{0,63V}+221\Omega= \frac{58123}{63} \Omega$$

für den ersten Widerstand $R_1$.
Vorteil der Berechnung des Widerstandes durch diese Formel ist klar, dass keine Stromwerte gemessen werden müssen.

## Projektentscheidung: Wetterstation






