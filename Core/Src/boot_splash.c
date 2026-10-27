#include "boot_splash.h"
#include "LCD.h"
#include "ui_boot_splash.h"

void BootSplash_Show(void)
{
    uint32_t i;

    LCD_ImageBegin(0, 0, UI_BOOT_SPLASH_WIDTH, UI_BOOT_SPLASH_HEIGHT);
    for(i = 0; i < UI_BOOT_SPLASH_RUN_COUNT; i++)
    {
        uint16_t token = ui_boot_splash_runs[i];
        uint16_t color = (uint16_t)(~ui_boot_splash_palette[(token >> 12) & 0x000F]);
        LCD_ImageWriteColor(color, (uint16_t)((token & 0x0FFF) + 1));
    }
    LCD_ImageEnd();
}
