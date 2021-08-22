#include "Fixed.hpp"
#include <glm/gtc/matrix_transform.hpp>

FixedView::FixedView(glm::vec3 direction) : m_direction(direction) {
}

void FixedView::update() {
	glm::vec3 up = glm::vec3(m_up);
	glm::vec3 right = glm::normalize(glm::cross(up, m_direction));
	glm::vec3 cameraUp = glm::cross(m_direction, right);
	m_view = glm::lookAt(m_position, m_position + m_direction, cameraUp);
}
