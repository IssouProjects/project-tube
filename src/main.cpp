// GLAD = used to find platform specific OpenGL function (specific from the graphic cards manufacturers)
#include <glad/glad.h>
// GLFW = opengl framework : used to create windows and such in a plateform-independant way
#include <GLFW/glfw3.h>
#include <KHR/khrplatform.h>
#include <iostream>

void framebuffer_size_callback (GLFWwindow* window, int width, int height);

int main ()
{
	glfwInit ();
	//using OpenGL version 3.3
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
	//using only the core module of OpenGL
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow (800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate ();
		return 1;
	}
	glfwMakeContextCurrent (window);

	if (!gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return 1;
	}

	glViewport (0, 0, 800, 600);

	glfwSetFramebufferSizeCallback (window, framebuffer_size_callback);

	while (!glfwWindowShouldClose (window))
	{
		glfwSwapBuffers (window);
		glfwPollEvents ();
	}

	glfwTerminate ();

	return 0;
}

void framebuffer_size_callback (GLFWwindow* window, int width, int height)
{
	glViewport (0, 0, width, height);
}