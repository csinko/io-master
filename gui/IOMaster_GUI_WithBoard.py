import tkinter as TK
import usb.core
import usb.util
import serial
import time
import threading
from tkinter import *
from tkinter import ttk
from tkinter import messagebox


window = TK.Tk()
window.title("IO Master Setup")
window.geometry("500x300")

ser = serial.Serial(port='/dev/ttyACM1', baudrate=115200)

def read_from_port(ser):
    while True:
        reading = ser.read()
        print(reading)
        if reading == b'3':
            messagebox.showinfo("Works", "Pushed Button")

def sendCommand(command):
    ser.write(command.encode('ascii', 'ignore'))

class Label:
    def __init__(self, win, text, clmn, row):
        self.lbl=ttk.Label(win, text=text)
        self.lbl.grid(column=clmn, row=row)

class combobox:
    def __init__(self, win, values, clmn, row):
        self.cb=ttk.Combobox(win, values=values, state = "readonly")
        self.cb.grid(column=clmn, row=row)
        self.cb.current(1)

class Button:
    def __init__(self, win, text, clmn, row):
        self.btn=ttk.Button(win, text=text, command=self.press)
        self.btn.grid(column=clmn, row=row)

    def press(self):
        btn_text = self.btn.cget('text')

        #Push Actions for "Configure" Button
        if btn_text == "Configure":
            OutputVariables = "Protocol: " + cb0.cb.get() + '\n' + "Voltage: " + cb1.cb.get() + '\n' + "Frequency: " + cb2.cb.get() + "\n"
            OutConfigTxt.configure(state="normal")
            OutConfigTxt.delete('1.0', END)
            OutConfigTxt.insert(TK.END, OutputVariables)
            OutConfigTxt.configure(state="disable")

            protocol = cb0.cb.get()
            voltage = cb1.cb.get()
            frequency = cb2.cb.get()

            if voltage == "3.3V":
                sendCommand('v0')
            if voltage == "5V":
                sendCommand('v1')
            if voltage == "12V":
                sendCommand('v2')
            if voltage == "24V":
                sendCommand('v3')
            
            #Wait for OKAY (z) before moving on

            if frequency == "1kHZ":
                sendCommand('f0')
            if frequency == "10kHZ":
                sendCommand('f1')
            if frequency == "100kHZ":
                sendCommand('f2')            
            if frequency == "1MHZ":
                sendCommand('f3')

            #wait for OKAY before finishing loop. (exit as necessary)

        #Push Actions for "Send Data" Button
        if btn_text == "Send Data":
            dataToSend = DataText.get('1.0', END)
            dataToSend = dataToSend.rstrip()
            for letter in dataToSend:
                if letter is not '0' and letter is not '1':
                    messagebox.showinfo("Error", "Invalid Data.\n Os and 1s Only")
                    return
            if dataToSend == '\n':
                messagebox.showinfo("Error", "Please Enter Data to Send.\n Os and 1s Only")
                return
            if len(dataToSend) is not 8:
                messagebox.showinfo("Error", "Invalid Data.\n Should be 8 bits long.\n Os and 1s Only")
                return
            dataToSend = 's' + dataToSend + '\0'
            OutConfigTxt.configure(state="normal")
            OutConfigTxt.delete('1.0', END)
            OutConfigTxt.insert(TK.END, "Data Sent: " + dataToSend.rstrip() + '\n' + str(len(dataToSend.rstrip())))
            OutConfigTxt.configure(state="disable")

            sendCommand(dataToSend)        #send command to the board

#Character Input Validation
def only_numbers(char):
    return char.isdigit()

validation = window.register(only_numbers)
entry = TK.Entry(window, validate="key", validatecommand=(validation, '%S'))

#declare Visual Components        
lbl0 = Label(window, "Protocol", 0, 0)
lbl1 = Label(window, "Voltage:", 0, 1)
lbl2 = Label(window, "Frequency:", 0, 2)
lbl3 = Label(window, "Data to Send:", 0, 3)

cb0 = combobox(window, ["I2C", "UART", "SPI", "SWD", "RS-485"], 1, 0)
cb0.cb.current(2)                                                                       #Set to SPI
cb0.cb.configure(state = "disabled")                                                    #Only want SPI For now
cb1 = combobox(window, ["3.3V","5V", "12V", "24V" ], 1, 1)
cb2 = combobox(window, ["1kHz", "10kHz", "100kHz", "1MHz"], 1, 2)

btn1 = Button(window, "Configure", 2, 1)                                                #Send configure Data
btn2 = Button(window, "Send Data", 2, 3)                                                #Send Input Data

DataText = TK.Text(window, height=1, width=17)                                          #Box to input Binary Data to send
DataText.grid(column=1, row=3)

OutConfigTxt = TK.Text(window, height = 5, width = 36, state = "disabled")              #Display sent configurables in this box
OutConfigTxt.grid(column=0, row=6, columnspan=3)      


def main():
    serialThread = threading.Thread(target=read_from_port, args=(ser,))
    serialThread.start()
    window.mainloop()

if (__name__ == '__main__'):
    main()
