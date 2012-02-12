import serial

# Constants
ACK  = chr(0x01)
INIT = chr(0x55)

def init(port,baud):
	conn = serial.Serial(port - 1)
	conn.baudrate = baud
	conn.timeout = 1
	
	# try sending the magic byte a few times to see if we get a response
	success = False
	tries = 10
	while tries > 0:
		conn.write( INIT )
		success = recv_ack(conn)
		if success:
			tries = 0
		else:
			tries -= 1

	if not success:
		raise "Could not communicate with device"
		
	return conn

def send(conn,byte):
	ack_byte = None
	conn.write( chr(byte) )
	return recv_ack( conn )

def recv_ack(conn):
	ack_byte = conn.read()
	if (ack_byte == ACK):
		return True
	else:
		return False

