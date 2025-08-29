import serial
import csv
import time

# Change 'COM3' to your ESP32 port
ser = serial.Serial('COM3', 115200, timeout=1)
time.sleep(2)  # Allow connection to establish

# Open CSV file for writing
with open("mpu6050_data.csv", "w", newline="") as file:
    writer = csv.writer(file)
    writer.writerow(["Timestamp", "Ax", "Ay", "Az", "Gx", "Gy", "Gz"])  # CSV Header

    print("Listening for MPU6050 data...")

    while True:
        try:
            line = ser.readline().decode(errors='ignore').strip()  # Read serial data
            if line:  # Check if line is not empty
                values = line.split()  # Split by spaces
                if len(values) == 6:  # Expecting 6 values (Ax, Ay, Az, Gx, Gy, Gz)
                    ax, ay, az, gx, gy, gz = values  # Extract values
                    timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
                    writer.writerow([timestamp, ax, ay, az, gx, gy, gz])  # Save values
                    file.flush()
                    print(f"Logged: {timestamp}, Ax: {ax}, Ay: {ay}, Az: {az}, Gx: {gx}, Gy: {gy}, Gz: {gz}")

        except KeyboardInterrupt:
            print("\nStopped by user.")
            break

ser.close()
