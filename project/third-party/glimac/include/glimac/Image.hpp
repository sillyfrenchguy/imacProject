#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "glm.hpp"
#include "FilePath.hpp"

namespace glimac {

class Image {
private:
    unsigned int m_nWidth = 0u;
    unsigned int m_nHeight = 0u;
    std::unique_ptr<glm::vec3[]> m_Pixels;
public:
    Image(unsigned int width, unsigned int height):
        m_nWidth(width), m_nHeight(height), m_Pixels(new glm::vec3[width * height]) {
    }

    unsigned int getWidth() const {
        return m_nWidth;
    }

    unsigned int getHeight() const {
        return m_nHeight;
    }

    const glm::vec3* getPixels() const {
        return m_Pixels.get();
    }

    glm::vec3* getPixels() {
        return m_Pixels.get();
    }
};

class ImageAlpha {
private:
    unsigned int m_nWidth = 0u;
    unsigned int m_nHeight = 0u;
    std::unique_ptr<glm::vec4[]> m_Pixels;
public:
    ImageAlpha(unsigned int width, unsigned int height):
        m_nWidth(width), m_nHeight(height), m_Pixels(new glm::vec4[width * height]) {
    }

    unsigned int getWidth() const {
        return m_nWidth;
    }

    unsigned int getHeight() const {
        return m_nHeight;
    }

    const glm::vec4* getPixels() const {
        return m_Pixels.get();
    }

    glm::vec4* getPixels() {
        return m_Pixels.get();
    }
};


std::unique_ptr<Image> loadImage(const FilePath& filepath);
std::unique_ptr<ImageAlpha> loadImageAlpha(const FilePath& filepath);

class ImageManager {
private:
    static std::unordered_map<FilePath, std::unique_ptr<Image>> m_ImageMap;
    static std::unordered_map<FilePath, std::unique_ptr<ImageAlpha>> m_ImageMapAlpha;
public:
    static const Image* loadImage(const FilePath& filepath);
    static const ImageAlpha* loadImageAlpha(const FilePath& filepath);
};


}
