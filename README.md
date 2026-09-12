# LIGNex1 RC Robot Controller

LIG D&A The SSEN Embedded SW School에서 진행한 팀 프로젝트입니다.

STM32F103과 FreeRTOS를 기반으로 로봇 팔과 주행 로봇을 제어하는
RC Robot Controller 시스템을 개발했습니다.

본 저장소는 프로젝트 당시 소스 코드를 개인 포트폴리오용으로 정리한 저장소입니다.

> Original Team Repository: (https://github.com/MainForm/LIGNex1_RC_Robot_Controller/tree/feature/controller_ble_merge_test)

## My Role

프로젝트에서는 시스템의 요구사항과 동작 방식을 팀원들과 논의하고,
Controller와 통신 모듈 사이에서 전달되는 데이터 구조를 정리하는 과정에 참여했습니다.

특히 주행 모드와 로봇 팔 모드를 구분하기 위한 상태값과
Controller-UGV 간 연결 상태를 나타내는 값을 정의하고,
모드가 전환될 때 사용하지 않는 입력값이 남지 않도록 초기화하는 방식을 논의했습니다.

※ 본 프로젝트는 팀 프로젝트이며, 저장소의 모든 소스 코드를 제가 작성한 것은 아닙니다.
