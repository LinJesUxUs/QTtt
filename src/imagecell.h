#ifndef IMAGECELL_H
#define IMAGECELL_H

#include <QString>
#include <QPixmap>

class ImageCell : public QPixmap
{
    Q_OBJECT
private:

    QPixmap m_nImg;
    static QPixmap m_nXImg;
    static QPixmap m_nOImg;
public:
    Q_PROPERTY(QPixmap xImg READ getXImg WRITE setXImg NOTIFY xImgChanged)
    Q_PROPERTY(QPixmap oImg READ getOImg WRITE setOImg NOTIFY oImgChanged)
    Q_PROPERTY(QVariant getImg READ getImg WRITE setImg NOTIFY imgChanged )
    ImageCell();

    void setImg( const QChar&);
    static void setXImg( const QPixmap&);
    static void setOImg( const QPixmap&);

    QPixmap getImg() const;
    static QPixmap getXImg();
    static QPixmap getOImg();

signals:
    void imgChanged(QPixmap);
    static void xImgChanged(QPixmap);
    static void oImgChanged(QPixmap);
};

#endif // IMAGECELL_H
