#pragma once

#include "keyboard.h"

class camera;

class camera_keyboard_handler : public keyboard_handler
{
	public:
		camera_keyboard_handler(camera & camera);
		camera_keyboard_handler(camera_keyboard_handler const & other) = delete;
		camera_keyboard_handler(camera_keyboard_handler const && other);
		~camera_keyboard_handler();

		camera_keyboard_handler& operator=(camera_keyboard_handler const & other) = delete;
		camera_keyboard_handler& operator=(camera_keyboard_handler const && other) = delete;

	private:
		camera & _camera;

		key_action_result on_key_press(int key, int mods);
		key_action_result on_key_release(int key, int mods);
		key_action_result on_key_hold(int key, int mods);
};
