#include "window.h"

GLFWwindow* create_window(window_creation_parameters const & parameters)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, (parameters.resizeable)? GL_TRUE : GL_FALSE);

	return (parameters.fullscreen)
		?	glfwCreateWindow(800, 600, "OpenGL", glfwGetPrimaryMonitor(), nullptr)
		:	glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
}
