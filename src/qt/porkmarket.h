#ifndef PORKMARKET_H
#define PORKMARKET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QVariant>

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE


class QVBoxLayout;
namespace Ui {
    class PorkMarket;
}

/** Overview ("home") page widget */
class PorkMarket : public QWidget
{
    Q_OBJECT

public:
    explicit PorkMarket(QWidget *parent = 0);
    ~PorkMarket();

 //  void setModel(WalletModel *model);
   // void showOutOfSyncWarning(bool fShow);

public slots:
 //   void setBalance(qint64 balance, qint64 stake, qint64 unconfirmedBalance, qint64 immatureBalance);
 //   void setNumTransactions(int count);

    void show_text(const QString &message);
signals:
   // void transactionClicked(const QModelIndex &index);

private:
    Ui::PorkMarket *ui;
        QVBoxLayout *layout;
      QByteArray ba;
private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
};

#endif // OVERVIEWPAGE_H