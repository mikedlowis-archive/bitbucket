import pygame
from pygame.locals import *

# State of all Buttons and Axes on the controller
state = {
	'buttons': {
		'A': 0, 
		'B': 0,
		'X': 0,
		'Y': 0,
		'LB': 0,
		'RB': 0,
		'BACK': 0,
		'START': 0,
		'LS': 0,
		'RS': 0,
	},
	'dpad': (0,0),
	'left_stick': {
		'x': 0,
		'y': 0
	},
	'right_stick': {
		'x': 0,
		'y': 0
	},
	'trigger': 0
}

# Queue of button events
button_events = []

# Button ID           0    1    2    3    4     5     6       7        8     9
button_id_lookup = [ 'A', 'B', 'X', 'Y', 'LB', 'RB', 'BACK', 'START', 'LS', 'RS' ]

def handleButtonUp(event):
	btn_name = button_id_lookup[event.button]
	state['buttons'][ btn_name ] = 0

def handleButtonDown(event):
	btn_name = button_id_lookup[event.button]
	state['buttons'][ btn_name ] = 1

def handleJoyAxisMotion(event):
	if (event.axis == 0):
		state['left_stick']['x'] = event.value
	elif (event.axis == 1):
		state['left_stick']['y'] = event.value
	elif (event.axis == 2):
		state['trigger'] = event.value
	elif (event.axis == 3):
		state['right_stick']['y'] = event.value
	elif (event.axis == 4):
		state['right_stick']['x'] = event.value

def handleJoyHatMotion(event):
	state['dpad'] = event.value

# process queued events
def processEvents():
	events = pygame.event.get()
	for event in events:
		if event.type == JOYAXISMOTION:
			handleJoyAxisMotion(event)
		elif event.type == JOYHATMOTION:
			handleJoyHatMotion(event)
		elif event.type == JOYBUTTONDOWN:
			handleButtonDown(event)
		elif event.type == JOYBUTTONUP:
			handleButtonUp(event)
		else:
			print("Unhandled event: ", event)

def get_state():
	return state

# System initialization
def init():
	pygame.init()
	if pygame.joystick.get_count() > 0:
		gamepad = pygame.joystick.Joystick(0)
		gamepad.init()
	else:
		raise "No joystick connected"

def quit():
	pygame.quit()

