/*
 Name:          Tim Schlachter / Anton Tran
 Klasse.        TG13/3
 Datum:         20.09.2021
 Aufgabe:   	Heizungssystem
 Controller:    C8051F340
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

//-----------------------------------------------------------------------------
// Hauptprogramm
//-----------------------------------------------------------------------------
void main(void)
{
	Grundeinstellungen();		    //siehe Datei Einstellungen.h
    initlcd ();						//	Initialisierung LCD-Display an P3
 	loeschenlcd ();				    //	Anzeige löschen	
    init();

	while (1)
	{
		ausgabe();

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