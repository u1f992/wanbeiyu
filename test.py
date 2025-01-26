import serial


# | Byte | Bit | Description    |
# | ---- | --- | -------------- |
# |  0   |  7  | 1  \           |
# |      |  6  | 1   \          |
# |      |  5  | 1              |
# |      |  4  | 1     0xfb     |
# |      |  3  | 1              |
# |      |  2  | 0    /         |
# |      |  1  | 1   /          |
# |      |  0  | 1  /           |
# | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
# |  1   |  7  | Power          | 0=release, 1=hold
# |      |  6  | Home           |
# |      |  5  | ZR             |
# |      |  4  | ZL             |
# |      |  3  | Y              |
# |      |  2  | X              |
# |      |  1  | L              |
# |      |  0  | R              |
# | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
# |  2   |  7  | Down           |
# |      |  6  | Up             |
# |      |  5  | Left           |
# |      |  4  | Right          |
# |      |  3  | Start          |
# |      |  2  | Select         |
# |      |  1  | B              |
# |      |  0  | A              |
# | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
# |  3   |  7  | Touch Screen   |
# |      |  6  | C Stick X      |
# |      |  5  | C Stick Y      |
# |      |  4  | Circle Pad X   |
# |      |  3  | Circle Pad Y   |
# |      |  2  | (Reserved)     |
# |      |  1  | (Reserved)     |
# |      |  0  | \              |
# | ~~~~ | ~~~ | ~\~~~~~~~~~~~~ |
# |  4   |  7  |                |
# |      |  6  | Touch Screen X |
# |      |  5  |                |
# |      |  4  | left-to-right, |
# |      |  3  | clamped to 319 |
# |      |  2  |                |
# |      |  1  |  /             |
# |      |  0  | /              |
# | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
# |  5   |  7  | \              |
# |      |  6  |                |
# |      |  5  | Touch Screen Y |
# |      |  4  |                |
# |      |  3  | top-to-bottom, |
# |      |  2  | clamped to 239 |
# |      |  1  |                |
# |      |  0  | /              |
# | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
# |  6   |  7  | \              |
# |      |  6  |                |
# |      |  5  | C Stick X      |
# |      |  4  |                |
# |      |  3  | left-to-right  |
# |      |  2  |                |
# |      |  1  |  /             |
# |      |  0  | /              |
# | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
# |  7   |  7  | \              |
# |      |  6  |                |
# |      |  5  | C Stick Y      |
# |      |  4  |                |
# |      |  3  | bottom-to-top  |
# |      |  2  |                |
# |      |  1  |  /             |
# |      |  0  | /              |
# | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
# |  8   |  7  | \              |
# |      |  6  |                |
# |      |  5  | Circle Pad X   |
# |      |  4  |                |
# |      |  3  | left-to-right  |
# |      |  2  |                |
# |      |  1  |  /             |
# |      |  0  | /              |
# | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
# |  9   |  7  | \              |
# |      |  6  |                |
# |      |  5  | Circle Pad Y   |
# |      |  4  |                |
# |      |  3  | bottom-to-top  |
# |      |  2  |                |
# |      |  1  |  /             |
# |      |  0  | /              |
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
    byte0 = 0xFB
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
