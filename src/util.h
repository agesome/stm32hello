#include <stm32h5xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

void check(HAL_StatusTypeDef status, const char desc[]);
void check_silent(HAL_StatusTypeDef status);
void message(const char *format, ...);

#ifdef __cplusplus
}
#endif
