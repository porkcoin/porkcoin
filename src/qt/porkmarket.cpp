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
#include <QMouseEvent>
#include <QTimer>
#include "net.h"
#include <QAbstractItemDelegate>
#include <QPainter>
#include <QLabel>
#include <QFileDialog>
#include <QBuffer>
#include "buydialog.h"
#include "renderarea.h"

PorkMarket::PorkMarket(QWidget *parent) :
    QWidget(parent)
{
    ph_list.clear();
    progressBar=new QProgressBar(this);
    startPushButton=new QPushButton("Start",this);
    PromptPushButton = new QPushButton("Prompt",this);
    resetPushButton = new QPushButton("Reset",this);

    startPushButton->move(40,480);
    PromptPushButton->move(110,480);
    resetPushButton->move(180,480);
     progressBar->move(260,480);

    counter=100;
    progressBar->setValue(counter);
    progressBar->setFixedWidth(420);
    connect(startPushButton, SIGNAL(clicked()), this, SLOT(on_startButton_clicked()));
    connect(PromptPushButton, SIGNAL(clicked()), this, SLOT(on_PromptButton_clicked()));
    connect(resetPushButton, SIGNAL(clicked()), this, SLOT(on_resetButton_clicked()));
    isRect = false;
    initData();

    isRect = false;isStart = false;
    clickCount = 0;

    this->LoadPic();
    this->savePictoMap();
}

void PorkMarket::on_startButton_clicked()
{
    if(!isStart)
    {
        isRect = false;

        counter=100;
        isRect = false;isStart = false;
        clickCount = 0;
        isStart = true;
        startNewGame();
     }
}

void PorkMarket::on_resetButton_clicked(void)
{
    QList<int> tlist;
    for(int i = 1; i < map_row - 1; i++)
    {
        for(int j = 1; j < map_col - 1; j++)
        {
           if(arr_map[i][j] != EMPTY)
            tlist.push_front(arr_map[i][j]);
        }
    }

    for(int i = 1; i < map_row - 1; i++)
    {
        for(int j = 1; j < map_col - 1; j++)
        {
            qsrand(time(NULL));
            int dex = qrand() % tlist.size();
            if(arr_map[i][j] != EMPTY)
            {
                arr_map[i][j] = tlist.at(dex);
                tlist.removeAt(dex);
            }
        }
    }
    update();
}

void PorkMarket::on_PromptButton_clicked()
{
    if(!isStart)
        return;

    for(int i = 1; i < map_row - 1; i++)
    {
        for(int j = 1; j < map_col - 1; j++)
        {
            for(int x = 1; x < map_row - 1; x++)
            {
                for(int y = 1; y < map_col - 1; y++)
                {
                    if(i == j&&x == y)
                    {
                        continue;
                    }

                    if(arr_map[i][x] == EMPTY)
                    {
                        continue;
                    }

                    if(arr_map[j][y] == EMPTY)
                    {
                        continue;
                    }


                    if(arr_map[i][x] != arr_map[j][y])
                    {
                         continue;
                    }

                    if(isWin(i,j,x,y))
                    {
                        rects.clear();
                        rects.push_back(QPoint(PHWIDTH * x,PHHEIGHT *i));
                        rects.push_back(QPoint(PHWIDTH * y,PHHEIGHT * j));

                        update();
                        QEventLoop loop;
                        QTimer::singleShot(300, &loop, SLOT(quit()));
                        loop.exec();

                        rects.clear();
                        lines.clear();
                        update();  return true;
                    }
                }
            }
        }
    }
}


void PorkMarket::updateProgressBar()
{
     if(counter > 0)
     {
        counter--;
        progressBar->setValue(counter);
     }
     else
     {
         isStart = false;
         timer->stop();
         delete timer;  //END CODE SNIPPET HERE

     }
}
void PorkMarket::initData()
{
    map_row = ROWCOUNT + 2;
    map_col = COLCOUNT + 2;

    //地图数组初始化
    for(int i = 0 ; i < map_row ; i++)
    {
        for(int j = 0 ; j < map_col ; j++)
        {
            arr_map[i][j] = EMPTY;
        }
    }
    sumCount = ROWCOUNT * COLCOUNT;
}

void PorkMarket::LoadPic()
{
   int count;
    count = 0;

    for(int i=0; i<IMAGESUM; i++)
    {
        QString phname = ":/pic/res/pic/"+QString::number(i,10)+".png";
        QPixmap pixmap(phname);
        ph_list.append(pixmap);

        for(int j=0 ; j<PERPH ; j++)
        {
            count ++ ;
            tmplist.append(i);
            if( count >= ROWxCOL )
                break;
        }

        if( count >= ROWxCOL )
            break;
    }

//    //qDebug()<<1;
}


