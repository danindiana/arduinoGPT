import serial
import subprocess

def scan_devices():
    """Scans for potential Arduino devices."""
    devices = subprocess.check_output('ls /dev/tty*', shell=True)
    devices = devices.decode().split('\n')
    arduino_devices = []
    for device in devices:
        if 'ACM' in device or 'USB' in device:
            arduino_devices.append(device)
    return arduino_devices

def capture_output(device):
    """Captures and saves output from the selected Arduino device."""
    ser = serial.Serial(device, 115200)  # Ensure the baud rate matches your Arduino
    with open('output.txt', 'w') as f:
        while True:
            try:
                line = ser.readline().decode('utf-8').strip()
                if line:
                    f.write(line + "\n")
                    print(line)  # Display the output on the console
            except KeyboardInterrupt:
                print("Exiting...")
                break

def main():
    """Prompts the user for device selection and begins capturing."""
    devices = scan_devices()
    if not devices:
        print("No Arduino devices found.")
        return

    print("Found Arduino devices:")
    for i, device in enumerate(devices):
        print(f"{i+1}. {device}")

    while True:  # Input validation loop
        try:
            choice = int(input("Enter the number of the device to capture (or 0 to exit): "))
            if 0 <= choice <= len(devices):
                break
            else:
                print("Invalid choice. Please try again.")
        except ValueError:
            print("Invalid input. Please enter a number.")

    if choice == 0:  # User chose to exit
        print("Exiting...")
    else:
        capture_output(devices[choice - 1])  

if __name__ == "__main__":
    main()
