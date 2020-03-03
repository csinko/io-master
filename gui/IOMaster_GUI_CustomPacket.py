import tkinter as TK
import usb.core
import usb.util
import serial
import time
import threading
import serial.tools.list_ports
import sys
#from tkinter import *
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
tabControl.grid(column=0, row=1, columnspan=3) #expand=1, fill="both")

ser = serial.Serial()

def InitializePopup():
    window.withdraw()

    popup = TK.Toplevel()
    popup.title("Select Device Port")
    popup.geometry("450x185")

    txtlbl = TK.Label(popup, text = "Select COM Port")
    txtlbl.pack()

    txtin = TK.Text(popup, height=1, width=17)
    txtin.pack()

    EnterBtn = TK.Button(popup, text = "Select", command = lambda : EntryCheck())
    EnterBtn.pack()

    avlbl = TK.Label(popup, text = "Available COM Ports:")
    avlbl.pack()

    txtout = TK.Text(popup, height=5, width=50)
    txtout.pack()

    ports = list(serial.tools.list_ports.comports())    
    for p in ports:
        txtout.insert(TK.END, p)
        txtout.insert(TK.END, '\n')
    txtout.configure(state = 'disable')

    def EntryCheck():
    #entry check for com port
        global ser
        strg = txtin.get('1.0', TK.END)
        try:
            ser = serial.Serial(strg.rstrip('\n'), 1200,  serial.EIGHTBITS, serial.PARITY_NONE, serial.STOPBITS_ONE)
        except:
            messagebox.showinfo("Error", "Could not open COM port")
            #InitializePopup()
            return
            
        OutConfigTxt.configure(state="normal")
        OutConfigTxt.insert(TK.END, "COM Port: " + strg + '\n')
        OutConfigTxt.configure(state="disable")
        window.deiconify()
        popup.destroy()


def read_from_port(ser):
    while True:
        reading = ser.read()
        print(reading)
        if reading == b'3':
            messagebox.showinfo("Works", "Pushed Button")

def sendCommand(command):
    try:
        ser.write(command)
    except:
        messagebox.showinfo("Error", "Could not write to COM port, verify the device is plugged in then restate the correct COM port")
        InitializePopup()

class Label:
    def __init__(self, win, text):
        self.lbl=ttk.Label(win, text=text)
        #self.lbl.grid(column=clmn, row=row)

class combobox:
    def __init__(self, win, values):
        self.cb=ttk.Combobox(win, values=values, state = "readonly")

def Configure_Results():
    #Store VariablesI
    Protocol = cb0.cb.get()
    UVoltage = VHin.get('1.0', TK.END)
    Frequency = cb2.cb.get()
    LVoltage = VLin.get('1.0', TK.END)
    DPower = cb5.cb.get()
    DataRate = cb6.cb.get()
    ClPolarity = cb7.cb.get()
    ChPolarity = cb9.cb.get()

    OutConfigTxt.configure(state="normal")
    OutConfigTxt.delete('1.0', TK.END)

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
        OutConfigTxt.insert(TK.END, "Upper Voltage: " + UVoltage)
    
    if Frequency == "":
        OutConfigTxt.insert(TK.END, "Frequency: N/A" + '\n')
    else:
        OutConfigTxt.insert(TK.END, "Frequency: " + Frequency + '\n')

    if LVoltage == "":
        OutConfigTxt.insert(TK.END, "Lower Voltage: N/A" + '\n')
    else:
        OutConfigTxt.insert(TK.END, "Lower Voltage: " + LVoltage)

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

    if (float(UVoltage) > 15 or float(UVoltage) < float(LVoltage)):
        #print(float(UVoltage))
        #print(float(LVoltage))
        messagebox.showinfo("Error", "Invalid Data.\n Pick a voltage of 15V or Lower. \n Also, Upper Voltage should be larger than Lower Voltage")
        return
    else:
        VH = float(UVoltage)

    if (float(LVoltage) < -15 or float(UVoltage) < float(LVoltage)):
        messagebox.showinfo("Error", "Invalid Data.\n Pick a voltage of -15V or Higher for Lower Voltage. \n Also, Upper Voltage should be larger than Lower Voltage")
        return
    else:
        VL = float(LVoltage)

    #rewr=1 because we are writing, commandbits determines what we are setting, resister State is unknown
    rewr = int(WrRetxt.get('1.0', TK.END))
    commandbits = int(ComBittxt.get('1.0', TK.END))
    resisterStates = int(ResisStattxt.get('1.0', TK.END))
    byteSend(rewr, commandbits, resisterStates, VH, VL)

    #End Function


