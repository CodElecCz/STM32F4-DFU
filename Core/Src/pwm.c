/*
 * adc.c
 *
 *  Created on: Oct 29, 2020
 *      Author: TURCAR
 */

#include "pwm.h"
#include "main.h"

#include <stdio.h>

extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim11;
extern TIM_HandleTypeDef htim13;
extern TIM_HandleTypeDef htim14;

#define PWM_RGB_CYCLE 		(255*0.12)
#define PWM_STATE_CYCLE		(255*1.0)

typedef struct
{
	uint8_t PinState[4];
} PWM;

static PWM pwm = {};

void HAL_PWM_WritePin(uint16_t GPIO_Pin, GPIO_PinState PinState)
{
	switch(GPIO_Pin)
	{
	case LED_STATE_Pin:
		__HAL_TIM_SET_COMPARE(&htim10, TIM_CHANNEL_1, PinState? PWM_STATE_CYCLE:0);
		pwm.PinState[0] = PinState;
		break;
	case LED_R_Pin:
		__HAL_TIM_SET_COMPARE(&htim11, TIM_CHANNEL_1, PinState? PWM_RGB_CYCLE:0);
		pwm.PinState[1] = PinState;
		break;
	case LED_G_Pin:
		__HAL_TIM_SET_COMPARE(&htim13, TIM_CHANNEL_1, PinState? PWM_RGB_CYCLE:0);
		pwm.PinState[2] = PinState;
		break;
	case LED_B_Pin:
		__HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, PinState? PWM_RGB_CYCLE:0);
		pwm.PinState[3] = PinState;
		break;
	}
}

uint8_t HAL_PWM_ReadPin(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
	case LED_STATE_Pin:
		return pwm.PinState[0];
	case LED_R_Pin:
		return pwm.PinState[1];
	case LED_G_Pin:
		return pwm.PinState[2];
	case LED_B_Pin:
		return pwm.PinState[3];
	default:
		return 0;
	}
}

void HAL_PWM_WriteRGB(uint8_t r, uint8_t g, uint8_t b)
{
	__HAL_TIM_SET_COMPARE(&htim11, TIM_CHANNEL_1, r>0? PWM_RGB_CYCLE*((double)r/255.0) : 0);
	__HAL_TIM_SET_COMPARE(&htim13, TIM_CHANNEL_1, g>0? PWM_RGB_CYCLE*((double)g/255.0) : 0);
	__HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, b>0? PWM_RGB_CYCLE*((double)b/255.0) : 0);
}

void MX_GPIO_LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_STATE_GPIO_Port, LED_STATE_Pin, GPIO_PIN_SET);

	GPIO_InitStruct.Pin = LED_R_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_R_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LED_G_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_G_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LED_B_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_B_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LED_STATE_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_STATE_GPIO_Port, &GPIO_InitStruct);
}
