#include "keyboard.h"
#include "GLFW/glfw3.h"

void keyboard_handler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	for(auto & handler : _handlers)
	{
		switch (action)
		{
			case GLFW_PRESS:
				if (handler->on_key_press(key, mods) == key_action_result::SWALLOWED) return;
				break;
			case GLFW_RELEASE:
				if (handler->on_key_release(key, mods) == key_action_result::SWALLOWED) return;
				break;
			case GLFW_REPEAT:
				if (handler->on_key_hold(key, mods) == key_action_result::SWALLOWED) return;
				break;
		}
	}
}

void keyboard_handler::remove_from_handlers(keyboard_handler const * handler)
{
	auto position = std::find(_handlers.begin(), _handlers.end(), this);
	if(position != _handlers.end())
		_handlers.erase(position);
}
