#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

// 초기 색상
GLfloat clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

// 마우스 오른쪽 버튼 다운 여부
bool rightButtonDown = false;
// 마우스 왼쪽 버튼 다운 여부
bool leftButtonDown = false;

// 이전 색상 저장 변수
GLfloat prevClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            rightButtonDown = true;
            // 현재 색상 저장
            prevClearColor[0] = clearColor[0];
            prevClearColor[1] = clearColor[1];
            prevClearColor[2] = clearColor[2];
            // 마우스 오른쪽 버튼 누르면 빨간색으로 변경
            clearColor[0] = 1.0f;
            clearColor[1] = 0.0f;
            clearColor[2] = 0.0f;
        }
        else if (action == GLFW_RELEASE)
        {
            rightButtonDown = false;
            // 마우스 오른쪽 버튼 뗄 때 이전 색상으로 복구
            clearColor[0] = prevClearColor[0];
            clearColor[1] = prevClearColor[1];
            clearColor[2] = prevClearColor[2];
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            leftButtonDown = true;
            // 현재 색상 저장
            prevClearColor[0] = clearColor[0];
            prevClearColor[1] = clearColor[1];
            prevClearColor[2] = clearColor[2];
            // 마우스 왼쪽 버튼 누르면 녹색으로 변경
            clearColor[0] = 0.0f;
            clearColor[1] = 1.0f;
            clearColor[2] = 0.0f;
        }
        else if (action == GLFW_RELEASE)
        {
            leftButtonDown = false;
            // 마우스 왼쪽 버튼 뗄 때 이전 색상으로 복구
            clearColor[0] = prevClearColor[0];
            clearColor[1] = prevClearColor[1];
            clearColor[2] = prevClearColor[2];
        }
    }
}

void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (rightButtonDown)
    {
        // 오른쪽 버튼 누르고 드래그 중이면 파란색으로 변경
        clearColor[0] = 0.0f;
        clearColor[1] = 0.0f;
        clearColor[2] = 1.0f;
    }
    else if (leftButtonDown)
    {
        // 왼쪽 버튼 누르고 드래그 중이면 마젠타색으로 변경
        clearColor[0] = 1.0f;
        clearColor[1] = 0.0f;
        clearColor[2] = 1.0f;
    }
    else
    {
        // 그 외의 경우에는 아무것도 하지 않음
    }
}

int main(void)
{
    // GLFW 라이브러리 초기화
    if (!glfwInit())
        return -1;

    // GLFW 윈도우 생성
    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // 윈도우의 OpenGL 컨텍스트를 현재 컨텍스트로 설정
    glfwMakeContextCurrent(window);

    // GLFW 에러 콜백 설정
    glfwSetErrorCallback(errorCallback);

    // 키 입력 콜백 설정
    glfwSetKeyCallback(window, keyCallback);

    // 마우스 버튼 이벤트 콜백 설정
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    // 마우스 이동 이벤트 콜백 설정
    glfwSetCursorPosCallback(window, mouseMoveCallback);

    while (!glfwWindowShouldClose(window))
    {
        // 이벤트 처리
        glfwPollEvents();

        // OpenGL 화면 지우기
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        // 화면 업데이트
        glfwSwapBuffers(window);
    }

    // GLFW 종료
    glfwTerminate();
    return 0;
}
