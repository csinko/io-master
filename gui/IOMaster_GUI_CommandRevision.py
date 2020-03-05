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
window.geometry("750x600")

tabControl = ttk.Notebook(window)
sendTab = ttk.Frame(tabControl)
receiveTab = ttk.Frame(tabControl)
tabControl.add(sendTab, text= 'Send')
tabControl.add(receiveTab, text='Receive')
tabControl.grid(column=0, row=1, columnspan=7) #expand=1, fill="both")

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
            ser = serial.Serial(strg.rstrip('\n'), 115200,  serial.EIGHTBITS, serial.PARITY_NONE, serial.STOPBITS_ONE)
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
        
        """
        print(reading)
        if reading == b'3':
            messagebox.showinfo("Works", "Pushed Button")
        """

def sendCommand(command):
    print(command.hex())
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

    if Protocol == "Custom Packet":
        rewr = int(WrRetxt.get('1.0', TK.END))
        commandbits = int(ComBittxt.get('1.0', TK.END))
        resisterStates = int(ResisStattxt.get('1.0', TK.END))

        byte2 = byte2in.get('1.0', TK.END)
        byte3 = byte3in.get('1.0', TK.END)
        byte4 = byte4in.get('1.0', TK.END)
        byte5 = byte5in.get('1.0', TK.END)

        if byte2.rstrip('\n') != 'NULL':
            byte2 = int(byte2)
        else:
            byte2 = byte2.rstrip('\n')

        if byte3.rstrip('\n') != 'NULL':
            byte3 = int(byte3)
        else:
            byte3 = byte3.rstrip('\n')

        if byte4.rstrip('\n') != 'NULL':
            byte4 = int(byte4)
        else:
            byte4 = byte4.rstrip('\n')

        if byte5.rstrip('\n') != 'NULL':
            byte5 = int(byte5)
        else:
            byte5 = byte5.rstrip('\n')

        byteSendConfig(rewr, commandbits, resisterStates, byte2, byte3, byte4, byte5)
        return

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
    #rewr = int(WrRetxt.get('1.0', TK.END))
    #resisterStates = int(ResisStattxt.get('1.0', TK.END))
    
    byteSendVoltage(1, 1, 0, VH, VL)
    byteSendVoltage(1, 2, 0, VH, VL)
    byteSendVoltage(1, 3, 0, VH, VL)
    byteSendVoltage(1, 4, 0, VH, VL)


    #End Function

def setStateToConfig():
    #send a 2 byte array of 1 and 1
    Config_Bytes = bytearray()

    Config_Bytes.append(1)
    Config_Bytes.append(1)
    sendCommand(Config_Bytes)

    OutConfigTxt.configure(state="normal")
    OutConfigTxt.insert(TK.END, "State Set to Configure: " + Config_Bytes.hex() + '\n')
    OutConfigTxt.configure(state="disable")
    

def byteSendVoltage(rewr, commandbits, resisterStates, VH, VL):
    VH = VH + 1.3
    #rewr=1 bit, commandbits=3, resisterstate=4 bits
    rewr = rewr << 7
    combits = commandbits << 4

    commandByte = rewr | combits | resisterStates #byte 1

    TVH = round(((2**12 - 1) / 33) * (16.5 - VH))
    TVL = round(((2**12 - 1) / 33) * (16.5 - VL))
    print("TVH")
    print(TVH)
    print("TVL")
    print(TVL)

    UVH = (TVH >> 8) & 0xff
    LVH = (TVH) & 0xff
    UVL = (TVL >> 8) & 0xff
    LVL = (TVL) & 0xff

    OutConfigTxt.configure(state="normal")

    Packet_Bytes = bytearray()
    Packet_Bytes.append(2) #Byte0
    Packet_Bytes.append(commandByte)#byte1
    Packet_Bytes.append(UVH)#byte2
    Packet_Bytes.append(LVH)#byte3
    Packet_Bytes.append(UVL)#byte4
    Packet_Bytes.append(LVL)#byte5

    OutConfigTxt.insert(TK.END, Packet_Bytes.hex())
    OutConfigTxt.configure(state="disable")

    sendCommand(Packet_Bytes)
    time.sleep(.1)


