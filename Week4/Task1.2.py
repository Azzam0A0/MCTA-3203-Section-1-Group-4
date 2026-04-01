import serial
import time
from collections import deque
import statistics

# -------- CONFIGURATION --------
SERIAL_PORT = 'COM6'   # <-- CHANGE THIS (e.g. 'COM7')
BAUD_RATE = 9600
# -------------------------------

# Buffers (store ~2 seconds of data)
history_x = deque(maxlen=40)
history_y = deque(maxlen=40)


def is_circular_motion(x_data, y_data):
    if len(x_data) < 10:
        return False

    # --- Step 1: Find center (mean) ---
    mean_x = statistics.mean(x_data)
    mean_y = statistics.mean(y_data)

    # Center the data
    centered = [(x - mean_x, y - mean_y) for x, y in zip(x_data, y_data)]

    # --- Step 2: Check amplitude (ignore small jitter) ---
    std_x = statistics.stdev(x_data)
    std_y = statistics.stdev(y_data)

    if std_x < 2000 or std_y < 2000:
        return False  # Not enough movement

    # --- Step 3: Check symmetry ---
    ratio = std_x / std_y if std_y != 0 else 0

    if ratio < 0.5 or ratio > 2.0:
        return False  # Not circular (too stretched)

    # --- Step 4: Check rotation using cross product ---
    cross_products = []

    for i in range(len(centered) - 1):
        x1, y1 = centered[i]
        x2, y2 = centered[i + 1]

        cross = x1 * y2 - y1 * x2
        cross_products.append(cross)

    # --- Step 5: Check consistent direction ---
    positive = sum(1 for c in cross_products if c > 0)
    negative = sum(1 for c in cross_products if c < 0)

    total = len(cross_products)

    if total == 0:
        return False

    if positive / total > 0.7 or negative / total > 0.7:
        return True

    return False


def main():
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)  # Allow Arduino to reset

    print("System ready. Move the MPU6050 in a circle to toggle the LED...")

    led_is_on = False  # Track LED state

    try:
        while True:
            raw = ser.readline().decode(errors='ignore').strip()

            if raw:
                parts = raw.split(',')

                if len(parts) >= 3:
                    try:
                        ax = int(parts[0])
                        ay = int(parts[1])

                        # Store data
                        history_x.append(ax)
                        history_y.append(ay)

                        # Only check when buffer is full
                        if len(history_x) == 40:
                            if is_circular_motion(history_x, history_y):

                                # Toggle LED state
                                led_is_on = not led_is_on

                                if led_is_on:
                                    print("Circle Detected! LED: ON")
                                    ser.write(b'O')
                                else:
                                    print("Circle Detected! LED: OFF")
                                    ser.write(b'F')

                                # -------- DEBOUNCE --------
                                history_x.clear()
                                history_y.clear()
                                # --------------------------

                    except ValueError:
                        pass  # Ignore bad data

    except KeyboardInterrupt:
        print("\nProgram stopped by user.")

    finally:
        ser.write(b'F')  # Ensure LED OFF
        ser.close()
        print("Serial connection closed.")


if __name__ == "__main__":
    main()