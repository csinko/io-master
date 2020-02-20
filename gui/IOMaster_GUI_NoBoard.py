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
window.geometry("400x500")

tabControl = ttk.Notebook(window)
sendTab = ttk.Frame(tabControl)
receiveTab = ttk.Frame(tabControl)
tabControl.add(sendTab, text= 'Send')
tabControl.add(receiveTab, text='Receive')
tabControl.grid(column=0, row=1, columnspan=2) #expand=1, fill="both")

#def refresh(eventObject):
    #insert code to reload the window

#ser = serial.Serial(port='COM8', baudrate=115200)

#def read_from_port(ser):
#    while True:
#        reading = ser.read()
#        print(reading)
#        if reading == b'3':
#            messagebox.showinfo("Works", "Pushed Button")

#def sendCommand(command):
#    ser.write(command.encode('ascii', 'ignore'))

class Label:
    def __init__(self, win, text):
        self.lbl=ttk.Label(win, text=text)
        #self.lbl.grid(column=clmn, row=row)

class combobox:
    def __init__(self, win, values):
        self.cb=ttk.Combobox(win, values=values, state = "readonly")
        #self.cb.grid(column=clmn, row=row)
        #self.cb.current(1)

def Configure_Results():
    #Store Variables
    Protocol = cb0.cb.get()
    UVoltage = cb1.cb.get()
    Frequency = cb2.cb.get()
    LVoltage = cb4.cb.get()
    DPower = cb5.cb.get()
    DataRate = cb6.cb.get()
    ClPolarity = cb7.cb.get()
    ChPolarity = cb9.cb.get()

    OutConfigTxt.configure(state="normal")
    OutConfigTxt.delete('1.0', END)

    #if Protocol == "I2C":
    #if Protocol == "UART":
    #if Protocol == "SPI":
    #if Protocol == "SWD":
    #if Protocol == "RS-485":

    if Protocol == "":
        OutConfigTxt.insert(TK.END, "Protocol: N/A" + '\n')
    else:
        OutConfigTxt.insert(TK.END, "Protocol: " + Protocol + '\n') 

    if UVoltage == "":
        OutConfigTxt.insert(TK.END, "Upper Voltage: N/A" + '\n')
    else:
        OutConfigTxt.insert(TK.END, "Upper Voltage: " + UVoltage + '\n')
    
    if Frequency == "":
        OutConfigTxt.insert(TK.END, "Frequency: N/A" + '\n')
    else:
        OutConfigTxt.insert(TK.END, "Frequency: " + Frequency + '\n')

    if LVoltage == "":
        OutConfigTxt.insert(TK.END, "Lower Voltage: N/A" + '\n')
    else:
        OutConfigTxt.insert(TK.END, "Lower Voltage: " + LVoltage + '\n')

    if DPower == "":
        OutConfigTxt.insert(TK.END, "Device Power Level: N/A" + '\n')
    else:
        OutConfigTxt.insert(TK.END, "Device Power Level: " + DPower + '\n')

    if DataRate == "":
        OutConfigTxt.insert(TK.END, "Data Rate: N/A" + '\n')
    else:
        OutConfigTxt.insert(TK.END, "Data Rate: " + DataRate + '\n')

    if ClPolarity == "":
        OutConfigTxt.insert(TK.END, "Clock Polarity: N/A" + '\n')
    else:
        OutConfigTxt.insert(TK.END, "Clock Polarity: " + ClPolarity + '\n')

    if ChPolarity == "":
        OutConfigTxt.insert(TK.END, "Chip Polarity: N/A" + '\n')
    else:
        OutConfigTxt.insert(TK.END, "Chip Polarity: " + ChPolarity + '\n')

    OutConfigTxt.configure(state="disable")

    #if voltage == "3.3V":
        #sendCommand('v0')
    #if voltage == "5V":
        #sendCommand('v1')
    #if voltage == "12V":
        #sendCommand('v2')
    #if voltage == "24V":
        #sendCommand('v3')
            
    #Wait for OKAY (z)
    #window.after(1000)

    #if frequency == "1kHZ":
        #sendCommand('f0')
    #if frequency == "10kHZ":
        #sendCommand('f1')
    #if frequency == "100kHZ":
        #sendCommand('f2')            
    #if frequency == "1MHZ":
        #sendCommand('f3')

    #End Function


