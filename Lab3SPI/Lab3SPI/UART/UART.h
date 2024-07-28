#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

#define M9600 0

void SetupUART0(uint8_t MODO);
void writeTextUART(char *Texto);
void writeUART(char Caracter);
char recibir(void);

#endif /* UART_H_ */
