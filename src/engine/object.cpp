#include <engine\object.hpp>
#include <engine\handle\handleManager.hpp>

Object::Object(uint16_t UID) : _UID(UID) {
	_handle = HandleManager::instance()->Add((void*)this, 0);
}

Handle* Object::getHandle() const {
	return _handle;
}

Object::~Object() {
	HandleManager::instance()->Remove(_handle);
}