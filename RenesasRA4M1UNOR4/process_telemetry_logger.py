import psutil
import signal
import logging
import subprocess
import threading
from logging.handlers import RotatingFileHandler, TimedRotatingFileHandler


logging.basicConfig(level=logging.INFO, 
                    format='%(asctime)s - %(levelname)s - PID:%(process)d - Message:%(message)s',
                    handlers=[RotatingFileHandler('process_monitor.log', maxBytes=1024*1024, backupCount=5), logging.StreamHandler()]
                   )

def stream_output(process, device_stamp):
    """
    Streams the output of a subprocess to logging framework.
    """
    while True:
        output = process.stdout.readline()
        if output == '' and process.poll() is not None:
            break
        if output:
            logging.info(f"{device_stamp} - OUT: {output.strip()}")

    process.stdout.close()
    return_code = process.wait()
    if return_code:
        logging.error(f"{device_stamp} - Subprocess exited with return code {return_code}")

def stream_process_telemetry(process, device_stamp):
    """
    Logs telemetry data of a process specified by the process object.
    """
    try:
        with process.oneshot():
            name = process.name()
            cpu_times = process.cpu_times()
            memory_info = process.memory_info()
            cmdline = " ".join(process.cmdline())
            
            logging.info(f"{device_stamp} - Telemetry start")
            logging.info(f"{device_stamp} - Name: {name}")
            logging.info(f"{device_stamp} - CPU Times: User={cpu_times.user}, System={cpu_times.system}")
            logging.info(f"{device_stamp} - Memory Usage: RSS={memory_info.rss}, VMS={memory_info.vms}")
            logging.info(f"{device_stamp} - Command Line: {cmdline}")
            logging.info(f"{device_stamp} - Telemetry end")
    except (psutil.NoSuchProcess, psutil.AccessDenied) as e:
        logging.error(f"{device_stamp} - Error accessing process: {e}")

def search_python_processes():
    """
    Searches for running Python processes, launches a subprocess for each,
    and streams their output while logging telemetry data.
    """
    python_process_count = 0  # Counter for the number of Python processes found
    logging.info("Starting to search for Python processes...")

    for process in psutil.process_iter(['pid', 'name', 'cpu_times', 'memory_info', 'cmdline']):
        if 'python' in process.info['name'].lower():
            python_process_count += 1
            pid = process.pid
            device_stamp = f"Device_P-{pid}"

            stream_process_telemetry(process, device_stamp)

            # Dummy subprocess creation for demonstration purposes
            subprocess_example = subprocess.Popen(["python3", "-u", "-c", f"print('Hello from {device_stamp}')"],
                                                  stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
            thread = threading.Thread(target=stream_output, args=(subprocess_example, device_stamp,))
            thread.start()

    logging.info(f"Search complete. Found {python_process_count} Python processes running.")

def handle_interrupt(signal, frame):
    """
    Handles Ctrl-C interrupt to terminate the program gracefully.
    """
    logging.info("Received Ctrl-C, exiting...")
    exit(0)

if __name__ == "__main__":
    signal.signal(signal.SIGINT, handle_interrupt)
    search_python_processes()
