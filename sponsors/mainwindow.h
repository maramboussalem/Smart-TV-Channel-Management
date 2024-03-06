#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "sponsors.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_ajouter_clicked();

    void on_pushButton_2_clicked();

    void on_deleteBut_clicked();

    void on_modifyButton_clicked();

    void on_showButton_clicked();


    void on_Reset_clicked();

    void on_Reset_2_clicked();



    void on_ranking_clicked();

private:
    Ui::MainWindow *ui;
    Sponsors S;
};
#endif // MAINWINDOW_H
