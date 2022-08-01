#pragma once

#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

class keyboard_handler
{
	public:
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	protected:
		enum class key_action_result
		{
			SWALLOWED,
			PASSED_ON
		};

		virtual key_action_result on_key_press(int key, int mods) = 0;
		virtual key_action_result on_key_release(int key, int mods) = 0;
		virtual key_action_result on_key_hold(int key, int mods) = 0;

		static std::vector<std::unique_ptr<keyboard_handler>> _handlers;

		void remove_from_handlers(keyboard_handler const * handler);
};
