#include "CameraView.hpp"

void CameraView::setPosition(glm::vec3 position) {
	m_position = position;
}

void CameraView::setUp(glm::vec3 up) {
	m_up = up;
}

glm::vec3 CameraView::getPosition() const {
	return m_position;
}

glm::mat4 CameraView::get() const {
	return m_view;
}
