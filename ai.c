/*  2006-12-31 机器落子算法     ....................................完成

    算法描述：

   算法描述：

    遍历整个棋盘，找出所有空白点，在每个空白点判断与该点相邻的4个方向上各方连续
    的棋子数，在每一个方向上,白子，即电脑连续的棋子总数为counter2；黑子，即人连
    续的棋子总数为counter1，黑子3连(counter1=3)加权20;白子3连(counter2=3)加权10;
    黑子4连(counter1=4)加权100;白子4个相连(counter2=4)加权70.设置side变量,用来纪
    录棋子两边的阻碍数.纪录(counter1+counter2)*5-side为该点在一个方向上的权值，
    然后在遍历整个棋盘空白点，计算出每个空格点4个方向上权值的总和,返回权值最大的
    点的坐标（这里用全局变量dx，dy表示）,该点就是计算机落子点
*/
#include"math.h"
#include"stdio.h"
#include"conio.h"
#include"graphics.h"
#include"dos.h"
#include"process.h"
#include"bios.h"


/**********************************人工智能部分********************************/

int bkmap[21][21]={0};
int computer[21][21][4]={0};     /*1右 2上 3右上 4右下*/

int dx;                        /* 权值最大点的坐标*/
int dy;


/*判断左右方向上己方连续的棋数*/
int rightcount(int i,int j)
{
    int counter1=0,counter2=0;
    int side=0;
    int j1=j;
    while(bkmap[i][j1+1]==16&&j1<21)    /*向右检查白色棋子*/
    {
        j1++;
        counter1++;
    }

    j1=j;
    while(bkmap[i][j1+1]==1&&j1<21)    /*向右检查黑色对方棋子*/
    {
        j1++;
        counter2++;
    }
    if(bkmap[i][j1]==16||j1==21)
    {
        side++;             /*判断右侧是否有白子或已到边界*/
    }

    j1=j;
    while(bkmap[i][j1-1]==16&&j1>=0)    /*向左检查白色棋子*/
    {
        j1--;
        counter1++;
    }

    j1=j;
    while(bkmap[i][j1-1]==1&&j1>=0)    /*向左检查黑色对方棋子*/
    {
        j1--;
        counter2++;
    }

    if(bkmap[i][j1]==16||j1<0)
    {
        side++;             /*判断左侧是否有黑子或已到边界*/
    }

    if(counter1==3) counter1+=40;/*如果白色有三个相连，加权40*/
    if(counter2==3) counter2+=25;/*如果黑色有三个相连，加权25*/

    if(counter1==4) counter1+=100;/*如果白色有4个相连，加权100*/
    if(counter2==4) counter2+=70;/*如果黑色有4个相连，加权70*/
    return (counter1+counter2)*5-side;
}

/*判断上下方向上己方连续的棋数*/
int upcount(int i,int j)
{
    int counter1=0,counter2=0;
    int i1=i;
    int side=0;
    while(bkmap[i1+1][j]==16&&i1<21)    /*向上检查白色棋子*/
    {
        i1++;
        counter1++;
    }

    i1=i;
    while(bkmap[i1+1][j]==1&&i1<21)    /*向上检查黑色对方棋子*/
    {
        i1++;
        counter2++;
    }

    if(bkmap[i1][j]==16||i1==21)
    {
        side++;             /*判断上侧是否有白子或已到边界*/
    }

    i1=i;
    while(bkmap[i1-1][j]==16&&i1>=0)    /*向下检查白色棋子*/
    {
        i1--;
        counter1++;
    }

    i1=i;
    while(bkmap[i1-1][j]==1&&i1>=0)    /*向下检查black棋子*/
    {
        i1--;
        counter2++;
    }

    if(bkmap[i1][j]==16||i1<0)
    {
        side++;             /*判断下侧是否有黑子或已到边界*/
    }

    if(counter1==3) counter1+=40;/*如果白色有三个相连，加权40*/
    if(counter2==3) counter2+=25;/*如果黑色有三个相连，加权25*/

    if(counter1==4) counter1+=100;/*如果白色有4个相连，加权100*/
    if(counter2==4) counter2+=70;/*如果黑色有4个相连，加权70*/

    return (counter1+counter2)*5-side;
}

