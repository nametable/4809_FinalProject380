#!/bin/bash
# Uses PyBluez

import bluetooth
import json
import os.path
import time
import keyboard
import random
import string
import pandas as pd
from queue import Queue
from time import sleep, time
rfcomm_service = None

if os.path.exists('service_cache.json'):
    with open('service_cache.json', 'r') as json_cache_file:
        rfcomm_service = json.load(json_cache_file)

if (not rfcomm_service):
    nearby_devices = bluetooth.discover_devices(lookup_names=True)
    print("Found {} devices.".format(len(nearby_devices)))

    device_id = ''
    for device in nearby_devices:
        print(device)
        if device[1] == "BT KB Control": #device name - change if need be
            device_id = device[0]


    for service in bluetooth.find_service(address=device_id):
        if service['protocol'] == 'RFCOMM': # rfcomm protocol
            rfcomm_service = service

    with open('service_cache.json', 'w') as json_cache_file:
        json.dump(rfcomm_service, json_cache_file)

port = rfcomm_service['port']
name = rfcomm_service['name']
host = rfcomm_service['host']

print(f'Connecting to {name}:{host} on port {port}')

sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
sock.connect((host,port))

key_queue = Queue()

keyboard.start_recording(key_queue)
start_time = time()
test_string = ''.join(random.choice(string.printable[:96]) for _ in range(128))
sock.send(test_string + "\n")
input()
# keyboard.wait('esc')
keyboard.stop_recording()

sock.close()

last_time = start_time
current_time = 0
time_between_presses = [0]
time_of_presses = [start_time]
name_presses = ['START']
print(f'T: {start_time}')
for evt in key_queue.queue:
    if evt.event_type == 'down' and evt.name != 'enter' and evt.name != 'shift':
        current_time = evt.time
        print(f'T: {evt.time} -> {evt.name} #{evt.event_type}')
        print(f'{current_time - last_time}')
        time_of_presses.append(evt.time)
        time_between_presses.append(current_time - last_time)
        name_presses.append(evt.name)
        last_time = current_time
    
print(f'Avg Time Between presses: {sum(time_between_presses) / len(time_between_presses)}')

# with open('')

df = pd.DataFrame(
    {
        "key": name_presses,
        "time": time_of_presses,
        "time_since_last_press": time_between_presses
    }
)

df.to_csv('performance_data.csv')