package communication;

import jssc.*;

public class SerialComm {

	SerialPort port;

	private boolean debug;  // Indicator of "debugging mode"
	
	// This function can be called to enable or disable "debugging mode"
	void setDebug(boolean mode) {
		debug = mode;
	}	
	

	// Constructor for the SerialComm class
	public SerialComm(String name) throws SerialPortException {
		port = new SerialPort(name);		
		port.openPort();
		port.setParams(SerialPort.BAUDRATE_9600,
			SerialPort.DATABITS_8,
			SerialPort.STOPBITS_1,
			SerialPort.PARITY_NONE);
		
		debug = false; // Default is to NOT be in debug mode
	}
	
	public void writeByte(byte myByte) {
		try {
			port.writeByte(myByte);
			if (debug == true) {
				System.out.print("<0x" + String.format("%02x",myByte) + ">");
			}
		} catch(SerialPortException e) {
			e.printStackTrace();
		}
	}
	
	public byte readByte() {
		try {
			byte[] buffer = port.readBytes(1);
			if (buffer != null && buffer.length > 0) {
				if (debug == true) {
					System.out.print("[0x" + String.format("%02x",buffer[0]) + "]");
				}
				return buffer[0];
			}
		} catch(SerialPortException e) {
			e.printStackTrace();
		}
		return -1;
	}
	
	public boolean available() {
		try {
			return (port.getInputBufferBytesCount() > 0);
		} catch(SerialPortException e) {
			e.printStackTrace();
			return false;
		}
	}
	
}