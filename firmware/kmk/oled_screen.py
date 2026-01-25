import board
import busio
import displayio
import terminalio
import i2cdisplaybus
from adafruit_display_text import label
import adafruit_displayio_ssd1306

displayio.release_displays()

i2c = busio.I2C(scl=board.SCL, sda=board.SDA)
display_bus = i2cdisplaybus.I2CDisplayBus(i2c, device_address=0x3C)

display = adafruit_displayio_ssd1306.SSD1306(
    display_bus, width=128, height=32
)

display.rotation = 180

text = "DISPLAY OK"
char_w = 6
char_h = 8

text_width = len(text) * char_w
x = (128 - text_width) // 2
y = (32 - char_h) // 2

group = displayio.Group()
group.append(
    label.Label(
        terminalio.FONT,
        text=text,
        x=x,
        y=y,
    )
)

display.root_group = group

def clear_display(display):
    display.root_group = displayio.Group()
