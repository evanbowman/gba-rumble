# gba-rumble
A minimal rumble library for the GBA. Supports rumble on either the GameboyPlayer, or on a GameboyAdvance via a cartridge rumble motor. I basically developed this based on the resources on GBATEK, plus blackbox testing ROMS by feeding in data and adding print statements to some emulators. Tested on an actual GameboyPlayer.

# Setup and Usage
This rumble library does not unlock the Gameboy Player. Prior initializing the library, you will need to display the Gameboy Player splash screen for a few frames. If the console accepts your splash screen, the GBP will notify your application by sending a pattern of specific button signals. For an example of gameboy player unlocking, see here: https://github.com/evanbowman/blind-jump-portable/blob/20210108-external-link-do-not-delete/source/platform/gba/gba_platform.cpp#L525

Usage example:
```C++
// C++

if (unlock_gameboy_player()) {

    RumbleGBPConfig conf{[](void (*rumble_isr)(void)) {
        irqEnable(IRQ_SERIAL);
        irqSet(IRQ_SERIAL, rumble_isr);
    }};

    rumble_init(&conf);

 } else {
    rumble_init(nullptr);
 }

// ...

// main loop:

RumbleState current_state = rumble_stop;

int counter = 0;

while (true) {
    // should be called approx. once per frame.
    rumble_update();

    if (++counter == 80) {
        counter = 0;
        if (current_state == rumble_stop) {
            current_state = rumble_start;
        } else {
            current_state = rumble_stop;
        }
        rumble_set_state(current_state);
    }

    your_vsync_function();
}
```

# Compiling
It's a single C source file with no dependencies, just drop it into your project.

# Licence
MIT. No need to credit me.
