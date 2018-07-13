#include "nodesinputdialog.h"

#include <QDebug>

NodesInputDialog::NodesInputDialog(QWidget *parent)
: QDialog(parent)
, mProject( nullptr ) {
    setupUi(this);
    setWindowTitle("Create new nodes...");
    connect( this->okButton, SIGNAL(clicked()), this, SLOT(checkValues()));
}

NodesInputDialog::~NodesInputDialog() {
    // empty
}

void setProject(Project *project );

void NodesInputDialog::checkValues() {
    QString x = this->xInput->text();
    QString y = this->yInput->text();

    qDebug() << x << y;
}
