#include "Entity.h"

void Entity::bindSprite(Sprite* sprite) {
	auto size = sprite->getContentSize();
	this->setContentSize(size);
	this->m_size = size;
	this->m_sprite = sprite;

	m_sprite->setPosition(Point(size.width * 0.5f, size.height * 0.5f));
	this->addChild(m_sprite);
}

Sprite* Entity::getSprite() const {
	return this->m_sprite;
}

Entity::Entity() {
	this->m_sprite = nullptr;
}

Entity::~Entity() {

}