def byteSend(rewr, commandbits, resisterStates, VH, VL):
    #rewr=1 bit, commandbits=3, resisterstate=4 bits
    rewr = rewr << 7
    combits = commandbits << 4

    commandByte = rewr | combits | resisterStates #byte 1

    TVH = round(((2**12 - 1) / 30) * (24 - VH))
    TVL = round(((2**12 - 1) / 30) * (24 - VL))

    UVH = (TVH >> 8) & 0xff
    LVH = (TVH) & 0xff
    UVL = (TVL >> 8) & 0xff
    LVL = (TVL) & 0xff

    OutConfigTxt.configure(state="normal")

    Packet_Bytes = bytearray()
    Packet_Bytes.append(commandByte)#byte1
    Packet_Bytes.append(UVH)#byte2
    Packet_Bytes.append(LVH)#byte3
    Packet_Bytes.append(UVL)#byte4
    Packet_Bytes.append(LVL)#byte5

    OutConfigTxt.insert(TK.END, Packet_Bytes.hex())
    OutConfigTxt.configure(state="disable")

    sendCommand(Packet_Bytes)

def Data_To_Send():
    dataToSend = DataText3.get('1.0', TK.END)
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
    OutConfigTxt.delete('1.0', TK.END)
    OutConfigTxt.insert(TK.END, "Data Sent: " + dataToSend.rstrip() + '\n' + str(len(dataToSend.rstrip())))
    OutConfigTxt.configure(state="disable")
    sendCommand(dataToSend.rstrip())

class Button:
    def __init__(self, win, text):
        self.btn=ttk.Button(win, text=text, command=self.press)

    def press(self):
        btn_text = self.btn.cget('text')
        if btn_text == "Configure":
            Configure_Results()

        if btn_text == "Send Data":
            Data_To_Send()

        if btn_text == "Reset COM Port":
            InitializePopup()

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
WrRelbl = Label(sendTab, "Read Write bit:")                                 #read write bit for custom packet send (1 bit)
ComBitlbl = Label(sendTab, "Commandbits:")                                  #Set command bits (3 bits)
ResisStatlbl = Label(sendTab, "Resister State:")                            #set resister state (either 0, 1, 2)(4 bits)

lbl0.lbl.grid(column=0, row=0)                                              #place protocol selection label (Always On)

cb0 = combobox(window, ["I2C", "UART", "SPI", "SWD", "RS-485", "All", "Custom Packet"])             #create drop down for protocol selection
VHin = TK.Text(sendTab, height=1, width=17)                                  #Voltage Selection
cb2 = combobox(sendTab, ["1kHz", "10kHz", "100kHz", "1MHz"])                #Frequency Selection
VLin = TK.Text(sendTab, height=1, width=17)                                  #Lower volatage level
cb5 = combobox(sendTab, ["3.3V","5V", "12V", "24V" ])                       #Device Power Level
cb6 = combobox(sendTab, ["Data Rates"])                                     #Data Rates 
cb7 = combobox(sendTab, ["Rising Edge", "Falling edge"])                    #Clock Polarity
cb9 = combobox(sendTab, ["0", "1"])                                         #Chip Select Polarity


cb0.cb.grid(column=1, row=0)                                                #Place drop down for protocols

DataText3 = TK.Text(sendTab, height=1, width=17)                            #Box to enter 8 bit command to board (gets checked)
AddressText = TK.Text(sendTab, height=1, width=17)                          #Box to enter the device address. 
OutConfigTxt = TK.Text(window, height = 15, width = 42, state = "disabled")  #Display sent configurables in this box
OutConfigTxt.grid(column=0, row=6, columnspan=3)

