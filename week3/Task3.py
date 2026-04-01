import serial
import matplotlib.pyplot as plt
import time

# -- Replace 'COMx' with your Arduino's actual serial port (e.g., 'COM3')
ser = serial.Serial('COM6', 9600)
time.sleep(2)  # Wait for Arduino to reset

plt.ion()  # Interactive mode for real-time plotting
fig, ax = plt.subplots()
x_vals, y_vals = [], []

print("Plotting real-time servo angles. Press CTRL+C in the terminal to stop.")

try:
    while True:
        raw = ser.readline().decode().strip()

        # Check if the incoming data is a valid number
        if raw.isdigit():
            angle = int(raw)
            print(f"Servo Angle: {angle}°")

            x_vals.append(len(x_vals))
            y_vals.append(angle)

            # Update the plot
            ax.clear()
            ax.set_ylim(0, 180)
            ax.set_title("Real-Time Servo Angle Plot")
            ax.set_xlabel("Samples")
            ax.set_ylabel("Angle (°)")
            ax.plot(x_vals, y_vals)
            plt.pause(0.05)

except KeyboardInterrupt:
    print("\nSending stop command to Arduino...")
    # Send the stop signal to the Arduino
    ser.write(b'x')
    time.sleep(1)
finally:
    ser.close()
    plt.ioff()  # Turn off interactive mode
    plt.show()  # Display the final static plot
    print("Serial connection closed.")
