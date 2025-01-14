# 프로젝트 개요
QT 프로그램과 STM32F411RE를 사용하여 Raspberry Pi 7" Touch Display에 Wallpad를 만들어보는 프로젝트입니다.

# 프로젝트 목표
- Raspberry Pi와 7" Touch Display를 사용하여 QT를 활용한 Wallpad 구현.
- STM32F411RE를 사용하여 센서 값 전달.
- ESP8266을 사용한 데이터 전송.

# Hardware 구성
- Raspberry Pi와 7" Touch Display는 Flexible Flat Cable을 사용하여 연결.
- Raspberry Pi와 Webcam은 USB로 연결
- STM32F411RE와 DHT11, LED, ESP8266, CDS센서(ADC)는 GPIO로 연결.

<p align="center">
<img src="./Img/wallpad hardware.jpg">

<img src="./Img/Wallpad Real Hardware.jpg">
</p>

# Software 구성

## 서버와 STM32F411RE와 통신
- STM32에서 전송된 CDS 센서 값과 DHT11 값을 "@"로 구분하여 전송.
- Raspberry Pi에서는 LED를 켜기 위한 LED 전달 (추후 영상으로 소개)

<p align="center">
<img src="./Img/server stm tcpip.png">
</p>