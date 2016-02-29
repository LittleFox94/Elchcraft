#include "../include/objectwavefront.h"
#include "../../common/include/loadhandler.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cstring>

namespace Elchcraft {
    namespace Graphics {
        struct Point2D {
            float x;
            float y;
        };

        struct Point3D {
            float x;
            float y;
            float z;
        };

        struct DataTemp {
            float* data;
            size_t size;
        };

        ObjectWavefront::ObjectWavefront(std::string file)
            : _file(file),
              _loadingFinished(false) {
            Elchcraft::Common::LoadHandler::getInstance()->addLoadable(this);
        }

        void ObjectWavefront::onLoad() {
            std::ifstream filestream(_file, std::ios_base::in);

            std::string name, mtllib;

            std::vector<Point3D> vertices;
            std::vector<Point2D> textureCoords;
            std::vector<Point3D> normales;
            std::vector<GLfloat> readyToStoreInVRAM;

            while(!filestream.eof()) {
                std::string line;
                std::getline(filestream, line);
                
                std::stringstream linestream(line);

                std::string command;
                std::getline(linestream, command, ' ');

                if(command == "mtllib") {
                    std::getline(linestream, mtllib);
                }
                else if(command == "o") {
                    std::getline(linestream, name);
                }
                else if(command == "v") {
                    float x, y, z;
                    linestream >> x >> y >> z;
                    vertices.push_back({x, y, z});
                }
                else if(command == "vt") {
                    float x, y;
                    linestream >> x >> y;
                    textureCoords.push_back({x, y});
                }
                else if(command == "vn") {
                    float x, y, z;
                    linestream >> x >> y >> z;
                    normales.push_back({x, y, z});
                }
                else if(command == "f") {
                    std::string adata, bdata, cdata;
                    std::getline(linestream, adata, ' ');
                    std::getline(linestream, bdata, ' ');
                    std::getline(linestream, cdata, ' ');

                    std::stringstream astream(adata),
                                      bstream(bdata),
                                      cstream(cdata);

                    std::string av, at, an, bv, bt, bn, cv, ct, cn;
                    
                    std::getline(astream, av, '/');
                    std::getline(astream, at, '/');
                    std::getline(astream, an, '/');
                    
                    std::getline(bstream, bv, '/');
                    std::getline(bstream, bt, '/');
                    std::getline(bstream, bn, '/');

                    std::getline(cstream, cv, '/');
                    std::getline(cstream, ct, '/');
                    std::getline(cstream, cn, '/');

                    Point3D avert = vertices.at(std::atoi(av.c_str()) - 1);
                    Point3D bvert = vertices.at(std::atoi(bv.c_str()) - 1);
                    Point3D cvert = vertices.at(std::atoi(cv.c_str()) - 1);

                    readyToStoreInVRAM.push_back(avert.x);
                    readyToStoreInVRAM.push_back(avert.y);
                    readyToStoreInVRAM.push_back(avert.z);

                    readyToStoreInVRAM.push_back(bvert.x);
                    readyToStoreInVRAM.push_back(bvert.y);
                    readyToStoreInVRAM.push_back(bvert.z);

                    readyToStoreInVRAM.push_back(cvert.x);
                    readyToStoreInVRAM.push_back(cvert.y);
                    readyToStoreInVRAM.push_back(cvert.z);
                }
            }

            DataTemp* temp = new DataTemp();
            temp->data = new GLfloat[readyToStoreInVRAM.size()];
            std::memcpy(temp->data, readyToStoreInVRAM.data(), readyToStoreInVRAM.size() * sizeof(GLfloat));
            temp->size = readyToStoreInVRAM.size() * sizeof(GLfloat);
            _datatemp = (void*)temp;
        }

        void ObjectWavefront::glFinish() {
            glBindVertexArray(_vertexArrayID);
            glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

            DataTemp* temp = (DataTemp*)_datatemp;

            glBufferData(GL_ARRAY_BUFFER, temp->size, temp->data, GL_STATIC_DRAW);
            _vertexCount = temp->size / sizeof(GLfloat);
            std::cerr << "Stored " << _vertexCount << " vertices in VRAM" << std::endl;

            delete temp->data;
            delete temp;

            _loadingFinished = true;
        }

        void ObjectWavefront::render() {
            if(!_loadingFinished) {
                return;
            }

            ObjectArray::render();
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glDrawArrays(GL_TRIANGLES, 0, _vertexCount);
            glDisableVertexAttribArray(0);
        }
    }
}
