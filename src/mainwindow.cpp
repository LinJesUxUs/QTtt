#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Xpix.addFile(":/resources/files/Y.JPG");
    Opix.addFile(":/resources/files/A.JPG");
    Zpix1.addFile(":/resources/files/Z1.JPG");
    Zpix2.addFile(":/resources/files/Z2.JPG");
    Zpix3.addFile(":/resources/files/Z3.JPG");
    Zpix4.addFile(":/resources/files/Z4.JPG");
    Zpix5.addFile(":/resources/files/Z5.JPG");
    Zpix6.addFile(":/resources/files/Z6.JPG");
    Zpix7.addFile(":/resources/files/Z7.JPG");
    Zpix8.addFile(":/resources/files/Z8.JPG");
    Zpix9.addFile(":/resources/files/Z9.JPG");
    Opix1.addFile(":/resources/files/AWin1.JPG");
    Opix2.addFile(":/resources/files/AWin2.JPG");
    Opix3.addFile(":/resources/files/AWin3.JPG");
    Opix4.addFile(":/resources/files/AWin4.JPG");
    Opix5.addFile(":/resources/files/AWin5.JPG");
    Opix6.addFile(":/resources/files/AWin6.JPG");
    Opix7.addFile(":/resources/files/AWin7.JPG");
    Opix8.addFile(":/resources/files/AWin8.JPG");
    Opix9.addFile(":/resources/files/AWin9.JPG");
    Xpix1.addFile(":/resources/files/YWin1.jpg");
    Xpix2.addFile(":/resources/files/YWin2.jpg");
    Xpix3.addFile(":/resources/files/YWin3.jpg");
    Xpix4.addFile(":/resources/files/YWin4.jpg");
    Xpix5.addFile(":/resources/files/YWin5.jpg");
    Xpix6.addFile(":/resources/files/YWin6.jpg");
    Xpix7.addFile(":/resources/files/YWin7.jpg");
    Xpix8.addFile(":/resources/files/YWin8.jpg");
    Xpix9.addFile(":/resources/files/YWin9.jpg");

    Over1.addFile(":/resources/files/Over1.JPG");
    Over2.addFile(":/resources/files/Over2.JPG");
    Over3.addFile(":/resources/files/Over3.JPG");
    Over4.addFile(":/resources/files/Over4.JPG");
    Over5.addFile(":/resources/files/Over5.JPG");
    Over6.addFile(":/resources/files/Over6.JPG");
    Over7.addFile(":/resources/files/Over7.JPG");
    Over8.addFile(":/resources/files/Over8.JPG");
    Over9.addFile(":/resources/files/Over9.JPG");

    MainWindow::Restart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::XWin()
{
    ui->pushButton->setIcon(Xpix1);
    ui->pushButton_2->setIcon(Xpix2);
    ui->pushButton_3->setIcon(Xpix3);
    ui->pushButton_4->setIcon(Xpix4);
    ui->pushButton_5->setIcon(Xpix5);
    ui->pushButton_6->setIcon(Xpix6);
    ui->pushButton_7->setIcon(Xpix7);
    ui->pushButton_8->setIcon(Xpix8);
    ui->pushButton_9->setIcon(Xpix9);
}

void MainWindow::OWin()
{
    ui->pushButton->setIcon(Opix1);
    ui->pushButton_2->setIcon(Opix2);
    ui->pushButton_3->setIcon(Opix3);
    ui->pushButton_4->setIcon(Opix4);
    ui->pushButton_5->setIcon(Opix5);
    ui->pushButton_6->setIcon(Opix6);
    ui->pushButton_7->setIcon(Opix7);
    ui->pushButton_8->setIcon(Opix8);
    ui->pushButton_9->setIcon(Opix9);
}

void MainWindow::Over()
{
    ui->pushButton->setIcon(Over1);
    ui->pushButton_2->setIcon(Over2);
    ui->pushButton_3->setIcon(Over3);
    ui->pushButton_4->setIcon(Over4);
    ui->pushButton_5->setIcon(Over5);
    ui->pushButton_6->setIcon(Over6);
    ui->pushButton_7->setIcon(Over7);
    ui->pushButton_8->setIcon(Over8);
    ui->pushButton_9->setIcon(Over9);
}

void MainWindow::Restart()
{
    start.Clear_board();
    ui->pushButton->setIcon(Zpix1);
    ui->pushButton_2->setIcon(Zpix2);
    ui->pushButton_3->setIcon(Zpix3);
    ui->pushButton_4->setIcon(Zpix4);
    ui->pushButton_5->setIcon(Zpix5);
    ui->pushButton_6->setIcon(Zpix6);
    ui->pushButton_7->setIcon(Zpix7);
    ui->pushButton_8->setIcon(Zpix8);
    ui->pushButton_9->setIcon(Zpix9);
}

