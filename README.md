## Beschreibung

Im Rahmen des Gruppenprojektes Smart-Home muss jede Kleingruppe ein unabhängiges Teilsystem entwickeln. In diesem Teilsystem geht es um eine automatisierte Heizungssteuerung, die man manuell aktivieren/deaktivieren kann und eine Richttemperatur mit Hilfe von zwei Tastern einstellen kann. Der Status sowie die aktuelle Temperatur und die Richttemperatur wird auf einem LCD-Display angezeigt. Das System funktioniert mit einem NTC-Widerstand (Negative Temperature Coefficient Thermistor), der mit Hilfe des ADC0804 an den Mikrocontroller C8051F340 von Silicon Laboratories angeschlossen ist.

## Schaltplan

![](https://github.com/TrickShotMLG02/TG13_3_Heizungssystem/blob/bd521ed5e8aaa8eadc44ef0b3915566787d644cc/Dokumentation/Schaltplan.PNG)

## Bedienung

![](https://github.com/TrickShotMLG02/TG13_3_Heizungssystem/blob/master/Dokumentation/Heizungssteuerung.png)

Zu Beginn wird der Sollwert mit Hilfe der zwei Taster (Plus und Minus) durch das Drücken des jeweiligen Tasters eingestellt. Der Sollwert lässt sich in 1°C Schritten verändern. Die aktuelle Temperatur sowie der derzeitige Sollwert werden auf dem LCD-Display angezeigt. Auch der Systemstatus ist dort vermerkt. Dieser lässt sich durch das Drücken des An/Aus-Tasters verändern. Die untere Grenze für den Sollwert beträgt 15°C und die obere Grenze beträgt 25°C. Nach dem Einschalten des Systems ist das System standartmässig aktiviert und auf einen Sollwert von 21°C eingestellt. Ist die aktuelle Temperatur grösser als der Sollwert, dann leuchtet die Blaue LED auf (Simulation für Kühlung). Ist die aktuelle Temperatur kleiner als der Sollwert, so leuchtet die Rote LED auf (Simulation für Heizung). Ist das System deaktiviert (Systemstatus = Off) so leuchtet keine der beiden LEDs. Es werden trotzdem die aktuelle Temperatur sowie der eingestellte Sollwert angezeigt. Auch während das System deaktiviert ist lässt sich der Sollwert mit Hilfe der beiden Taster (Plus und Minus) verändern.

## Aufbau
![Aufbau_01](https://github.com/TrickShotMLG02/TG13_3_Heizungssystem/blob/master/Dokumentation/Aufbau_01.jpg)
![Aufbau_02](https://github.com/TrickShotMLG02/TG13_3_Heizungssystem/blob/master/Dokumentation/Aufbau_02.jpg)

## Programmablaufplan

![](https://github.com/TrickShotMLG02/TG13_3_Heizungssystem/blob/master/Dokumentation/Programmablaufplan.png)



## Code

### Variablen
![](https://github.com/TrickShotMLG02/TG13_3_Heizungssystem/blob/master/Dokumentation/CodeSnippets/Bildschirmfoto%202021-12-06%20um%2009.32.42.png)

Hier sind alle Variablen deklariert sowie deren Verwendungszweck im Programm angegeben.


### Funktionen
![](https://github.com/TrickShotMLG02/TG13_3_Heizungssystem/blob/master/Dokumentation/CodeSnippets/Bildschirmfoto%202021-12-06%20um%2009.34.27.png)

Das sind alle Methoden, die von der main()-Methode oder von sich selbst verwendet werden. Die drei Methoden initlcd(), loeschenlcd() sowie textlcd() sind für die Ansteuerung des LCD-Displays verantwortlich.


### Init()
![](https://github.com/TrickShotMLG02/TG13_3_Heizungssystem/blob/master/Dokumentation/CodeSnippets/Bildschirmfoto%202021-12-06%20um%2009.35.13.png)

Zu Beginn wird in der Init der standartmässige Sollwert eingestellt. Des weiteren wird festgelegt, dass das System aktiviert ist. |


### Ausgabe()
![](https://github.com/TrickShotMLG02/TG13_3_Heizungssystem/blob/master/Dokumentation/CodeSnippets/Bildschirmfoto%202021-12-06%20um%2009.35.23.png)

Die Methode ausgabe() kümmert sich um die Ausgabe der Werte auf dem LCD-Display. In der ersten Zeile wird die aktuelle Temperatur ausgegeben. In der 2. Zeile wird der Sollwert und der Systemstatus (ON/OFF) ausgegeben.


### ReadTemperatur()
![](https://github.com/TrickShotMLG02/TG13_3_Heizungssystem/blob/master/Dokumentation/CodeSnippets/Bildschirmfoto%202021-12-06%20um%2009.35.33.png)

Die Methode readTemperatur() liest die Temperatur vom ADC0804 aus. Zuerst stellen wir mit dem bit P1.1 ein, dass keine Daten ausgelesen werden. Danach wird die Wandlung durch einen kurzen Impuls an P1.2 gestartet und wieder beendet. Die Schleife dient als Zeitverzögerung, sodass das wandeln des analogen Signals problemlos erfolgen kann. Durch das Löschen des Bits P1.1 wird der ermittelte Wert zum Lesen freigegeben. Zum Schluss wird noch die aktuelle Temperatur berechnet, indem wir mit Hilfe der gemessenen Spannungen des NTCs und dem ADC-Signal die Temperatur berechnen.


### Main()
![](https://github.com/TrickShotMLG02/TG13_3_Heizungssystem/blob/master/Dokumentation/CodeSnippets/Bildschirmfoto%202021-12-06%20um%2009.36.37.png)

Die main()-Methode spiegelt das ganze Programm wieder. Zunächst wird die oben erklärte Methode ausgabe() aufgerufen. Danach warden die 3 Taster (+ / - / On/Off) überprüft und der Sollwert erhöht/verringert oder das System Aktiviert/Deaktiviert. In den Zeilen 151 – 161 werden die blaue und die rote LED angesteuert. Da der Port P4 nicht bitadressierbar ist, muss hier immer ein ganzes Byte geschrieben werden. Beachte, dass die LEDs durch einen Inverter angesteuert werden, sodass die 0 in dem jeweiligen Byte den Status aktiviert wiederspiegelt.


## Projektplanung
| **Teilschritt** | **Zu erledigen bis** | **Verantwortlicher** |
| --- | --- | --- |
| LCD-Display Ansteuerung | 20.09.2021 | Tim Schlachter |
| Taster (+ / - / On/Off) | 04.10.2021 | Anton Tran |
| Temperatursensor anschliessen | 04.10.2021 | Anton Tran |
| Ansteuerung ADC0804 | 18.10.2021 | Tim Schlachter |
| Temperatursensor Analogspannung messen | 08.11.2021 | Anton Tran |
| Anschliessen LEDs | 08.11.2021 | Anton Tran |
| Temperatur digital auswerten mit ADC | 22.11.2021 | Tim Schlachter |
| Simulation (Heizung/Kühlung) | 22.11.2021 | Tim Schlachter |
| Dokumentation | 20.12.2021 | Tim Schlachter/Anton Tran |
