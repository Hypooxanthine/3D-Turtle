#include "HypoGl/Texture.h"

#include <jpeglib.h>
#include <jerror.h>
#include <iostream>
#include <limits>

Texture::Texture()
{}

Texture::Texture(const Color& col)
{
    textureSize = {1, 1};

    data.reserve(3);
    data.push_back(std::clamp(col.r, 0.f, 1.f) * std::numeric_limits<uint8_t>::max());
    data.push_back(std::clamp(col.g, 0.f, 1.f) * std::numeric_limits<uint8_t>::max());
    data.push_back(std::clamp(col.b, 0.f, 1.f) * std::numeric_limits<uint8_t>::max());
}

bool Texture::loadFromFile(const std::string& path)
{
    FILE* file;

    if(file = fopen(path.data(), "rb"); file == NULL)
    {
        std::cout << "Impossible de trouver le fichier " << path << std::endl;
        return false;
    }

    size_t extPos = path.find_last_of(".");

    if(extPos == std::string::npos) return false;

    extPos += 1;

    std::string extension;

    for(size_t i = extPos ; i < path.size() ; i++)
        extension += path.at(i);

    if(extension == "jpg" || extension == "jpeg")
    {
        jpeg_decompress_struct cinfo;
        jpeg_error_mgr jerr;

        cinfo.err = jpeg_std_error(&jerr);
        jpeg_create_decompress(&cinfo);
        jpeg_stdio_src(&cinfo, file);
        jpeg_read_header(&cinfo, TRUE);

        if(cinfo.jpeg_color_space == JCS_GRAYSCALE)
        {
            std::cout << "Image is not RGB." << std::endl;
            return false;
        }

        textureSize = {cinfo.image_width, cinfo.image_height};

        data.clear();
        data.reserve(getWidth() * getHeight() * 3);

        jpeg_start_decompress(&cinfo);

        uint8_t* line = new uint8_t[3 * getWidth()];

        while(cinfo.output_scanline < getHeight())
        {
            jpeg_read_scanlines(&cinfo, &line, 1);

            for(size_t i = 0 ; i < getWidth() * 3 ; i++)
                data.push_back(line[i]);
        }

        delete line;

        jpeg_finish_decompress(&cinfo);
        jpeg_destroy_decompress(&cinfo);

        return true;
    }
    else
    {
        std::cout << "Bad image extension." << std::endl;
        return false;
    }
}

const Texture Texture::White  = Texture({1.f, 1.f, 1.f});
const Texture Texture::Black  = Texture({0.f, 0.f, 0.f});
const Texture Texture::Red    = Texture({1.f, 0.f, 0.f});
const Texture Texture::Green  = Texture({0.f, 1.f, 0.f});
const Texture Texture::Blue   = Texture({0.f, 0.f, 1.f});
