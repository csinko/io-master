import tkinter as TK
import usb.core
import usb.util
import serial
import time
import threading
import serial.tools.list_ports
from tkinter import *
from tkinter import ttk
from tkinter import messagebox


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

    Packet_Bytes = bytearray()
    #print(Packet_Bytes)
    Packet_Bytes.append(commandByte)#byte1
    #print(Packet_Bytes)
    Packet_Bytes.append(UVH)#byte2
    #print(Packet_Bytes)
    Packet_Bytes.append(LVH)#byte3
    #print(Packet_Bytes)
    Packet_Bytes.append(UVL)#byte4
    #print(Packet_Bytes)
    Packet_Bytes.append(LVL)#byte5
    print(Packet_Bytes)

    #sendCommmand(packet)


def main():
    rewr = 1
    combits = 4
    resst = 2

    VH = 3.3
    VL = -3.3

    byteSend(rewr, combits, resst, VH, VL)

if (__name__ == '__main__'):
    main()


