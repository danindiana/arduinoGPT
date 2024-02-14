import pyudev
import re

# Constants
ARDUINO_VENDOR_ID = "2341"

# Regular expression to match relevant attributes in device info
attribute_pattern = re.compile(r'ATTRS\{idVendor\}=="([\w]+)".*ATTRS\{idProduct\}=="([\w]+)"')

def find_arduino_devices():
    """Finds Arduino devices and extracts relevant attributes"""
    arduino_devices = []
    context = pyudev.Context()  # Create a udev context

    for device in context.list_devices(subsystem='usb'):
        print(f"Scanning device: {device.device_node}")
        # Search for vendor and product ID from direct attributes 
        if device.attributes.get('idVendor') == ARDUINO_VENDOR_ID:
            print(f"Found Arduino device: {device.device_node}")
            arduino_devices.append({
                'device_node': device.device_node,
                'vendor_id': device.attributes['idVendor'],
                'product_id': device.attributes['idProduct'],
            })

        # Sometimes attributes are nested within 'properties'
        for key, value in device.properties.items():
            match = attribute_pattern.match(value)
            if match and match.group(1) == ARDUINO_VENDOR_ID:
                print(f"Found Arduino device: {device.device_node}")
                arduino_devices.append({
                    'device_node': device.device_node,
                    'vendor_id': match.group(1),
                    'product_id': match.group(2),
                })

    return arduino_devices

if __name__ == "__main__":
    devices = find_arduino_devices()

    if devices:
        print("Found Arduino devices:")
        for device in devices:
            print("  Device Node: ", device['device_node'])
            print("  Vendor ID:   ", device['vendor_id'])
            print("  Product ID:  ", device['product_id'])
            print("-" * 20)
    else:
        print("No Arduino devices found.")
