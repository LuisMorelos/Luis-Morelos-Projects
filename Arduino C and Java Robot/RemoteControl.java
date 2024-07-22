package communication;

import java.io.IOException;

import jssc.*;

enum State {
	READ_MAGIC,
	READ_KEY,
	READ_INFO,
	READ_ERROR,
	READ_TIME,
	READ_POT,
	READ_SENSOR
}

public class RemoteControl {
	final byte magicNum = 0x21;
	final byte infoString = 0x30;
	final byte errorString = 0x31;
	final byte timeStamp = 0x32;
	final byte potReading = 0x33;
	final byte sensorReading = 0x34;
	final String ERROR_MESSAGE = "TOO HIGH!!!";
	final byte movementKey = 0x35;
	final byte movementTime = 0x0A;

	final private SerialComm port;

	public RemoteControl(String portname) throws SerialPortException {
		port = new SerialComm(portname);
	}

	public void run() {
		// insert FSM code here to read messages from port
		// and write to console
		State state = State.READ_MAGIC;
		int index = 0;
		long infoStringSize = 0;
		long errorStringSize = 0;
		String tempInfo = "";
		String tempError = "";
		long value = 0;

		while (true) {
			if (port.available()) {
				byte b = port.readByte();
				switch (state) {
				case READ_MAGIC:
					if (b == this.magicNum) {
						state = State.READ_KEY;
					}
					break;

				case READ_KEY:
					switch (b) {
					case infoString:
						state = State.READ_INFO;
						index = 0;
						value = 0;
						infoStringSize = 0;
						tempInfo = "";
						break;
					case errorString:
						state = State.READ_ERROR;
						index = 0;
						value = 0;
						errorStringSize = 0;
						tempError = "";
						break;
					case timeStamp:
						state = State.READ_TIME;
						index = 0;
						value = 0;
						break;
					case potReading:
						state = State.READ_POT;
						index = 0;
						value = 0;
						break;
					case sensorReading:
						state = State.READ_SENSOR;
						index = 0;
						value = 0;
						break;
					default:
						state = State.READ_MAGIC;
						break;
					}
					break;

				case READ_INFO:
					if (index < 2) {
						infoStringSize = (infoStringSize << 8) | (b & 0xff);
						index++;
					}
					else if (index >= 2) {
						if (index < infoStringSize + 1) {
							tempInfo += (char)b;
							index++;
						}
						else {
							state = State.READ_MAGIC;
							System.out.println(tempInfo);
						}
					}
					break;

				case READ_ERROR:
					if (index < 2) {
						errorStringSize = (errorStringSize << 8) | (b & 0xff);
						index++;
					}
					else if (index >= 2) {
						if (index < errorStringSize + 1) {
							tempError += (char)b;
							index++;
						}
						else {
							state = State.READ_MAGIC;
							System.out.println(tempError);
						}
					}
					break;

				case READ_TIME:
					value = (value << 8) | (b & 0xff);
					index++;
					if (index == 4) {
						System.out.println(value);
						state = State.READ_MAGIC;
					}
					break;

				case READ_POT:
					value = (value << 8) | (b & 0xff);
					index++;
					if (index == 4) {
						System.out.println(value);
						state = State.READ_MAGIC;
					}
					break;

				case READ_SENSOR:
					value = (value << 8) | (b & 0xff);
					index++;
					if (index == 4) {
						double reading = (value * 0.0343) / 2;
						System.out.println(reading);
						state = State.READ_MAGIC;
					}
					break;

				default:
					state = State.READ_MAGIC;
					break;
				}
			}
			
			try {
				if (System.in.available() > 0) {
					port.writeByte(magicNum);
					port.writeByte(movementKey);
					port.writeByte((byte)System.in.read());
					port.writeByte(movementTime);
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	public static void main(String[] args) throws SerialPortException {
		RemoteControl rc = new RemoteControl("COM3"); // Adjust this to be the right port for your machine
		rc.run();
	}
}
