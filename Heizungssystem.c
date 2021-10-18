/*
 Name:          Tim Schlachter / Anton Tran
 Klasse.        TG13/3
 Datum:         20.09.2021
 Aufgabe:   	Heizungssystem
 Controller:    C8051F340
 
 Beschreibung:
    Ziel ist es ein Heizungssystem zu ertellen, bei dem eine Richttemperatur
    mit Hilfe von 2 Tastern eingestellt werden kann. Das System versucht diese
    Temperatur konstant zu halten, sofern das System mit dem Anschalter aktiviert
    wurde. Die Richttemperatur und die derzeitige Temperatur wird auf einem LCD-Display
    angezeigt. Die Heizfunktion wird druch eine rote LED und die Kühlfunktion durch eine
    blaue LED dargestellt.
    
    - Spannung temperatursensor messen
    - ADC Auflösung: 0,019V pro bit
	https://sensorkit.joy-it.net/de/sensors/ky-013
 */
 
 
 /*
 
    P0: LCD
    P1: Steuerleitung ADC
    P2: Datenleitung ADC
    P3: Taster
    P4: LED-Leiste für ADC Auswertung
    
 
 */

 //-----------------------------------------------------------------------------
 // Include Dateien
 //-----------------------------------------------------------------------------
#include <stdio.h>									// für sprinf		
#include <C_8051F340.h>                //Erweiterte SFR Zuordnungen
#include <Einstellungen.h>             //beinhaltet die Funktion Grundeinstellungen

//-----------------------------------------------------------------------------
// Pin/Port Zuweisungen
//-----------------------------------------------------------------------------
unsigned char buf [20] ;	        // Zwischenspeicher für LCD-Text

unsigned char systemStatus = 1;     // Systemstatus: 1 -> an, 0 -> aus

double step = 0.5;                  // Schrittgrösse

double currentTemp = 21;            // Derzeitige Temperatur 
double selectedTemp = 21;           // Ausgewählte Temperatur 

double minTemp = 15;                // Untere Temperaturgrenze
double maxTemp = 30;                // Obere Temperaturgrenze

unsigned int i = 0;                 // ReadTemperatur CounterVariable

//-----------------------------------------------------------------------------
// Eigene Funktionen
//-----------------------------------------------------------------------------

// externe Funktionen in lcd.c; Diese Datei zum Projekt hinzufügen
extern void initlcd (void);						//	Initialisierung LCD-Display an P0			
extern void loeschenlcd (void);
extern void textlcd (unsigned char *text,unsigned char zeile);

void init(void)
{
	selectedTemp = 21;
}

void ausgabe(void)
{
    //LCD Display
    sprintf (buf,"Derzeitige Temperatur: %d°",currentTemp);
	// Text mit Variable formatieren und in buf kopieren		
	//	% Ausgabeformat folgt, d Dezimalzahl mit Vorzeichen, a auszugebende Variable	
	textlcd (buf,1);
    sprintf (buf,"Sollwert: %d°",selectedTemp);
  	textlcd (buf,2);
}

unsigned int readTemperatur()
{
        int i = 0;
        P1_1 = 1;
        P1_2 = 0;
        P1_2 = 1;
        for (i = 0; i < 5000; i++)
        P1_1 = 0;
        return P2;
}

//-----------------------------------------------------------------------------
// Hauptprogramm
//-----------------------------------------------------------------------------
void main(void)
{
	Grundeinstellungen();		    //  Siehe Datei Einstellungen.h
    initlcd ();						//	Initialisierung LCD-Display an P3
 	loeschenlcd ();				    //	Anzeige löschen	
    init();

    P2MDOUT = 0;
    P2 = 255;
    P4 = 0;
    P1_0 = 0;


	while (1)
	{
		ausgabe();
        P4 = readTemperatur();
		if (!P3_1)				//Plus
		{
            if (selectedTemp <= (maxTemp - step))
            {
                selectedTemp += step;
            }
			while (!P3_1);		//Warten bis Taster losgelassen
		}

    
		if (!P3_2)				//Minus
		{
			if (selectedTemp >= (minTemp + step))
            {
                selectedTemp -= step;
            }
			while (!P3_2);		//Warten bis Taster losgelassen
		}
    
    
        // An / Aus
        if (!P3_3)
        {
           systemStatus = !systemStatus; 
           while (!P3_3);		//Warten bis Taster losgelassen
        }
	}

}