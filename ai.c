/*  2006-12-31 ���������㷨     ....................................���

    �㷨������

   �㷨������

    �����������̣��ҳ����пհ׵㣬��ÿ���հ׵��ж���õ����ڵ�4�������ϸ�������
    ������������ÿһ��������,���ӣ���������������������Ϊcounter2�����ӣ�������
    ������������Ϊcounter1������3��(counter1=3)��Ȩ20;����3��(counter2=3)��Ȩ10;
    ����4��(counter1=4)��Ȩ100;����4������(counter2=4)��Ȩ70.����side����,������
    ¼�������ߵ��谭��.��¼(counter1+counter2)*5-sideΪ�õ���һ�������ϵ�Ȩֵ��
    Ȼ���ڱ����������̿հ׵㣬�����ÿ���ո��4��������Ȩֵ���ܺ�,����Ȩֵ����
    ������꣨������ȫ�ֱ���dx��dy��ʾ��,�õ���Ǽ�������ӵ�
*/
#include"math.h"
#include"stdio.h"
#include"conio.h"
#include"graphics.h"
#include"dos.h"
#include"process.h"
#include"bios.h"


/**********************************�˹����ܲ���********************************/

int bkmap[21][21]={0};
int computer[21][21][4]={0};     /*1�� 2�� 3���� 4����*/

int dx;                        /* Ȩֵ���������*/
int dy;


/*�ж����ҷ����ϼ�������������*/
int rightcount(int i,int j)
{
    int counter1=0,counter2=0;
    int side=0;
    int j1=j;
    while(bkmap[i][j1+1]==16&&j1<21)    /*���Ҽ���ɫ����*/
    {
        j1++;
        counter1++;
    }

    j1=j;
    while(bkmap[i][j1+1]==1&&j1<21)    /*���Ҽ���ɫ�Է�����*/
    {
        j1++;
        counter2++;
    }
    if(bkmap[i][j1]==16||j1==21)
    {
        side++;             /*�ж��Ҳ��Ƿ��а��ӻ��ѵ��߽�*/
    }

    j1=j;
    while(bkmap[i][j1-1]==16&&j1>=0)    /*�������ɫ����*/
    {
        j1--;
        counter1++;
    }

    j1=j;
    while(bkmap[i][j1-1]==1&&j1>=0)    /*�������ɫ�Է�����*/
    {
        j1--;
        counter2++;
    }

    if(bkmap[i][j1]==16||j1<0)
    {
        side++;             /*�ж�����Ƿ��к��ӻ��ѵ��߽�*/
    }

    if(counter1==3) counter1+=40;/*�����ɫ��������������Ȩ40*/
    if(counter2==3) counter2+=25;/*�����ɫ��������������Ȩ25*/

    if(counter1==4) counter1+=100;/*�����ɫ��4����������Ȩ100*/
    if(counter2==4) counter2+=70;/*�����ɫ��4����������Ȩ70*/
    return (counter1+counter2)*5-side;
}

/*�ж����·����ϼ�������������*/
int upcount(int i,int j)
{
    int counter1=0,counter2=0;
    int i1=i;
    int side=0;
    while(bkmap[i1+1][j]==16&&i1<21)    /*���ϼ���ɫ����*/
    {
        i1++;
        counter1++;
    }

    i1=i;
    while(bkmap[i1+1][j]==1&&i1<21)    /*���ϼ���ɫ�Է�����*/
    {
        i1++;
        counter2++;
    }

    if(bkmap[i1][j]==16||i1==21)
    {
        side++;             /*�ж��ϲ��Ƿ��а��ӻ��ѵ��߽�*/
    }

    i1=i;
    while(bkmap[i1-1][j]==16&&i1>=0)    /*���¼���ɫ����*/
    {
        i1--;
        counter1++;
    }

    i1=i;
    while(bkmap[i1-1][j]==1&&i1>=0)    /*���¼��black����*/
    {
        i1--;
        counter2++;
    }

    if(bkmap[i1][j]==16||i1<0)
    {
        side++;             /*�ж��²��Ƿ��к��ӻ��ѵ��߽�*/
    }

    if(counter1==3) counter1+=40;/*�����ɫ��������������Ȩ40*/
    if(counter2==3) counter2+=25;/*�����ɫ��������������Ȩ25*/

    if(counter1==4) counter1+=100;/*�����ɫ��4����������Ȩ100*/
    if(counter2==4) counter2+=70;/*�����ɫ��4����������Ȩ70*/

    return (counter1+counter2)*5-side;
}

