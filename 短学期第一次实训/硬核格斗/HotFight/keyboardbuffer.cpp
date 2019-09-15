#include "keyboardbuffer.h"
#include <QString>

KeyBoardBuffer::KeyBoardBuffer()
{
    // 初始化缓冲区
    m_buffer = "";
}

QString KeyBoardBuffer::getBuffer() const
{
   return m_buffer;
}

int KeyBoardBuffer::getCurrentSize() const
{
    return m_buffer.size();
}

void KeyBoardBuffer::popFirst()
{
    m_buffer.remove(0,1);
}

void KeyBoardBuffer::addKey(QChar a)
{
    if(m_buffer.size() == SIZE)
        popFirst();
    m_buffer.push_back(a);
}

void KeyBoardBuffer::clear()
{
    m_buffer = "";
}
