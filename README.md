# Console Chess

학부 수업에서 진행한 C 기반 체스 프로젝트입니다. Windows 콘솔에서 두 명이 번갈아 플레이하며, Win32 콘솔 색상을 사용해 체스판과 이동 가능한 칸을 표시합니다.

## 프로젝트 정보

| 항목 | 내용 |
| --- | --- |
| 진행 시기 | 2022년 1학년 2학기 |
| 과목 | C언어 |

## Gameplay

<p align="center"><em>플레이 이미지가 추가될 자리입니다.</em></p>

<!--
플레이 이미지를 docs/images/gameplay.png로 추가한 뒤 위 안내 문구를 지우고
아래 이미지 태그의 주석을 해제하세요.

<p align="center">
  <img src="docs/images/gameplay.png" alt="Console Chess gameplay" width="640">
</p>
-->

## Features

- 로컬 2인 턴제 플레이
- 킹, 퀸, 룩, 비숍, 나이트, 폰의 기본 이동 규칙
- 말을 선택하면 이동 가능한 칸을 초록색으로 표시
- 경로를 가로막는 말을 검사하는 슬라이딩 기물 이동
- 폰의 첫 이동 2칸 전진, 대각선 잡기, 마지막 행 자동 퀸 승급
- 입력 범위와 같은 편 기물 선택 검증

## Rules used in this project

수업 프로젝트의 흐름을 유지한 간소화 버전입니다. 상대 킹을 잡으면 승리하며, 체크/체크메이트 판정, 캐슬링, 앙파상은 구현 범위에 포함하지 않았습니다.

백은 대문자, 흑은 소문자로 표시되며 백이 먼저 시작합니다. 좌표는 `G1`, `E4`처럼 행 문자 `A-H`와 열 숫자 `1-8`을 입력합니다. 좌표 입력 중 `Q`를 입력하면 메인 메뉴로 돌아갑니다.

## Build with Visual Studio

1. Visual Studio 2022에서 `console-chess.sln`을 엽니다.
2. `Release`와 원하는 플랫폼(`x64` 또는 `x86`)을 선택합니다.
3. 솔루션을 빌드하고 실행합니다.

프로젝트는 MSVC v143 toolset과 UTF-8 소스 인코딩을 사용합니다.

## Build with CMake

이 폴더의 터미널에서 다음 명령을 실행합니다.

```bash
cmake -S . -B build
cmake --build build --config Release
```

Windows 콘솔 API를 사용하므로 Windows 환경에서 실행해야 합니다.

## Structure

```text
c-console-chess/
├─ CMakeLists.txt
├─ console-chess.sln
├─ docs/images/              # README용 플레이 이미지
└─ src/
   ├─ console-chess.vcxproj
   ├─ main.c          # 메인 메뉴
   ├─ game.c          # 게임 상태와 입력 흐름
   ├─ rules.c         # 기물 이동 규칙과 보드 변경
   ├─ console_ui.c    # 컬러 체스판과 도움말 출력
   └─ chess.h         # 공용 타입과 함수 선언
```
