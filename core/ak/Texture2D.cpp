//
// Created by thecr on 9/25/2024.
//

#include "Texture2D.h"

namespace ak {
    Texture2D::Texture2D(const char *filePath, int filterMode, int wrapMode) {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
        int nrChannels;
        unsigned char* data = stbi_load(filePath, &m_width, &m_height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture: " << filePath << std::endl;
        }
        stbi_image_free(data);
    }

    Texture2D::~Texture2D() {

    }

    void Texture2D::Bind(unsigned int slot) {
        glBindTexture(GL_TEXTURE_2D, m_id);
    }
} // ak