void MainWindow::on_exit_clicked()
{
    close();
}

void MainWindow::on_restart_clicked()
{
    MainWindow::Restart();
}

void MainWindow::ifOver()
{
    start.Change_game();
    if (start.Over()!=' '||start.step>=9)
    {
        switch (start.Over())
        {
            case 'X':
            MainWindow::XWin();
            break;
            case 'O':
            MainWindow::OWin();
            break;
            case ' ':
            MainWindow::Over();
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    int x=0;
    int y=0;
    if (start.Over()==' '&&start.step<9)
    {
        if(start.Command(x,y))
        {
            switch (start.Get_game())
            {
                case 'X':
                ui->pushButton->setIcon(Xpix);
                break;
                case 'O':
                ui->pushButton->setIcon(Opix);
                break;
            }
        }
    }
    MainWindow::ifOver();
}

void MainWindow::on_pushButton_2_clicked()
{
    int x=1;
    int y=0;
    if (start.Over()==' '&&start.step<9)
    {
        if(start.Command(x,y))
        {
            switch (start.Get_game())
            {
                case 'X':
                ui->pushButton_2->setIcon(Xpix);
                break;
                case 'O':
                ui->pushButton_2->setIcon(Opix);
                break;
            }
        }
    }
    MainWindow::ifOver();
}

void MainWindow::on_pushButton_3_clicked()
{
    int x=2;
    int y=0;
    if (start.Over()==' '&&start.step<9)
    {
        if(start.Command(x,y))
        {
            switch (start.Get_game())
            {
                case 'X':
                ui->pushButton_3->setIcon(Xpix);
                break;
                case 'O':
                ui->pushButton_3->setIcon(Opix);
                break;
            }
        }
    }
    MainWindow::ifOver();
}

void MainWindow::on_pushButton_4_clicked()
{
    int x=0;
    int y=1;
    if (start.Over()==' '&&start.step<9)
    {
        if(start.Command(x,y))
        {
            switch (start.Get_game())
            {
                case 'X':
                ui->pushButton_4->setIcon(Xpix);
                break;
                case 'O':
                ui->pushButton_4->setIcon(Opix);
                break;
            }
        }
    }
    MainWindow::ifOver();
}

void MainWindow::on_pushButton_5_clicked()
{
    int x=1;
    int y=1;
    if (start.Over()==' '&&start.step<9)
    {
        if(start.Command(x,y))
        {
            switch (start.Get_game())
            {
                case 'X':
                ui->pushButton_5->setIcon(Xpix);
                break;
                case 'O':
                ui->pushButton_5->setIcon(Opix);
                break;
            }
        }
    }
    MainWindow::ifOver();
}

void MainWindow::on_pushButton_6_clicked()
{
    int x=2;
    int y=1;
    if (start.Over()==' '&&start.step<9)
    {
        if(start.Command(x,y))
        {
            switch (start.Get_game())
            {
                case 'X':
                ui->pushButton_6->setIcon(Xpix);
                break;
                case 'O':
                ui->pushButton_6->setIcon(Opix);
                break;
            }
        }
    }
    MainWindow::ifOver();
}

void MainWindow::on_pushButton_7_clicked()
{
    int x=0;
    int y=2;
    if (start.Over()==' '&&start.step<9)
    {
        if(start.Command(x,y))
        {
            switch (start.Get_game())
            {
                case 'X':
                ui->pushButton_7->setIcon(Xpix);
                break;
                case 'O':
                ui->pushButton_7->setIcon(Opix);
                break;
            }
        }
    }
    MainWindow::ifOver();
}

void MainWindow::on_pushButton_8_clicked()
{
    int x=1;
    int y=2;
    if (start.Over()==' '&&start.step<9)
    {
        if(start.Command(x,y))
        {
            switch (start.Get_game())
            {
                case 'X':
                ui->pushButton_8->setIcon(Xpix);
                break;
                case 'O':
                ui->pushButton_8->setIcon(Opix);
                break;
            }
        }
    }
    MainWindow::ifOver();
}

void MainWindow::on_pushButton_9_clicked()
{
    int x=2;
    int y=2;
    if (start.Over()==' '&&start.step<9)
    {
        if(start.Command(x,y))
        {
            switch (start.Get_game())
            {
                case 'X':
                ui->pushButton_9->setIcon(Xpix);
                break;
                case 'O':
                ui->pushButton_9->setIcon(Opix);
                break;
            }
        }
    }
    MainWindow::ifOver();
}
