#include"graphics.h"
#include"stdlib.h"
#include"dos.h"

union k /*!!!!!!To get a key press!!!!!!*/
{

char c[2];
int i;

};
typedef  union k KEY;
KEY key;

union REGS regs;

int mora=0;

int InitMouse()/*初始化鼠标*/
{
    int retcode;
    regs.x.ax=0;
    int86(0x33,& regs,& regs);
    retcode=regs.x.ax;
    if(retcode==0)
        return 0;  /*没有正确安装，返回0*/
    regs.x.ax=7;
    regs.x.cx=10;
    regs.x.dx=610;
    int86(0x33,& regs,& regs);
    regs.x.ax=8;
    regs.x.cx=10;
    regs.x.dx=470;
    int86(0x33,& regs,& regs);
    return  retcode;
}

void DrawMouse(int mx,int my,int color)/*输出鼠标图象*/
{
    int i;
    int x,y;
    setlinestyle(0,0,1);
    setcolor(color);

    if(mx>420||my>420||mora==1)
    {

        line(mx,my,mx+5,my+20);
        line(mx+5,my+20,mx+20,my+20);
        line(mx+6,my+19,mx+18,my+19);
        line(mx+6,my+18,mx+17,my+18);
        for(i=0;i<15;i++)
            line(mx+5-i/4,my+17-i,mx+16-i,my+17-i);
        for(i=0;i<5;i++)
            line(mx+10+i,my+21,mx+15+i,my+27);
        setcolor(color);
        line(mx+1,my+1,mx+19,my+19);
        line(mx+16,my+21,mx+21,my+21);
        line(mx+16,my+22,mx+20,my+27);
        line(mx+16,my+28,mx+21,my+28);
    }
    else
    {
        x=((mx+10)/20)*20;
        y=((my+10)/20)*20;
        line(x-10,y+10,x+10,y+10);
        line(x-10,y-10,x+10,y-10);
        line(x-10,y-10,x-10,y+10);
        line(x+10,y-10,x+10,y+10);
    }
}


void NewMouse(int *x,int *y,int *buttons) /*读取鼠标，键盘，时间*/
{
    int oldx=*x,oldy=*y;
    int x1,y1;
    int newx,newy,mb;

    char str[5];
    setwritemode(1);
    do
    {
        int86(0x33,& regs,& regs);
        regs.x.ax=3;
        newx=regs.x.cx;
        newy=regs.x.dx;
        mb=regs.x.bx;

        if(kbhit())
        {
            key.i=bioskey(0);/******2006-4-6 20:22 find it,made it!*******/
            tolower(key.c[0]);
        }
    }while(newx==oldx && newy==oldy && mb==0&&key.i==0);
    *buttons=mb;
    DrawMouse(oldx,oldy,YELLOW);
    DrawMouse(newx,newy,YELLOW);
    *x=newx;
    *y=newy;
    setwritemode(0);
    if(mb==3)
    {
        closegraph();
        exit(0);
    }
}

int leftpressed()
{
    int b;
    int86(0x33,& regs,& regs);
    regs.x.ax=3;
    b=regs.x.bx;
    int86(0x33,& regs,& regs);
    regs.x.ax=3;
    b=regs.x.bx;
    printf("%d",b);
    if(b==1) return b;
    else return 0;
}