/*�ж����Ϸ����ϼ�������������*/
int rupcount(i,j)
{
    int counter1=0,counter2=0;
    int i1=i,j1=j;
    int side=0;

    while(bkmap[i1+1][j1+1]==16&&i1<21&&j1<21)    /*�����ϼ���ɫ����*/
    {
        i1++;
        j1++;
        counter1++;
    }

    i1=i;
    j1=j;
    while(bkmap[i1+1][j1+1]==1&&i1<21&&j1<21)    /*�����ϼ��black����*/
    {
        i1++;
        j1++;
        counter2++;
    }

    if(bkmap[i1][j1]==16||i1==21||j1==21)
    {
        side++;             /*�ж����ϲ��Ƿ��к��ӻ��ѵ��߽�*/
    }

    i1=i;
    j1=j;
    while(bkmap[i1-1][j1-1]==16&&i1>=0&&j1>=0)    /*�����¼���ɫ����*/
    {
        i1--;
        j1--;
        counter1++;
    }

    i1=i;
    j1=j;
    while(bkmap[i1-1][j1-1]==1&&i1>=0&&j1>=0)    /*�����¼��black����*/
    {
        i1--;
        j1--;
        counter2++;
    }

    if(bkmap[i1][j1]==16||i1<0||j1<0)
    {
        side++;             /*�ж����²��Ƿ��к��ӻ��ѵ��߽�*/
    }

    if(counter1==3) counter1+=40;/*�����ɫ��������������Ȩ40*/
    if(counter2==3) counter2+=25;/*�����ɫ��������������Ȩ25*/

    if(counter1==4) counter1+=100;/*�����ɫ��4����������Ȩ100*/
    if(counter2==4) counter2+=70;/*�����ɫ��4����������Ȩ70*/

    return (counter1+counter2)*5-side;
}

/*�ж����·����ϼ�������������*/
int rdowncount(i,j)
{
    int counter1=0,counter2=0;
    int i1=i,j1=j;
    int side=0;

    while(bkmap[i1-1][j1+1]==16&&i1>=0&&j1<21)    /*�����ϼ���ɫ����*/
    {
        i1--;
        j1++;
        counter1++;
    }

    i1=i;
    j1=j;
    while(bkmap[i1-1][j1+1]==1&&i1>=0&&j1<21)    /*�����ϼ��black����*/
    {
        i1--;
        j1++;
        counter2++;
    }

    if(bkmap[i1-1][j1+1]==16||i1<0||j1==21)
    {
        side++;             /*�ж����ϲ��Ƿ��к��ӻ��ѵ��߽�*/
    }

    i1=i;
    j1=j;
    while(bkmap[i1+1][j1-1]==16&&i1<21&&j1>=0)    /*�����¼���ɫ����*/
    {
        i1++;
        j1--;
        counter1++;
    }

    i1=i;
    j1=j;
    while(bkmap[i1+1][j1-1]==1&&i1<21&&j1>=0)    /*�����¼��black����*/
    {
        i1++;
        j1--;
        counter2++;
    }

    if(bkmap[i1+1][j1-1]==16||i1==21||j1<0)
    {
        side++;             /*�ж����²��Ƿ��к��ӻ��ѵ��߽�*/
    }

    if(counter1==3) counter1+=40;/*�����ɫ��������������Ȩ40*/
    if(counter2==3) counter2+=25;/*�����ɫ��������������Ȩ25*/

    if(counter1==4) counter1+=100;/*�����ɫ��4����������Ȩ100*/
    if(counter2==4) counter2+=70;/*�����ɫ��4����������Ȩ70*/

    return (counter1+counter2)*5-side;
}

void machine()        /*�����ǰ��壬2*/
{
    int i=0,j=0,k=0;
    int info;  /*ÿ���ո���Ȩֵ*/
    int temp=0;
    int computer[21][21][4]={0};
    for(i=0;i<21;i++)       /*ɨ������*/
    {
        for(j=0;j<21;j++)
        {
            if(bkmap[i][j]==0)     /*���пո��*/
            {
            /*���ҷ�����*/
                computer[i][j][0]=rightcount(i,j);

            /*���·�����*/
                computer[i][j][1]=upcount(i,j);

            /*���Ϸ�����*/
                computer[i][j][2]=rupcount(i,j);

            /*���·�����*/
                computer[i][j][3]=rdowncount(i,j);

                info=0;
                for(k=0;k<4;k++)
                {
                    info+=computer[i][j][k];          /*4������Ȩֵ���*/
                }

                if(info>=temp)                         /*�ҳ�Ȩֵ����*/
                {

                    dx=i;dy=j;
                    temp=info;
                }
            }
        }
    }
}

/*����ʹ��
main()
{
    machine();
    printf("%d     %d",point.dx,point.dy);
    getch();
} */
