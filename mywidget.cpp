#include "mywidget.h"
#include "ui_mywidget.h"

#include<QFile>
#include<QDebug>
#include<QTextStream>
#include<QFileDialog>

QString mFilename = "C:/Users/user/Desktop/1117/file.txt";

void Write(QString Filename, QString str){

    QFile mFile(Filename);

    if(!mFile.open(QFile::WriteOnly | QFile::Text)){
        qDebug()<<"could not open file for write";
        return;
    }

    QTextStream out(&mFile);
    out<<str;
    mFile.flush();
    mFile.close();
}

QString Read(QString Filename){
    QFile mFile(Filename);

    if(!mFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug()<<"could not open file for read";
        return "";
    }

    QTextStream in(&mFile);
    QString text = in.readAll();
    mFile.close();
    return text;
}
myWidget::myWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::myWidget)
    , currentFilename("")  // Initialize with empty filename
{
    ui->setupUi(this);

    QStringList ColTotle;
    ui->tableWidget->setColumnCount(4);
    ColTotle<<QStringLiteral("學號")<<QStringLiteral("班級")<<QStringLiteral("姓名")<<QStringLiteral("電話");
    ui->tableWidget->setHorizontalHeaderLabels(ColTotle);
}

myWidget::~myWidget()
{
    delete ui;
}

void myWidget::on_pushButton_2_clicked()
{
    QTableWidgetItem *inputRow1,*inputRow2,*inputRow3,*inputRow4;
    inputRow1 = new QTableWidgetItem(QString(ui->lineEdit->text()));
    inputRow2 = new QTableWidgetItem(QString(ui->lineEdit_2->text()));
    inputRow3 = new QTableWidgetItem(QString(ui->lineEdit_3->text()));
    inputRow4 = new QTableWidgetItem(QString(ui->lineEdit_4->text()));

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,inputRow1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,inputRow2);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,inputRow3);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,inputRow4);
    
    // Clear input fields after adding
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}


void myWidget::on_pushButton_clicked()
{
    QString filename;
    
    // If we have a current filename (from import), use it; otherwise show save dialog
    if(!currentFilename.isEmpty()){
        filename = currentFilename;
    } else {
        // Show save file dialog
        filename = QFileDialog::getSaveFileName(this,
            QStringLiteral("另存新檔"),
            mFilename,
            "Text Files (*.txt);;All Files (*)");
        
        // If user cancelled the dialog, return
        if(filename.isEmpty()){
            return;
        }
        
        // Store the filename for future use
        currentFilename = filename;
    }

    QString saveFile="";

    for(int i=0;i<ui->tableWidget->rowCount();i++){
        for(int j=0;j<ui->tableWidget->columnCount();j++){
            saveFile+=(j==0)?"":",";
            saveFile+=ui->tableWidget->item(i,j)->text();
        }
        saveFile+="\n";
    }
    Write(filename,saveFile);
}

void myWidget::on_pushButton_4_clicked()
{
    // Save data first using the same logic as export
    QString filename;
    
    // If we have a current filename (from import), use it; otherwise show save dialog
    if(!currentFilename.isEmpty()){
        filename = currentFilename;
    } else {
        // Show save file dialog
        filename = QFileDialog::getSaveFileName(this,
            QStringLiteral("另存新檔"),
            mFilename,
            "Text Files (*.txt);;All Files (*)");
        
        // If user cancelled the dialog, just close without saving
        if(filename.isEmpty()){
            close();
            return;
        }
    }
    
    QString saveFile="";
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        for(int j=0;j<ui->tableWidget->columnCount();j++){
            saveFile+=(j==0)?"":",";
            saveFile+=ui->tableWidget->item(i,j)->text();
        }
        saveFile+="\n";
    }
    Write(filename,saveFile);
    
    // Then close the application
    close();
}


void myWidget::on_pushButton_3_clicked()
{
    // Show open file dialog
    QString filename = QFileDialog::getOpenFileName(this,
        QStringLiteral("選擇匯入的檔案"),
        mFilename,
        "Text Files (*.txt);;All Files (*)");
    
    // If user cancelled the dialog, return
    if(filename.isEmpty()){
        return;
    }

    QString text = Read(filename);
    if(text.isEmpty()){
        qDebug()<<"No data to import or file is empty";
        return;
    }
    
    // Store the filename for future use
    currentFilename = filename;

    // Clear existing table data
    ui->tableWidget->setRowCount(0);

    // Split by lines
    QStringList lines = text.split("\n", Qt::SkipEmptyParts);

    for(const QString &line : lines){
        // Split by comma
        QStringList fields = line.split(",");

        if(fields.size() == 4){
            // Add a new row
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);

            // Set the data for each column
            for(int i = 0; i < 4; i++){
                QTableWidgetItem *item = new QTableWidgetItem(fields[i]);
                ui->tableWidget->setItem(row, i, item);
            }
        }
    }
}

