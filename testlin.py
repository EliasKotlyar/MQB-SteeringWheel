#!/usr/bin/env python3
"""
Class for driving
"""
import logging
import time
import can
from time import sleep
bus = can.interface.Bus(channel="sllin0", bustype="socketcan")
msg1 = can.Message(
    arbitration_id=0x0F, is_extended_id=False, is_remote_frame=True
)
msg2 = can.Message(
    arbitration_id=0x0E, is_extended_id=False, is_remote_frame=True
)
msg3 = can.Message(
    arbitration_id=0x0D, is_extended_id=False, is_remote_frame=True,
    data=[0x1A ,0xF9, 0xFF,0xFF  ]
)
# 0.1 = 100ms
bus.send_periodic(msg2, 0.1)
bus.send_periodic(msg3, 0.1)
bus.send_periodic(msg4, 0.2)


try:
    while True:
        for msg in bus:
            if msg.arbitration_id == 0x0F:
                data = msg.data
                #print(data[2])
        sleep(1)
except KeyboardInterrupt:
    pass
