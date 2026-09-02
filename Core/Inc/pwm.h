/*
 * adc.h
 *
 *  Created on: 12.01.2021
 *      Author: TURCAR
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

#include "main.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t HAL_PWM_ReadPin(uint16_t GPIO_Pin);
void HAL_PWM_WritePin(uint16_t GPIO_Pin, GPIO_PinState PinState);

/*
 * RGB Led
 */
#define RGB_COLOR_NONE						0,0,0
#define RGB_COLOR_TCP_UART 					255, 60, 0
#define RGB_COLOR_ERROR 					255, 0, 0
#define RGB_COLOR_PROCESS					127, 0, 255
#define RGB_COLOR_START						0, 255, 0
#define RGB_COLOR_LINKUP					0, 0, 255


void HAL_PWM_WriteRGB(uint8_t r, uint8_t g, uint8_t b);

void MX_GPIO_LED_Init();

#ifdef __cplusplus
}
#endif

#endif /* INC_PWM_H_ */
