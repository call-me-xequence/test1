#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDir"
#include "QStringList"
#include "QDateTime"
struct FILEINFO
{
QString strFileName;
qint64 iModifTime;
bool operator==( const FILEINFO & other ) const
#ifdef Q_OS_WIN
     { return ( strFileName.compare( other.strFileName, Qt::CaseInsensitive ) == 0 ); }
#else
     { return ( strFileName.compare( other.strFileName, Qt::CaseSensitive ) == 0 ); }
#endif
};

bool getFileList( const QString & strDirName, QList<FILEINFO> & fileInfoList )
{



fileInfoList.clear();



  QDir dir( strDirName );
  QFileInfoList entryList = dir.entryInfoList( QDir::Files );
  for ( const QFileInfo & fi : entryList )
    {
    FILEINFO finf;

    QDateTime dtm = fi.fileTime( QFileDevice::FileModificationTime );

    finf.strFileName = fi.fileName();
    finf.iModifTime = dtm.toSecsSinceEpoch();
    fileInfoList << finf;
    }


return true;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString strDir ("C:/Users/RM525-DENIS/Desktop");
    QString strDir1 ("C:/Qt");
    QDir Dir (strDir);
    QStringList list = Dir.entryList(QDir::AllDirs);
    QList <FILEINFO> fileList;

    if (!getFileList(strDir1, fileList)){
        ui->textEdit->append(strDir1);
    }
    else{
    for(int i =0; i < fileList.size(); i++){
        ui->textEdit->append(fileList[i].strFileName);
    }
    }

}

