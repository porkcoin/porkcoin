#include "porkmarket.h"
#include "ui_porkmarket.h"

#include "walletmodel.h"
#include "bitcoinunits.h"
#include "optionsmodel.h"
#include "transactiontablemodel.h"
#include "transactionfilterproxy.h"
#include "guiutil.h"
#include "guiconstants.h"
#include "askpassphrasedialog.h"
#include "net.h"
#include <QAbstractItemDelegate>
#include <QPainter>
#include <QLabel>
#include <QFileDialog>
#include <QBuffer>

PorkMarket::PorkMarket(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PorkMarket)
{
    ui->setupUi(this);

 /*   QPixmap pixmap;
    pixmap.load(":/images/res/images/1.png");
    ui->label->setPixmap(pixmap);

    QPixmap pixmap1;
    pixmap1.load(":/images/res/images/2.png");
    ui->label_2->setPixmap(pixmap1);
*/

 //layout = new QVBoxLayout(ui->scrollAreaWidgetContents);


//    // Recent transactions
//    ui->listTransactions->setItemDelegate(txdelegate);
//    ui->listTransactions->setIconSize(QSize(DECORATION_SIZE, DECORATION_SIZE));
//    ui->listTransactions->setMinimumHeight(NUM_ITEMS * (DECORATION_SIZE + 2));
//    ui->listTransactions->setAttribute(Qt::WA_MacShowFocusRect, false);

//    connect(ui->listTransactions, SIGNAL(clicked(QModelIndex)), this, SLOT(handleTransactionClicked(QModelIndex)));

//    // init "out of sync" warning labels
//    ui->labelWalletStatus->setText("(" + tr("out of sync") + ")");
//    ui->labelTransactionsStatus->setText("(" + tr("out of sync") + ")");

//    QPixmap pixmap;
//     pixmap.load(":/images/splash");
// //   pixmap.scaled(400,600);
// //    QPalette   palette;
//      //  palette.drawPixmap(ui->frame_2->backgroundRole(),QBrush(pixmap));
//  //      ui->frame_2->setPalette(palette);
//      //  ui->frame->setMask(pixmap.mask());  //可以将图片中透明部分显示为透明的
//      //  ui->frame_2->setAutoFillBackground(true);
//       // ui->frame_2->show();

//     ui->label_7->setPixmap(pixmap);
//    // start with displaying the "out of sync" warnings
//    showOutOfSyncWarning(true);
}



PorkMarket::~PorkMarket()
{
    delete ui;
}

void PorkMarket::on_pushButton_clicked()
{
    QString str= ui->textEdit->toPlainText();
    QString img = QString(ba.toBase64());


    QImage  ima;
    ima.loadFromData(QByteArray::fromBase64(img.toLatin1()));
  //  ui->label_3->setPixmap(QPixmap::fromImage(ima));



    QString link = ui->lineEdit->text();
    QString mes= str + "|"+img;
           RelayMyMessage("test",mes.toStdString().c_str());
  // show_text(mes);
}

void PorkMarket::show_text(const QString &message)
{
 //   QString mes=QString::fromStdString(message);
    QStringList list = message.split("|",QString::SkipEmptyParts);

    QWidget* w = new QWidget();

    QVBoxLayout* vbl = new QVBoxLayout(w);
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    QLabel* lab_01 = new QLabel(current_date);
    vbl->addWidget(lab_01);


    QLabel* lab_02 = new QLabel("urrent_date");
    QImage  image;
    if(list.size()>1)
    image.loadFromData(QByteArray::fromBase64(list[1].toLatin1()));
    lab_02->setPixmap(QPixmap::fromImage(image));

    QLabel* lab_03 = new QLabel(list[0]);

    QHBoxLayout* Hbl = new QHBoxLayout(w);
    Hbl->addWidget(lab_02);
    Hbl->addWidget(lab_03);
    vbl->addLayout(Hbl);
    vbl->setSizeConstraint( QLayout::SetFixedSize );
    w->setLayout(vbl);

    QListWidgetItem* lwi = new QListWidgetItem;
    lwi->setSizeHint( w->sizeHint() );
    ui->listWidget->addItem(lwi);
    ui->listWidget->setItemWidget(lwi, w);
}

void PorkMarket::on_pushButton_2_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("打开图像"), ".", tr("图像文件(*.png)"));
    QImage  image;
    image.load(path);
    image=image.scaled(100,100,Qt::IgnoreAspectRatio,Qt::FastTransformation);

   // myPixma = QVariant(image);
    ui->label_2->setPixmap(QPixmap::fromImage(image));



    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");

  //  QString img = ;



  //  QByteArray ba = );

  //  QPixmap pixmap1;
 //   pixmap1.loadFromData(QByteArray::fromBase64(myPixma.toBase64()),"PNG");
   // u//->label_3->setPixmap(pixmap1);

}
