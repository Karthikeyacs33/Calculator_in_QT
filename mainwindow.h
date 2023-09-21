#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;

private slots:
    void Numpressed();
    void mathbuttonpressed();
    //void resultbutton();
    void changesign();
    void clearpressed();

    void on_result_clicked();
    void on_backtocalc_clicked();
    void on_checkres_clicked();
    void on_bac2calc_clicked();
};
#endif // MAINWINDOW_H
