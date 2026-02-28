//
// Created by djdisaster on 28/02/2026.
//

#ifndef UNTITLED2_VERTEXARRAY_H
#define UNTITLED2_VERTEXARRAY_H
#include "VertexBuffer.h"


class VertexArray {
private:

public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout&);

};


#endif //UNTITLED2_VERTEXARRAY_H