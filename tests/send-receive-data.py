import threading
import serial
import queue
import time

isConnected = False
port = '/dev/ttyACM0'
baud = 9600

serial_port = serial.Serial(port, baud, timeout = 0)

def handle_data(data):
    print(data)

def read_from_port(ser):
    while not isConnected:
        connected = True
        while True:
            print("test")
            reading = ser.readline().decode()
            handle_data(reading)


def read_keyboard_input(inputQueue):
    print("Ready for keyboard input:")
    while(True):
        input_str = input()
        inputQueue.put(input_str)


def main():
    EXIT_COMMAND = "exit"
    inputQueue = queue.Queue()
    inputThread = threading.Thread(target=read_keyboard_input, args=(inputQueue,), daemon=True)
    serialThread = threading.Thread(target=read_from_port, args=(serial_port,))
    inputThread.start()
    serialThread.start()

    while (True):
        if (inputQueue.qsize() > 0):
            input_str = inputQueue.get()
            print("input_str = {}".format(input_str))
            if (input_str == EXIT_COMMAND):
                print("Exiting serial terminal.")
                break

        time.sleep(0.01)
    print("End.")

if (__name__ == '__main__'):
    main()