#Setting any of the 4 bytes to NULL will skip that byte in the array
def byteSendConfig(rewr, commandbits, resisterStates, byte2, byte3, byte4, byte5):
    #set state of the board to configure
    setStateToConfig()

    #rewr=1 bit, commandbits=3, resisterstate=4 bits
    rewr = rewr << 7
    combits = commandbits << 4

    commandByte = rewr | combits | resisterStates #byte 1

    OutConfigTxt.configure(state="normal")

    Packet_Bytes = bytearray()

    Packet_Bytes.append(2) #Config Command Byte

    Packet_Bytes.append(commandByte)#byte1
    if byte2 != 'NULL':
        Packet_Bytes.append(byte2)#byte2
    if byte3 != 'NULL':
        Packet_Bytes.append(byte3)#byte3
    if byte4 != 'NULL':
        Packet_Bytes.append(byte4)#byte4
    if byte5 != 'NULL':
        Packet_Bytes.append(byte5)#byte5

    OutConfigTxt.insert(TK.END, "Data Sent: " + Packet_Bytes.hex() + '\n')
    OutConfigTxt.configure(state="disable")

    sendCommand(Packet_Bytes)

def setStateToLoadData():
    #send a 2 byte array of 1 and 1
    Config_Bytes = bytearray()

    Config_Bytes.append(1)
    Config_Bytes.append(2)
    sendCommand(Config_Bytes)

    OutConfigTxt.configure(state="normal")
    OutConfigTxt.insert(TK.END, "State Set to Configure: " + Config_Bytes.hex() + '\n')
    OutConfigTxt.configure(state="disable")

def Data_To_Send():
    #convert text to byte array. 
    Data_Bytes = bytearray()
    dataToSend = DataText3.get('1.0', TK.END)
    for element in dataToSend.rstrip('\n'):
        Data_Bytes.append(ord(element))


    #Make packet to send
    byteArrayLength = len(Data_Bytes)
    Data_Send_Bytes = bytearray()
    Data_Send_Bytes.append(3)
    Data_Send_Bytes.append(1)
    Data_Send_Bytes.append(byteArrayLength)
    Data_Send_Bytes.extend(Data_Bytes)

    sendCommand(Data_Send_Bytes)

    OutConfigTxt.configure(state="normal")
    OutConfigTxt.insert(TK.END, "Data Sent: " + Data_Send_Bytes.hex() + '\n')
    OutConfigTxt.configure(state="disable")

def pinConfiguration():
    #Determine bits
    def getBitConfig(strEntry):
        if strEntry == "MOSI" or strEntry == "SS":
            return 2    #Outpin
        elif strEntry == "MISO":
            return 1    #InPin
        elif strEntry == "SCLK":
            return 3    #ClockPin
        else:
            return 0    #pin Disabled
    
    #set Pin Configuration for SPI based on user input
    if cb0.cb.get() == "SPI":
        pin1 = pin1spi.cb.get()
        pin2 = pin2spi.cb.get()
        pin3 = pin3spi.cb.get()
        pin4 = pin4spi.cb.get()

        if pin1 == pin2 or pin1 == pin3 or pin1 == pin4 or pin2 == pin3 or pin2 == pin4 or pin3 == pin4:
            messagebox.showinfo("Error", "Invalid Data.\n The pins should all be unique")
            return

    Abits = getBitConfig(pin1)
    Bbits = getBitConfig(pin2)
    Cbits = getBitConfig(pin3)
    Dbits = getBitConfig(pin4)

    #byte 1
    rewr = 1
    commandbits = 7
    resisterStates = 0 

    #byte 2
    pinPattern = (Dbits << 6) | (Cbits << 4) | (Bbits << 2) | (Abits)

    byteSendConfig(rewr,commandbits,resisterStates,pinPattern,'NULL','NULL','NULL')
    
