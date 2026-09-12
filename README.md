# LIGNex1 RC Robot Controller
<img width="1496" height="1496" alt="KakaoTalk_20260912_161510002_01" src="https://github.com/user-attachments/assets/ba0e61fb-78e6-428b-8bb4-71b573f202ad" />
<img width="1496" height="1496" alt="KakaoTalk_20260912_161510002" src="https://github.com/user-attachments/assets/2f0ef763-73f1-42cd-a2b1-8760a4663bef" />

LIG D&A The SSEN Embedded SW School에서 진행한 팀 프로젝트입니다.

STM32와 FreeRTOS를 기반으로 로봇의 주행과 로봇 팔을 제어하기 위한
RC Robot Controller 시스템을 개발했습니다.

Controller에서 조이스틱과 가변저항의 입력값을 처리하고,
Bluetooth 통신을 통해 UGV에 제어 데이터를 전달하여
주행 및 로봇 팔을 조작할 수 있도록 구성했습니다.

## Features

- Joystick을 이용한 UGV 주행 제어
- 가변저항을 이용한 로봇 팔 제어
- 주행 / 로봇 팔 제어 모드 전환
- Controller와 UGV 간 Bluetooth 통신
- FreeRTOS 기반 Task 구성

## Development Environment

- MCU: STM32F103
- RTOS: FreeRTOS
- Language: C
- STM32CubeMX
- CMake

## Team Repository

본 저장소는 팀 프로젝트 당시 소스 코드를 개인 포트폴리오용으로 정리한 저장소입니다.

Original Team Repository: https://github.com/MainForm/LIGNex1_RC_Robot_Controller/tree/feature/controller_ble_merge_test

## Result

[완성된 로봇 사진]
