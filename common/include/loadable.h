#ifndef _COMMON_LOADABLE_H_INCLUDED
#define _COMMON_LOADABLE_H_INCLUDED

namespace Elchcraft {
    namespace Common {
        class Loadable {
            public:
                Loadable() : _finished(false) {
                }

                bool finished() {
                    return _finished;
                }

                void load() {
                    onLoad();
                    _finished = true;
                }

                virtual void glFinish() {
                }

            protected:
                void* _datatemp;
                virtual void onLoad() = 0;

            private:
                bool _finished;
        };
    }
}

#endif
