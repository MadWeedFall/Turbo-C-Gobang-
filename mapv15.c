/*2006-4-6 17:00 begin to work*/

#include"math.h"
#include"stdio.h"
#include"conio.h"
#include"graphics.h"
#include"dos.h"
#include"process.h"
#include"dos.h"
#include"bios.h"
#include"data.c"
#include"ai.c"
#include"mouse.c"

#define up 72
#define down 80
#define left 75
#define right 77

void mySound();/*pc喇叭发声,一方胜利时的音乐*/
int notInOne(int x,int y);/*检测是否在当前位置已有棋子*/
void restart();/*重新开启游戏*/
int mylogo();/*画logo*/
void drawmat(char *mat,int matsize,int x,int y,int color);/*在屏幕上显示字符点阵*/
void load();/*读档*/
void save();/*存档*/
void menu();/*画菜单界面*/
void debuger();/*测试工具，将数据输出至屏幕，测试时使用*/
void xhairs(int a,int b);/*在屏幕上划十字形光标*/
void drawmap();/*在屏幕上画棋盘，我进入图形编程的第一步*/
void drawchessman(int x,int y,int color);/*在(x,y)画棋子*/
void winornot(int x,int y,int color);/*判断胜负*/
void drawhardcircle(int x,int y,int r,int color);/*因为tc最高支持800x640，画小圆的函数的自己写*/
void outword(int tx,int ty,char word[]);/*函数实现清除原有字符，向屏幕重新输出字符*/

struct d
{

 int x;
 int y;

};

typedef struct d dot;
dot dis;

int hassound=0;/*判断是否有声音*/
int hasfinished=0;

int path=20;/*定义每一格的长度*/
/*int bkmap[20][20];*/


main()
{
      int px,py; /*记录移动之前的坐标以实现重绘*/
      int mx,my,nx,ny,button;/*鼠标的新旧坐标，按键*/
      int conter=0;

      int device=DETECT;
      int mode=VGAHI;

      int choice;
      dis.x=240;
      dis.y=240;
      registerbgidriver(EGAVGA_driver);
      initgraph(&device,&mode,"");/*初始化图形模式*/
      InitMouse();

      choice=mylogo();
      key.i=0;
setbkcolor(BLACK);
cleardevice();
setcolor(YELLOW);

  drawmap();

while(1)
{
    key.i=0;/*将键盘按键复位*/
      /*xhairs(px,py);*/ /******2006-4-10 Debug******/
        px=dis.x;py=dis.y;
      xhairs(dis.x,dis.y);/*****2006-4-8 15:20 the cursor is done******/


    NewMouse(&mx,&my,&button);/*产生新的鼠标，中断获得新坐标值,并判断键盘是否按键，获得按键值*/
        int86(0x33,& regs,& regs);
        regs.x.ax=3;
        nx=regs.x.cx;
        ny=regs.x.dx;


    if(nx>=460&&nx<=540&&ny>=140&&ny<=150&&button==1)
    {
        closegraph();
        exit(0);
    }
    if(nx>=460&&nx<=540&&ny>=180&&ny<=190&&button==1)
    {
         save();
         outword(320,460,"SAVED");
         key.i=0;

    }

    if(nx>=460&&nx<=540&&ny>=200&&ny<=210&&button==1)
    {
       load();
       outword(320,460,"LOADED");
       key.i=0;

    }
    if(nx>=460&&nx<=540&&ny>=220&&ny<=230&&button==1)
    {
        restart();
        key.i=0;
    }

    if((mx>nx-10) && (mx<nx+10) && (my>ny-10) && (my<ny+10) && button==1&&(mx<=420 )&&(my<=420))
    {
        dis.x=((nx+10)/20)*20;dis.y= ((ny+10)/20)*20;

        if((conter+1)%2&&notInOne(dis.x,dis.y)&&!hasfinished)
        {
            drawchessman(dis.x,dis.y, BLACK);
            drawhardcircle(590,260,path/3+2,BLACK);
            winornot(dis.x,dis.y,BLACK);
            conter++;
        }
        else if(notInOne(dis.x,dis.y)&&choice==2&&!hasfinished)
        {
            drawchessman(dis.x,dis.y,WHITE);
            drawhardcircle(590,260,path/3+2,WHITE);
            winornot(dis.x,dis.y,WHITE);
            conter++;
        }
    }

    if(hassound)
    {
        sound(1000);
        delay(1000000);
        nosound();
    }


    if(!key.c[0])
    {
        switch (key.c[1])
        {
            case up:    if(dis.y>20)
                        {
                           dis.y-=path;break; /*2006-4-8 debug*/
                        }
                        else break;

            case down:  if(dis.y<420)
                        {
                            dis.y+=path;break;
                        }
                        else break;

            case left:  if(dis.x>20)
                        {
                            dis.x-=path;break;
                        }
                        else break;

            case right: if(dis.x<420)
                        {
                            dis.x+=path; break;
                        }
                        else break;

        }
    }
    else
    {
        switch(tolower(key.c[0]))

       {     case 'z':   if((conter+1)%2&&notInOne(dis.x,dis.y)&&!hasfinished)
                            {
                                drawchessman(dis.x,dis.y, BLACK);
                                drawhardcircle(590,260,path/3+2,BLACK);
                                winornot(dis.x,dis.y,BLACK);
                                conter++;
                                break;
                            }
                        else if(notInOne(dis.x,dis.y)&&choice==2&&!hasfinished)
                        {
                            drawchessman(dis.x,dis.y,WHITE);
                            drawhardcircle(590,260,path/3+2,WHITE);
                            winornot(dis.x,dis.y,WHITE);
                            conter++;
                            break;
                        }
                        else break;
            case 's':
                    save();
                    outword(320,460,"SAVED");break;

            case 'l': load();
                    outword(320,460,"LOADED");break;

            case 'r': restart();

            case 'q':
                    closegraph();
                    exit(0);

            case 'd': debuger();break; /*to make the method winornot()*/
        }
        xhairs(px,py);
    }
    if((conter+1)%2==0&&choice==1&&!hasfinished)
    {
        machine();
        drawchessman((dy+1)*20,(dx+1)*20,WHITE);
        drawhardcircle(590,260,path/3+2,WHITE);
        winornot((dy+1)*20,(dx+1)*20,WHITE);
        conter++;
    }
    xhairs(px,py); /*clear the fomer cursor*/

}

/*printf("%d,%d\n",dis.x,dis.y);
getch();*/  /*use to debug*/

closegraph();
  exit(0);

}



