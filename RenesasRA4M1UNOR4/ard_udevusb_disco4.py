import pyudev
import re
import serial
import serial.tools.list_ports

# Constants
ARDUINO_VENDOR_ID = "2341"
BAUD_RATE = 115200  # Set this to the baud rate of your Arduino program

def find_arduino_serial_ports():
    """Find and return a list of serial port names associated with Arduino devices."""
    arduino_ports = []
    # Get a list of all connected USB serial devices
    ports = serial.tools.list_ports.comports()
    for port in ports:
        if port.vid is not None and hex(port.vid) == hex(int(ARDUINO_VENDOR_ID, 16)):
            arduino_ports.append(port.device)
    return arduino_ports

def read_from_arduino(port_name):
    """Attempt to access a given Arduino serial port and read its output."""
    try:
        # Open the serial port
        with serial.Serial(port_name, BAUD_RATE, timeout=1) as ser:
            print(f"Opened {port_name}, reading data... (press Ctrl+C to stop)")
            while True:
                line = ser.readline().decode('utf-8').rstrip()
                if line:
                    print(f"Read: {line}")
    except serial.SerialException as e:
        print(f"Error accessing {port_name}: {e}")
    except KeyboardInterrupt:
        print(f"Stopped reading from {port_name}.")

def main_menu(arduino_ports):
    """Main menu that allows the user to choose an Arduino device to read from."""
    print("Available Arduino devices:")
    for idx, port in enumerate(arduino_ports):
        print(f"{idx + 1}: {port}")

    selected = input("Select the device you want to read from (enter the number): ")

    try:
        selected_idx = int(selected) - 1
        if selected_idx < 0 or selected_idx >= len(arduino_ports):
            raise ValueError("Invalid selection")
        read_from_arduino(arduino_ports[selected_idx])
    except ValueError as e:
        print(f"Invalid input. Please run the program again and select a valid device number.")

if __name__ == "__main__":
    arduino_ports = find_arduino_serial_ports()
    if arduino_ports:
        main_menu(arduino_ports)
    else:
        print("No Arduino devices found with a serial port.")
