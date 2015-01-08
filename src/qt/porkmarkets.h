#ifndef PORKMARKETS_H
#define PORKMARKETS_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

namespace Ui {
    class PorkMarkets;
}

/** Overview ("home") page widget */
class PorkMarkets : public QWidget
{
    Q_OBJECT

public:
    explicit PorkMarkets(QWidget *parent = 0);
    ~PorkMarkets();

 //  void setModel(WalletModel *model);
   // void showOutOfSyncWarning(bool fShow);

public slots:
 //   void setBalance(qint64 balance, qint64 stake, qint64 unconfirmedBalance, qint64 immatureBalance);
 //   void setNumTransactions(int count);

signals:
   // void transactionClicked(const QModelIndex &index);

private:
    Ui::PorkMarkets *ui;

private slots:
  //  void updateDisplayUnit();
  //  void handleTransactionClicked(const QModelIndex &index);
};

#endif // OVERVIEWPAGE_H
