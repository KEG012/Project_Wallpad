#ifndef __DHT11_H
#define __DHT11_H

//#include "stm32f1xx_hal.h"
#include "stm32f4xx_hal.h"

#define DHT11_GPIO_Port GPIOA
#define DHT11_Pin       GPIO_PIN_9

typedef struct {
	uint8_t humiData_Int;
	uint8_t humiData_Double;
	uint8_t tempData_Int;
	uint8_t tempData_Double;
	uint8_t checkSum;
	uint8_t status;
}DHT11_TypeDef;

extern TIM_HandleTypeDef htim1;

#include "dht11.h"

void delay_us(uint16_t us);
void DHT11_Set_Output();
void DHT11_Set_Input();
void DHT11_Init();
DHT11_TypeDef DHT11_ReadData(void);
#endif
