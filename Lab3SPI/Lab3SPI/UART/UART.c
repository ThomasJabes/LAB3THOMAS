#include "UART.h"

void SetupUART0(uint8_t MODO) {
	if (MODO == M9600) {
		// Paso 1: RX como entrada y TX como salida
		DDRD &= ~(1<<DDD0);
		DDRD |= (1<<DDD1);

		// Paso 2: Configuración UCSR0A
		UCSR0A = 0;

		// Paso 3: Configuración UCSR0B, habilitamos RX y TX
		UCSR0B = (1<<RXEN0) | (1<<TXEN0);

		// Paso 4: Configuración UCSR0C, Asíncrono, paridad: None, 1 bit de stop, 8 bits de datos
		UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);

		// Paso 5: Configuración velocidad de baudrate: 9600
		UBRR0 = 103;
	}
}

void writeTextUART(char *Texto) {
	for (int i = 0; Texto[i] != '\0'; i++) {
		while (!(UCSR0A & (1<<UDRE0)));
		UDR0 = Texto[i];
	}
}

void writeUART(char Caracter) {
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = Caracter;
}
