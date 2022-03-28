#pragma once

#include <string>

const std::string VERTEX_SHADER = R"SHADER(
#version 150 core

in vec3 position;

uniform mat4 model_view_projection_matrix;

void main()
{
	gl_Position = model_view_projection_matrix * vec4(position, 1.0);
}
)SHADER";

const std::string FRAGMENT_SHADER = R"SHADER(
#version 150 core

out vec4 outColor;

void main()
{
    outColor = vec4(1.0, 0.0, 0.0, 1.0);
}
)SHADER";

