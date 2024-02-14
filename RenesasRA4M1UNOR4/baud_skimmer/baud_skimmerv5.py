import serial
print(serial.__file__)
#import pyserial
#print(pyserial.__file__)
import time
import pyudev
import re
import serial.tools.list_ports
import logging
import sys
print(sys.path)



# Configure logging
logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)

# Create a file handler which logs even debug messages
fh = logging.FileHandler('serial_monitor.log')
fh.setLevel(logging.DEBUG)

# Create console handler with a higher log level
ch = logging.StreamHandler()
ch.setLevel(logging.ERROR)

# Create formatter and add it to the handlers
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
fh.setFormatter(formatter)
ch.setFormatter(formatter)

# Add the handlers to the logger
logger.addHandler(fh)
logger.addHandler(ch)

# ... (rest of your constants and heuristic_check function)

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
                logger.info(f"Trying baud rate: {baud_rate}...")
                time.sleep(2)  # Wait for data to accumulate
                data = ser.read(ser.in_waiting or 100)
                if heuristic_check(data):
                    logger.info(f"Data received at baud rate {baud_rate} looks coherent.")
                    return baud_rate
        except serial.SerialException as e:
            logger.error(f"Error when checking baud rate {baud_rate}: {e}")
    return None

# ... (rest of your functions and main function)

def find_arduino_serial_ports():
    """Find and return a list of serial port names associated with Arduino devices."""
    arduino_ports = []
    # Get a list of all connected USB serial devices
    ports = serial.tools.list_ports.comports()
    for port in ports:
        if port.vid is not None and hex(port.vid) == hex(int("2341", 16)):
            arduino_ports.append(port.device)
    return arduino_ports


def read_from_arduino(port_name, baud_rate):
    """Attempt to access a given Arduino serial port and read its output."""
    try:
        # Open the serial port
        with serial.Serial(port_name, baud_rate, timeout=1) as ser:
            logger.info(f"Opened {port_name}, reading data... (press Ctrl+C to stop)")
            while True:
                line = ser.readline().decode('utf-8').rstrip()
                if line:
                    logger.debug(f"Read: {line}") 
    except serial.SerialException as e:
        logger.error(f"Error accessing {port_name}: {e}")
    except KeyboardInterrupt:
        logger.info(f"Stopped reading from {port_name}.")

def main_menu(arduino_ports):
    """Main menu that allows the user to choose an Arduino device to read from."""
    logger.debug("Available Arduino devices: " + str(arduino_ports))  # Debug available devices

    # ... (The rest of your main_menu function remains the same)

    """Main menu that allows the user to choose an Arduino device to read from."""
    print("Available Arduino devices:")
    for idx, port in enumerate(arduino_ports):
        print(f"{idx + 1}: {port}")

    selected = input("Select the device you want to read from (enter the number): ")

    try:
        selected_idx = int(selected) - 1
        if selected_idx < 0 or selected_idx >= len(arduino_ports):
            raise ValueError("Invalid selection")
        detected_baud_rate = detect_baud_rate(arduino_ports[selected_idx])
        if detected_baud_rate:
            print(f"Detected baud rate: {detected_baud_rate}")
            read_from_arduino(arduino_ports[selected_idx], detected_baud_rate)
        else:
            print("Failed to detect a coherent baud rate.")
    except ValueError as e:
        print(f"Invalid input. Please run the program again and select a valid device number.")


if __name__ == "__main__":
    arduino_ports = find_arduino_serial_ports()
    if arduino_ports:
        main_menu(arduino_ports)
    else:
        print("No Arduino devices found with a serial port.")
