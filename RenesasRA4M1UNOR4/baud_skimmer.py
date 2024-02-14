import serial
import time

# List of common baud rates to test
COMMON_BAUD_RATES = [
    300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200
]

def heuristic_check(data):
    """
    Heuristic check to see if the data consists of mostly printable ASCII characters.
    This check should be adjusted based on expected data format from the Arduino.
    """
    # If you receive messages with a certain format/structure from your Arduino, implement that check here.
    printable_count = sum(c < 127 and c > 31 for c in data)
    return printable_count > len(data) * 0.7  # Example: 70% of the characters should be printable

def detect_baud_rate(port_name, timeout=2):
    """
    Try to auto-detect the baud rate for the given port by reading data at
    various baud rates and applying a heuristic check to the data.
    """
    for baud_rate in COMMON_BAUD_RATES:
        try:
            with serial.Serial(port_name, baud_rate, timeout=timeout) as ser:
                print(f"Trying baud rate: {baud_rate}...")
                time.sleep(2)  # Wait for data to accumulate
                data = ser.read(ser.in_waiting or 100)
                if heuristic_check(data):
                    print(f"Data received at baud rate {baud_rate} looks coherent.")
                    return baud_rate
        except serial.SerialException as e:
            print(f"Error when checking baud rate {baud_rate}: {e}")
    return None

def read_from_arduino(port_name, baud_rate):
    # Implementation remains the same as earlier
    ...

if __name__ == "__main__":
    port_name = "/dev/ttyACM1"  # Change this to your Arduino's port
    detected_baud_rate = detect_baud_rate(port_name)

    if detected_baud_rate:
        print(f"Detected baud rate: {detected_baud_rate}")
        read_from_arduino(port_name, detected_baud_rate)
    else:
        print("Failed to detect a coherent baud rate.")
