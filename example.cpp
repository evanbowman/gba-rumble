#include "gba.h"
#include "gbp_logo.hpp"
#include "rumble.h"



bool unlock_gbp()
{
    bool gbp_detected = false;

    static const int splashscreen_duration(125);

    static volatile u32* keys = (volatile u32*)0x04000130;

    // Show the Gameboy Player splash screen.
    memcpy16((u16*)0x6008000, gbp_logo_pixels, (sizeof gbp_logo_pixels) / 2);
    memcpy16((u16*)0x6000000, gbp_logo_tiles, (sizeof gbp_logo_tiles) / 2);
    memcpy16(MEM_BG_PALETTE, gbp_logo_palette, (sizeof gbp_logo_palette) / 2);

    for (int i = 0; i < splashscreen_duration; ++i) {
        // If the gameboy player hardware/software accepted our spash screen,
        // the system will raise a joystick state where L+R+U+D on the D-Pad are
        // all pressed at once. If we see this keymask, we know that we have
        // successfully unlocked the gameboy player.
        if (*keys == 0x030F) {
            gbp_detected = true;
        }

        VBlankIntrWait();
    }

    // Hide the gameboy player logo. Ram reset not required, just the simplest
    // way of clearing the tiles, for demonstration purposes.
    RegisterRamReset(RESET_VRAM);

    return gbp_detected;
}



int main()
{
    REG_DISPCNT = MODE_0 | BG0_ENABLE;
    *((volatile u16*)0x4000008) = 0x0088;

    irqInit();
    irqEnable(IRQ_VBLANK);

    if (unlock_gbp()) {

        RumbleGBPConfig conf{[](void (*rumble_isr)(void)) {
            irqEnable(IRQ_SERIAL);
            irqSet(IRQ_SERIAL, rumble_isr);
        }};

        rumble_init(&conf);

    } else {
        rumble_init(nullptr);
    }

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

        VBlankIntrWait();
    }
}
