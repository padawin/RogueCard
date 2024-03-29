#ifndef __OBJECT__
#define __OBJECT__

#include <memory>
#include <map>
#include <string>
#include "GameObjectRenderer.hpp"
#include "Component.hpp"
#include "Camera.hpp"

class GameObject {
	protected:
	glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_angle = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_scale = glm::vec3(1.0f, 1.0f, 1.0f);

	std::map<std::string, std::shared_ptr<Component>> m_mComponents = {};

	public:
	virtual ~GameObject() {}
	virtual void init() {};
	virtual void setPosition(float x, float y, float z);
	virtual void setScale(float x, float y, float z);
	virtual void setRotation(float x, float y, float z);
	virtual glm::vec3 getPosition() const;
	virtual glm::vec3 getRotation() const;
	virtual glm::vec3 getScale() const;
	virtual void update();
	virtual void render(std::shared_ptr<Camera> camera);
	virtual void addComponent(std::string name, std::shared_ptr<Component> component);
	virtual void initComponents();
	virtual void clearComponents();
	virtual std::shared_ptr<Component> getComponent(std::string name);
	template<class T>
	std::shared_ptr<T> getComponent(std::string name);
};

template<class T>
std::shared_ptr<T> GameObject::getComponent(std::string name) {
	if (m_mComponents.find(name) == m_mComponents.end()) {
		return nullptr;
	}

	return std::dynamic_pointer_cast<T>(m_mComponents[name]);
}

#endif
