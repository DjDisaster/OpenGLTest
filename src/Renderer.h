//
// Created by djdisaster on 28/02/2026.
//
#include <GL/glew.h>

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#ifndef UNTITLED2_RENDERER_H
#define UNTITLED2_RENDERER_H


class Renderer {
private:
public:
    void Clear() const;
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& s) const;
};


#endif //UNTITLED2_RENDERER_H