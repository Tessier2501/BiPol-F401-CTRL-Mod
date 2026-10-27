#include "boot_splash.h"
#include "LCD.h"
#include "ui_boot_splash.h"

static uint32_t splash_run_index(uint16_t token)
{
    return (uint32_t)((token >> 12) & 0x000F);
}

static uint32_t splash_run_length(uint16_t token)
{
    return (uint32_t)((token & 0x0FFF) + 1);
}

bool BootSplash_Show(void)
{
    uint32_t i;
    uint32_t total_pixels = 0;
    uint32_t expected_pixels = (uint32_t)UI_BOOT_SPLASH_WIDTH * UI_BOOT_SPLASH_HEIGHT;

    if((UI_BOOT_SPLASH_WIDTH != lcddev.width) || (UI_BOOT_SPLASH_HEIGHT != lcddev.height))
    {
        return false;
    }

    for(i = 0; i < UI_BOOT_SPLASH_RUN_COUNT; i++)
    {
        if(splash_run_index(ui_boot_splash_runs[i]) >= UI_BOOT_SPLASH_COLORS)
        {
            return false;
        }
        total_pixels += splash_run_length(ui_boot_splash_runs[i]);
        if(total_pixels > expected_pixels)
        {
            return false;
        }
    }
    if(total_pixels != expected_pixels)
    {
        return false;
    }

    LCD_ImageBegin(0, 0, UI_BOOT_SPLASH_WIDTH, UI_BOOT_SPLASH_HEIGHT);
    for(i = 0; i < UI_BOOT_SPLASH_RUN_COUNT; i++)
    {
        uint16_t token = ui_boot_splash_runs[i];
        uint16_t color = (uint16_t)(~ui_boot_splash_palette[splash_run_index(token)]);
        LCD_ImageWriteColor(color, (uint16_t)splash_run_length(token));
    }
    LCD_ImageEnd();

    return true;
}
