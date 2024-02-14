import psutil
import subprocess
import signal

def search_python_processes():
    """
    Searches for running Python processes using psutil library and attempts to
    capture and stream the output to the console.
    """
    python_process_count = 0  # Counter for the number of Python processes found
    print("Starting to search for Python processes...")

    for process in psutil.process_iter(['pid', 'name']):  # Include 'pid' in the properties
        try:
            if 'python' in process.info['name'].lower():  # Case-insensitive comparison
                python_process_count += 1
                print(f"Found Python process with PID: {process.info['pid']}")

                # Attempt to attach to the process and capture its output
                proc = subprocess.Popen(['strace', '-p', str(process.info['pid']), '-s', '9999', '-e', 'read,write'],
                                        stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
                try:
                    for line in proc.stdout:
                        print(line.decode('utf-8'), end='')  # Stream output to console
                except Exception as e:
                    print(f"Error streaming process output: {e}")
                finally:
                    proc.terminate()  # Terminate the Popen subprocess

        except (psutil.NoSuchProcess, psutil.AccessDenied, psutil.ZombieProcess) as e:
            print(f"Error with process iteration: {e}")
            continue  # Handle potential errors gracefully and continue the loop

    print(f"Search complete. Found {python_process_count} Python processes running.")

def handle_interrupt(signal, frame):
    """
    Handles Ctrl-C interrupt to terminate the program gracefully.
    """
    print("Received Ctrl-C, exiting...")
    exit(0)

if __name__ == "__main__":
    signal.signal(signal.SIGINT, handle_interrupt)  # Register signal handler
    search_python_processes()

    print("Entering infinite loop. Press Ctrl-C to exit.")
    try:
        while True:  # Simulate infinite loop for demonstration
            pass
    except KeyboardInterrupt:
        handle_interrupt()