def receiveOrSend():
    try:
        bytes2find = int(B2Rtxt.get('1.0', TK.END))
    except:
        messagebox.showinfo("Error", "Enter a Valid Positive Number for Bytes to Read")
        return
    if bytes2find < 0:
        messagebox.showinfo("Error", "Enter a Valid Positive Number for Bytes to Read")
        return

    # Send designated Load Data Mode
    setStateToLoadData()
    
    #Check how many bytes to recieve before sending data
    if bytes2find == 0:
        Data_To_Send()
        return
    
    #send Bytes to read command
    B2S_Bytes = bytearray()
    B2S_Bytes.append(2)
    B2S_Bytes.append(bytes2find)
    sendCommand(B2S_Bytes)

    #Else Look for the amount of Bytes entered
    receivedBytes = bytearray()
    #read in Byte
    #receivedBytes = ser.read(bytes2find)         #line causes code to stop responding. Cause unknown

    OutConfigTxt.configure(state="normal")
    OutConfigTxt.insert(TK.END, "Looked for Byte: " + receivedBytes.hex() + '\n')
    OutConfigTxt.configure(state="disable")

class Button:
    def __init__(self, win, text):
        self.btn=ttk.Button(win, text=text, command=self.press)

    def press(self):
        btn_text = self.btn.cget('text')
        if btn_text == "Configure":
            setStateToConfig()
            Configure_Results()

        if btn_text == "Send Data":
            receiveOrSend()

        if btn_text == "Reset COM Port":
            InitializePopup()

        if btn_text == "Configure Pins":
            pinConfiguration()

#Each object needs to be created ouside the function and placed on the window in the function

lbl0 = Label(window, "Protocol:")                                           #Protocol
lbl1 = Label(sendTab, "Upper Voltage:")                                     #Upper Voltage
lbl2 = Label(sendTab, "Frequency:")                                         #Frequency
Data2Send = Label(sendTab, "Data to Send:")                                 #Data to Send
lbl4 = Label(sendTab, "Lower Voltage:")                                     #Lower Voltage
lbl5 = Label(sendTab, "Device Power Voltage:")                              #Device Power Voltage
lbl6 = Label(sendTab, "Data Rate:")                                         #Data Rate
lbl7 = Label(sendTab, "Clock Polarity:")                                    #Clock Polarity (Rise or fall)
lbl8 = Label(sendTab, "Device Address:")                                    #Device Address
lbl9 = Label(sendTab, "Chip Select Polarity:")                              #Chip Select Polarity
WrRelbl = Label(sendTab, "Read Write bit:")                                 #read write bit for custom packet send (1 bit)
ComBitlbl = Label(sendTab, "Commandbits:")                                  #Set command bits (3 bits)
ResisStatlbl = Label(sendTab, "Resister State:")                            #set resister state (either 0, 1, 2)(4 bits)

pin1lbl = Label(sendTab, "Pin 1:")                                          #Create Label for Pin1 dropdown
pin2lbl = Label(sendTab, "Pin 2:")                                          #Create Label for Pin2 dropdown
pin3lbl = Label(sendTab, "Pin 3:")                                          #Create Label for Pin3 dropdown
pin4lbl = Label(sendTab, "Pin 4:")                                          #Create Label for Pin4 dropdown

lbl0.lbl.grid(column=0, row=0)                                              #place protocol selection label (Always On)

cb0 = combobox(window, ["I2C", "UART", "SPI", "SWD", "RS-485", "All", "Custom Packet"])             #create drop down for protocol selection
VHin = TK.Text(sendTab, height=1, width=17)                                  #Voltage Selection
cb2 = combobox(sendTab, ["1kHz", "10kHz", "100kHz", "1MHz"])                #Frequency Selection
VLin = TK.Text(sendTab, height=1, width=17)                                  #Lower volatage level
cb5 = combobox(sendTab, ["3.3V","5V", "12V", "24V" ])                       #Device Power Level
cb6 = combobox(sendTab, ["Data Rates"])                                     #Data Rates 
cb7 = combobox(sendTab, ["Rising Edge", "Falling edge"])                    #Clock Polarity
cb9 = combobox(sendTab, ["0", "1"])                                         #Chip Select Polarity

