#ifndef SENDMESSAGESDIALOG_H
#define SENDMESSAGESDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
    class SendMessagesDialog;
}



//QT_BEGIN_NAMESPACE
//class QUrl;
//QT_END_NAMESPACE

/** Dialog for sending messages */
class SendMessagesDialog : public QDialog
{
    Q_OBJECT

public:


    explicit SendMessagesDialog( QWidget *parent = 0);
    ~SendMessagesDialog();


private:
    Ui::SendMessagesDialog *ui;

};

#endif // SENDMESSAGESDIALOG_H
