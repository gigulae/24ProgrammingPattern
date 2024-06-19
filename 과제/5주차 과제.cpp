#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float moveFactor = 0.0f;
float scaleFactor = 1.0f;

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
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		moveFactor += 0.01f;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		scaleFactor += 0.1f;
	}
}

int setVertexRotation(float x, float y, float angle_degree)
{
	float M_PI = 3.14;
	float angle = angle_degree / 180 * M_PI;

	glVertex2f(x * cos(angle) - (y * sin(angle)), x * sin(angle) + (y * cos(angle)));
	return 0;
}



float angle = 0;

int render()
{
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.7f, 0.8f, 0.85f);
	setVertexRotation(0.0f, 0.0f, 0);

	for (int i = 0; i < 360; i = i + 72)
	{
		setVertexRotation(1.0f, 0.0f, i + angle);
		setVertexRotation(0.5f, 0.0f, i + 36 + angle);
	}

	setVertexRotation(1.0f, 0.0f, angle);

	glEnd();

	angle += 0;


	glLineWidth(10.0f);

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);



	for (int i = 0; i < 360; i = i + 72)
	{
		setVertexRotation(0.5f, 0.0f, i - 36 + angle);
		setVertexRotation(1.0f, 0.0f, i + angle);

		setVertexRotation(1.0f, 0.0f, i + angle);
		setVertexRotation(0.5f, 0.0f, i + 36 + angle);
	}

	glEnd();

	return 0;
}



////점1
//glColor3f(1.0f, 1.0f, 1.0f);
//glVertex2f(0.0f * scaleFactor, (1.0f+ moveFactor) * scaleFactor);
////점2
//glColor3f(1.0f, 1.0f, 1.0f);
//glVertex2f(0.5f * scaleFactor, (0.0f+ moveFactor) * scaleFactor);
////점3
//glColor3f(1.0f, 1.0f, 1.0f);
//glVertex2f(-0.5f * scaleFactor, (0.0f+ moveFactor) * scaleFactor);


int main(void)
{
	//glfw라이브러리 초기화
	if (!glfwInit())
		return -1;

	GLFWwindow* window;
	window = glfwCreateWindow(800, 800, "MuSoeunEngine", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(window, keyCallback);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		render();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;

}