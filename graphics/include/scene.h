#ifndef _GRAPHICS_SCENE_H_INCLUDED
#define _GRAPHICS_SCENE_H_INCLUDED

#include "object.h"

#include <list>

namespace Elchcraft {
    namespace Graphics {
        typedef unsigned long long SceneObjectIdentifier;

        class Scene {
            public:
                Scene();
                virtual ~Scene();

                void addObject(Object* object, unsigned short weight);
                void removeObject(Object* object);

                const std::list<Object*>* getObjects() const;

             private:
                std::list<Object*> _objects;
        };
    }
}

#endif
