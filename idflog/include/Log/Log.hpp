#include <cstdio>

#if ESP_PLATFORM
#include <esp_log.h>
#endif

// Note: define tags in your files like this:
// constexpr const char *TAG = "MyModule";

#ifdef ESP_LOGD
#define LOGD(tag, format, ...) ESP_LOGD(tag, format, ##__VA_ARGS__)
#else
#define LOGD(tag, format, ...) printf("DEBUG: " format "\n", ##__VA_ARGS__)
#endif

#ifdef ESP_LOGI
#define LOGI(tag, format, ...) ESP_LOGI(tag, format, ##__VA_ARGS__)
#else
#define LOGI(tag, format, ...) printf("INFO: " format "\n", ##__VA_ARGS__)
#endif

#ifdef ESP_LOGW
#define LOGW(tag, format, ...) ESP_LOGW(tag, format, ##__VA_ARGS__)
#else
#define LOGW(tag, format, ...) printf("WARNING: " format "\n", ##__VA_ARGS__)
#endif

#ifdef ESP_LOGE
#define LOGE(tag, format, ...) ESP_LOGE(tag, format, ##__VA_ARGS__)
#else
#define LOGE(tag, format, ...) printf("ERROR: " format "\n", ##__VA_ARGS__)
#endif
