//
// Created by djdisaster on 02/03/2026.
//

#ifndef UNTITLED2_TEXTURE_H
#define UNTITLED2_TEXTURE_H
#include "Renderer.h"

class texture {
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
public:
    Texture(const std::string& path);
};


#endif //UNTITLED2_TEXTURE_H