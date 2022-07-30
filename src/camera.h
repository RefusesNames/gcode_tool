#pragma once

#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

class camera
{
    public:
        camera(
            glm::vec3 const & position,
            glm::vec3 const & view_direction,
            glm::vec3 const & up
        );

        void move_by(glm::vec3 const & translation);
        void move_by_relative_to_view(glm::vec3 const & translation);
        void move_to(glm::vec3 const & translation);

        void look_at(glm::vec3 const & look_at_this);

        void zoom(float amount);

        glm::mat4 get_view_matrix() const;
        glm::vec3 get_position() const;
        glm::vec3 get_view_direction() const;
        glm::vec3 get_up() const;

    private:
        glm::vec3 _position;
        glm::vec3 _view_direction;
        glm::vec3 _up;
};
