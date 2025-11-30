import board

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

#
# --- Hardware pin mapping ---
#
# Columns                : Column0, 1, 2 = GP26, GP27, GP28
# Rows                   : Row0, 1, 2    = GP4, GP2, GP1
# Rotary encoder A/B     : GP0, GP3
# RGB data               : GP29
# OLED I2C               : SDA=GP6, SCL=GP7

keyboard.col_pins = (board.GP26, board.GP27, board.GP28)
keyboard.row_pins = (board.GP4, board.GP2, board.GP1)

keyboard.diode_orientation = DiodeOrientation.COL2ROW

macros = Macros()
keyboard.modules.append(macros)

keyboard.extensions.append(MediaKeys())

keyboard.keymap = [
    [
        KC.MPRV, KC.MPLY, KC.MNXT,  # Row 0
        KC.A, KC.S, KC.D,  # Row 1 (Placeholder)
        KC.Z, KC.X, KC.C,  # Row 2 (Placeholder)
    ]
]

encoder_handler = EncoderHandler()
encoder_handler.pins = ((board.GP0, board.GP3, None, False),)
encoder_handler.map = (
    ((KC.VOLD, KC.VOLU, KC.NO),)
)

keyboard.modules.append(encoder_handler)

rgb = RGB(pixel_pin=board.GP29, num_pixels=2)
keyboard.extensions.append(rgb)