#include "camera_keyboard_handler.h"

#include <memory>
#include <glm/glm.hpp>

#include "../camera.h"

keyboard_handler::key_action_result camera_keyboard_handler::on_key_press(int key, int mods)
{
	// if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	// 	glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_S)
		_camera.move_by(glm::vec3(0.0f, 0.0f, -1.0f));

	if (key == GLFW_KEY_W)
		_camera.move_by(glm::vec3(0.0f, 0.0f, 1.0f));

	if (key == GLFW_KEY_A)
		_camera.move_by(glm::vec3(1.0f, 0.0f, 0.0f));

	if (key == GLFW_KEY_D)
		_camera.move_by(glm::vec3(-1.0f, 0.0f, 0.0f));

	return key_action_result::SWALLOWED;
}

keyboard_handler::key_action_result camera_keyboard_handler::on_key_release(int key, int mods)
{
	return key_action_result::PASSED_ON;
}

keyboard_handler::key_action_result camera_keyboard_handler::on_key_hold(int key, int mods)
{
	return key_action_result::PASSED_ON;
}

camera_keyboard_handler::camera_keyboard_handler(camera & camera) noexcept
	:_camera(camera)
{
	_handlers.emplace_back(this);
}

camera_keyboard_handler::camera_keyboard_handler(camera_keyboard_handler const && other) noexcept
	:_camera(other._camera)
{
	remove_from_handlers(&other);
	_handlers.emplace_back(this);
}

camera_keyboard_handler::~camera_keyboard_handler()
{
	remove_from_handlers(this);
}