//将图片随机存入地图数组
void PorkMarket::savePictoMap(void)
{
    int i,j;
    for(i = 1; i < map_row - 1; i++)
    {
        for(j = 1; j < map_col - 1; j++)
        {
           // qsrand(time(NULL));
            int dex = qrand() % tmplist.size();
            arr_map[i][j] = tmplist.at(dex);
            tmplist.removeAt(dex);
        }
    }
}

//根据地图数组将容器中对应图片画出来
void PorkMarket::DrawGameMap(QPainter *p)
{
    for(int i = 1; i < map_row - 1; i++)
    {
        for(int j = 1; j < map_col - 1; j++)
        {
            if(arr_map[i][j] == EMPTY)
            {
                continue;
            }

            p->drawPixmap(j*(PHWIDTH),i*(PHHEIGHT),PHWIDTH,PHHEIGHT,ph_list.at(arr_map[i][j]));
        }
    }

    QPen pen(Qt::red);
    if(isRect)
    {

        pen.setStyle(Qt::SolidLine);
        pen.setWidth(2);
        p->setPen(pen);
        for(int i=0;i<rects.size();i++)
        {
        p->drawRect(rects[i].x(),rects[i].y(),PHWIDTH,PHHEIGHT);
        }
       }

    if(rects.size()==2 )
    {
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(2);
        p->setPen(pen);
        p->drawLines(lines);
    }


    if(sumCount == 0)
    {
        counter=100;
        isStart = false;

        p->setPen(QColor(Qt::red));
        p->drawText(224,192,100,100,NULL,tr("You Win!"));
    }

    return;
}

void PorkMarket::paintEvent(QPaintEvent *)
{
    //窗口事件
    QPainter p(this);

 //   if(isDrawPic)
   DrawGameMap(&p);

    p.end();
}

void PorkMarket::startNewGame()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateProgressBar()));
    timer->start(2000);
    updateProgressBar();
    this->update();
}


void PorkMarket::mousePressEvent(QMouseEvent *e)
{
    if(!isStart )return;
    int x,y;
    y = (e->x() / PHWIDTH);
    x = (e->y() / PHHEIGHT);

    if(arr_map[x][y] == EMPTY)
    {
        rects.clear();
        return;
    }
    else
    {

        isRect = true;
        clickCount++;
        if(clickCount == 1)
        {
            clickX0 = x;
            clickY0 = y;
            rects.clear();
            rects.push_back(QPoint(PHWIDTH * clickY0,PHHEIGHT * clickX0));
            update();
            return;
        }

        if(clickCount == 2)
        {
            clickX1 = x;
            clickY1 = y;

            clickCount = 0;
            isRect = true;

            if(clickX0 == clickX1 && clickY0 == clickY1)
            {
                rects.clear();
                rects.push_back(QPoint(PHWIDTH * clickY1,PHHEIGHT * clickX1));

                update();
                return;
            }
            if(arr_map[clickX0][clickY0] != arr_map[clickX1][clickY1])
            {
                rects.clear();
                rects.push_back(QPoint(PHWIDTH * clickY1,PHHEIGHT * clickX1));
                update();
                return;
            }


            if(this->isWin(clickX0,clickX1,clickY0,clickY1))
            {
                counter++;progressBar->setValue(counter);
                rects.clear();
                rects.push_back(QPoint(PHWIDTH * clickY0,PHHEIGHT * clickX0));
                rects.push_back(QPoint(PHWIDTH * clickY1,PHHEIGHT * clickX1));
                sumCount--;
                update();
                QEventLoop loop;
                QTimer::singleShot(500, &loop, SLOT(quit()));
                loop.exec();
                arr_map[clickX0][clickY0] = EMPTY;
                arr_map[clickX1][clickY1] = EMPTY;
                rects.clear();
                lines.clear();
                update();
                return;
            }
        }
    }

    update();
}