/*
  foncution:draw a map
  interface:void
*/
void drawmap(void)
{
int x,y;
    for(x=0;x<=440;x++) line(0,x,440,x);
    for(y=0;y<=440;y++) line(y,0,y,440);

    setcolor(BLACK);

    for(x=0;x<=440;x+=path) line(0,x,440,x);
    for(y=0;y<=440;y+=path) line(y,0,y,440);
    setcolor(YELLOW);
    line(0,450,680,450);
    line(450,0,450,450);
    moveto(0,460);
    settextstyle(GOTHIC_FONT,0,6);
    outtext("M E S S A G:");
    moveto(460,40);
    outtext("\30 : UP");
    moveto(460,60);
    outtext("\31 : DOWN");
    moveto(460,80);
    outtext("\32 : LEFT");
    moveto(460,100);
    outtext("\33 : RIGHT");
    moveto(460,120);
    outtext("Z : DROP THE CHESSMAN");
    moveto(460,140);
    outtext("Q : QUIT");
    moveto(460,180);
    outtext("S : SAVE");
    moveto(460,200);
    outtext("L : LOAD");
    moveto(460,220);
    outtext("R : RESTART");
    moveto(460,260);
    outtext("The last drop :");
    for(x=250;x<=270;x++) line(580,x,600,x);
    for(y=580;y<=600;y++) line(y,250,y,270);
    setcolor(RED);
    setlinestyle(SOLID_LINE,1,10);
    line(0,0,0,440);
    setlinestyle(SOLID_LINE,1,10);
    line(440,0,440,440);
    setlinestyle(SOLID_LINE,1,10);
    line(0,440,440,440);
}

/*
  founcution:draw a chessman
  interface:int x,y (show the position) int color (the color of the chessman)
*/

void drawchessman(int x,int y,int color)
{
    drawhardcircle(x,y,path/3+2,color);
    bkmap[y/path-1][x/path-1]=color+1;/*在这里棋盘数组赋值,黑1白2*/
}




/*
foncution:draw a curcor
interface:int a,b (the coordinates)
*/

