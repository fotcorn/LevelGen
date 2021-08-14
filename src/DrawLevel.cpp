#include "DrawLevel.h"

#include <iostream>
#include "Level.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "external/stb_image_write.h"
#pragma GCC diagnostic pop


void ExportLevelToPng(const Level& level)
{
    constexpr int imageSize = LEVEL_SIZE;
    unsigned char pixelData[imageSize * imageSize * 3];
    for (int y = 0; y < LEVEL_SIZE; y++)
    {
        for (int x = 0; x < LEVEL_SIZE; x++)
        {
            unsigned char R = 0xFF;
            unsigned char G = 0xFF;
            unsigned char B = 0xFF;
            if (x == level.start.x  && y == level.start.y)
            {
                R = 0xFF;
                G = 0x0;
                B = 0x0;
            }
            else if (x == level.dest.x  && y == level.dest.y)
            {
                R = 0x37;
                G = 0xa8;
                B = 0x2a;
            }
            else if (level.tiles[x][y].path)
            {
                R = 0x00;
                G = 0x4d;
                B = 0x99;
            }
            else if (level.tiles[x][y].occupied)
            {
                R = 0x0;
                G = 0x0;
                B = 0x0;
            }
            pixelData[(y * LEVEL_SIZE + x) * 3] = R;
            pixelData[(y * LEVEL_SIZE + x) * 3 + 1] = G;
            pixelData[(y * LEVEL_SIZE + x) * 3 + 2] = B;
        }
    }

    stbi_write_png("level.png", imageSize, imageSize, 3, &pixelData, imageSize * 3);
}
