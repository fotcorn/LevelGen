
#include "DrawLevel.h"

#include <iostream>
#include "Level.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "external/stb_image_write.h"

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
            if (x == level.startX  && y == level.startY)
            {
                R = 0xFF;
                G = 0x0;
                B = 0x0;
            }
            else if (x == level.goalX  && y == level.goalY)
            {
                R = 0x37;
                G = 0xa8;
                B = 0x2a;
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
