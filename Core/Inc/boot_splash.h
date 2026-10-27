#ifndef BIPOL_F401_CTRL_BOOT_SPLASH_H
#define BIPOL_F401_CTRL_BOOT_SPLASH_H

#include <stdbool.h>

#define BOOT_SPLASH_DURATION_MS  3000U

//绘制开机启动屏；资源校验失败时返回 false，调用方直接进入标准界面
bool BootSplash_Show(void);

#endif //BIPOL_F401_CTRL_BOOT_SPLASH_H
