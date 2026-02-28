//
// Created by djdisaster on 28/02/2026.
//

#ifndef UNTITLED2_INDEXBUFFER_H
#define UNTITLED2_INDEXBUFFER_H


class IndexBuffer {
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();
    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_Count; }
};


#endif //UNTITLED2_INDEXBUFFER_H