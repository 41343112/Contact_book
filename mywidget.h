#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

QT_BEGIN_NAMESPACE
namespace Ui {
class myWidget;
}
QT_END_NAMESPACE

class myWidget : public QWidget
{
    Q_OBJECT

public:
    myWidget(QWidget *parent = nullptr);
    ~myWidget();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::myWidget *ui;
    QString currentFilename;  // Track the currently loaded/imported filename
    void animateRowInsertion(int row);
    void animateWindowFadeIn();
};
#endif // MYWIDGET_H
