# Media Macropad

This is my submission for Hackpad! Has the following very cool features

- 2 Neopixels
- A 128x32 OLED screen
- 9 keys in a 3x3 orientation
- KMK firmware

## Schematic

Here's a picture of the schematic

![Schematic for Media Macropad](/assets/Schematic.png)

## PCB

I had to rework the PCB traces a few times to make space for mounting holes, but it worked out in the end. The dimensions of the PCB are 99x95 (WxH)

![PCB for Media Macropad](/assets/PCB.png)

## CAD

Was relatively painless to make the case once I finalised my PCB design, the only issue was I went back and forth a few times.

![3D Model of entire Media Macropad](/assets/CAD_PCB.png)

Here's the base and the shell of the case as individual parts.

![3D Model of the case for the Macropad](/assets/CAD_NOPCB.png)

## Firmware

The firmware was build with KMK and Python. The screen is unimplemented as of now, but will be Soon™.
There is now a better, alternative firmware created with QMK which also supports KIN to send information to the keyboard (Use the non-via one)

## Bill of Materials

Parts:

- 9x Cherry MX Switches
- 2x SK6812 MINI Leds
- 1x XIAO RP2040
- 9x Blank DSA Keycaps
- 4x M3x16 screws
- 4x M3x8 screws
- 8x M3 Heatset
- 9x Through-hole 1N4148 Diodes
- 1x EC11 Rotary encoder
- 1x 128x32 0.91 inch OLED display

Other Stuff:

- The PCB
- The Case, comprised of two 3D printed parts

## Credits

Here's a list of libraries and resources I used to create my hackpad

### Kicad Libraries

- XIAO footprints/schematics - <https://github.com/Seeed-Studio/OPL_Kicad_Library>
- 0.91 OLED Display footprints - <https://github.com/gorbachev/KiCad-SSD1306-0.91-OLED-4pin-128x32.pretty>
- Rotary Encoder footprints - <https://kicad.github.io/footprints/Rotary_Encoder>

### 3D Models

- SK6812 LED - <https://grabcad.com/library/sk6812-mini-sk6814-smd3535-1>
- Cherry MX Switches - <https://grabcad.com/library/cherry-mx-switches-mx-1>
- Rotary Encoder - <https://grabcad.com/library/rotary-encoder-17>
- OLED Display - <https://grabcad.com/library/display-oled128x32-1>
- XIAO RP2040 - <https://grabcad.com/library/seeed-studio-xiao-rp2040-1>

### Tutorials/References

- Duccs Fidget Toy - <https://github.com/hackclub/hackpad/tree/main/hackpads/Duccs%20Fidget%20Toy>
- Cyao's Mega Macropad - <https://github.com/hackclub/hackpad/tree/main/hackpads/cyaopad>
- Orpheuspad - <https://github.com/hackclub/hackpad/blob/main/hackpads/orpheuspad/pcb/.gitignore>
- Joe Scotto's PCB Design Video - <https://www.youtube.com/watch?v=8WXpGTIbxlQ>
- KMK Docs - <https://github.com/KMKfw/kmk_firmware/tree/main/docs/en>
