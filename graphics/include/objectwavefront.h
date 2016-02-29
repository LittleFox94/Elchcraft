#ifndef _GRAPHICS_OBJECTWAVEFRONT_H_INCLUDED
#define _GRAPHICS_OBJECTWAVEFRONT_H_INCLUDED

#include "objectarray.h"
#include "../../common/include/loadable.h"

#include <string>
#include <unordered_map>

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
                struct Material {
                    float ns, ni, d;
                    int illum;
                    float ka_r, ka_g, ka_b;
                    float kd_r, kd_g, kd_b;
                    float ks_r, ks_g, ks_b;
                    float ke_r, ke_g, ke_b;
                };

                unsigned int _vertexCount;
                std::string _file;
                bool _loadingFinished;

                GLuint _colorBuffer;

                void loadMaterialFile(std::string const& file, std::unordered_map<std::string, Material>& materials);
        };
    }
}

#endif