/*判断右上方向上己方连续的棋数*/
int rupcount(i,j)
{
    int counter1=0,counter2=0;
    int i1=i,j1=j;
    int side=0;

    while(bkmap[i1+1][j1+1]==16&&i1<21&&j1<21)    /*向右上检查白色棋子*/
    {
        i1++;
        j1++;
        counter1++;
    }

    i1=i;
    j1=j;
    while(bkmap[i1+1][j1+1]==1&&i1<21&&j1<21)    /*向右上检查black棋子*/
    {
        i1++;
        j1++;
        counter2++;
    }

    if(bkmap[i1][j1]==16||i1==21||j1==21)
    {
        side++;             /*判断右上侧是否有黑子或已到边界*/
    }

    i1=i;
    j1=j;
    while(bkmap[i1-1][j1-1]==16&&i1>=0&&j1>=0)    /*向左下检查白色棋子*/
    {
        i1--;
        j1--;
        counter1++;
    }

    i1=i;
    j1=j;
    while(bkmap[i1-1][j1-1]==1&&i1>=0&&j1>=0)    /*向左下检查black棋子*/
    {
        i1--;
        j1--;
        counter2++;
    }

    if(bkmap[i1][j1]==16||i1<0||j1<0)
    {
        side++;             /*判断左下侧是否有黑子或已到边界*/
    }

    if(counter1==3) counter1+=40;/*如果白色有三个相连，加权40*/
    if(counter2==3) counter2+=25;/*如果黑色有三个相连，加权25*/

    if(counter1==4) counter1+=100;/*如果白色有4个相连，加权100*/
    if(counter2==4) counter2+=70;/*如果黑色有4个相连，加权70*/

    return (counter1+counter2)*5-side;
}

/*判断右下方向上己方连续的棋数*/
int rdowncount(i,j)
{
    int counter1=0,counter2=0;
    int i1=i,j1=j;
    int side=0;

    while(bkmap[i1-1][j1+1]==16&&i1>=0&&j1<21)    /*向左上检查白色棋子*/
    {
        i1--;
        j1++;
        counter1++;
    }

    i1=i;
    j1=j;
    while(bkmap[i1-1][j1+1]==1&&i1>=0&&j1<21)    /*向左上检查black棋子*/
    {
        i1--;
        j1++;
        counter2++;
    }

    if(bkmap[i1-1][j1+1]==16||i1<0||j1==21)
    {
        side++;             /*判断左上侧是否有黑子或已到边界*/
    }

    i1=i;
    j1=j;
    while(bkmap[i1+1][j1-1]==16&&i1<21&&j1>=0)    /*向右下检查白色棋子*/
    {
        i1++;
        j1--;
        counter1++;
    }

    i1=i;
    j1=j;
    while(bkmap[i1+1][j1-1]==1&&i1<21&&j1>=0)    /*向右下检查black棋子*/
    {
        i1++;
        j1--;
        counter2++;
    }

    if(bkmap[i1+1][j1-1]==16||i1==21||j1<0)
    {
        side++;             /*判断右下侧是否有黑子或已到边界*/
    }

    if(counter1==3) counter1+=40;/*如果白色有三个相连，加权40*/
    if(counter2==3) counter2+=25;/*如果黑色有三个相连，加权25*/

    if(counter1==4) counter1+=100;/*如果白色有4个相连，加权100*/
    if(counter2==4) counter2+=70;/*如果黑色有4个相连，加权70*/

    return (counter1+counter2)*5-side;
}

void machine()        /*电脑是白棋，2*/
{
    int i=0,j=0,k=0;
    int info;  /*每个空格点的权值*/
    int temp=0;
    int computer[21][21][4]={0};
    for(i=0;i<21;i++)       /*扫描棋盘*/
    {
        for(j=0;j<21;j++)
        {
            if(bkmap[i][j]==0)     /*所有空格点*/
            {
            /*左右方向上*/
                computer[i][j][0]=rightcount(i,j);

            /*上下方向上*/
                computer[i][j][1]=upcount(i,j);

            /*右上方向上*/
                computer[i][j][2]=rupcount(i,j);

            /*右下方向上*/
                computer[i][j][3]=rdowncount(i,j);

                info=0;
                for(k=0;k<4;k++)
                {
                    info+=computer[i][j][k];          /*4个方向权值相加*/
                }

                if(info>=temp)                         /*找出权值最大点*/
                {

                    dx=i;dy=j;
                    temp=info;
                }
            }
        }
    }
}

/*测试使用
main()
{
    machine();
    printf("%d     %d",point.dx,point.dy);
    getch();
} */
