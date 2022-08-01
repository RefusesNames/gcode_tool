#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "gcode_reader.h"

struct axis_aligned_bounding_box
{
	glm::vec3 lower = glm::vec3();
	glm::vec3 upper = glm::vec3();
	glm::vec3 weighted_center = glm::vec3();
};

struct annotated_vertex
{
	glm::vec3 position;
	uint32_t type;
};

struct mouse_information
{
	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	bool left_button_pressed = false;
	bool right_button_pressed = false;
	bool middle_button_pressed = false;
	float scroll_value = 0.0f;
};

void error_callback(int, const char * error_message);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void mouse_position_callback(GLFWwindow * window, double x_position, double y_position);

void scroll_callback(GLFWwindow * window, double x_offset, double y_offset);

GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)

std::vector<annotated_vertex> commands_to_vertices(std::vector<gcode::command> & commands);

axis_aligned_bounding_box create_aabb(std::vector<annotated_vertex> const & vertices);
