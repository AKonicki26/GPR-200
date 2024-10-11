//
// Created by thecr on 9/13/2024.
//

#ifndef EWRENDER_SHADER_H
#define EWRENDER_SHADER_H

#include <glm/fwd.hpp>

#include "./../../core/ew/external/glad.h"

namespace ak {

    class Shader {
    public:
        unsigned int ID;

        Shader(const char* vertexPath, const char* fragmentPath);

        void use();

        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setMat4(const std::string &name, const glm::mat4 &value) const;
    };

} // ak

#endif //EWRENDER_SHADER_H
