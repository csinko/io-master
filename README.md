# io-master
Dominate the I/O!

## Subsystems Overviews

### [GUI](https://github.com/csinko/io-master/wiki/GUI-Subsystem)
The purpose of the GUI interface is to create a user friendly yet customizable program to help users tell the micro-controller to use whatever protocols that the user wishes to use from the provided list. The interface will include drop down menus to adjust the protocol that the board will use.  This interface will also allow the user to select what information they want to send through the device as well as start and stop the flow of information through the device. The GUI will also define the hardware pins and clock speeds needed to run whichever protocol is selected. This includes setting the voltage levels that the board will expect to see. This will define what is seen as a 1 or a 0. The gui will most likely be done using python. Possible challenges include figuring out which GUI base to use in python. Possible options are appJar, TkInter, PyQT, or Kivy. More research will be done on each to figure out which one is best suited for this project. 

### [MCU Firmware](https://github.com/csinko/io-master/wiki/MCU-Firmware-Subsystem)
The MCU is responsible for reading and writing the logic. Firmware will need to be designed to load in data from the computer, connect it to the corresponding DMA register that routes to the correct output, and stream data as it comes in. Likewise, the firmware will also need to read in data over the DMA, and transfer it to send to the computer when appropriate. Strict scheduling and context switching will need to be designed in order to ensure smooth operation at high frequencies. Other contexts will need to be considered, such as reading from one set of I/O and writing to another set, or recording logic data read in to an SD card.

### [MCU Power and Interface](https://github.com/csinko/io-master/wiki/MCU-Power-and-Interface-Subsystem)
MCU Power and Interface is responsible for receiving configuration and executing commands. These commands will come through the serial bus and need to be parsed/decoded. Execution will include adjusting the clock speed, target voltage levels, and re-configuring pins as specified by the commands received.

These capabilities will be crucial for switching between protocols on the multi-use pins. The challenges will be primarily with creating a good control scheme for managing all the necessary multiplexers to route signals to all the proper pins, at the correct speed and voltages.

### [I/O Level Shifting and Logic](https://github.com/csinko/io-master/wiki/IO-Level-Shifting-and-Logic-Subsystem)
The Level Shifting and Logic Subsystem is responsible for providing electrical conversion between the microcontroller interface and the device under test. This includes acting as an output and input to the microcontroller, providing logic-high, logic-low, and floating output states, bidirectional logic-level conversion, and capability to drive/receive differential or single-ended lines. This block should be fully configurable via control signals from the microcontroller. This includes setting the high and low voltages, optional pull-up/pull-down resistors, and multiplexing the line between single-ended and differential hardware. Design challenges include implementing a bidirectional differential transceiver and ensuring that multiplexing does not affect high speed operation.

### [Circuit Protection](https://github.com/csinko/io-master/wiki/Circuit-Protection-Subsystem)
Circuit protection is a crucial part of any device to help safeguard against unexpected and unplanned power issues. This is important to prevent injury to users, damage to the device and potentially fire. This will include having fuses, diodes, conformal coating, reverse polarity protection, over voltage protection and will protect against accidental grounding.
Some challenges that may occur is due to the learning curve of designing the circuit protection circuit. Designing a circuit that can account for over voltage protection, short circuit protection, reverse polarity protection, etc and maintain a small footprint on a circuit board could prove to be difficult. Accounting for different/higher voltage levels used by the different protocols may become a challenge.
