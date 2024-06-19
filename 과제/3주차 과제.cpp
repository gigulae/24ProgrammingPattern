#include <iostream>
#include <windows.h>

// 키코드와 색깔 매핑을 위한 구조체
struct BlockInfo {
    int keyCode;
    WORD color;
};

// 색상 정의
enum ConsoleColor {
    WHITE = 7,
    RED = 12,
    GREEN = 10,
    YELLOW = 14,
    CYAN = 11,
    MAGENTA = 13
};

void drawBlock(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    std::cout << "■";
}

int main() {
    // 프로그램 시작 메시지 출력
    std::cout << "화면에 그림을 그리는 프로그램입니다." << std::endl;
    std::cout << "학번: 202034001" << std::endl;
    std::cout << "이름: 김기수" << std::endl;

    // 블록 정보 설정
    BlockInfo blocks[] = {
        { 1, WHITE },
        { 2, RED },
        { 4, GREEN },
        { 8, YELLOW },
        { 16, CYAN },
        { 32, MAGENTA },
        { 64, 0 } // 종료 키코드
    };

    int input;
    do {
        // 입력 받기
        std::cout << "\n화면에 그릴 물체코드를 입력하세요 (종료: 64): ";
        std::cin >> input;

        // 입력값에 따라 블록 그리기
        for (int i = 0; blocks[i].keyCode != 64; ++i) {
            if (input == blocks[i].keyCode) {
                drawBlock(blocks[i].color);
                break;
            }
        }

    } while (input != 64);

    return 0;
}
