# gba-rumble
A minimal rumble library for the GBA. Supports rumble on either the GameboyPlayer, or on a GameboyAdvance via a cartridge rumble motor. I basically developed this based on the resources on GBATEK, plus blackbox testing ROMS by feeding in data and adding print statements to some emulators. Tested on an actual GameboyPlayer.

# Setup and Usage
This rumble library does not unlock the Gameboy Player. Prior initializing the library, you will need to display the Gameboy Player splash screen for a few frames. If the console accepts your splash screen, the GBP will notify your application by sending a pattern of specific button signals. See example.cpp for an example, and see the releases page of this repository for an example rom.

# Compiling
It's a single C source file with no dependencies, just drop rumble.c/rumble.h into your project.

# Licence
MIT. No need to credit me.
