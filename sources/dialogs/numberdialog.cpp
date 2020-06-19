#include "numberdialog.h"
#include "../imagearea.h"
#include "../datasingleton.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFont>
#include <QFontDialog>
#include <QDialogButtonBox>
#include <QMessageBox>

NumberDialog::NumberDialog(QString text, ImageArea *parent, QString title) :
    QDialog(parent)
{
    initializeGui();
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    setWindowTitle(title);
}

void NumberDialog::initializeGui()
{
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QHBoxLayout *hBox = new QHBoxLayout();
    hBox->addWidget(buttonBox);
	mySpinBox = new QSpinBox();
	mySpinBox->setRange(91, 179);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(mySpinBox);
    mainLayout->addLayout(hBox);
    setLayout(mainLayout);
    connect(mySpinBox, SIGNAL(valueChanged(int)), this, SLOT(valueChanged()));
}

void NumberDialog::valueChanged()
{
    emit valueChanged(qobject_cast<ImageArea*>(this->parent()), mySpinBox->value());
}

void NumberDialog::selectFont()
{
    bool ok;
    QFont font = DataSingleton::Instance()->getTextFont();
    font = QFontDialog::getFont(&ok, font, this);
    if (ok)
    {
        DataSingleton::Instance()->setTextFont(font);
		valueChanged();
		mySpinBox->setFocus();
    }
}
