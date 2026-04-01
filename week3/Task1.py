import serial
import time

# -- Replace 'COMx' with your Arduino's serial port
ser = serial.Serial('COM6', 9600)
time.sleep(2)  # Wait for Arduino to reset

print("Running... Press CTRL+C to stop.")

try:
    while True:
        line = ser.readline().decode().strip()
        if "/" in line:
            try:
                # Parse Arduino data
                data = line.split("/")
                voltage = float(data[0])
                adc_value = int(data[1].replace("ADC:", "").strip())
                resistance = float(data[2].replace("R:", "").strip())

                print(f"Voltage: {voltage:.2f} V | ADC: {adc_value} | Resistance: {resistance:.2f} Ω")

                # LED Control Logic
                if adc_value > (1023 / 2):
                    ser.write(b"LED ON\n")
                else:
                    ser.write(b"LED OFF\n")
            except Exception as e:
                print("Parsing Error:", line, "->", e)

except KeyboardInterrupt:
    print("\nStopped by user.")
finally:
    ser.close()
    print("Serial connection closed.")
