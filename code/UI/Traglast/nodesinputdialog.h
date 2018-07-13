#ifndef NODESINPUTDIALOG_H
#define NODESINPUTDIALOG_H

#include "ui_nodesdialog.h"

#include <QDialog>

class Project;

class NodesInputDialog : public QDialog, private Ui::NodesInputDialog {
    Q_OBJECT

public:
    NodesInputDialog(QWidget *parent = nullptr);
    ~NodesInputDialog();
    void setProject(Project *project );

private slots:
    void checkValues();

private:
    Project *mProject;
};

#endif // NODESINPUTDIALOG_H
