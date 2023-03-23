#pragma once

#include <string>
#include <vector>

#include "Color.h"
#include "DataStructures.h"

class Texture
{
public:
    using ImageData = std::vector<uint8_t>;

    Texture();
    Texture(const Color& col);

    bool loadFromFile(const std::string& path);

    inline const ImageData& getData() const { return data; }
    inline const unsigned int& getWidth() const { return textureSize.x; }
    inline const unsigned int& getHeight() const { return textureSize.y; }

    static const Texture White;
    static const Texture Black;
    static const Texture Red;
    static const Texture Green;
    static const Texture Blue;

private:
    ImageData data;
    Vector2u textureSize;
};
