/*Universidad del Valle de Guatemala 
 * ADC.c
 * IE3054 Electronica Digital 2
 *	Laboratorio 3
 * Created: 27/07/2024 1:01:49
 *  Author: Thomas 21626
 */ 

#include "ADC.h"

void SetupADC(uint8_t PinADC){
	switch (PinADC)
	{
		case PC0 :
		DIDR0 |= (1<<ADC0D);
		ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2));
		break;
		case PC1 :
		ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2));
		ADMUX|=(1<<MUX0);
		DIDR0 |= (1<<ADC1D);
		break;
		case PC2 :
		ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2));
		ADMUX|=(1<<MUX1);
		DIDR0 |= (1<<ADC2D);
		break;
		case PC3 :
		ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2));
		ADMUX|=(1<<MUX0)|(1<<MUX1);
		DIDR0 |= (1<<ADC3D);
		break;
		case PC4 :
		ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2));
		ADMUX|=(1<<MUX2);
		DIDR0 |= (1<<ADC4D);
		break;
		case PC5 :
		ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2));
		ADMUX|=(1<<MUX2)|(1<<MUX0);
		DIDR0 |= (1<<ADC5D);
		break;
		case PC6 :
		ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2));
		ADMUX|=(1<<MUX2)|(1<<MUX1);
		break;
		case PC7 :
		ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2));
		ADMUX|=(1<<MUX2)|(1<<MUX1)|(1<<MUX0);
		break;
	}
	// JUSTIFICACION IZQUIERDA
	ADMUX |= (1<<ADLAR);
	// REFERENCIA INTERNA
	ADMUX |= (1<<REFS0);
	// HABILITAR INTERRUPCION
	ADCSRA |= (1<<ADIE);
	// PRESCALER 128
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	// HABILITAR
	ADCSRA |= (1<<ADEN);
}

uint16_t ADC_Read(uint8_t channel) {
	// Seleccionar el canal de entrada ADC (de 0 a 7):
	// - Limpiar los 3 bits inferiores de ADMUX
	// - Establecer los bits del canal en ADMUX
	ADMUX = (ADMUX & 0xF8) | (channel & 0x07);

	// Iniciar la conversión ADC:
	// - Establecer bit ADSC (ADC Start Conversion)
	ADCSRA |= (1 << ADSC);

	// Esperar a que la conversión se complete:
	// - El bit ADSC se limpia cuando la conversión está completa
	while (ADCSRA & (1 << ADSC));

	// Leer y retornar el resultado (ADC es de 10 bits):
	return ADC;
}