def Data_To_Send():
    dataToSend = DataText3.get('1.0', END)
    for letter in dataToSend.rstrip():
        if letter is not '0' and letter is not '1':
            messagebox.showinfo("Error", "Invalid Data.\n Os and 1s Only")
            return
    if dataToSend == '\n':
        messagebox.showinfo("Error", "Please Enter Data to Send.\n Os and 1s Only")
        return
    if len(dataToSend.rstrip()) is not 8:
        messagebox.showinfo("Error", "Invalid Data.\n Should be 8 bits long.\n Os and 1s Only")
        return
    #print(dataToSend.rstrip())
    dataToSend = 's' + dataToSend.rstrip() + '\0'
    #print(dataToSend.rstrip())
    OutConfigTxt.configure(state="normal")
    OutConfigTxt.delete('1.0', END)
    OutConfigTxt.insert(TK.END, "Data Sent: " + dataToSend.rstrip() + '\n' + str(len(dataToSend.rstrip())))
    OutConfigTxt.configure(state="disable")
    #sendCommand(dataToSend.rstrip())

class Button:
    def __init__(self, win, text):
        self.btn=ttk.Button(win, text=text, command=self.press)
        #self.btn.grid(column=clmn, row=row)

    def press(self):
        btn_text = self.btn.cget('text')
        if btn_text == "Configure":
            Configure_Results()

        if btn_text == "Send Data":
            Data_To_Send()

#Each object needs to be created ouside the function and placed on the window in the function

lbl0 = Label(window, "Protocol:")                                           #Protocol
lbl1 = Label(sendTab, "Upper Voltage:")                                     #Upper Voltage
lbl2 = Label(sendTab, "Frequency:")                                         #Frequency
lbl3 = Label(sendTab, "Data to Send:")                                      #Data to Send
lbl4 = Label(sendTab, "Lower Voltage:")                                     #Lower Voltage
lbl5 = Label(sendTab, "Device Power Voltage:")                              #Device Power Voltage
lbl6 = Label(sendTab, "Data Rate:")                                         #Data Rate
lbl7 = Label(sendTab, "Clock Polarity:")                                    #Clock Polarity (Rise or fall)
lbl8 = Label(sendTab, "Device Address:")                                    #Device Address
lbl9 = Label(sendTab, "Chip Select Polarity:")                              #Chip Select Polarity

lbl0.lbl.grid(column=0, row=0)                                              #place protocol selection label (Always On)

cb0 = combobox(window, ["I2C", "UART", "SPI", "SWD", "RS-485"])             #create drop down for protocol selection
cb1 = combobox(sendTab, ["3.3V","5V", "12V", "24V" ])                       #Voltage Selection
cb2 = combobox(sendTab, ["1kHz", "10kHz", "100kHz", "1MHz"])                #Frequency Selection
cb4 = combobox(sendTab, ["-3.3V","-5V", "-12V", "-24V" ])                   #Lower volatage level
cb5 = combobox(sendTab, ["3.3V","5V", "12V", "24V" ])                       #Device Power Level
cb6 = combobox(sendTab, ["Data Rates"])                                     #Data Rates 
cb7 = combobox(sendTab, ["Rising Edge", "Falling edge"])                    #Clock Polarity
cb9 = combobox(sendTab, ["0", "1"])                                         #Chip Select Polarity


cb0.cb.grid(column=1, row=0)                                                #Place drop down for protocols

DataText3 = TK.Text(sendTab, height=1, width=17)                            #Box to enter 8 bit command to board (gets checked)
AddressText = TK.Text(sendTab, height=1, width=17)                          #Box to enter the device address. 
OutConfigTxt = TK.Text(window, height = 15, width = 42, state = "disabled")  #Display sent configurables in this box
OutConfigTxt.grid(column=0, row=6, columnspan=3)

btn1 = Button(sendTab, "Configure")                           #Send configure
btn2 = Button(sendTab, "Send Data")

#Choose which objects are displayed based on the protocol chosen