bool PorkMarket::isWin(int x0,int x1,int y0, int y1)
{
    lines.clear();
    bool ret;
    if(x0 == x1)
    {
        ret = oneHLine(x0,y0,y1);
        if(ret)
        {
          //  drawLine(x0,y0,x0,y1);
            return true;
        }
    }

    lines.clear();

    if(y0 == y1)
    {
        ret = oneVLine(y0,x0,x1);
        if(ret)
        {
           // drawLine(x0,y0,x1,y0);
            return true;
        }
    }

    lines.clear();
    if(x0 != x1 && y0 != y1)
    {
        ret = twoLine(x0,x1,y0,y1);
        if(ret)
            return true;
    }

    lines.clear();
    ret = threeLine(x0,x1,y0,y1);
    if(ret)
        return true;

    return false;
}

bool PorkMarket::oneHLine(int x,int y0, int y1)
{
    int i;

    if(abs(y0 - y1) == 1)
    {
        drawLine(x,y0,x,y1);
        return true;

    }else if(y0 > y1)
    {
        for(i = 0; i < y0 - y1 - 1; i++)
        {
            if(arr_map[x][y1 + i + 1] != EMPTY)
            {
                return false;
            }

        }

         drawLine(x,y0,x,y1);
        return true;

    }else
    {
        for(i = 0; i < y1 - y0 - 1; i++)
        {
            if(arr_map[x][y0 + i + 1] != EMPTY)
            {
                return false;
            }

        }

         drawLine(x,y0,x,y1);
        return true;
    }

    return false;
}

bool PorkMarket::oneVLine(int y, int x0, int x1)
{
    int i;

    if(abs(x0 - x1) == 1)
    {
       drawLine(x0,y,x1,y);
        return true;

    }else if(x0 > x1)
    {
        for(i = 0; i < x0 - x1 - 1; i++)
        {
            if(arr_map[x1 + i + 1][y] != EMPTY)
            {
                return false;
            }

        }
         drawLine(x0,y,x1,y);
        return true;

    }else
    {
        for(i = 0; i < x1 - x0 - 1; i++)
        {
            if(arr_map[x0 + i + 1][y] != EMPTY)
            {
                return false;
            }

        }
  drawLine(x0,y,x1,y);
        return true;
    }

    return false;
}

bool PorkMarket::twoLine(int x0, int x1, int y0, int y1,bool ret)
{

    if(arr_map[x0][y1] == EMPTY && oneHLine(x0,y0,y1) && oneVLine(y1,x0,x1))
    {
     // drawLine(x0,y1,x1,y1);
        return true;
    }


    if(!ret)
        lines.clear();

    if(arr_map[x1][y0] == EMPTY && oneVLine(y0,x0,x1) && oneHLine(x1,y0,y1))
    {
   //  drawLine(x1,y0,x1,y1);
        return true;
    }

    return false;
}

 #include <QSet>
uint qHash(const QPoint key)
{
    return key.x()*10+ key.y();
}
bool PorkMarket::threeLine(int x0, int x1, int y0, int y1)
{
    int i;
    bool ret;

    //横向扫描
    for(i = 0; i < map_col; i++)
    {
         lines.clear();
        if(i == y0 || arr_map[x0][i] != EMPTY)
         continue;
        ret = oneHLine(x0,y0,i);
        if(ret)
        {
            ret = twoLine(x0,x1,i,y1,ret);
            if(ret)
            {
                QSet<QPoint> s;
                for(int i=0;i<lines.size();i++)
                {
                    QLine line=lines[i];
                  //  line.p1();
                    s.insert(line.p1());
                    s.insert(line.p2());
                }

                if(s.size()==5)
                {
                    printf("%d",s.size());
                    lines.removeAt(1);

                }

                return true;
            }
        }
    }
 lines.clear();
    //纵向扫描
    for(i = 0; i < map_row; i++)
    { lines.clear();
        if(i == x0 || arr_map[i][y0] != EMPTY)
         continue;
        ret = oneVLine(y0,x0,i);
        if(ret)
        {
            ret = twoLine(i,x1,y0,y1,ret);
            if(ret)
            {

                //  drawLine(i,y0,i,y1);
               //  drawLine(x0,y0,x1,y0);
                // drawLine(i,y1,x1,y1);

                return true;
            }
        }
    }

    return false;
}

/* 在两个给定点之间画一条较粗的直线 */
void PorkMarket::drawLine(const int &aX, const int &aY,  const int &bX, const int &bY)
{
    int x1=aY*PHWIDTH+PHWIDTH/2;
    int y1=aX*PHWIDTH+PHWIDTH/2;
    int x2=bY*PHWIDTH+PHWIDTH/2;
    int y2=bX*PHWIDTH+PHWIDTH/2;

    QLine line(x1,y1,x2,y2);
    lines.append(line);
}
