#ifndef _GRAPHICS_OBJECTWAVEFRONT_H_INCLUDED
#define _GRAPHICS_OBJECTWAVEFRONT_H_INCLUDED

#include "objectarray.h"
#include "../../common/include/loadable.h"

#include <string>

namespace Elchcraft {
    namespace Graphics {
        class ObjectWavefront : public ObjectArray, public Elchcraft::Common::Loadable {
            public:
                ObjectWavefront(std::string file);
                virtual void render();
                virtual void glFinish();
            protected:
                virtual void onLoad();
            private:
                unsigned int _vertexCount;
                std::string _file;
                bool _loadingFinished;
        };
    }
}

#endif
