//
// Created by thecr on 9/25/2024.
//

#ifndef EWRENDER_TEXTURE2D_H
#define EWRENDER_TEXTURE2D_H

#include "./../../core/ew/external/glad.h"
#include "./../../core/ew/external/stb_image.h"
#include <iostream>

namespace ak {

    class Texture2D {
    public:
        Texture2D(const char* filePath, int filterMode, int wrapMode);
        ~Texture2D();
        void Bind(unsigned int slot = 0);
    private:
        unsigned int m_id;
        int m_width, m_height;
    };

} // ak

#endif //EWRENDER_TEXTURE2D_H
