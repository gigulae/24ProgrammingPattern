#pragma comment(lib, "Opengl32.lib")

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <cmath>

class Dino {
public:
    float x, y; // 위치
    float width, height; // 너비와 높이
    float speed; // 이동 속도
    float gravity; // 중력 가속도
    float jumpSpeed; // 점프 속도
    float velocityY; // 수직 속도
    bool isJumping;

    Dino(float initialX, float initialY)
        : x(initialX), y(initialY), width(50.0f), height(50.0f), speed(5.0f), gravity(15.0f), jumpSpeed(8.0f), velocityY(0.0f), isJumping(false) {}

    void jump() {
        if (!isJumping) {
            velocityY = jumpSpeed;
            isJumping = true;
        }
    }

    void update() {
        if (isJumping) {
            // 중력 적용
            velocityY -= gravity * 0.01f;

            // 위치 업데이트
            y += velocityY;

            // 바닥에 닿으면
            if (y <= 100.0f) {
                y = 100.0f; // 최소 높이로 설정
                isJumping = false;
                velocityY = 0.0f; // 속도 초기화
            }
        }
    }

    void draw() {
        glPushMatrix();
        glTranslatef(x, y, 0.0f);
        glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f); // 캐릭터를 빨간색으로 설정
        glVertex2f(0.0f, 0.0f);
        glVertex2f(width, 0.0f);
        glVertex2f(width, height);
        glVertex2f(0.0f, height);
        glEnd();
        glPopMatrix();
    }
};

class Obstacle {
public:
    float x, y; // 위치
    float width, height; // 너비와 높이
    float speedX; // 가로 이동 속도

    Obstacle(float initialX, float initialY, float initialSpeedX) : x(initialX), y(initialY), width(60.0f), height(120.0f), speedX(initialSpeedX) {}

    void update() {
        x -= speedX;
        if (x < -width) { // 화면 왼쪽 끝으로 이동했을 때 재사용
            x = 800.0f; // 임시로 화면 너비로 설정
        }
    }

    void draw() {
        glPushMatrix();
        glTranslatef(x, y, 0.0f);
        glBegin(GL_QUADS);
        glColor3f(0.0f, 1.0f, 0.0f); // 장애물을 초록색으로 설정
        glVertex2f(0.0f, 0.0f);
        glVertex2f(width, 0.0f);
        glVertex2f(width, height);
        glVertex2f(0.0f, height);
        glEnd();
        glPopMatrix();
    }
};

class Ground {
public:
    float y; // 지면의 y 위치

    Ground(float initialY) : y(initialY) {}

    void draw() {
        glPushMatrix();
        glBegin(GL_QUADS);
        glColor3f(1.0f, 0.78f, 0.03f); // 지면을 황색으로 설정
        glVertex2f(0.0f, y);
        glVertex2f(800.0f, y);
        glVertex2f(800.0f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        glEnd();
        glPopMatrix();
    }
};

Dino dino(100.0f, 100.0f);
Obstacle obstacle(800.0f, 100.0f, 7.0f);
Ground ground(100.100f);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        dino.jump();
    }
}

bool checkCollision(const Dino& dino, const Obstacle& obstacle) {
    // 충돌 박스 겹침 여부 확인
    if (dino.x + dino.width >= obstacle.x && 
        obstacle.x + obstacle.width >= dino.x &&
        dino.y + dino.height >= obstacle.y &&
        obstacle.y + obstacle.height >= dino.y) {
        return true;
    }
    return false;
}

int main() {
    // GLFW 초기화
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // 윈도우 생성
    GLFWwindow* window = glfwCreateWindow(800, 600, "Google Dino Run Copy Game", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // OpenGL 컨텍스트를 생성한 윈도우에 연결
    glfwMakeContextCurrent(window);

    // OpenGL 초기화
    glClearColor(0.0f, 0.12f, 0.39f, 1.0f); // 배경색을 검은색으로 설정

    // 뷰포트 설정
    glViewport(0, 0, 800, 600);

    // 투영 변환 설정
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);

    // 입력 콜백 함수 등록
    glfwSetKeyCallback(window, key_callback);

    // 게임 루프
    while (!glfwWindowShouldClose(window)) {
        // 입력 처리
        glfwPollEvents();

        // 게임 오브젝트 업데이트
        dino.update();
        obstacle.update();

        // 충돌 감지
        if (checkCollision(dino, obstacle)) {
            std::cout << "Game Over!" << std::endl;
            break; // 게임 종료 로직
        }

        // 화면 지우기
        glClear(GL_COLOR_BUFFER_BIT);

        // 지면 그리기
        ground.draw();

        // 게임 오브젝트 그리기
        dino.draw();
        obstacle.draw();

        // 화면 업데이트
        glfwSwapBuffers(window);
    }

    // GLFW 종료
    glfwTerminate();
    return 0;
}
