import board
from kmk.kmk_keyboard import KMKKeyboard
from kmk.keys import KC
from kmk.scanners import DiodeOrientation

# Modules
from kmk.modules.encoder import EncoderHandler
from kmk.modules.macros import Macros

# Extensions
from kmk.extensions.rgb import RGB
from kmk.extensions.media_keys import MediaKeys

keyboard = KMKKeyboard()

# Adding Modules and Extensions
macros = Macros()
keyboard.modules.append(macros)

encoder_handler = EncoderHandler()
keyboard.modules.append(encoder_handler)

keyboard.extensions.append(MediaKeys())

#
# --- Hardware pin mapping ---
#
# Columns                : D0, D1, D2
# Rows                   : D9, D8, D7
# Rotary encoder A/B     : D6, D10
# RGB data               : D3
# OLED I2C               : SDA=D5, SCL=D4

keyboard.col_pins = (board.D0, board.D1, board.D2)
keyboard.row_pins = (board.D9, board.D8, board.D7)

keyboard.diode_orientation = DiodeOrientation.COL2ROW

keyboard.keymap = [
    [
        KC.MPRV, KC.MPLY, KC.MNXT,  # Row 0
        KC.A, KC.S, KC.D,  # Row 1 (Placeholder)
        KC.Z, KC.X, KC.C,  # Row 2 (Placeholder)
    ]
]


encoder_handler.pins = ((board.D6, board.D10, None, False),)
encoder_handler.map = [
    [[KC.VOLD, KC.VOLU, KC.MUTE], None]
]

# rgb = RGB(pixel_pin=board.GP29, num_pixels=2)
# keyboard.extensions.append(rgb)

keyboard.go()