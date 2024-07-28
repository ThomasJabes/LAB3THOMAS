#*Universidad del Valle de Guatemala 
 # Interfaz
 # IE3054 Electronica Digital 2
 # Created: 20/07/2024 13:01:49
 # Author: Thomas 21626
 

import tkinter as tk
import serial
import time

# Configuración de la comunicación serial
ser = serial.Serial('COM14', 9600, timeout=1)  # Asegúrate de usar el puerto correcto
time.sleep(2)  # Esperar a que la conexión se establezca

def update_values():
    ser.write(b'R')  # Solicitar valores de los potenciómetros
    line = ser.readline().decode('utf-8').strip()
    print(f"Received line: {line}")  # Depuración: mostrar la línea recibida
    if line:
        try:
            # Extraer y procesar los valores de los potenciómetros
            if line.startswith("Pot1: "):
                pot1_raw = int(line.replace("Pot1: ", "").strip())
                pot1_voltage = (pot1_raw / 255.0) * 5.0
                pot1_label.config(text=f"Pot1: {pot1_voltage:.2f} V")
                print(f"Pot1 Voltage: {pot1_voltage:.2f} V")  # Depuración
            elif line.startswith("Pot2: "):
                pot2_raw = int(line.replace("Pot2: ", "").strip())
                pot2_voltage = (pot2_raw / 255.0) * 5.0
                pot2_label.config(text=f"Pot2: {pot2_voltage:.2f} V")
                print(f"Pot2 Voltage: {pot2_voltage:.2f} V")  # Depuración
            else:
                print("Received line format is incorrect.")  # Depuración
        except Exception as e:
            print(f"Error parsing line: {line}")
            print(e)
    else:
        print("No line received.")  # Depuración
    root.after(1000, update_values)  # Actualizar cada segundo

def send_value():
    value = entry_value.get()
    if value.isdigit() and 0 <= int(value) <= 255:
        ser.write(value.encode())
        entry_value.delete(0, tk.END)
        entry_value.insert(0, "Enviado")

# Crear la ventana principal
root = tk.Tk()
root.title("Interfaz Gráfica")

# Crear y organizar los widgets
pot1_label = tk.Label(root, text="Pot1: 0.00V")
pot1_label.pack(pady=5)

pot2_label = tk.Label(root, text="Pot2: 0.00V")
pot2_label.pack(pady=5)

entry_value = tk.Entry(root)
entry_value.pack(pady=5)
entry_value.insert(0, "Ingrese un valor (0-255)")

send_button = tk.Button(root, text="Enviar", command=send_value)
send_button.pack(pady=5)

# Iniciar la actualización de los valores de los potenciómetros
root.after(1000, update_values)

# Iniciar el loop de la interfaz gráfica
root.mainloop()

# Cerrar la comunicación serial al salir
ser.close()


