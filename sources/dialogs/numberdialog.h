#ifndef NUMBERDIALOG_H
#define NUMBERDIALOG_H

#include "../imagearea.h"

#include <QDialog>
#include <qspinbox.h>

class NumberDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     *
     * @param parent Pointer for parent.
     */
    explicit NumberDialog(QString text, ImageArea *parent, QString title);
   
private:
    void initializeGui();
    QSpinBox *mySpinBox;
  
signals:
    void valueChanged(ImageArea *, const int);

private slots:
    void valueChanged();
    void selectFont();
};

#endif // NUMBERDIALOG_H
