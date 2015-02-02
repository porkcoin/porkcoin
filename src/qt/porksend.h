#ifndef PORKSEND_H
#define PORKSEND_H

#include <QWidget>
#include <QVBoxLayout>
#include <QVariant>
#include <QListWidget>
#include <QListWidgetItem>
#include <QProgressBar>
#include <QPushButton>
#include <QTimer>


#define IMAGESUM 24
#define PERPH 8
#define ROWCOUNT 10          //行数
#define COLCOUNT 16         //列数
#define ROWxCOL 160
#define EMPTY -1

//图片宽和高
#define PHWIDTH 40
#define PHHEIGHT 40
/** Overview ("home") page widget */
class PorkSendPage : public QWidget
{
    Q_OBJECT
public slots:void updateProgressBar();
public:
    explicit PorkSendPage(QWidget *parent = 0);
    ~PorkSendPage(){}

 //  void setModel(WalletModel *model){}
   void LoadPic(void);

   void savePictoMap(void);

   void DrawGameMap(QPainter *p);

   void startNewGame(void);

   void initData(void);

   bool isWin(int,int,int,int);
   bool oneHLine(int,int,int);
   bool oneVLine(int,int,int);
   bool twoLine(int,int,int,int,bool ret = false);
   bool threeLine(int,int,int,int);


   void drawLine(const int &aX, const int &aY, const int &bX, const int &bY);

protected:
   void paintEvent(QPaintEvent *);
   void mousePressEvent(QMouseEvent *event);
private slots:
    void on_startButton_clicked();
    void on_PromptButton_clicked();
    void on_resetButton_clicked();
private:
    QList<QPixmap> ph_list;
    QList<int> tmplist;
    int arr_map[ROWCOUNT+2][COLCOUNT+2];
    QVector<QLine> lines;
    QVector<QPoint> rects;

    QProgressBar *progressBar;
    QPushButton *startPushButton;
    QPushButton *PromptPushButton;
    QPushButton *resetPushButton;

    QTimer* timer;
    int  counter;
    //地图行、列数
    int map_row;
    int map_col;

    bool isRect;
    bool isStart;
    int clickCount; //click count

    int clickX0;
    int clickY0;
    int clickX1;
    int clickY1;

    int sumCount;
    void connectFri(QListWidgetItem * );
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
};



#endif // OVERVIEWPAGE_H
