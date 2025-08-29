import serial
import csv
import time

# Configure Serial Port (Change COMx to match your ESP32 port)
ser = serial.Serial('COM3', 115200, timeout=1)  # Change 'COM3' to your correct port
time.sleep(2)  # Allow connection to establish

# Open CSV file for writing
with open("dht11_data.csv", "w", newline="") as file:
    writer = csv.writer(file)
    writer.writerow(["Timestamp", "Temperature (°C)", "Humidity (%)"])  # CSV Header

    print("Listening for ESP32 DHT11 data...")

    while True:
        try:
            line = ser.readline().decode(errors='ignore').strip()  # Read serial data
            if line:  # Check if line is not empty
                if "Temperature" in line and "Humidity" in line:  # Ensure correct format
                    parts = line.split(", ")  # Example: "Temperature: 25.3 °C, Humidity: 60.2 %"
                    
                    try:
                        temperature = float(parts[0].split(": ")[1].split(" ")[0])  # Extract temperature
                        humidity = float(parts[1].split(": ")[1].split(" ")[0])  # Extract humidity
                        timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
                        writer.writerow([timestamp, temperature, humidity])  # Save values
                        file.flush()
                        print(f"Logged: {timestamp}, Temp: {temperature}°C, Humidity: {humidity}%")
                    except (IndexError, ValueError):
                        print("Parsing error: Invalid data format")
        
        except KeyboardInterrupt:
            print("\nStopped by user.")
            break

ser.close()
