#pragma once

#include <string>

const std::string VERTEX_SHADER = R"SHADER(
#version 150 core

in vec3 position;
in uint command_type;

out vec3 vertex_color;

uniform mat4 model_view_projection_matrix;

void main()
{
	gl_Position = model_view_projection_matrix * vec4(position, 1.0);
    if (command_type == 1U)
        vertex_color = vec3(0.0, 0.0, 1.0);
    else if (command_type == 2U)
        vertex_color = vec3(0.0, 1.0, 0.0);
    else
        vertex_color = vec3(1.0, 0.0, 0.0);
}
)SHADER";

const std::string FRAGMENT_SHADER = R"SHADER(
#version 150 core

in vec3 vertex_color;

out vec4 outColor;

void main()
{
    outColor = vec4(vertex_color, 1.0);
}
)SHADER";