void xhairs(int a,int b)
{
 int i;
 for(i=a-3;i<=a+3;i++)
  putpixel(i,b,YELLOW^getpixel(i,b));
 for(i=b-3;i<=b+3;i++)
  putpixel(a,i,YELLOW^getpixel(a,i));
}


/*
foncution:To tell who has won
interface:int x,y (the coordinates of the present chessman)
*/

void winornot(int x,int y,int color) /**********2006-4-11 I make it!!!!*******/
{
  int m;
  int n;
  int s;

 for(m=0;m<21;m++)
   {

    for(n=0;n<21;n++)
     {
       if((bkmap[m][n]==bkmap[m][n+1])&&(bkmap[m][n+1]==bkmap[m][n+2])&&(bkmap[m][n+2]==bkmap[m][n+3])&&(bkmap[m][n+3]==bkmap[m][n+4])&&(bkmap[m][n]!=0)&&n<=16)
        {
         outword(320,460,"Y O U   W I N ! ! !");
        if(hassound)
            for(s=0;s<5;s++)
            mySound();
            hasfinished=1;
            setwritemode(0);
            while(!kbhit())
            {
               drawchessman((n+1)*20,(m+1)*20,YELLOW);
               drawchessman((n+2)*20,(m+1)*20,YELLOW);
                drawchessman((n+3)*20,(m+1)*20,YELLOW);
                drawchessman((n+4)*20,(m+1)*20,YELLOW);
                drawchessman((n+5)*20,(m+1)*20,YELLOW);
                delay(5000);
                drawchessman((n+1)*20,(m+1)*20,color);
                drawchessman((n+2)*20,(m+1)*20,color);
                drawchessman((n+3)*20,(m+1)*20,color);
                drawchessman((n+4)*20,(m+1)*20,color);
                drawchessman((n+5)*20,(m+1)*20,color);
                delay(5000);
            }
        setwritemode(1);
        break;
        }
       else if((bkmap[m][n]==bkmap[m+1][n])&&(bkmap[m+1][n]==bkmap[m+2][n])&&(bkmap[m+2][n]==bkmap[m+3][n])&&(bkmap[m+3][n]==bkmap[m+4][n])&&(bkmap[m][n]!=0)&&m<=16)
        {
          outword(320,460,"A n o t h e r  o n e  l o s e !");
         if(hassound)
            for(s=0;s<5;s++)
            mySound();
            hasfinished=1;
            setwritemode(0);
            while(!kbhit())
            {
                drawchessman((n+1)*20,(m+1)*20,YELLOW);
                drawchessman((n+1)*20,(m+2)*20,YELLOW);
                drawchessman((n+1)*20,(m+3)*20,YELLOW);
                drawchessman((n+1)*20,(m+4)*20,YELLOW);
                drawchessman((n+1)*20,(m+5)*20,YELLOW);
                delay(5000);
                drawchessman((n+1)*20,(m+1)*20,color);
                drawchessman((n+1)*20,(m+2)*20,color);
                drawchessman((n+1)*20,(m+3)*20,color);
                drawchessman((n+1)*20,(m+4)*20,color);
                drawchessman((n+1)*20,(m+5)*20,color);
                delay(5000);
            }
        setwritemode(1);
         break;
        }
       else if((bkmap[m][n]==bkmap[m+1][n+1])&&(bkmap[m+1][n+1]==bkmap[m+2][n+2])&&(bkmap[m+2][n+2]==bkmap[m+3][n+3])&&(bkmap[m+3][n+3]==bkmap[m+4][n+4])&&(bkmap[m][n]!=0)&&m<=16&&n<=16)
        {
          outword(320,460,"W I N  N E R ! ! !");
         if(hassound)
            for(s=0;s<5;s++)
            mySound();
            hasfinished=1;
            setwritemode(0);
            while(!kbhit())
            {
                drawchessman((n+1)*20,(m+1)*20,YELLOW);
                drawchessman((n+2)*20,(m+2)*20,YELLOW);
                drawchessman((n+3)*20,(m+3)*20,YELLOW);
                drawchessman((n+4)*20,(m+4)*20,YELLOW);
                drawchessman((n+5)*20,(m+5)*20,YELLOW);
                delay(5000);
                drawchessman((n+1)*20,(m+1)*20,color);
                drawchessman((n+2)*20,(m+2)*20,color);
                drawchessman((n+3)*20,(m+3)*20,color);
                drawchessman((n+4)*20,(m+4)*20,color);
                drawchessman((n+5)*20,(m+5)*20,color);
                delay(5000);
            }
            setwritemode(1);
            break;
        }
       else if((bkmap[m][n]==bkmap[m+1][n-1])&&(bkmap[m+1][n-1]==bkmap[m+2][n-2])&&(bkmap[m+2][n-2]==bkmap[m+3][n-3])&&(bkmap[m+3][n-3]==bkmap[m+4][n-4])&&(bkmap[m][n]!=0)&&m<=16&&n>=4)
        {
          outword(320,460,"W I N  N E R ! ! !");
         if(hassound)
            for(s=0;s<5;s++)
            mySound();
            hasfinished=1;
            setwritemode(0);
            while(!kbhit())
            {
                drawchessman((n+1)*20,(m+1)*20,YELLOW);
                drawchessman((n)*20,(m+2)*20,YELLOW);
                drawchessman((n-1)*20,(m+3)*20,YELLOW);
                drawchessman((n-2)*20,(m+4)*20,YELLOW);
                drawchessman((n-3)*20,(m+5)*20,YELLOW);
                delay(5000);
                drawchessman((n+1)*20,(m+1)*20,color);
                drawchessman((n)*20,(m+2)*20,color);
                drawchessman((n-1)*20,(m+3)*20,color);
                drawchessman((n-2)*20,(m+4)*20,color);
                drawchessman((n-3)*20,(m+5)*20,color);
                delay(5000);
            }
            setwritemode(1);
         break;
        }
     }

    }

}
/*
foncution:debug
interface:void(global bkmap[][])
*/

