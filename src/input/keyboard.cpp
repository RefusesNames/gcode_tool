#include "keyboard.h"
#include "GLFW/glfw3.h"

std::vector<std::unique_ptr<keyboard_handler>> keyboard_handler::_handlers = {};

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
	auto is_given_handler = [handler](std::unique_ptr<keyboard_handler> const & other_handler) { return other_handler.get() == handler; };
	auto position = std::find_if(_handlers.begin(), _handlers.end(), is_given_handler);
	if(position != _handlers.end())
		_handlers.erase(position);
}
