import controller
import comm
import time
import math

def update_servo_pos(conn):
	state = controller.get_state()
	new_pos = int((-1 * math.degrees( math.asin( state['trigger'] ) )) + 90)
	print new_pos
	comm.send(conn,new_pos)

# Main entry
if __name__ == "__main__":
	conn = comm.init(6,115200)
	controller.init()
	while True:
		controller.processEvents()
		update_servo_pos(conn)
	conn.close()