pin1spi = combobox(sendTab, ["MOSI", "MISO", "SCLK", "SS"])                 #Combobox options for Pin for SPI
pin2spi = combobox(sendTab, ["MOSI", "MISO", "SCLK", "SS"])                 #Combobox options for Pin for SPI
pin3spi = combobox(sendTab, ["MOSI", "MISO", "SCLK", "SS"])                 #Combobox options for Pin for SPI
pin4spi = combobox(sendTab, ["MOSI", "MISO", "SCLK", "SS"])                 #Combobox options for Pin for SPI


cb0.cb.grid(column=1, row=0)                                                #Place drop down for protocols

DataText3 = TK.Text(sendTab, height=1, width=17)                            #Box to enter 8 bit command to board (gets checked)
AddressText = TK.Text(sendTab, height=1, width=17)                          #Box to enter the device address. 
OutConfigTxt = TK.Text(window, height = 15, width = 42, state = "disabled")  #Display sent configurables in this box
OutConfigTxt.grid(column=0, row=6, columnspan=7, padx=(0,0))

WrRetxt = TK.Text(sendTab, height=1, width=17)                                 #read write bit for custom packet send (1 bit)
WrRetxt.insert(TK.END, "1")
ComBittxt = TK.Text(sendTab, height=1, width=17)                                  #Set command bits (3 bits)
ComBittxt.insert(TK.END, "7")
ResisStattxt = TK.Text(sendTab, height=1, width=17)                            #set resister state (either 0, 1, 2)(4 bits)
ResisStattxt.insert(TK.END, "0")


btn1 = Button(sendTab, "Configure")                           #Send configure
Data2SendBtn = Button(sendTab, "Send Data")
ReComBtn = Button(window, "Reset COM Port")
ReComBtn.btn.grid(column = 2, row = 0)
pinSetBtn = Button(sendTab, "Configure Pins")

#Byte Input Config
b2lbl = Label(sendTab, "Byte 2 (As Integer or 'NULL'): ")                                    #Input for Byte 2 Label
b3lbl = Label(sendTab, "Byte 3 (As Integer or 'NULL'): ")                                    #Input for Byte 3 Label
b4lbl = Label(sendTab, "Byte 4 (As Integer or 'NULL'): ")                                    #Input for Byte 4 Label
b5lbl = Label(sendTab, "Byte 5 (As Integer or 'NULL'): ")                                    #Input for Byte 5 Label
byte2in = TK.Text(sendTab, height=1, width=17)                                               #input for manual packet composition for Byte 2
byte3in = TK.Text(sendTab, height=1, width=17)                                               #input for manual packet composition for Byte 3
byte4in = TK.Text(sendTab, height=1, width=17)                                               #input for manual packet composition for Byte 4
byte5in = TK.Text(sendTab, height=1, width=17)                                               #input for manual packet composition for Byte 5

#SendReceieve textbox
B2Rlbl = Label(sendTab, "Bytes to Recieve:")                                                 #Bytes to Receive Label
B2Rtxt = TK.Text(sendTab, height=1, width=17)                                                #Bytes to Receive Input
B2Rtxt.insert(TK.END, "0")                                                                   #Preset to 0

#Choose which objects are displayed based on the protocol chosen

