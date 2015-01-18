#include "sendmessagesdialog.h"
#include "ui_sendmessagesdialog.h"
//#include "init.h"
#include "walletmodel.h"
//#include "messagemodel.h"
#include "addressbookpage.h"
#include "optionsmodel.h"
//#include "sendmessagesentry.h"
//#include "guiutil.h"

#include <QMessageBox>
#include <QLocale>
#include <QTextDocument>
#include <QScrollBar>
#include <QClipboard>
#include <QDataWidgetMapper>

SendMessagesDialog::SendMessagesDialog( QWidget *parent) :
    QDialog(parent)

{

    ui->setupUi(this);
    //connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));

}



SendMessagesDialog::~SendMessagesDialog()
{
   // delete ui;
}
