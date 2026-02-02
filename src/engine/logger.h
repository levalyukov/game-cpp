#pragma once

#include <iostream>

#define LOGI_COLOR  "\x1b[0m"
#define LOGO_COLOR  "\x1b[32m"
#define LOGE_COLOR  "\x1b[31m"
#define LOGW_COLOR  "\x1b[33m"

#define LOGI(msg, ...) {printf(LOGI_COLOR "[*] " LOGI_COLOR msg "\n", ##__VA_ARGS__);}
#define LOGO(msg, ...) {printf(LOGO_COLOR "[+] " LOGI_COLOR msg "\n", ##__VA_ARGS__);}
#define LOGE(msg, ...) {printf(LOGE_COLOR "[-] " LOGI_COLOR msg "\n", ##__VA_ARGS__);}
#define LOGW(msg, ...) {printf(LOGW_COLOR "[!] " LOGI_COLOR msg "\n", ##__VA_ARGS__);}