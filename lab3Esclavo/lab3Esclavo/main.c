/*Universidad del Valle de Guatemala 
 * main.c
 * IE3054 Electronica Digital 2
 *	Laboratorio 3
 * Created: 27/07/2024 1:01:49
 *  Author: Thomas 21626
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "SPI/SPI.h"
#include "ADC/ADC.h"

void setup() {
	// Inicializar SPI como esclavo
	spiInit(SPI_SLAVE_SS, SPI_DATA_ORDER_MSB, SPI_CLOCK_IDLE_LOW, SPI_CLOCK_FIRST_EDGE);
	// Inicializar ADC para leer los valores de los potenciómetros
	SetupADC(PC4); // A4
	SetupADC(PC5); // A5
}

uint8_t readADC(uint8_t channel) {
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC));
	return ADCH;
}

int main(void) {
	setup();
	uint8_t potValue1, potValue2;
	
	while (1) {
		if (spiDataReady()) {
			uint8_t command = spiRead();
			if (command == 0x01) {
				potValue1 = readADC(PC4); // Leer potenciómetro en A4
				spiWrite(potValue1);
				} else if (command == 0x02) {
				potValue2 = readADC(PC5); // Leer potenciómetro en A5
				spiWrite(potValue2);
			}
		}
	}
	
	return 0;
}
