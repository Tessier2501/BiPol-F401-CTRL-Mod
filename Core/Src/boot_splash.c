#include "boot_splash.h"
#include "LCD.h"
#include "ui_boot_splash.h"
#include "stdio.h"

_Static_assert(UI_BOOT_SPLASH_WIDTH == 480, "boot splash width must be 480");
_Static_assert(UI_BOOT_SPLASH_HEIGHT == 320, "boot splash height must be 320");
_Static_assert(UI_BOOT_SPLASH_COLORS <= 16, "boot splash palette exceeds 16 colours");
_Static_assert(UI_BOOT_SPLASH_COLORS * 2 + UI_BOOT_SPLASH_RUN_COUNT * 2 <= 24 * 1024,
               "boot splash asset exceeds the 24 KiB budget");

void BootSplash_Show(void)
{
    uint32_t i;
    uint32_t total_pixels = 0;
    uint32_t expected_pixels = (uint32_t)UI_BOOT_SPLASH_WIDTH * UI_BOOT_SPLASH_HEIGHT;

    for(i = 0; i < UI_BOOT_SPLASH_RUN_COUNT; i++)
    {
        uint16_t token = ui_boot_splash_runs[i];
        if(((token >> 12) & 0x000F) >= UI_BOOT_SPLASH_COLORS)
        {
            printf("BootSplash: palette index out of range\r\n");
            Error_Handler();
        }
        total_pixels += (uint32_t)((token & 0x0FFF) + 1);
    }
    if(total_pixels != expected_pixels)
    {
        printf("BootSplash: run stream does not cover the screen\r\n");
        Error_Handler();
    }

    LCD_ImageBegin(0, 0, UI_BOOT_SPLASH_WIDTH, UI_BOOT_SPLASH_HEIGHT);
    for(i = 0; i < UI_BOOT_SPLASH_RUN_COUNT; i++)
    {
        uint16_t token = ui_boot_splash_runs[i];
        uint16_t color = (uint16_t)(~ui_boot_splash_palette[(token >> 12) & 0x000F]);
        LCD_ImageWriteColor(color, (uint16_t)((token & 0x0FFF) + 1));
    }
    LCD_ImageEnd();
}
