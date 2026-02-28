//
// Created by djdisaster on 28/02/2026.
//

#ifndef UNTITLED2_VERTEXBUFFER_H
#define UNTITLED2_VERTEXBUFFER_H


class VertexBuffer {
private:
    unsigned int m_RendererID;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    void Bind() const;
    void Unbind() const;
};


#endif //UNTITLED2_VERTEXBUFFER_H