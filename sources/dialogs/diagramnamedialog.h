#ifndef DIAGRAMNAMEDIALOG_H
#define DIAGRAMNAMEDIALOG_H

#include "../imagearea.h"

#include <QDialog>
#include <QTextEdit>

class DiagramNameDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     *
     * @param parent Pointer for parent.
     */
    explicit DiagramNameDialog(QString text, ImageArea *parent);
   
private:
    void initializeGui();
    QTextEdit *mTextEdit;
  
signals:
    void textChanged(ImageArea *, const QString);

private slots:
    void textChanged();
    void selectFont();
};

#endif // DIAGRAMNAMEDIALOG_H
