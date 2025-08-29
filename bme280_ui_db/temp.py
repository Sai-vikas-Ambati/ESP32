import serial
import csv
import time

# Configure the correct serial port for ESP32
ser = serial.Serial('COM7', 115200, timeout=1)
time.sleep(2)  # Allow connection to establish

# Open CSV file for writing
with open("bmp280_data.csv", "w", newline="") as file:
    writer = csv.writer(file)
    writer.writerow(["Timestamp", "Temperature (°C)", "Pressure (hPa)"])  # CSV Header

    print("Listening for ESP32 data...")

    while True:
        try:
            line = ser.readline().decode(errors='ignore').strip()  # Read serial data
            if line:  # Check if line is not empty
                values = line.split()  # Split by spaces
                if len(values) == 2:  # Expecting temperature and pressure
                    temperature, pressure = values  # Extract values
                    timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
                    writer.writerow([timestamp, temperature, pressure])  # Save values
                    file.flush()
                    print(f"Logged: {timestamp}, Temp: {temperature}°C, Pressure: {pressure} hPa")
        
        except KeyboardInterrupt:
            print("\nStopped by user.")
            break

ser.close()