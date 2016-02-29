#ifndef _COMMON_LOADHANDLER_H_INCLUDED
#define _COMMON_LOADHANDLER_H_INCLUDED

#include "loadable.h"

#include <list>
#include <thread>

namespace Elchcraft {
    namespace Common {
        enum class LoadVerbosity {
            Fullscreen,
            Widget,
            None,
        };

        class LoadHandler {
            public:
                static LoadHandler* getInstance() {
                    if(_instance == nullptr) {
                        _instance = new LoadHandler();
                    }

                    return _instance;
                }

                LoadHandler() {
                }

                void addLoadable(Loadable* loadable) {
                    _loadables.push_back(loadable);

                    std::thread thread(&LoadHandler::runLoadable, this, loadable);
                    thread.detach();
                }

                size_t getNumJobs() {
                    return _loadables.size();
                }

                size_t getNumFinishedJobs() {
                    size_t ret = 0;
                    for(auto l : _loadables) {
                        if(l->finished()) {
                            ret++;
                        }
                    }
                    return ret;
                }

                bool glFinishLoading() {
                    if(_glWaitingLoadables.size() == 0) {
                        return false;
                    }

                    _glWaitingLoadables.front()->glFinish();
                    _glWaitingLoadables.pop_front();
                    return true;
                }

            private:
                static LoadHandler* _instance;

                std::list<Loadable*> _loadables;
                std::list<Loadable*> _glWaitingLoadables;

                void runLoadable(Loadable* loadable) {
                    loadable->load();
                    _glWaitingLoadables.push_back(loadable);
                    _loadables.remove(loadable);
                }
        };
    }
}

#endif
