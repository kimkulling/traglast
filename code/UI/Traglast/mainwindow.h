#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Project;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr );
    ~MainWindow();

public slots:
    void newProject();
    void quit();
    void generateNodes();

private:
    Ui::MainWindow *ui;
    QAction *mQuit;
    Project *mProject;
};

#endif // MAINWINDOW_H
