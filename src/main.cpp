#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

#include"window.h"
#include"gcode_reader.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main(int argc, char *argv[])
{
	if (!glfwInit()) 
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	else
		std::cout << "Successfully initialized GLFW" << std::endl;

    auto window_parameters = window_creation_parameters();
	auto window = create_window(window_parameters);

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	gcode::reader reader;
	auto commands = reader.read_file(argv[1]);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}
	else
		std::cout << "Successfully initialized OpenGL context" << std::endl;

    while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);

		glfwSwapBuffers(window);

		if (glGetError() != GL_NO_ERROR)
		{
			std::cerr << "ERROR" << std::endl;
		}
	}

	glfwTerminate();

    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
