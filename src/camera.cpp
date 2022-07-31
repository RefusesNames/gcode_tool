#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

camera::camera(
		glm::vec3 const & position,
		glm::vec3 const & view_direction,
		glm::vec3 const & up
		)
	: _position(position),
	_view_direction(glm::normalize(view_direction)),
	_up(glm::normalize(up))
{
}

void camera::move_by(glm::vec3 const & translation)
{
	_position += translation;
}

void camera::move_by_relative_to_view(glm::vec3 const & translation)
{
	_position += translation;
}

void camera::move_to(glm::vec3 const & new_position)
{
	_position = new_position;
}

void camera::look_at(glm::vec3 const & look_at_this)
{
	_view_direction = glm::normalize(look_at_this - _position);
}

void camera::zoom(float amount)
{
	_position += _view_direction * amount; 
}

glm::mat4 camera::get_view_matrix() const
{
	auto translation = glm::translate(_position);
	return translation * glm::lookAt(glm::vec3(), _view_direction, _up);
}

glm::vec3 camera::get_position() const
{
	return _position;
}

glm::vec3 camera::get_view_direction() const
{
	return _view_direction;
}

glm::vec3 camera::get_up() const
{
	return _up;
}
