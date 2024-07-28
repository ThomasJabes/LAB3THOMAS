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
#include <stdint.h>
#include <stdlib.h>  // Para la función itoa
#include "SPI/SPI.h"
#include "UART/UART.h"

void setup() {
	// Inicializar SPI como maestro
	spiInit(SPI_MASTER_OSC_DIV16, SPI_DATA_ORDER_MSB, SPI_CLOCK_IDLE_LOW, SPI_CLOCK_FIRST_EDGE);
	// Inicializar UART para comunicación con la computadora
	SetupUART0(M9600);
	writeTextUART("UART Iniciada\r\n");
	
	// Configurar pines PC0, PC1, PC2, PC3, PC4, PC5 como salida
	DDRC |= (1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3) | (1 << DDC4) | (1 << DDC5);
	// Configurar pines PD5, PD6 como salida
	DDRD |= (1 << DDD5) | (1 << DDD6);
}

void setLEDs(uint8_t value) {
	// Establecer el estado de los LEDs de acuerdo al valor recibido
	PORTC = (value & 0x3F); // Los 6 bits menos significativos para PC0-PC5
	PORTD = (PORTD & 0x9F) | ((value & 0xC0) >> 1); // Los 2 bits más significativos para PD5 y PD6
}

void loop() {
	uint8_t potValue1, potValue2;
	char buffer[10];  // Buffer para convertir entero a cadena

	// Solicitar valor del primer potenciómetro
	spiWrite(0x01);
	_delay_ms(10);
	potValue1 = spiRead();
	
	// Convertir potValue1 a cadena y enviarla
	itoa(potValue1, buffer, 10);
	writeTextUART("Pot1: ");
	writeTextUART(buffer);
	writeTextUART("\r\n");
	
	// Solicitar valor del segundo potenciómetro
	spiWrite(0x02);
	_delay_ms(10);
	potValue2 = spiRead();
	
	// Convertir potValue2 a cadena y enviarla
	itoa(potValue2, buffer, 10);
	writeTextUART("Pot2: ");
	writeTextUART(buffer);
	writeTextUART("\r\n");
	
	// Leer entrada desde UART para controlar los LEDs
	if (UCSR0A & (1<<RXC0)) {  // Si hay datos disponibles en el buffer de recepción
		char inputBuffer[4] = {0};
		uint8_t inputIndex = 0;
		while (UCSR0A & (1<<RXC0)) {
			char receivedChar = UDR0;
			if (receivedChar >= '0' && receivedChar <= '9' && inputIndex < 3) {
				inputBuffer[inputIndex++] = receivedChar;
			}
		}
		if (inputIndex > 0) {
			uint8_t inputValue = atoi(inputBuffer);  // Convertir cadena a entero
			setLEDs(inputValue);  // Actualizar LEDs
			writeTextUART("Valor recibido: ");
			writeTextUART(inputBuffer);
			writeTextUART("\r\n");
		}
	}
	
	_delay_ms(1000);
}

int main(void) {
	setup();
	while (1) {
		loop();
	}
	return 0;
}