void debuger()
{
int i;
int j;
for (i=0;i<21;i++)
 for (j=0;j<21;j++)
  {
  printf("%d",bkmap[i][j]);
  if(j==19) printf("\n");
  }
}
/*foncution:save();
 *interface:void;
 *usage:savefile;*/

void save()
{
    FILE *fp;
    int i,j;
         fp=fopen("save.sav","w+");
        for(i=0;i<21;i++)
            for(j=0;j<21;j++)
                {
                 if(bkmap[i][j]==0) fputc('0',fp);

                 else if(bkmap[i][j]==WHITE+1) fputc('1',fp);

                 else if(bkmap[i][j]==BLACK+1) fputc('4',fp);

                }

  fclose(fp);


}

/*foncution:load();
 *interface:void;
 *usage:load file and turn the resualt to screen;*/
void load()
{
    FILE *fp;
    int i,j;
    char temp;
    int counter;

    fp=fopen("save.sav","r+");
       for(i=0;i<21;i++)
            for(j=0;j<21;j++)
               {
                 temp=fgetc(fp);

                 if(temp!='0') counter++;
                 if(temp=='0') bkmap[i][j]=0;
                 if(temp=='1') bkmap[i][j]=WHITE+1;
                 if(temp=='4') bkmap[i][j]=BLACK+1;/*2006-4-12 finish!将文件中的数据转化为实际使用的数据*/
                }
    fclose(fp);
     for(i=0;i<21;i++)
            for(j=0;j<21;j++)
                 if(bkmap[i][j]!=0)
                    drawchessman(path*(j+1),path*(i+1),bkmap[i][j]-1);
    drawchessman(590,260,(counter%2)?BLACK:WHITE);
}

/*foncution:mylogo();
 *interface:void;
 *usage:draw a logo of mine.*/
