import math
import time

import serial


def send(
    ser: serial.Serial,
    power: bool = False,
    home: bool = False,
    zr: bool = False,
    zl: bool = False,
    y: bool = False,
    x: bool = False,
    l: bool = False,
    r: bool = False,
    down: bool = False,
    up: bool = False,
    left: bool = False,
    right: bool = False,
    start: bool = False,
    select: bool = False,
    b: bool = False,
    a: bool = False,
    touch_screen: tuple[int, int] | None = None,
    c_stick: tuple[int | None, int | None] = (None, None),
    circle_pad: tuple[int | None, int | None] = (None, None),
):
    byte0 = 0x4A
    byte1 = (
        (power << 7)
        | (home << 6)
        | (zr << 5)
        | (zl << 4)
        | (y << 3)
        | (x << 2)
        | (l << 1)
        | r
    )
    byte2 = (
        (down << 7)
        | (up << 6)
        | (left << 5)
        | (right << 4)
        | (start << 3)
        | (select << 2)
        | (b << 1)
        | a
    )
    touch_x = max(0, min(319, touch_screen[0])) if touch_screen else 0
    touch_x_msb = (touch_x >> 8) & 1
    touch_flag = 1 if touch_screen is not None else 0
    c_stick_x_flag = 1 if c_stick[0] is not None else 0
    c_stick_y_flag = 1 if c_stick[1] is not None else 0
    circle_pad_x_flag = 1 if circle_pad[0] is not None else 0
    circle_pad_y_flag = 1 if circle_pad[1] is not None else 0
    byte3 = (
        (touch_flag << 7)
        | (c_stick_x_flag << 6)
        | (c_stick_y_flag << 5)
        | (circle_pad_x_flag << 4)
        | (circle_pad_y_flag << 3)
        | touch_x_msb
    )
    byte4 = touch_x & 0xFF
    byte5 = max(0, min(239, touch_screen[1])) if touch_screen else 0
    byte6 = max(0, min(255, c_stick[0])) if c_stick[0] else 0
    byte7 = max(0, min(255, c_stick[1])) if c_stick[1] else 0
    byte8 = max(0, min(255, circle_pad[0])) if circle_pad[0] else 0
    byte9 = max(0, min(255, circle_pad[1])) if circle_pad[1] else 0
    ser.write(
        bytes([byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7, byte8, byte9])
    )


def draw_circle(ser, cx, cy, r, steps):
    for i in range(steps + 1):
        angle = 2 * math.pi * i / steps
        x = int(cx + r * math.cos(angle))
        y = int(cy + r * math.sin(angle))
        send(ser, touch_screen=(x, y))
        time.sleep(0.05)
    send(ser)
