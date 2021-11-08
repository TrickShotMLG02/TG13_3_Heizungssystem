/*
 Name:          Tim Schlachter / Anton Tran
 Klasse.        TG13/3
 Datum:         20.09.2021 - 08.11..2021
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
    - ADC 1 bit änderung = 1° Änderung
	https://sensorkit.joy-it.net/de/sensors/ky-013
 */

 /*
 Portbelegung:
    P0: LCD
    P1: Steuerleitung ADC
    P2: Datenleitung ADC
    P3: Taster
    P4: Rote LED: P4_6 Blaue LED: P4_7
 */

 //-----------------------------------------------------------------------------
 // Include Dateien
 //-----------------------------------------------------------------------------
#include <stdio.h>					    // für sprinf		
#include <C_8051F340.h>                 //Erweiterte SFR Zuordnungen
#include <Einstellungen.h>              //beinhaltet die Funktion Grundeinstellungen


//-----------------------------------------------------------------------------
// Pin/Port Zuweisungen
//-----------------------------------------------------------------------------
unsigned char buf [20] ;	        // Zwischenspeicher für LCD-Text

unsigned char systemStatus = 1;     // Systemstatus: 1 -> an, 0 -> aus

int step = 1;                       // Schrittgrösse

int currentTemp = 21;               // Derzeitige Temperatur 
int selectedTemp = 21;              // Ausgewählte Temperatur 

int minTemp = 15;                   // Untere Temperaturgrenze
int maxTemp = 25;                   // Obere Temperaturgrenze

unsigned int i = 0;                 // ReadTemperatur CounterVariable


//-----------------------------------------------------------------------------
// Eigene Funktionen
//-----------------------------------------------------------------------------

// externe Funktionen in lcd.c; Diese Datei zum Projekt hinzufügen
extern void initlcd (void);         			//	Initialisierung LCD-Display an P0			
extern void loeschenlcd (void);
extern void textlcd (unsigned char *text,unsigned char zeile);

void init(void)
{
	selectedTemp = 21;
    systemStatus = 1;
}

void ausgabe(void)
{
    //LCD Display
    sprintf (buf,"Temperatur: %d",currentTemp);
	// Text mit Variable formatieren und in buf kopieren		
	//	% Ausgabeformat folgt, d Dezimalzahl mit Vorzeichen, a auszugebende Variable	
	textlcd (buf,1);

    if (systemStatus == 0)
    {
        sprintf (buf,"Sollwert: %d OFF",selectedTemp);
        textlcd (buf,2);
    }
    else
    {
        sprintf (buf,"Sollwert: %d ON ",selectedTemp);
        textlcd (buf,2);
    }
  	
}

unsigned int readTemperatur()
{
    int i = 0;
    P1_1 = 1;
    P1_2 = 0;
    P1_2 = 1;
    for (i = 0; i < 5000; i++)
    P1_1 = 0;
    
    
    //Calculate Temperature From ADC Signal
    //0b11100001: 4,72V (25°) - 0b11101011:  4,96V (15°)
    currentTemp = 250 - P2;
    //return currentTemp;
    
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
        P4 = P2;
		if (!P3_0)				//Plus
		{
            if (selectedTemp <= (maxTemp - step))
            {
                selectedTemp += step;
            }
			while (!P3_0);		//Warten bis Taster losgelassen
		}
     
		if (!P3_1)				//Minus
		{
			if (selectedTemp >= (minTemp + step))
            {
                selectedTemp -= step;
            }
			while (!P3_1);		//Warten bis Taster losgelassen
		}
    
        // An / Aus
        if (!P3_2)
        {
           systemStatus = !systemStatus; 
           while (!P3_2);		//Warten bis Taster losgelassen
        }
    
        if (systemStatus == 1)
        {
            P4 = 0b01111111;
            if (currentTemp > selectedTemp)
                P4 = 0b01111111;
            else if (currentTemp < selectedTemp)
                P4 = 0b10111111;
        }
        else
            P4 = 255;
	}
}