int mylogo()
{
    int row=1,prow=2;
    int mx,my,nx,ny,button;
    int y=30;

    drawmat(Tan,64,340,190-y,GREEN);
    drawmat(wu,64,130,190-y,YELLOW);
    drawmat(zi,64,210,190-y,YELLOW);
    drawmat(qi,64,280,190-y,YELLOW);

    moveto(410,260-y);
    outtext("\3 v1.5 \3");
    moveto(140,280-y);
    outtext("\30\31 to select,'z' to affirm :");
    setcolor(YELLOW);
    moveto(180,300-y);
    outtext("1P vs COM");
    moveto(180,320-y);
    outtext("1P vs 2P");
    moveto(180,340-y);
    outtext("Sound");
    outword(240,340-y,"OFF");
    moveto(180,360-y);
    outtext("Quit");
    drawhardcircle(150,280+(row*20)-y,5,YELLOW);

    mora=1;/*保证在该街面上画箭头形光标*/

    while(1)
    {
        key.i=0;
        drawhardcircle(150,280+(prow*20)-y,5,BLACK);

        NewMouse(&mx,&my,&button);/*产生新的鼠标，中断获得新坐标值,并判断键盘是否按键，获得按键值*/
        int86(0x33,& regs,& regs);
        regs.x.ax=3;
        nx=regs.x.cx;
        ny=regs.x.dx;

        if(nx>=180&&nx<=240&&ny>=300-y&&ny<=320-y&&button==1)
        {
            mora=0;
            return 1;
        }
        if(nx>=180&&nx<=240&&ny>=320-y&&ny<=340-y&&button==1)
        {
            mora=0;
            return 2;
        }
        if(nx>=180&&nx<=240&&ny>=340-y&&ny<=360-y&&button==1)
        {
            hassound=!hassound;
            if(hassound)
            outword(240,340-y,"ON");
            else
            outword(240,340-y,"OFF");
        }
        if(nx>=180&&nx<=240&&ny>=360-y&&ny<=380-y&&button==1)
        {
            closegraph();
            exit(0);
        }

        if(!key.c[0])
            switch (key.c[1])
            {
                case up:
                        prow=row;
                        row=(row-1)%4!=0?(row-1)%4:4;
                        drawhardcircle(150,280+(row*20)-y,5,YELLOW);
                        break;

                case down:
                        prow=row;
                        row=(row+1)%4!=0?(row+1)%4:4;
                        drawhardcircle(150,280+(row*20)-y,5,YELLOW);
                        break;
                default:break;
            }
        else
            switch(key.c[0])
            {
                case 'z':
                        setwritemode(0);
                        if(row!=3&&row!=4)
                        {
                            mora=0;
                            return row;
                        }
                        if(row==4)/*选择quit*/
                        {
                            closegraph();
                            exit(0);
                        }
                        if(row==3)/*选择是否发声，默认off*/
                        {
                            hassound=!hassound;
                            if(hassound)
                            outword(240,340-y,"ON");
                            else
                            outword(240,340-y,"OFF");
                        }
                        break;
                case 'q':
                        closegraph();
                        exit(0);
                        break;
            }
    }
}

void drawmat(char *mat,int matsize,int x,int y,int color)
/*依次：字模指针、点阵大小、起始坐标(x,y)、颜色*/
{int i,j,k,n;
 n=(matsize-1)/8+1;
 for(j=0;j<matsize;j++)
  for(i=0;i<n;i++)
   for(k=0;k<8;k++)
    if(mat[j*n+i]&(0x80>>k))  /*测试为1的位则显示*/
     putpixel(x+i*8+k,y+j,color);
}

void restart()
{
    int i,j;

    cleardevice();

    for(i=0;i<21;i++)
        for(j=0;j<21;j++)
            {
                bkmap[i][j]=0;
            }
    hassound=0;
    hasfinished=0;/*结束标记复位*/
    main();

}
/*2006-4-9*/
int notInOne(int x,int y)
{
  if(bkmap[y/path-1][x/path-1]==0) return 1;
  else return 0;

}
/*2006-4-11*/
void mySound()
{
    int i;

    for(i=0;i<5;i++)
          {
            sound((i+1)*1000);
            delay(10000000);
            nosound();
            delay(10000000);
          }
}
/*2006-4-12*/
void drawhardcircle(int x,int y,int r,int color)
{
    int i,j;
    setcolor(color);

    for(i=0;i<=r;i++) line(x-sqrt(r*r-i*i),y+i,x+sqrt(r*r-i*i),y+i);
    for(i=0;i<=r;i++) line(x-sqrt(r*r-i*i),y-i,x+sqrt(r*r-i*i),y-i);
}
/*2006-12-26*/
void outword(int tx,int ty,char word[])
{
    int x,y;
    setcolor(BLACK);
    for(x=ty;x<=640;x++) line(tx,x,800,x);
    for(y=tx;y<=800;y++) line(y,ty,y,640);
    setcolor(YELLOW);
    moveto(tx,ty);
    outtext(word);
}