WrRetxt = TK.Text(sendTab, height=1, width=17)                                 #read write bit for custom packet send (1 bit)
WrRetxt.insert(TK.END, "1")
ComBittxt = TK.Text(sendTab, height=1, width=17)                                  #Set command bits (3 bits)
ComBittxt.insert(TK.END, "6")
ResisStattxt = TK.Text(sendTab, height=1, width=17)                            #set resister state (either 0, 1, 2)(4 bits)
ResisStattxt.insert(TK.END, "2")


btn1 = Button(sendTab, "Configure")                           #Send configure
btn2 = Button(sendTab, "Send Data")
ReComBtn = Button(window, "Reset COM Port")
ReComBtn.btn.grid(column = 2, row = 0)

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

        WrRelbl.lbl.grid_forget()                                  #read write bit for custom packet send (1 bit)
        ComBitlbl.lbl.grid_forget()                                   #Set command bits (3 bits)
        ResisStatlbl.lbl.grid_forget()                             #set resister state (either 0, 1, 2)(4 bits)

        VHin.grid(column=1, row=3)                                #Upper Voltage
        cb2.cb.grid(column=1, row=5)                                #Frequency
        VLin.grid(column=1, row=2)                                #Lower Voltage Level
        cb5.cb.grid(column=1, row=6)                                #Device Power
        cb6.cb.grid(column=1, row=7)                                #Data Rates
        cb7.cb.grid(column=1, row=4)                                #Clock Polarity
        cb9.cb.grid(column=1, row=9)                                #Chip Select Polarity

        DataText3.grid(column=1, row=10)                            #Data to send
        AddressText.grid(column=1, row=8)                           #Device Address Box

        WrRetxt.grid_forget()                                #read write bit for custom packet send (1 bit)
        ComBittxt.grid_forget()                                  #Set command bits (3 bits)
        ResisStattxt.grid_forget()                             #set resister state (either 0, 1, 2)(4 bits)

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

        WrRelbl.lbl.grid_forget()                                  #read write bit for custom packet send (1 bit)
        ComBitlbl.lbl.grid_forget()                                   #Set command bits (3 bits)
        ResisStatlbl.lbl.grid_forget()                             #set resister state (either 0, 1, 2)(4 bits)

        VHin.grid(column=1, row=3)                                #Upper Voltage
        cb2.cb.grid(column=1, row=5)                                #Frequency
        VLin.grid(column=1, row=2)                                #Lower Voltage Level
        cb5.cb.grid(column=1, row=6)                                #Device Power
        cb6.cb.grid(column=1, row=7)                                #Data Rates
        cb7.cb.grid(column=1, row=4)                                #Clock Polarity
        cb9.cb.grid_forget()                                        #Chip Select Polarity
        
        #Empty Unused Boxes
        cb9.cb.set('')                                              

        DataText3.grid(column=1, row=10)                            #Data to send
        AddressText.grid(column=1, row=8)                           #Device Address Box

        WrRetxt.grid_forget()                                #read write bit for custom packet send (1 bit)
        ComBittxt.grid_forget()                                  #Set command bits (3 bits)
        ResisStattxt.grid_forget()                             #set resister state (either 0, 1, 2)(4 bits)

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

        WrRelbl.lbl.grid_forget()                                  #read write bit for custom packet send (1 bit)
        ComBitlbl.lbl.grid_forget()                                   #Set command bits (3 bits)
        ResisStatlbl.lbl.grid_forget()                             #set resister state (either 0, 1, 2)(4 bits)

        VHin.grid(column=1, row=3)                                #Upper Voltage
        cb2.cb.grid_forget()                                        #Frequency
        VLin.grid(column=1, row=2)                                #Lower Voltage Level
        cb5.cb.grid(column=1, row=6)                                #Device Power
        cb6.cb.grid(column=1, row=7)                                #Data Rates
        cb7.cb.grid(column=1, row=4)                                #Clock Polarity
        cb9.cb.grid_forget()                                        #Chip Select Polarity

        #Empty Unused Boxes
        cb2.cb.set('')
        cb9.cb.set('')
        AddressText.delete('1.0', TK.END)

        DataText3.grid(column=1, row=10)                            #Data to send
        AddressText.grid_forget()                                   #Device Address Box

        WrRetxt.grid_forget()                                #read write bit for custom packet send (1 bit)
        ComBittxt.grid_forget()                                  #Set command bits (3 bits)
        ResisStattxt.grid_forget()                             #set resister state (either 0, 1, 2)(4 bits)

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

        WrRelbl.lbl.grid_forget()                                  #read write bit for custom packet send (1 bit)
        ComBitlbl.lbl.grid_forget()                                   #Set command bits (3 bits)
        ResisStatlbl.lbl.grid_forget()                             #set resister state (either 0, 1, 2)(4 bits)

        VHin.grid(column=1, row=3)                                #Upper Voltage
        cb2.cb.grid_forget()                                        #Frequency
        VLin.grid(column=1, row=2)                                #Lower Voltage Level
        cb5.cb.grid(column=1, row=6)                                #Device Power
        cb6.cb.grid_forget()                                        #Data Rates
        cb7.cb.grid(column=1, row=4)                                #Clock Polarity
        cb9.cb.grid_forget()                                        #Chip Select Polarity

        #Empty Unused Boxes
        cb2.cb.set('')
        cb6.cb.set('')
        cb9.cb.set('')
        AddressText.delete('1.0', TK.END)
        DataText3.delete('1.0', TK.END)

        DataText3.grid_forget()                                     #Data to send
        AddressText.grid_forget()                                   #Device Address Box

        WrRetxt.grid_forget()                                #read write bit for custom packet send (1 bit)
        ComBittxt.grid_forget()                                  #Set command bits (3 bits)
        ResisStattxt.grid_forget()                             #set resister state (either 0, 1, 2)(4 bits)

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

        WrRelbl.lbl.grid_forget()                                 #read write bit for custom packet send (1 bit)
        ComBitlbl.lbl.grid_forget()                                   #Set command bits (3 bits)
        ResisStatlbl.lbl.grid_forget()                             #set resister state (either 0, 1, 2)(4 bits)

        VHin.grid(column=1, row=3)                                #Upper Voltage
        cb2.cb.grid_forget()                                        #Frequency
        VLin.grid(column=1, row=2)                                #Lower Voltage Level
        cb5.cb.grid(column=1, row=6)                                #Device Power
        cb6.cb.grid(column=1, row=7)                                #Data Rates
        cb7.cb.grid_forget()                                        #Clock Polarity
        cb9.cb.grid_forget()                                        #Chip Select Polarity

        #Empty Unused Boxes
        cb2.cb.set('')
        cb7.cb.set('')
        cb9.cb.set('')
        AddressText.delete('1.0', TK.END)

        DataText3.grid(column=1, row=10)                            #Data to send
        AddressText.grid_forget()                                   #Device Address Box

        WrRetxt.grid_forget()                                #read write bit for custom packet send (1 bit)
        ComBittxt.grid_forget()                                  #Set command bits (3 bits)
        ResisStattxt.grid_forget()                             #set resister state (either 0, 1, 2)(4 bits)

        btn1.btn.grid(column=2, row=2)                              #Send configure
        btn2.btn.grid(column=2, row=10)                             #Send Data from text box

    #Display Custom Options
    if cb0.cb.get() == 'All':
        lbl1.lbl.grid(column=0, row=3)                              #Upper Voltage
        lbl2.lbl.grid(column=0, row=5)                              #Frequency
        lbl3.lbl.grid(column=0, row=10)                             #Data to send
        lbl4.lbl.grid(column=0, row=2)                              #Lower Voltage
        lbl5.lbl.grid(column=0, row=6)                              #Device Power
        lbl6.lbl.grid(column=0, row=7)                              #Data Rate
        lbl7.lbl.grid(column=0, row=4)                              #Clock Polarity
        lbl8.lbl.grid(column=0, row=8)                              #Device Address
        lbl9.lbl.grid(column=0, row=9)                              #Chip Select Polarity

        WrRelbl.lbl.grid_forget()                                  #read write bit for custom packet send (1 bit)
        ComBitlbl.lbl.grid_forget()                                   #Set command bits (3 bits)
        ResisStatlbl.lbl.grid_forget()                             #set resister state (either 0, 1, 2)(4 bits)

        VHin.grid(column=1, row=3)                                #Upper Voltage
        cb2.cb.grid(column=1, row=5)                                #Frequency
        VLin.grid(column=1, row=2)                                #Lower Voltage Level
        cb5.cb.grid(column=1, row=6)                                #Device Power
        cb6.cb.grid(column=1, row=7)                                #Data Rates
        cb7.cb.grid(column=1, row=4)                                #Clock Polarity
        cb9.cb.grid(column=1, row=9)                                #Chip Select Polarity

        DataText3.grid(column=1, row=10)                            #Data to send
        AddressText.grid(column=1, row=8)                           #Device Address Box

        WrRetxt.grid_forget()                                #read write bit for custom packet send (1 bit)
        ComBittxt.grid_forget()                                  #Set command bits (3 bits)
        ResisStattxt.grid_forget()                             #set resister state (either 0, 1, 2)(4 bits)

        btn1.btn.grid(column=2, row=2)                              #Send configure
        btn2.btn.grid(column=2, row=10)                             #Send Data from text box

    if cb0.cb.get() == 'Custom Packet':
        lbl1.lbl.grid(column=0, row=4)                               #Upper Voltage
        lbl2.lbl.grid_forget()                              #Frequency
        lbl3.lbl.grid_forget()                             #Data to send
        lbl4.lbl.grid(column=0, row=5)                              #Lower Voltage
        lbl5.lbl.grid_forget()                              #Device Power
        lbl6.lbl.grid_forget()                              #Data Rate
        lbl7.lbl.grid_forget()                              #Clock Polarity
        lbl8.lbl.grid_forget()                              #Device Address
        lbl9.lbl.grid_forget()                              #Chip Select Polarity

        WrRelbl.lbl.grid(column=0, row=1)                                  #read write bit for custom packet send (1 bit)
        ComBitlbl.lbl.grid(column=0, row=2)                                   #Set command bits (3 bits)
        ResisStatlbl.lbl.grid(column=0, row=3)                             #set resister state (either 0, 1, 2)(4 bits)

        VHin.grid(column=1, row=4)                                #Upper Voltage
        cb2.cb.grid_forget()                                #Frequency
        VLin.grid(column=1, row=5)                                #Lower Voltage Level
        cb5.cb.grid_forget()                                #Device Power
        cb6.cb.grid_forget()                                #Data Rates
        cb7.cb.grid_forget()                               #Clock Polarity
        cb9.cb.grid_forget()                                #Chip Select Polarity

        DataText3.grid_forget()                            #Data to send
        AddressText.grid_forget()                           #Device Address Box

        WrRetxt.grid(column=1, row=1)                                #read write bit for custom packet send (1 bit)
        ComBittxt.grid(column=1, row=2)                                  #Set command bits (3 bits)
        ResisStattxt.grid(column=1, row=3)                             #set resister state (either 0, 1, 2)(4 bits)

        btn1.btn.grid(column=2, row=2)                              #Send configure
        btn2.btn.grid_forget()                             #Send Data from text box

cb0.cb.bind("<<ComboboxSelected>>", display_create)                         #link protocol selection combobox to ubove function. Display fields update when drop box changes. 

def main():
    #global ser
    #ser = serial.Serial('/dev/ttyUSB0')
    InitializePopup()
    #serialThread = threading.Thread(target=read_from_port, args=(ser,))
    #serialThread.start()
    window.mainloop()

if (__name__ == '__main__'):
    main()
