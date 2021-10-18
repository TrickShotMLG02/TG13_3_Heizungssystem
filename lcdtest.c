/* lcdtest.c ******************************************************************************
 * 					Tests zur Ausgabe an das LCD-Display                                                                                                            *
 ******************************************************************************************
 *						zum Projekt gehört die Datei lcd.c im Ordner ..\hilf_c\ 
 ******************************************************************************************/

#include <stdio.h>									// für sprinf											
#include <C_8051F340.h>
#include <Einstellungen.h>

// externe Funktionen in lcd.c; Diese Datei zum Projekt hinzufügen
 extern void initlcd (void);						//	Initialisierung LCD-Display an P0			
 extern void loeschenlcd (void);
 extern void textlcd (unsigned char *text,unsigned char zeile);	
 
void main (void)
	{
	unsigned char buf [20] ;	    // Zwischenspeicher für LCD-Text
	unsigned char a,b,c;			// Variablen zum Testen der LCD-Ausgabe
    
    Grundeinstellungen();	
	initlcd ();						//	Initialisierung LCD-Display an P3
 	loeschenlcd ();				    //	Anzeige löschen	
    /*
 	textlcd ("   HGS-Singen",1);	//	Text ausgeben	Achtung " ", nicht  '  '	!	
 	sprintf (buf," Klasse TG13/3");	//	Test sprintf
	textlcd (buf,2);
    */    
	
	a = 26;							
	b = 45;
	c = a + b++;							
	sprintf (buf,"a = %d b = %d",a,b);
	// Text mit Variable formatieren und in buf kopieren		
	//	% Ausgabeformat folgt, d Dezimalzahl mit Vorzeichen, a auszugebende Variable	
	textlcd (buf,1);																															
	//	Ausgabe des Textpuffers an Zeile 1 des LCD-Displays													
  	sprintf (buf,"c = %d",c);	
  	textlcd (buf,2);																		
    
	while (1); 
	} 

