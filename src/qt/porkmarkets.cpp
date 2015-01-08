#include "porkmarkets.h"
#include "ui_porkmarkets.h"

#include "walletmodel.h"
#include "bitcoinunits.h"
#include "optionsmodel.h"
#include "transactiontablemodel.h"
#include "transactionfilterproxy.h"
#include "guiutil.h"
#include "guiconstants.h"
#include "askpassphrasedialog.h"

#include <QAbstractItemDelegate>
#include <QPainter>



PorkMarkets::PorkMarkets(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PorkMarkets)
{
    ui->setupUi(this);

    QPixmap pixmap;
    pixmap.load(":/images/res/images/1.png");
    ui->label->setPixmap(pixmap);

    QPixmap pixmap1;
    pixmap1.load(":/images/res/images/2.png");
    ui->label_2->setPixmap(pixmap1);


    QPixmap pixmap2;
    pixmap2.load(":/images/res/images/3.png");
    ui->label_3->setPixmap(pixmap2);

    QPixmap pixmap3;
    pixmap3.load(":/images/res/images/4.png");
    ui->label_4->setPixmap(pixmap3);


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



PorkMarkets::~PorkMarkets()
{
    delete ui;
}

