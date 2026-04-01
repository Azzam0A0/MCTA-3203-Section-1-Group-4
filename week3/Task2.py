import serial

"""
Define the serial port and baud rate
(adjust the port COMx as per your Arduino, e.g., 'COM3' or 'COM7')
"""
ser = serial.Serial('COM6', 9600)

try:
    while True:
        angle_input = input("Enter servo angle (0-180 deg, or 'q' to quit): ")

        if angle_input.lower() == 'q':
            break

        try:
            angle = int(angle_input)
            if 0 <= angle <= 180:
                # Send the servo's angle to the Arduino with a newline
                ser.write((str(angle) + '\n').encode())
            else:
                print("Angle must be between 0 and 180 degrees.")
        except ValueError:
            print("Invalid input. Please enter a valid number or 'q' to quit.")

except KeyboardInterrupt:
    pass  # Handle keyboard interrupt (CTRL+C)
finally:
    ser.close()  # Close the serial connection
    print("Serial connection closed.")