def display_create(window):
    #Create Interface for SPI
    if cb0.cb.get() == 'SPI':
        lbl1.lbl.grid(column=0, row=3)                              #Upper Voltage
        lbl2.lbl.grid(column=0, row=5)                              #Frequency
        lbl3.lbl.grid(column=0, row=10)                             #Data to send
        lbl4.lbl.grid(column=0, row=2)                              #Lower Voltage
        lbl5.lbl.grid(column=0, row=6)                              #Device Power
        lbl6.lbl.grid(column=0, row=7)                              #Data Rate
        lbl7.lbl.grid(column=0, row=4)                              #Clock Polarity
        lbl8.lbl.grid(column=0, row=8)                              #Device Address
        lbl9.lbl.grid(column=0, row=9)                              #Chip Select Polarity

        cb1.cb.grid(column=1, row=3)                                #Upper Voltage
        cb2.cb.grid(column=1, row=5)                                #Frequency
        cb4.cb.grid(column=1, row=2)                                #Lower Voltage Level
        cb5.cb.grid(column=1, row=6)                                #Device Power
        cb6.cb.grid(column=1, row=7)                                #Data Rates
        cb7.cb.grid(column=1, row=4)                                #Clock Polarity
        cb9.cb.grid(column=1, row=9)                                #Chip Select Polarity

        DataText3.grid(column=1, row=10)                            #Data to send
        AddressText.grid(column=1, row=8)                           #Device Address Box

        btn1.btn.grid(column=2, row=2)                              #Send configure
        btn2.btn.grid(column=2, row=10)                             #Send Data from text box

    #Display I2C Components
    if cb0.cb.get() == 'I2C':
        lbl1.lbl.grid(column=0, row=3)                              #Upper Voltage
        lbl2.lbl.grid(column=0, row=5)                              #Frequency
        lbl3.lbl.grid(column=0, row=10)                             #Data to send
        lbl4.lbl.grid(column=0, row=2)                              #Lower Voltage
        lbl5.lbl.grid(column=0, row=6)                              #Device Power
        lbl6.lbl.grid(column=0, row=7)                              #Data Rate
        lbl7.lbl.grid(column=0, row=4)                              #Clock Polarity
        lbl8.lbl.grid(column=0, row=8)                              #Device Address
        lbl9.lbl.grid_forget()                                      #Chip Select Polarity

        cb1.cb.grid(column=1, row=3)                                #Upper Voltage
        cb2.cb.grid(column=1, row=5)                                #Frequency
        cb4.cb.grid(column=1, row=2)                                #Lower Voltage Level
        cb5.cb.grid(column=1, row=6)                                #Device Power
        cb6.cb.grid(column=1, row=7)                                #Data Rates
        cb7.cb.grid(column=1, row=4)                                #Clock Polarity
        cb9.cb.grid_forget()                                        #Chip Select Polarity
        
        #Empty Unused Boxes
        cb9.cb.set('')                                              

        DataText3.grid(column=1, row=10)                            #Data to send
        AddressText.grid(column=1, row=8)                           #Device Address Box

        btn1.btn.grid(column=2, row=2)                              #Send configure
        btn2.btn.grid(column=2, row=10)                             #Send Data from text box

    
    #Display UART Components
    if cb0.cb.get() == 'UART':
        lbl1.lbl.grid(column=0, row=3)                              #Upper Voltage
        lbl2.lbl.grid_forget()                                      #Frequency
        lbl3.lbl.grid(column=0, row=10)                             #Data to send
        lbl4.lbl.grid(column=0, row=2)                              #Lower Voltage
        lbl5.lbl.grid(column=0, row=6)                              #Device Power
        lbl6.lbl.grid(column=0, row=7)                              #Data Rate
        lbl7.lbl.grid(column=0, row=4)                              #Clock Polarity
        lbl8.lbl.grid_forget()                                      #Device Address
        lbl9.lbl.grid_forget()                                      #Chip Select Polarity

        cb1.cb.grid(column=1, row=3)                                #Upper Voltage
        cb2.cb.grid_forget()                                        #Frequency
        cb4.cb.grid(column=1, row=2)                                #Lower Voltage Level
        cb5.cb.grid(column=1, row=6)                                #Device Power
        cb6.cb.grid(column=1, row=7)                                #Data Rates
        cb7.cb.grid(column=1, row=4)                                #Clock Polarity
        cb9.cb.grid_forget()                                        #Chip Select Polarity

        #Empty Unused Boxes
        cb2.cb.set('')
        cb9.cb.set('')
        AddressText.delete('1.0', END)

        DataText3.grid(column=1, row=10)                            #Data to send
        AddressText.grid_forget()                                   #Device Address Box

        btn1.btn.grid(column=2, row=2)                              #Send configure
        btn2.btn.grid(column=2, row=10)                             #Send Data from text box


    #Display SWD Components
    if cb0.cb.get() == 'SWD':
        lbl1.lbl.grid(column=0, row=3)                              #Upper Voltage
        lbl2.lbl.grid_forget()                                      #Frequency
        lbl3.lbl.grid_forget()                                      #Data to send
        lbl4.lbl.grid(column=0, row=2)                              #Lower Voltage
        lbl5.lbl.grid(column=0, row=6)                              #Device Power
        lbl6.lbl.grid_forget()                                      #Data Rate
        lbl7.lbl.grid(column=0, row=4)                              #Clock Polarity
        lbl8.lbl.grid_forget()                                      #Device Address
        lbl9.lbl.grid_forget()                                      #Chip Select Polarity

        cb1.cb.grid(column=1, row=3)                                #Upper Voltage
        cb2.cb.grid_forget()                                        #Frequency
        cb4.cb.grid(column=1, row=2)                                #Lower Voltage Level
        cb5.cb.grid(column=1, row=6)                                #Device Power
        cb6.cb.grid_forget()                                        #Data Rates
        cb7.cb.grid(column=1, row=4)                                #Clock Polarity
        cb9.cb.grid_forget()                                        #Chip Select Polarity

        #Empty Unused Boxes
        cb2.cb.set('')
        cb6.cb.set('')
        cb9.cb.set('')
        AddressText.delete('1.0', END)
        DataText3.delete('1.0', END)

        DataText3.grid_forget()                                     #Data to send
        AddressText.grid_forget()                                   #Device Address Box

        btn1.btn.grid(column=2, row=2)                              #Send configure
        btn2.btn.grid_forget()                                      #Send Data from text box


    #display RS-485 Components 
    if cb0.cb.get() == 'RS-485':
        lbl1.lbl.grid(column=0, row=3)                              #Upper Voltage
        lbl2.lbl.grid_forget()                                      #Frequency
        lbl3.lbl.grid(column=0, row=10)                             #Data to send
        lbl4.lbl.grid(column=0, row=2)                              #Lower Voltage
        lbl5.lbl.grid(column=0, row=6)                              #Device Power
        lbl6.lbl.grid(column=0, row=7)                              #Data Rate
        lbl7.lbl.grid_forget()                                      #Clock Polarity
        lbl8.lbl.grid_forget()                                      #Device Address
        lbl9.lbl.grid_forget()                                      #Chip Select Polarity

        cb1.cb.grid(column=1, row=3)                                #Upper Voltage
        cb2.cb.grid_forget()                                        #Frequency
        cb4.cb.grid(column=1, row=2)                                #Lower Voltage Level
        cb5.cb.grid(column=1, row=6)                                #Device Power
        cb6.cb.grid(column=1, row=7)                                #Data Rates
        cb7.cb.grid_forget()                                        #Clock Polarity
        cb9.cb.grid_forget()                                        #Chip Select Polarity

        #Empty Unused Boxes
        cb2.cb.set('')
        cb7.cb.set('')
        cb9.cb.set('')
        AddressText.delete('1.0', END)

        DataText3.grid(column=1, row=10)                            #Data to send
        AddressText.grid_forget()                                   #Device Address Box

        btn1.btn.grid(column=2, row=2)                              #Send configure
        btn2.btn.grid(column=2, row=10)                             #Send Data from text box



cb0.cb.bind("<<ComboboxSelected>>", display_create)                         #link protocol selection combobox to ubove function. Display fields update when drop box changes. 
      

#if dev is None:
    #raise ValueError('The device is not connnected')
    #messagebox.showinfo("Works", "No Device Connected")

def main():
    #serialThread = threading.Thread(target=read_from_port, args=(ser,))
    #serialThread.start()
    window.mainloop()

if (__name__ == '__main__'):
    main()
