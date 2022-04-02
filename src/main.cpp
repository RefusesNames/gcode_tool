#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/string_cast.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<iostream>

#include"window.h"
#include"gcode_reader.h"
#include"shaders.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void error_callback(int, const char * error_message);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void mouse_position_callback(GLFWwindow * window, double x_position, double y_position);

void scroll_callback(GLFWwindow * window, double x_offset, double y_offset);

GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)

std::vector<glm::vec3> commands_to_vertices(std::vector<gcode::command> & commands);

auto camera_position = glm::vec3(0.0f, 0.0f, -3.0f);

auto object_translation = glm::vec3(0.0f, 0.0f, 0.0f);

struct mouse_information
{
    glm::vec2 position = glm::vec2(0.0f, 0.0f);
    bool left_button_pressed = false;
    bool right_button_pressed = false;
    bool middle_button_pressed = false;
    float scroll_value = 0.0f;
} mouse;

void zoom_out();
void zoom_in();

int main(int argc, char *argv[])
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    else
        std::cout << "Successfully initialized GLFW" << std::endl;

    auto window_parameters = window_creation_parameters();
    auto window = create_window(window_parameters);

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_position_callback);
    glfwSetScrollCallback(window, scroll_callback);

    gcode::reader reader;
    auto commands = reader.read_file(argv[1]);
    auto vertices = commands_to_vertices(commands);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }
    else
        std::cout << "Successfully initialized OpenGL context" << std::endl;

    // create VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // create data
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float) * 3, vertices.data(), GL_STATIC_DRAW);

    // vertex shader
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    auto vertex_shader_source = VERTEX_SHADER.c_str();
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    GLint status;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, buffer);
        std::cerr << "Failed to compile vertex shader:" << buffer << std::endl;
    }

    // fragment shader
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    auto fragment_shader_source = FRAGMENT_SHADER.c_str();
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512];
        glGetShaderInfoLog(fragment_shader, 512, NULL, buffer);
        std::cerr << "Failed to compile fragment shader:" << buffer << std::endl;
    }

    // shader program
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);

    glBindFragDataLocation(shader_program, 0, "outColor");

    glLinkProgram(shader_program);
    glUseProgram(shader_program);

    // attributes
    GLint position_attribute = glGetAttribLocation(shader_program, "position");
    glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0 , 0);
    glEnableVertexAttribArray(position_attribute);



    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        auto model_matrix = glm::translate(glm::mat4(1.0f), object_translation);
        auto view_matrix = glm::lookAt(camera_position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        auto projection_matrix = glm::perspective(glm::radians(45.0f), (float) window_parameters.width / (float) window_parameters.height, 1.0f, 1000.0f);
        auto mvp_matrix = projection_matrix * view_matrix * model_matrix;
        GLint matrix_uniform = glGetUniformLocation(shader_program, "model_view_projection_matrix");
        glUniformMatrix4fv(matrix_uniform, 1, GL_FALSE, glm::value_ptr(mvp_matrix));

        glDrawArrays(GL_LINE_STRIP, 0, vertices.size());

        glfwSwapBuffers(window);

        if (glGetError() != GL_NO_ERROR)
        {
            std::cerr << "ERROR" << std::endl;
        }
    }

    glfwTerminate();

    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        zoom_out();
        
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        zoom_in();

    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        camera_position.x--;

    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        camera_position.x++;

}

void error_callback(int, const char* error_message)
{
    std::cerr << "GLFW error: " << error_message << std::endl;
}

GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cerr << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}

std::vector<glm::vec3> commands_to_vertices(std::vector<gcode::command> & commands)
{
    glm::vec3 previous_location = glm::vec3(0, 0, 0);
    std::vector<glm::vec3> vertices;
    vertices.reserve(commands.size());

    for(auto & command : commands)
    {
        for(auto & parameter : command.parameters)
        {
            if (parameter.name == 'Z')
                parameter.name = 'Y';
            else if (parameter.name == 'Y')
            {
                parameter.name = 'Z';
                parameter.value *= -1.0f;
            }
            else if (parameter.name == 'X')
                parameter.value *= -1.0f;
        }
    }

    for(auto command : commands)
    {
        auto get_coordinate_value = [&command, &previous_location](char axis)
        {
            for(auto parameter : command.parameters)
            {
                if (parameter.name == axis)
                    return parameter.value;
            }
            if (axis == 'X')
                return previous_location.x;
            if (axis == 'Y')
                return previous_location.y;
            if (axis == 'Z')
                return previous_location.z;
            std::cerr << "Invalid axis: " << axis << std::endl;

            return 0.0f;
        };
        switch (command.code)
        {
            case gcode::command::G28:
                previous_location = glm::vec3(0, 0, 0);
                break;
            case gcode::command::G0:
            case gcode::command::G1:
                previous_location = glm::vec3(
                    get_coordinate_value('X'),
                    get_coordinate_value('Y'),
                    get_coordinate_value('Z')
                );
                break;
            default:
                break;
        }
        vertices.push_back(previous_location);
    }

    return vertices;
}

void zoom_out()
{
    camera_position.z--;
}

void zoom_in()
{
    camera_position.z++;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        mouse.left_button_pressed = true;
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        mouse.left_button_pressed = false;
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        mouse.right_button_pressed = true;
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        mouse.right_button_pressed = false;
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
        mouse.middle_button_pressed = true;
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
        mouse.middle_button_pressed = false;

}

void mouse_position_callback(GLFWwindow * window, double x_position, double y_position)
{
    auto new_position = glm::vec2(x_position, y_position);
    if (mouse.middle_button_pressed)
    {
        auto difference = new_position - mouse.position;
        object_translation += glm::vec3(difference, 0);
    }
    mouse.position = new_position;
}

void scroll_callback(GLFWwindow * window, double x_offset, double y_offset)
{
    camera_position.z += static_cast<float>(y_offset);
    mouse.scroll_value += static_cast<float>(y_offset);
}
