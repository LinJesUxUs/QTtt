#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Game start;
    void Restart();
    int w;
    int h;
    QIcon Xpix;
    QIcon Opix;

    QIcon Zpix1;
    QIcon Zpix2;
    QIcon Zpix3;
    QIcon Zpix4;
    QIcon Zpix5;
    QIcon Zpix6;
    QIcon Zpix7;
    QIcon Zpix8;
    QIcon Zpix9;

    QIcon Xpix1;
    QIcon Xpix2;
    QIcon Xpix3;
    QIcon Xpix4;
    QIcon Xpix5;
    QIcon Xpix6;
    QIcon Xpix7;
    QIcon Xpix8;
    QIcon Xpix9;

    QIcon Opix1;
    QIcon Opix2;
    QIcon Opix3;
    QIcon Opix4;
    QIcon Opix5;
    QIcon Opix6;
    QIcon Opix7;
    QIcon Opix8;
    QIcon Opix9;

    QIcon Over1;
    QIcon Over2;
    QIcon Over3;
    QIcon Over4;
    QIcon Over5;
    QIcon Over6;
    QIcon Over7;
    QIcon Over8;
    QIcon Over9;

    void XWin();
    void OWin();
    void Over();
    void ifOver();


private slots:

//    void digits_numbers(int key);

    void on_exit_clicked();
    void on_restart_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
