#include "SceneState.hpp"
#include <codecvt>
#include <locale>

SceneState::SceneState(UserActions &userActions) :
	m_userActions(userActions)
{
}

void SceneState::_update() {
	if (m_cameraView != nullptr) {
		m_cameraView->update();
	}
	if (m_UICameraView != nullptr) {
		m_UICameraView->update();
	}
}

void SceneState::setUICamera(std::shared_ptr<Camera> camera) {
	m_UICamera = camera;
}

void SceneState::setCamera(std::shared_ptr<Camera> camera) {
	m_camera = camera;
}

void SceneState::setUICameraView(std::shared_ptr<CameraView> cameraView) {
	m_UICameraView = cameraView;
}

void SceneState::setCameraView(std::shared_ptr<CameraView> cameraView) {
	m_cameraView = cameraView;
}

void SceneState::render() {
	if (m_UICamera == nullptr && m_uiObjects.size() > 0) {
		std::cerr << "ERROR: Setting a UI Camera is required to render UI Objects\n";
	}
	for (auto ui : m_uiObjects) {
		ui->render(m_UICamera);
	}
}

void SceneState::_addUIObject(std::shared_ptr<GameObject> obj) {
	m_uiObjects.push_back(obj);
}
