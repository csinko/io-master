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

ser = serial.Serial(port='COM7', baudrate=115200)

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
        self.cb=ttk.Combobox(win, values=values)
        self.cb.grid(column=clmn, row=row)
        self.cb.current(1)
        #self.cb.pack()

class Button:
    def __init__(self, win, text, clmn, row):
        self.btn=ttk.Button(win, text=text, command=self.press)
        self.btn.grid(column=clmn, row=row)

    def press(self):
        btn_text = self.btn.cget('text')
        if btn_text == "show results":
            OutputVariables = "Voltage: " + cb1.cb.get() + '\n' + "Frequency: " + cb2.cb.get() + '\n' + "Number: " + cb3.cb.get() + "\n" + "Color: " + cb4.cb.get() + '\n'
            txt.delete('1.0', END)
            txt.insert(TK.END, OutputVariables)
        if btn_text == "Push Color":
            #messagebox.showinfo("Works", "Pushed Color")
            selected_Color = cb4.cb.get()
            if selected_Color == "None":
                sendCommand('0')
            if selected_Color == "Red":
                sendCommand('2')
            if selected_Color == "Green":
                sendCommand('1')


        

#lbl1 = Label(window, "Voltage:", 0, 0)
#lbl2 = Label(window, "Frequency:", 0, 1)
#lbl3 = Label(window, "Number:", 0, 2)
lbl4 = Label(window, "Color:", 0, 3)

#cb1 = combobox(window, ["0V", "3.3V","5V", "10V"], 1, 0)
#cb2 = combobox(window, ["1kHz", "2kHz", "3kHz"], 1, 1)
#cb3 = combobox(window, ["0", "1"], 1, 2)
cb4 = combobox(window, ["None", "Red", "Green"], 1, 3)
#btn1 = Button(window, "show results", 2, 1)
btn2 = Button(window, "Push Color", 2, 3)

txt = TK.Text(window, height=10, width=35)
txt.grid(column=0, row=4, columnspan=3)

#dev = usb.core.find(idVendor=0xfffe, idProduct=0x0001)          #change addresses to match our device
#if dev is None:
#    raise ValueError('The device is not connnected')
#    messagebox.showinfo("Error", "No Device Connected")

    

def main():
    serialThread = threading.Thread(target=read_from_port, args=(ser,))
    serialThread.start()
    window.mainloop()

if (__name__ == '__main__'):
    main()
