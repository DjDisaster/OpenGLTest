//
// Created by djdisaster on 28/02/2026.
//

#ifndef UNTITLED2_VERTEXARRAY_H
#define UNTITLED2_VERTEXARRAY_H
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


class VertexArray {
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout&);
    void Bind() const;
    void Unbind() const;
};


#endif //UNTITLED2_VERTEXARRAY_H