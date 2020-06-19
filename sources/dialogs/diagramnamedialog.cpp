#include "diagramnamedialog.h"
#include "../imagearea.h"
#include "../datasingleton.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFont>
#include <QFontDialog>
#include <QDialogButtonBox>
#include <QMessageBox>

DiagramNameDialog::DiagramNameDialog(QString text, ImageArea *parent) :
    QDialog(parent)
{
    initializeGui();
    if (!text.isEmpty())
    {
        mTextEdit->setText(text);
        QTextCursor cursor(mTextEdit->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        mTextEdit->setTextCursor(cursor);
    }
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    setWindowTitle(tr("Diagram Name"));
}

void DiagramNameDialog::initializeGui()
{
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QHBoxLayout *hBox = new QHBoxLayout();
    hBox->addWidget(buttonBox);
    mTextEdit = new QTextEdit();
    mTextEdit->setLineWrapMode(QTextEdit::NoWrap);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(mTextEdit);
    mainLayout->addLayout(hBox);
    setLayout(mainLayout);
    connect(mTextEdit, SIGNAL(textChanged()), this, SLOT(textChanged()));
}

void DiagramNameDialog::textChanged()
{
    emit textChanged(qobject_cast<ImageArea*>(this->parent()), mTextEdit->toPlainText());
}

void DiagramNameDialog::selectFont()
{
    bool ok;
    QFont font = DataSingleton::Instance()->getTextFont();
    font = QFontDialog::getFont(&ok, font, this);
    if (ok)
    {
        DataSingleton::Instance()->setTextFont(font);
        textChanged();
        mTextEdit->setFocus();
    }
}
