#!/bin/bash
# Uses PyBluez

import bluetooth
import json
import os.path
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
        if device[1] == "BT KB Control":
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

sock.send("Hello, this is message from Logan!!!!")
sock.close()