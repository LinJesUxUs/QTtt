#include "imagecell.h"

ImageCell::ImageCell() {}

void ImageCell::setImg(const QChar & val)
{
    switch (val.toLatin1()){
    case 'X':
        m_nImg = m_nXImg;
        break;
    case 'O':
        m_nImg = m_nOImg;
        break;
    }
    emit imgChanged(m_nImg);
}

void ImageCell::setXImg(const QPixmap & val)
{
    m_nXImg = val;
    emit xImgChanged(m_nXImg);
}

void ImageCell::setOImg(const QPixmap & val)
{
    m_nOImg = val;
    emit oImgChanged(m_nOImg);
}

QPixmap ImageCell::getImg() const
{
    return m_nImg;
}

QPixmap ImageCell::getXImg()
{
    return m_nXImg;
}

QPixmap ImageCell::getOImg()
{
    return m_nOImg;
}
