"""
State Commands
"""
def  get_state_command():
    return bytes([0x01, 0x00])

def set_state_configuration_command():
    return bytes([0x01, 0x01])

def set_state_data_command():
    return bytes([0x01, 0x02])

def set_state_run_command():
    return bytes([0x01, 0x03])

def set_state_stop_command():
    return bytes([0x01, 0x04])

"""
Configuration Commands
"""
def get_configuration_target_device_voltage():
    return bytes([0x02, 0x00])

def set_configuration_target_device_voltage(voltage):

def get_configuration_pin_parameters(pinNumber):
    if pinNumber < 1 or pinNumber > 4:
        raise Exception('pinNumber should be between 1 and 4, found {}'.format(pinNumber))
    return bytes([0x02, 0x02, pinNumber])

PINPARAMETERS = set(['pullup', 'pulldown', 'tristate', 'disabled'])

def set_configuration_pin_parameters(pinNumber, state):
    if pinNumber < 1 or pinNumber > 4:
        raise Exception('pinNumber should be between 1 and 4, found {}'.format(pinNumber))
    assert state in PINPARAMETERS
    state_bits = 0b00
    if state == 'pullup':
        state_bits = 0b10
    elif state == 'pulldown':
        state_bits = 0b01
    elif state == 'tristate':
        state_bits = 0b11
    return bytes([0x02, 0x03, pinNumber, state_bits])


def get_configuration_data_speed():
    return bytes([0x02, 0x04])

def set_configuration_data_speed(frequency):
    if frequency < 1 or frequency > 10000:
        raise Exception('frequency should be between 1 and 10000, found {}'.format(frequency))
    freq_upper = (frequency >> 8) & 0x00FF
    freq_lower = frequency & 0x00FF
    return bytes([0x02, 0x05])


def get_configuration_differential_mode(pinNumber):
    if pinNumber < 1 or pinNumber > 4:
        raise Exception('pinNumber should be between 1 and 4, found {}'.format(pinNumber))
    return bytes([0x02, 0x06, pinNumber])

def set_configuration_differential_mode(pinNumber, enabled):
    if pinNumber < 1 or pinNumber > 4:
        raise Exception('pinNumber should be between 1 and 4, found {}'.format(pinNumber))
    if enabled is True:
        return bytes([0x02, 0x07, pinNumber, 0x01])
    elif enabled is False:
        return bytes([0x02, 0x07, pinNumber, 0x00])
    raise Exception('enabled should be either True or False')


def get_configuration_pin_mode(pinNumber):
    if pinNumber < 1 or pinNumber > 4:
        raise Exception('pinNumber should be between 1 and 4, found {}'.format(pinNumber))
    return bytes([0x02, 0x08, pinNumber])

PINMODES = set(['disabled', 'input', 'output', 'clock', 'chipselect'])

def set_configuration_pin_mode(pinNumber, mode):
    if pinNumber < 1 or pinNumber > 4:
        raise Exception('pinNumber should be between 1 and 4, found {}'.format(pinNumber))
    assert mode in PINMODES
    mode_bits = 0b000
    if mode == 'input':
        mode_btis = 0b001
    elif mode == 'output':
        mode_bits = 0b010
    elif mode == 'clock':
        mode_bits = 0b011
    elif mode == 'chipselect':
        mode_bits = 0b100
    return bytes([0x02, 0x09, pinNumber, mode_bits])


def get_configuration_data_parameters(pinNumber):
    if pinNumber < 1 or pinNumber > 4:
        raise Exception('pinNumber should be between 1 and 4, found {}'.format(pinNumber))
    return bytes([0x02, 0x0A, pinNumber])

def set_configuration_data_parameters(pinNumber, idleState, polarity):
    if pinNumber < 1 or pinNumber > 4:
        raise Exception('pinNumber should be between 1 and 4, found {}'.format(pinNumber))
    idleState_bits = 0b00
    if idleState is True:
        idleState_bits = 0b10
    elif idleState is not False:
        raise Exception('idleSate should be True or False')
    polarity_bits = 0b00
    if polarity is True:
        polarity_bits = 0b01
    elif polarity is not False:
        raise Exception('polarity should be True or False')
    return bytes([0x02, 0x0B, pinNumber, idleState_bits | polarity_bits])


def get_configuration_pin_logic_levels(pinNumber):
    return bytes([0x02, 0x0C])

def set_configuration_pin_logic_levels(pinNumber, highVoltage, lowVoltage):
    if pinNumber < 1 or pinNumber > 4:
        raise Exception('pinNumber should be between 1 and 4, found {}'.format(pinNumber))
    if highVoltage < lowVoltage or highVoltage > 15 or highVoltage < 0 or lowVoltage > 15 or lowVoltage < 0:
        raise Exception('highVoltage must be >= lowVoltage and both must be in range of [0, 15]')

    high_voltage_scaled = round(((2**12 - 1) / 33) * (16.5 - VH))
    low_voltage_scaled = round(((2**12 - 1) / 33) * (16.5 - VL))

    high_voltage_upper_bits = (high_voltage_scaled >> 8) & 0x00FF
    high_voltage_lower_bits = high_voltage_scaled & 0x00FF

    low_voltage_upper_bits = (low_voltage_scaled >> 8) & 0x00FF
    low_voltage_lower_bits = low_voltage_scaled & 0x00FF

    return bytes([0x02, 0x0D, pinNumber, high_voltage_upper_bits, high_voltage_lower_bits, low_voltage_upper_bits, low_voltage_lower_bits])


"""
Data Commands
"""
def set_data_send(data):
    size = len(data)
    if size > 255 or size <= 0:
        raise Exception('Can only support [1,255] bytes of data, found {} bytes'.format(size))
    return bytearray([0x03, 0x00, size]).append(data)

def set_data_receive(numBytes):
    if numBytes <= 0 or numBytes > 255:
            raise Exception('Can only support [1,255] bytes of data, found {} bytes'.format(numBytes))
    return bytes([0x03, 0x01, numBytes])
