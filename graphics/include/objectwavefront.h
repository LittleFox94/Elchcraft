#ifndef _GRAPHICS_OBJECTWAVEFRONT_H_INCLUDED
#define _GRAPHICS_OBJECTWAVEFRONT_H_INCLUDED

#include "objectarray.h"

#include <string>

namespace Elchcraft {
    namespace Graphics {
        class ObjectWavefront : public ObjectArray {
            public:
                ObjectWavefront(std::string file);
                virtual void render();
            private:
                unsigned int _vertexCount;
        };
    }
}

#endif
