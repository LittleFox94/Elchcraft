#include "../include/objectwavefront.h"
#include "../../common/include/loadhandler.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <unordered_map>
#include <unistd.h>

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
            float* vertices;
            float* colors;
            size_t size;
        };
       
        ObjectWavefront::ObjectWavefront(std::string file)
            : _file(file),
              _loadingFinished(false),
              _colorBuffer(0) {
            Elchcraft::Common::LoadHandler::getInstance()->addLoadable(this);
        }

        void ObjectWavefront::loadMaterialFile(std::string const& file, std::unordered_map<std::string, Material>& materials) {
            std::ifstream filestream(file);

            std::string currentName;
            Material currentMaterial;

            if(!filestream.good()) {
                std::cerr << "Could not open material file \"" << file << "\"!" << std::endl;
            }

            while(filestream.good()) {
                std::string line;
                std::getline(filestream, line);

                std::stringstream linestream(line);

                std::string command;
                std::getline(linestream, command, ' ');

                if(line.length() > command.length()) {
                    linestream.str(line.substr(command.length() + 1));
                }

                if(command == "newmtl") {
                    materials[currentName] = currentMaterial;
                    std::getline(linestream, currentName);
                }
                else if(command == "illum") {
                    currentMaterial.illum = std::stoi(linestream.str());
                }
                else if(command == "d") {
                    currentMaterial.d = std::stod(linestream.str());
                }
                else if(command == "Ns") {
                    currentMaterial.ns = std::stod(linestream.str());
                }
                else if(command == "Ni") {
                    currentMaterial.ni = std::stod(linestream.str());
                }
                else if(command == "Ka") {
                    linestream >> currentMaterial.ka_r >> currentMaterial.ka_g >> currentMaterial.ka_b;
                }
                else if(command == "Kd") {
                    linestream >> currentMaterial.kd_r >> currentMaterial.kd_g >> currentMaterial.kd_b;
                }
                else if(command == "Ks") {
                    linestream >> currentMaterial.ks_r >> currentMaterial.ks_g >> currentMaterial.ks_b;
                }
                else if(command == "Ke") {
                    linestream >> currentMaterial.ke_r >> currentMaterial.ke_g >> currentMaterial.ke_b;
                }
            }

            materials[currentName] = currentMaterial;
        }

        void ObjectWavefront::onLoad() {
            std::ifstream filestream(_file);

            if(!filestream.good()) {
                std::cerr << "Could not open model \"" << _file << "\"!" << std::endl;
                return;
            }

            std::string name, mtllib;

            std::unordered_map<std::string, Material> materials;
            std::vector<Point3D> vertices;
            std::vector<Point2D> textureCoords;
            std::vector<Point3D> normales;

            std::vector<GLfloat> finalVertices;
            std::vector<GLfloat> finalColors;

            while(filestream.good()) {
                std::string line;
                std::getline(filestream, line);
                
                std::stringstream linestream(line);

                std::string command;
                std::getline(linestream, command, ' ');

                Material currentMaterial;

                if(command == "mtllib") {
                    std::getline(linestream, mtllib);

                    std::string directory = _file.substr(0, _file.find_last_of("/"));
                    loadMaterialFile(directory + "/" + mtllib, materials);
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
                else if(command == "usemtl") {
                    std::string name;
                    std::getline(linestream, name);
                    currentMaterial = materials[name];
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

                    finalVertices.reserve(9);
                    finalVertices.push_back(avert.x);
                    finalVertices.push_back(avert.y);
                    finalVertices.push_back(avert.z);

                    finalVertices.push_back(bvert.x);
                    finalVertices.push_back(bvert.y);
                    finalVertices.push_back(bvert.z);

                    finalVertices.push_back(cvert.x);
                    finalVertices.push_back(cvert.y);
                    finalVertices.push_back(cvert.z);

                    finalColors.reserve(9);
                    for(int i = 0; i < 3; i++) {
                        finalColors.push_back(currentMaterial.kd_r);
                        finalColors.push_back(currentMaterial.kd_g);
                        finalColors.push_back(currentMaterial.kd_b);
                    }
                }
            }

            DataTemp* temp = new DataTemp();

            temp->vertices = new GLfloat[finalVertices.size()];
            std::memcpy(temp->vertices, finalVertices.data(), finalVertices.size() * sizeof(GLfloat));

            temp->colors = new GLfloat[finalColors.size()];
            std::memcpy(temp->colors, finalColors.data(), finalColors.size() * sizeof(GLfloat));

            temp->size = finalVertices.size() * sizeof(GLfloat);
            _datatemp = (void*)temp;
        }

        void ObjectWavefront::glFinish() {
            if(_datatemp == nullptr) {
                return;
            }

            glBindVertexArray(_vertexArrayID);
            glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

            DataTemp* temp = (DataTemp*)_datatemp;

            glBufferData(GL_ARRAY_BUFFER, temp->size, temp->vertices, GL_STATIC_DRAW);
            _vertexCount = temp->size / sizeof(GLfloat);

            glGenBuffers(1, &_colorBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);
            glBufferData(GL_ARRAY_BUFFER, temp->size, temp->colors, GL_STATIC_DRAW);

            delete temp->vertices;
            delete temp->colors;
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

            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glDisableVertexAttribArray(0);
        }
    }
}
