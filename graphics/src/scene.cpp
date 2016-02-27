#include "../include/scene.h"

namespace Elchcraft {
    namespace Graphics {
        Scene::Scene() {
        }

        Scene::~Scene() {
        }

        void Scene::addObject(Object* object, unsigned short weight) {
            _objects.push_back(object);
        }

        void Scene::removeObject(Object* object) {
            _objects.remove(object);
        }

        const std::list<Object*>* Scene::getObjects() const {
            return &_objects;
        }
    }
}