def display_create(window):
    #Create Interface for SPI
    if cb0.cb.get() == 'SPI':
        lbl1.lbl.grid(column=0, row=3)                              #Upper Voltage
        lbl2.lbl.grid(column=0, row=5)                              #Frequency
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

        #Pin Settings
        pin1lbl.lbl.grid(column=0, row=11)                          #Create Label for Pin1 dropdown
        pin2lbl.lbl.grid(column=0, row=12)                          #Create Label for Pin2 dropdown
        pin3lbl.lbl.grid(column=0, row=13)                          #Create Label for Pin3 dropdown
        pin4lbl.lbl.grid(column=0, row=14)                          #Create Label for Pin4 dropdown
        pin1spi.cb.grid(column=1, row=11)                           #Combobox options for Pin for SPI
        pin2spi.cb.grid(column=1, row=12)                           #Combobox options for Pin for SPI
        pin3spi.cb.grid(column=1, row=13)                           #Combobox options for Pin for SPI
        pin4spi.cb.grid(column=1, row=14)                           #Combobox options for Pin for SPI
        pinSetBtn.btn.grid(column=2, row=11)                        #Send the configuration of the pins to the board

        DataText3.grid(column=1, row=10)                            #Data to send
        AddressText.grid(column=1, row=8)                           #Device Address Box

        WrRetxt.grid_forget()                                #read write bit for custom packet send (1 bit)
        ComBittxt.grid_forget()                                  #Set command bits (3 bits)
        ResisStattxt.grid_forget()                             #set resister state (either 0, 1, 2)(4 bits)

        btn1.btn.grid(column=2, row=2)                              #Send configure

        #Byte Input Config
        b2lbl.lbl.grid_forget()                                    #Input for Byte 2 Label
        b3lbl.lbl.grid_forget()                                    #Input for Byte 3 Label
        b4lbl.lbl.grid_forget()                                    #Input for Byte 4 Label
        b5lbl.lbl.grid_forget()                                    #Input for Byte 5 Label
        byte2in.grid_forget()                                      #input for manual packet composition for Byte 2
        byte3in.grid_forget()                                      #input for manual packet composition for Byte 3
        byte4in.grid_forget()                                      #input for manual packet composition for Byte 4
        byte5in.grid_forget()                                      #input for manual packet composition for Byte 5

        #SendReceieve textbox
        B2Rlbl.lbl.grid(column=4, row=2, padx=(50,0))                       #Bytes to Receive Label
        B2Rtxt.grid(column=5, row=2)                                        #Bytes to Receive Input
        Data2Send.lbl.grid(column=4, row=3, padx=(50,0))                    #Data to send
        DataText3.grid(column=5, row=3)                                     #Data to send
        Data2SendBtn.btn.grid(column=6, row=2)                              #Send Data from text box

    #Display I2C Components
    if cb0.cb.get() == 'I2C':
        lbl1.lbl.grid(column=0, row=3)                              #Upper Voltage
        lbl2.lbl.grid(column=0, row=5)                              #Frequency
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

        AddressText.grid(column=1, row=8)                           #Device Address Box

        WrRetxt.grid_forget()                                #read write bit for custom packet send (1 bit)
        ComBittxt.grid_forget()                                  #Set command bits (3 bits)
        ResisStattxt.grid_forget()                             #set resister state (either 0, 1, 2)(4 bits)

        btn1.btn.grid(column=2, row=2)                              #Send configure

        #Pin Labels
        pin1lbl.lbl.grid(column=0, row=11)                          #Create Label for Pin1 dropdown
        pin2lbl.lbl.grid(column=0, row=12)                          #Create Label for Pin2 dropdown
        pin3lbl.lbl.grid(column=0, row=13)                          #Create Label for Pin3 dropdown
        pin4lbl.lbl.grid(column=0, row=14)                          #Create Label for Pin4 dropdown
        pin1spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pin2spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pin3spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pin4spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pinSetBtn.btn.grid(column=2, row=11)                        #Send the configuration of the pins to the board

        #Byte Input Config
        b2lbl.lbl.grid_forget()                                    #Input for Byte 2 Label
        b3lbl.lbl.grid_forget()                                    #Input for Byte 3 Label
        b4lbl.lbl.grid_forget()                                    #Input for Byte 4 Label
        b5lbl.lbl.grid_forget()                                    #Input for Byte 5 Label
        byte2in.grid_forget()                                      #input for manual packet composition for Byte 2
        byte3in.grid_forget()                                      #input for manual packet composition for Byte 3
        byte4in.grid_forget()                                      #input for manual packet composition for Byte 4
        byte5in.grid_forget()                                      #input for manual packet composition for Byte 5

        #SendReceieve textbox
        B2Rlbl.lbl.grid(column=4, row=2, padx=(50,0))                       #Bytes to Receive Label
        B2Rtxt.grid(column=5, row=2)                                        #Bytes to Receive Input
        Data2Send.lbl.grid(column=4, row=3, padx=(50,0))                    #Data to send
        DataText3.grid(column=5, row=3)                                     #Data to send
        Data2SendBtn.btn.grid(column=6, row=2)                              #Send Data from text box

    
    #Display UART Components
    if cb0.cb.get() == 'UART':
        lbl1.lbl.grid(column=0, row=3)                              #Upper Voltage
        lbl2.lbl.grid_forget()                                      #Frequency
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

        AddressText.grid_forget()                                   #Device Address Box

        WrRetxt.grid_forget()                                #read write bit for custom packet send (1 bit)
        ComBittxt.grid_forget()                                  #Set command bits (3 bits)
        ResisStattxt.grid_forget()                             #set resister state (either 0, 1, 2)(4 bits)

        btn1.btn.grid(column=2, row=2)                              #Send configure

        #Pin Labels
        pin1lbl.lbl.grid(column=0, row=11)                          #Create Label for Pin1 dropdown
        pin2lbl.lbl.grid(column=0, row=12)                          #Create Label for Pin2 dropdown
        pin3lbl.lbl.grid(column=0, row=13)                          #Create Label for Pin3 dropdown
        pin4lbl.lbl.grid(column=0, row=14)                          #Create Label for Pin4 dropdown
        pin1spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pin2spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pin3spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pin4spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pinSetBtn.btn.grid(column=2, row=11)                        #Send the configuration of the pins to the board

        #Byte Input Config
        b2lbl.lbl.grid_forget()                                    #Input for Byte 2 Label
        b3lbl.lbl.grid_forget()                                    #Input for Byte 3 Label
        b4lbl.lbl.grid_forget()                                    #Input for Byte 4 Label
        b5lbl.lbl.grid_forget()                                    #Input for Byte 5 Label
        byte2in.grid_forget()                                      #input for manual packet composition for Byte 2
        byte3in.grid_forget()                                      #input for manual packet composition for Byte 3
        byte4in.grid_forget()                                      #input for manual packet composition for Byte 4
        byte5in.grid_forget()                                      #input for manual packet composition for Byte 5

        #SendReceieve textbox
        B2Rlbl.lbl.grid(column=4, row=2, padx=(50,0))                       #Bytes to Receive Label
        B2Rtxt.grid(column=5, row=2)                                        #Bytes to Receive Input
        Data2Send.lbl.grid(column=4, row=3, padx=(50,0))                    #Data to send
        DataText3.grid(column=5, row=3)                                     #Data to send
        Data2SendBtn.btn.grid(column=6, row=2)                              #Send Data from text box


    #Display SWD Components
    if cb0.cb.get() == 'SWD':
        lbl1.lbl.grid(column=0, row=3)                              #Upper Voltage
        lbl2.lbl.grid_forget()                                      #Frequency
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

        AddressText.grid_forget()                                   #Device Address Box

        WrRetxt.grid_forget()                                #read write bit for custom packet send (1 bit)
        ComBittxt.grid_forget()                                  #Set command bits (3 bits)
        ResisStattxt.grid_forget()                             #set resister state (either 0, 1, 2)(4 bits)

        btn1.btn.grid(column=2, row=2)                              #Send configure
        

        #Pin Labels
        pin1lbl.lbl.grid(column=0, row=11)                          #Create Label for Pin1 dropdown
        pin2lbl.lbl.grid(column=0, row=12)                          #Create Label for Pin2 dropdown
        pin3lbl.lbl.grid(column=0, row=13)                          #Create Label for Pin3 dropdown
        pin4lbl.lbl.grid(column=0, row=14)                          #Create Label for Pin4 dropdown
        pin1spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pin2spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pin3spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pin4spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pinSetBtn.btn.grid(column=2, row=11)                        #Send the configuration of the pins to the board

        #Byte Input Config
        b2lbl.lbl.grid_forget()                                    #Input for Byte 2 Label
        b3lbl.lbl.grid_forget()                                    #Input for Byte 3 Label
        b4lbl.lbl.grid_forget()                                    #Input for Byte 4 Label
        b5lbl.lbl.grid_forget()                                    #Input for Byte 5 Label
        byte2in.grid_forget()                                      #input for manual packet composition for Byte 2
        byte3in.grid_forget()                                      #input for manual packet composition for Byte 3
        byte4in.grid_forget()                                      #input for manual packet composition for Byte 4
        byte5in.grid_forget()                                      #input for manual packet composition for Byte 5

        #SendReceieve textbox
        B2Rlbl.lbl.grid_forget()                                            #Bytes to Receive Label
        B2Rtxt.grid_forget()                                                #Bytes to Receive Input
        Data2Send.lbl.grid_forget()                                         #Data to send
        DataText3.grid_forget()                                             #Data to send
        Data2SendBtn.btn.grid_forget()                                      #Send Data from text box


    #display RS-485 Components 
    if cb0.cb.get() == 'RS-485':
        lbl1.lbl.grid(column=0, row=3)                              #Upper Voltage
        lbl2.lbl.grid_forget()                                      #Frequency
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

        AddressText.grid_forget()                                   #Device Address Box

        WrRetxt.grid_forget()                                #read write bit for custom packet send (1 bit)
        ComBittxt.grid_forget()                                  #Set command bits (3 bits)
        ResisStattxt.grid_forget()                             #set resister state (either 0, 1, 2)(4 bits)

        btn1.btn.grid(column=2, row=2)                              #Send configure

        #Pin Labels
        pin1lbl.lbl.grid(column=0, row=11)                          #Create Label for Pin1 dropdown
        pin2lbl.lbl.grid(column=0, row=12)                          #Create Label for Pin2 dropdown
        pin3lbl.lbl.grid(column=0, row=13)                          #Create Label for Pin3 dropdown
        pin4lbl.lbl.grid(column=0, row=14)                          #Create Label for Pin4 dropdown
        pin1spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pin2spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pin3spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pin4spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pinSetBtn.btn.grid(column=2, row=11)                        #Send the configuration of the pins to the board

        #Byte Input Config
        b2lbl.lbl.grid_forget()                                    #Input for Byte 2 Label
        b3lbl.lbl.grid_forget()                                    #Input for Byte 3 Label
        b4lbl.lbl.grid_forget()                                    #Input for Byte 4 Label
        b5lbl.lbl.grid_forget()                                    #Input for Byte 5 Label
        byte2in.grid_forget()                                      #input for manual packet composition for Byte 2
        byte3in.grid_forget()                                      #input for manual packet composition for Byte 3
        byte4in.grid_forget()                                      #input for manual packet composition for Byte 4
        byte5in.grid_forget()                                      #input for manual packet composition for Byte 5

        #SendReceieve textbox
        B2Rlbl.lbl.grid(column=4, row=2, padx=(50,0))                       #Bytes to Receive Label
        B2Rtxt.grid(column=5, row=2)                                        #Bytes to Receive Input
        Data2Send.lbl.grid(column=4, row=3, padx=(50,0))                    #Data to send
        DataText3.grid(column=5, row=3)                                     #Data to send
        Data2SendBtn.btn.grid(column=6, row=2)                              #Send Data from text box

    #Display Custom Options
    if cb0.cb.get() == 'All':
        lbl1.lbl.grid(column=0, row=3)                              #Upper Voltage
        lbl2.lbl.grid(column=0, row=5)                              #Frequency
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

        AddressText.grid(column=1, row=8)                           #Device Address Box

        WrRetxt.grid_forget()                                #read write bit for custom packet send (1 bit)
        ComBittxt.grid_forget()                                  #Set command bits (3 bits)
        ResisStattxt.grid_forget()                             #set resister state (either 0, 1, 2)(4 bits)

        btn1.btn.grid(column=2, row=2)                              #Send configure

        #Pin Labels
        pin1lbl.lbl.grid(column=0, row=11)                          #Create Label for Pin1 dropdown
        pin2lbl.lbl.grid(column=0, row=12)                          #Create Label for Pin2 dropdown
        pin3lbl.lbl.grid(column=0, row=13)                          #Create Label for Pin3 dropdown
        pin4lbl.lbl.grid(column=0, row=14)                          #Create Label for Pin4 dropdown
        pin1spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pin2spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pin3spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pin4spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pinSetBtn.btn.grid(column=2, row=11)                        #Send the configuration of the pins to the board

        #SendReceieve textbox
        B2Rlbl.lbl.grid(column=4, row=2, padx=(50,0))                       #Bytes to Receive Label
        B2Rtxt.grid(column=5, row=2)                                        #Bytes to Receive Input
        Data2Send.lbl.grid(column=4, row=3, padx=(50,0))                    #Data to send
        DataText3.grid(column=5, row=3)                                     #Data to send
        Data2SendBtn.btn.grid(column=6, row=2)                              #Send Data from text box

    if cb0.cb.get() == 'Custom Packet':
        lbl1.lbl.grid_forget()                               #Upper Voltage
        lbl2.lbl.grid_forget()                              #Frequency
        
        lbl4.lbl.grid_forget()                              #Lower Voltage
        lbl5.lbl.grid_forget()                              #Device Power
        lbl6.lbl.grid_forget()                              #Data Rate
        lbl7.lbl.grid_forget()                              #Clock Polarity
        lbl8.lbl.grid_forget()                              #Device Address
        lbl9.lbl.grid_forget()                              #Chip Select Polarity

        WrRelbl.lbl.grid(column=0, row=1)                                  #read write bit for custom packet send (1 bit)
        ComBitlbl.lbl.grid(column=0, row=2)                                   #Set command bits (3 bits)
        ResisStatlbl.lbl.grid(column=0, row=3)                             #set resister state (either 0, 1, 2)(4 bits)

        VHin.grid_forget()                                #Upper Voltage
        cb2.cb.grid_forget()                                #Frequency
        VLin.grid_forget()                                #Lower Voltage Level
        cb5.cb.grid_forget()                                #Device Power
        cb6.cb.grid_forget()                                #Data Rates
        cb7.cb.grid_forget()                               #Clock Polarity
        cb9.cb.grid_forget()                                #Chip Select Polarity

        
        AddressText.grid_forget()                           #Device Address Box

        WrRetxt.grid(column=1, row=1)                                #read write bit for custom packet send (1 bit)
        ComBittxt.grid(column=1, row=2)                                  #Set command bits (3 bits)
        ResisStattxt.grid(column=1, row=3)                             #set resister state (either 0, 1, 2)(4 bits)

        btn1.btn.grid(column=2, row=2)                              #Send configure
        

        #Pin Labels
        pin1lbl.lbl.grid_forget()                                   #Create Label for Pin1 dropdown
        pin2lbl.lbl.grid_forget()                                   #Create Label for Pin2 dropdown
        pin3lbl.lbl.grid_forget()                                   #Create Label for Pin3 dropdown
        pin4lbl.lbl.grid_forget()                                   #Create Label for Pin4 dropdown
        pin1spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pin2spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pin3spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pin4spi.cb.grid_forget()                                    #Combobox options for Pin for SPI
        pinSetBtn.btn.grid_forget()                                 #Send the configuration of the pins to the board

        #Byte Input Config
        b2lbl.lbl.grid(column = 0, row = 15)                                    #Input for Byte 2 Label
        b3lbl.lbl.grid(column = 0, row = 16)                                    #Input for Byte 3 Label
        b4lbl.lbl.grid(column = 0, row = 17)                                    #Input for Byte 4 Label
        b5lbl.lbl.grid(column = 0, row = 18)                                    #Input for Byte 5 Label
        byte2in.grid(column = 1, row = 15)                                               #input for manual packet composition for Byte 2
        byte3in.grid(column = 1, row = 16)                                               #input for manual packet composition for Byte 3
        byte4in.grid(column = 1, row = 17)                                               #input for manual packet composition for Byte 4
        byte5in.grid(column = 1, row = 18)                                               #input for manual packet composition for Byte 5

        #SendReceieve textbox
        B2Rlbl.lbl.grid_forget()                                #Bytes to Receive Label
        B2Rtxt.grid_forget()                                    #Bytes to Receive Input
        Data2Send.lbl.grid_forget()                             #Data to send
        DataText3.grid_forget()                                 #Data to send
        Data2SendBtn.btn.grid_forget()                          #Send Data from text box

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
