#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow )
{
    ui->setupUi( this );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString content = ui->textEdit->toPlainText();
    if( content.length() == 0 )
    {
        QMessageBox::about( this, "Notice", "Required information should not be empty!" );
    }
    else
    {
        QByteArray content_byte = content.toLatin1();
        char *content_char = content_byte.data();
        privateConvert( content_char );

        QString filePath = QDir::currentPath() + "/license.txt";
        QFile file( filePath );
        if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
            return;
        QTextStream out( &file );
        out << content_char;
        QMessageBox::about( this, "Notice", "License file has been generated!" );
    }
}

void MainWindow::privateConvert( char *pStr )
{
    int len = strlen( pStr );
    int i = 0;
    for( i = 0; i < len; i++ )
    {
        pStr[i] = ( pStr[i] + 16 ) * 2 / 3;
        if( '\0' == pStr[i] )
        {
            pStr[i] = 1;
        }
    }
//    qDebug() << pStr;
}

