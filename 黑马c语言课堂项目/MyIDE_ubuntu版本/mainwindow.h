#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void SayHello();
    void SaveFile(char* filename);
private slots:
    void on_actionUtf_8_triggered();

    void on_actionGbk_triggered();

    void on_actionOpen_triggered();

    void on_actionSava_as_triggered();

    void on_actionNew_triggered();

    void on_actionUndo_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionCompile_triggered();

    void on_actionExit_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
