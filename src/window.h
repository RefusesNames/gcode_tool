#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GLFW/glfw3.h>

struct window_creation_parameters
{
	bool fullscreen = false;
	bool resizeable = false;
	unsigned int width = 800;
	unsigned int height = 600;
	std::string title = "Bouncy Ball";	
};

GLFWwindow* create_window(window_creation_parameters const & parameters);

#endif
