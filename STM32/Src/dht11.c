#include "dht11.h"

void delay_us(uint16_t us) {
    __HAL_TIM_SET_COUNTER(&htim1, 0); // 타이머 카운터 초기화
    while (__HAL_TIM_GET_COUNTER(&htim1) < us); // 원하는 시간만큼 대기
}

void DHT11_Set_Output(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DHT11_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct);
}

void DHT11_Set_Input(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DHT11_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct);
}

void DHT11_Init(){
    DHT11_Set_Output(DHT11_GPIO_Port, DHT11_Pin);
	HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, SET);
	HAL_Delay(3000);
}

DHT11_TypeDef DHT11_ReadData(void) {
    DHT11_TypeDef dht11_data;
    uint8_t data[5] = {0};

    // 1. Start 신호 전송
    DHT11_Set_Output();
    HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, RESET);
    delay_us(18000); // 18ms 대기
    HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, SET);
    delay_us(30);
    DHT11_Set_Input();

    // 2. DHT11 응답 대기
    while (HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin) == GPIO_PIN_SET);
    while (HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin) == GPIO_PIN_RESET);
    while (HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin) == GPIO_PIN_SET);

    // 3. 데이터 읽기
    for (int byteIndex = 0; byteIndex < 5; byteIndex++) {
        uint8_t rx_data = 0;
        for (int bitIndex = 0; bitIndex < 8; bitIndex++) {
            while (HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin) == GPIO_PIN_RESET); // Low 신호 대기
            delay_us(40); // 40µs 대기 후 데이터 확인
            rx_data <<= 1;
            if (HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin) == GPIO_PIN_SET) {
                rx_data |= 1;
            }
            while (HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin) == GPIO_PIN_SET); // High 신호 종료 대기
        }
        data[byteIndex] = rx_data; // 바이트 저장
    }

    // 4. 체크섬 확인
    uint8_t checksum = data[0] + data[1] + data[2] + data[3];
    if ((checksum & 0xFF) != data[4]) {
        dht11_data.status = 1; // 체크섬 오류
        return dht11_data;
    }

    // 5. 데이터 저장
    dht11_data.humiData_Int= data[0];
    dht11_data.humiData_Double = data[1];
    dht11_data.tempData_Int = data[2];
    dht11_data.tempData_Double = data[3];
    dht11_data.checkSum = data[4];
    dht11_data.status = 0; // 성공

    return dht11_data;
}
