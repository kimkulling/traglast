#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nodesinputdialog.h"

#include "project.h"

#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
, mQuit(nullptr)
, mProject( nullptr ) {
    ui->setupUi(this);
    connect( ui->actionNew_project, &QAction::triggered, this, &MainWindow::newProject );
    connect( ui->actionQuit, &QAction::triggered, this, &MainWindow::quit );
    connect( ui->actionGenerateNodes, &QAction::triggered, this, &MainWindow::generateNodes );
}

MainWindow::~MainWindow() {
    delete mQuit;
    delete ui;

    delete mProject;
}

void MainWindow::newProject() {
    qDebug() << "test";

    mProject = new Project("test");
}

void MainWindow::quit() {
    QMessageBox msgBox;
    msgBox.setText("Do you really want to quit?");
    //msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No );
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
    switch (ret) {
        case QMessageBox::Yes:
            QMainWindow::close();
            break;

        case QMessageBox::No:
            return;

        default:
            break;
    }
}

void MainWindow::generateNodes() {
    NodesInputDialog *dlg = new NodesInputDialog(this);
    dlg->exec();
}
