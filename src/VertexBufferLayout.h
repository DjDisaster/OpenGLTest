//
// Created by djdisaster on 28/02/2026.
//

#ifndef UNTITLED2_VERTEXBUFFERLAYOUT_H
#define UNTITLED2_VERTEXBUFFERLAYOUT_H

#include <vector>
#include <GL/glew.h>

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    bool normalized;
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

public:
    VertexBufferLayout() : m_Stride(0) {}

    template<typename T>
    void Push(unsigned int count);

    [[nodiscard]] inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
    [[nodiscard]] inline unsigned int GetStride() const { return m_Stride; }
};

#endif //UNTITLED2_VERTEXBUFFERLAYOUT_H