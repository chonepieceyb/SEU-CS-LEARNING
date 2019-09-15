#ifndef KEYBOARDBUFFER_H
#define KEYBOARDBUFFER_H

#include <QString>

class KeyBoardBuffer
{
public:
    static const int SIZE = 3;
    KeyBoardBuffer();
    // 向缓冲区添加字符
    void addKey(QChar);
    // 返回缓冲区字符
    QString getBuffer()const;

    int getCurrentSize()const;
    //清除缓冲全部字符
    void clear();
private:
    // 缓冲区大小
    // 缓冲区
    QString m_buffer;
    // 弹出缓冲区第一个字符
    void popFirst();
};

#endif // KEYBOARDBUFFER_H
