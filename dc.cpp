#include<bits/stdc++.h>
using namespace std;
#define org 4//条件属性
#define objn 6//对象个数
#define ub 0.75//上界
#define lb 0.4//下界
#define lvofd 3//粒度层数
#define dNum 1//决策标签
struct dobj{
    float data[org];
    int sum=0;
    int flag=0;
    int state=0;//组号
    int statelv0=0;//第一级粒度的编号
    int statelv1=0;
    int statelv2=0;
    int region;//划分到的域 -1：负域 0：边界域 1：正域
    float valp;
};
struct divdec{//决策标签兼粒度划分
    char objNum[objn];//对象号
    int numofobj=0;
};
struct setregion{
    int objNum[objn];
    int numofobj=0;
};
struct dobj obj[objn];
struct divdec Ddec[objn];
struct divdec lv0[objn];
struct divdec lv1[objn];
struct divdec lv2[objn];
struct divdec lv3[objn];
int ii,jj,n;
int numofbq0=0;
int numofbq1=0;
int numofbq2=0;
int numofbq3=0;

struct setregion bndR[objn];//边界域
struct setregion negR[objn];//负域
struct setregion posR[objn];//正域
char result[objn] ;//做集合运算的结果存放
char *last;
float Ddata[objn][org] = { 0 };//定义一个1500*2的矩阵，用于存放数据
void tc()//测试代价
{
//=========
}
void dc()//延迟代价
{
//
}
void readin()
{

    ifstream infile;//定义读取文件流，相对于程序来说是in
    infile.open("2.txt");//打开文件
    for (int i = 0; i <objn; i++)//定义行循环
    {
        for (int j = 0; j<org; j++)
        {
            infile >> Ddata[i][j];//读取一个值（空格、制表符、换行隔开）就写入到矩阵中，行列
        }
    }
    infile.close();//读取完成之后关闭文件
}
void inp()//接受数据
{
    for (ii=0;ii<objn;ii++)
        for(jj=0;jj<org;jj++)
            obj[ii].data[jj]=Ddata[ii][jj];
}
void outp()//输出数据
{
    printf("\t");
    for(n=0;n<org;n++)
        printf("a%d\t",n);
    printf("sum\n");
    for (ii=0;ii<objn;ii++)
       {
           printf("x%d\t",ii);
        for(jj=0;jj<org;jj++)
        {
            obj[ii].sum+=obj[ii].data[jj];
            printf("%.0f\t",obj[ii].data[jj]);
        }
            printf("%d\n",obj[ii].sum);
        }
}
void dvd()//划分决策标签
{
    int i,j;//i对象号
    //int p=0;//类中对象的个数
    int c=0;//决策标签个数
    for(i=0;i<objn;i++)
    {
        int xx=i;
        if(i==0)
            {
                Ddec[c].objNum[Ddec[c].numofobj]=i+48;
                obj[i].state=c;
                Ddec[c].numofobj++;
                }
        else
        {

            for(j=0;j<i;j++)
               {
                if(obj[i].sum==obj[j].sum)
                {
                    obj[i].state=obj[j].state;
                    Ddec[obj[j].state].objNum[Ddec[obj[j].state].numofobj]=i+48;
                    Ddec[obj[j].state].numofobj++;
                    break;
                }
                else
                    {
                        xx--;
                        }

               if(xx==0)
                {
                    c++;
                    Ddec[c].objNum[Ddec[c].numofobj]=i+48;
                    obj[i].state=c;
                    Ddec[c].numofobj++;
                    //break;
                    //printf("%d",c);
                }
               }
        }
    }


    //printf("%d",c);
    int h1,h2,h3;//往下是输出属性标签划分对象的等价类   已完成
    for(h3=0;h3<c+1;h3++)
        printf("D%d\t\t\t",h3);
    printf("\n");
    for(h1=0;h1<c+1;h1++)
    {
        //while(Ddec[h1].numofobj!=0)
            for(int v=0;v<Ddec[h1].numofobj;v++)
                printf("X%c ",Ddec[h1].objNum[v]);
            Ddec[h1].numofobj--;
        printf("\t\t\t");
    }

printf("\n");

}
float conp(char *d,char *lv)//计算条件概率
{
    int lend=strlen(d);
    int lenlv=strlen(lv);
    last=set_intersection(d, d+lend,lv, lv+lenlv,result) ;
    *last = 0 ;
    //cout<<result<<'\t'<<d<<'\t'<<lv<<'\t'<<endl;
    int lenr=strlen(result);
    float p1=lend;
    float p2=lenlv;
    float p3=lenr;
    return (p3/p2);
}
void gran1()//第一级粒度
{
int i,j;//i对象号
    //int p=0;//类中对象的个数
    int c=0;//决策标签个数
    for(i=0;i<objn;i++)
    {
        int xx=i;
        if(i==0)
            {
                lv0[c].objNum[lv0[c].numofobj]=i+48;//ascii码表里的
                obj[i].statelv0=c;
                lv0[c].numofobj++;
                }
        else
        {

            for(j=0;j<i;j++)
               {
                if(obj[i].data[0]==obj[j].data[0])
                {
                    obj[i].statelv0=obj[j].statelv0;
                    lv0[obj[j].statelv0].objNum[lv0[obj[j].statelv0].numofobj]=i+48;
                    lv0[obj[j].statelv0].numofobj++;
                    break;
                }
                else
                    {
                        xx--;
                        }

               if(xx==0)
                {
                    c++;
                    lv0[c].objNum[lv0[c].numofobj]=i+48;
                    obj[i].statelv0=c;
                    lv0[c].numofobj++;
                }
               }
        }
    }
    numofbq0=c;
    int cotlv0;
    int posC=0;//正域计数
    int negC=0;
    int bndC=0;
    for( cotlv0=0;cotlv0<objn;cotlv0++)
    {
        if(conp(Ddec[dNum].objNum,lv0[obj[cotlv0].statelv0].objNum)>ub)//根据决策标签来划分obj[cotlv0].statelv0
        {
            obj[cotlv0].region=1;
            obj[cotlv0].flag++;//逻辑交
            posR[0].objNum[posC]=cotlv0;
            posC++;
            posR[0].numofobj++;
        }
        else if(conp(Ddec[dNum].objNum,lv0[obj[cotlv0].statelv0].objNum)<lb)
        {
            obj[cotlv0].region=-1;
            obj[cotlv0].flag--;//逻辑交
            negR[0].objNum[negC]=cotlv0;
            negC++;
            negR[0].numofobj++;
        }
        else
        {
            obj[cotlv0].region=0;
            bndR[0].objNum[bndC]=cotlv0;
            bndC++;
            bndR[0].numofobj++;
        }
    }


    int h1,h2,h3;
    for(h3=0;h3<c+1;h3++)
        printf("Lv0%d\t\t\t",h3);
    printf("\n");
    for(h1=0;h1<c+1;h1++)
    {
        h2=lv0[h1].numofobj;
            for(int v=0;v<lv0[h1].numofobj;v++)
                    printf("X%c ",lv0[h1].objNum[v]);
                h2--;
        printf("\t\t\t");
    }
   // printf("\n%d\n",numofbq0);
    printf("\n");
}



void gran2()
{
    int i,j,k,l;
    int c=0;
    for(j=0;j<numofbq0;j++)//numofbq数量加一为真实值 numofobj是真实值
        for(i=0;i<lv0[j].numofobj;i++)//numofbij是lv0[numofbq0].objNum[i] 是char类型！！！
        {
            //printf("%d",lv0[j].numofobj);
            int xx=i;
            if(i==0)
            {
                lv1[numofbq1].objNum[lv1[numofbq1].numofobj]=lv0[j].objNum[i];//ascii码表里的
                int ZZZ=lv0[j].objNum[i];
                obj[ZZZ-48].statelv1=numofbq1;
                lv1[numofbq1].numofobj++;
                }
            else
            {

                for(l=0;l<i;l++)
                {
                    int ZZZ=lv0[j].objNum[i];
                    int ZZZZ=lv0[j].objNum[l];
                    if(obj[ZZZ-48].data[1]==obj[ZZZZ-48].data[1])
                    {
                        obj[ZZZ-48].statelv1=obj[ZZZZ-48].statelv1;
                        lv1[obj[ZZZZ-48].statelv1].objNum[lv1[obj[ZZZZ-48].statelv1].numofobj]=lv0[numofbq0].objNum[i];
                        lv1[obj[ZZZZ-48].statelv1].numofobj++;
                        break;
                    }
                    else
                        {
                            xx--;
                        }

                    if(xx==0)
                        {
                            numofbq1++;
                            lv1[numofbq1].objNum[lv1[numofbq1].numofobj]=lv0[numofbq0].objNum[i];
                            int ZZZ=lv0[j].objNum[i];
                            obj[ZZZ-48].statelv1=numofbq1;
                            lv1[numofbq1].numofobj++;
                        }
                    }
                }
        }
    int cotlv1;
    int posC=0;//正域计数
    int negC=0;
    int bndC=0;
    for( cotlv1=0;cotlv1<objn;cotlv1++)
    {
        if(conp(Ddec[dNum].objNum,lv1[obj[cotlv1].statelv1].objNum)>ub)//Ddec[obj[cotlv1].statelv1].objNum
        {
            obj[cotlv1].region=1;
            obj[cotlv1].flag++;//逻辑交
            posR[1].objNum[posC]=cotlv1;
            posC++;
            posR[1].numofobj++;
        }
        else if(conp(Ddec[dNum].objNum,lv1[obj[cotlv1].statelv1].objNum)<lb)//
        {
            obj[cotlv1].region=-1;
            obj[cotlv1].flag--;//逻辑交
            negR[1].objNum[negC]=cotlv1;
            negC++;
            negR[1].numofobj++;
        }
        else
        {
            obj[cotlv1].region=0;
            bndR[1].objNum[bndC]=cotlv1;
            bndC++;
            bndR[1].numofobj++;
        }
    }

    int h1,h2,h3;
    for(h3=0;h3<numofbq1+1;h3++)
        printf("Lv1%d\t\t\t",h3);
    printf("\n");
    for(h1=0;h1<numofbq1+1;h1++)
    {
        h2=lv1[h1].numofobj;
            for(int v=0;v<lv1[h1].numofobj;v++)
                    printf("X%c ",lv1[h1].objNum[v]);
                h2--;
        printf("\t\t\t");
    }
    printf("\n");
}





/*void gran2()//第二级粒度
{
    int i,j;//i对象号
    //int p=0;//类中对象的个数
    int c=0;//决策标签个数
    for(i=0;i<objn;i++)
    {
        int xx=i;
        if(i==0)
            {
                lv1[c].objNum[lv1[c].numofobj]=i+48;//ascii码表里的
                obj[i].statelv1=c;
                lv1[c].numofobj++;
                }
        else
        {

            for(j=0;j<i;j++)
               {
                if(obj[i].data[1]==obj[j].data[1])
                {
                    obj[i].statelv1=obj[j].statelv1;
                    lv1[obj[j].statelv1].objNum[lv1[obj[j].statelv1].numofobj]=i+48;
                    lv1[obj[j].statelv1].numofobj++;
                    break;
                }
                else
                    {
                        xx--;
                        }

               if(xx==0)
                {
                    c++;
                    lv1[c].objNum[lv1[c].numofobj]=i+48;
                    obj[i].statelv1=c;
                    lv1[c].numofobj++;
                }
               }
        }
    }

    int cotlv1;
    int posC=0;//正域计数
    int negC=0;
    int bndC=0;
    for( cotlv1=0;cotlv1<objn;cotlv1++)
    {
        if(conp(Ddec[dNum].objNum,lv1[obj[cotlv1].statelv1].objNum)>ub)//Ddec[obj[cotlv1].statelv1].objNum
        {
            obj[cotlv1].region=1;
            obj[cotlv1].flag++;//逻辑交
            posR[1].objNum[posC]=cotlv1;
            posC++;
            posR[1].numofobj++;
        }
        else if(conp(Ddec[dNum].objNum,lv1[obj[cotlv1].statelv1].objNum)<lb)//
        {
            obj[cotlv1].region=-1;
            obj[cotlv1].flag--;//逻辑交
            negR[1].objNum[negC]=cotlv1;
            negC++;
            negR[1].numofobj++;
        }
        else
        {
            obj[cotlv1].region=0;
            bndR[1].objNum[bndC]=cotlv1;
            bndC++;
            bndR[1].numofobj++;
        }
    }


    int h1,h2,h3;
    for(h3=0;h3<c+1;h3++)
        printf("Lv1%d\t\t\t",h3);
    printf("\n");
    for(h1=0;h1<c+1;h1++)
    {
            for(int v=0;v<lv1[h1].numofobj;v++)
                    printf("X%c ",lv1[h1].objNum[v]);
                lv1[h1].numofobj--;
        printf("\t\t\t");
    }
    printf("\n");
}*/
void gran3()//三
{
    int i,j;//i对象号
    //int p=0;//类中对象的个数
    int c=0;//决策标签个数
    for(i=0;i<objn;i++)
    {
        int xx=i;
        if(i==0)
            {
                lv2[c].objNum[lv2[c].numofobj]=i+48;//ascii码表里的
                obj[i].statelv2=c;
                lv2[c].numofobj++;
                }
        else
        {

            for(j=0;j<i;j++)
               {
                if(obj[i].data[2]==obj[j].data[2])
                {
                    obj[i].statelv2=obj[j].statelv2;
                    lv2[obj[j].statelv2].objNum[lv2[obj[j].statelv2].numofobj]=i+48;
                    lv2[obj[j].statelv2].numofobj++;
                    break;
                }
                else
                    {
                        xx--;
                        }

               if(xx==0)
                {
                    c++;
                    lv2[c].objNum[lv2[c].numofobj]=i+48;
                    obj[i].statelv2=c;
                    lv2[c].numofobj++;
                }
               }
        }
    }

    int cotlv2;
    int posC=0;//正域计数
    int negC=0;
    int bndC=0;
    for( cotlv2=0;cotlv2<objn;cotlv2++)
    {
        if(conp(Ddec[dNum].objNum,lv2[obj[cotlv2].statelv2].objNum)>ub)//Ddec[obj[cotlv2].statelv2].objNum
        {
            obj[cotlv2].region=1;
            obj[cotlv2].flag++;//逻辑交
            posR[2].objNum[posC]=cotlv2;
            posC++;
            posR[2].numofobj++;
        }
        else if(conp(Ddec[dNum].objNum,lv2[obj[cotlv2].statelv2].objNum)<lb)//
        {
            obj[cotlv2].region=-1;
            obj[cotlv2].flag--;//逻辑交
            negR[2].objNum[negC]=cotlv2;
            negC++;
            negR[2].numofobj++;
        }
        else
        {
            obj[cotlv2].region=0;
            bndR[2].objNum[bndC]=cotlv2;
            bndC++;
            bndR[2].numofobj++;
        }
    }


    int h1,h2,h3;
    for(h3=0;h3<c+1;h3++)
        printf("Lv2%d\t\t\t",h3);
    printf("\n");
    for(h1=0;h1<c+1;h1++)
    {
            for(int v=0;v<lv2[h1].numofobj;v++)
                    printf("X%c ",lv2[h1].objNum[v]);
                lv2[h1].numofobj--;
        printf("\t\t\t");
    }
    printf("\n");
}

void csos()//三支决策后的结果
{
    int levofdvd;
    int i,j,k;
    printf("\nLv\tPOS\t\tBND\t\tNEG\n");
    for(levofdvd=0;levofdvd<lvofd;levofdvd++)
    {
        printf("Lv%d\t",levofdvd);
        for(i=0;i<posR[levofdvd].numofobj;i++)
            printf("X%d",posR[levofdvd].objNum[i]);
            printf("\t\t");
        for(j=0;j<posR[levofdvd].numofobj;j++)
            printf("X%d",bndR[levofdvd].objNum[j]);
            printf("\t\t");
        for(k=0;k<posR[levofdvd].numofobj;k++)
            printf("X%d",negR[levofdvd].objNum[k]);
        printf("\n");
    }
}

void mixresult()// ccccccccccccccccccccccccccccccc
{
    int i,j,k;
    printf("\nMIX\tPOS\t\tBND\t\tNEG\n\t");
        for(i=0;i<objn;i++)
            {
                if(obj[i].flag>=1)
                printf("X%d",i);
                }
            printf("\t\t");
        for(j=0;j<objn;j++)
        {
            if(obj[j].flag<1&&obj[j].flag>-1)
            printf("X%d",j);
        }
            printf("\t\t");
        for(k=0;k<objn;k++)
            {
                if(obj[k].flag<=-1)
                printf("X%d",k);
            }
        printf("\n");
}
int main()
{
    readin();
    inp();
    outp();
    dvd();
    gran1();
    gran2();
    gran3();
    csos();
    mixresult();

   // printf("%f\n",conp(Ddec[0].objNum,lv0[0].objNum));
   // printf("%f\n",conp(Ddec[0].objNum,lv1[0].objNum));
   // printf("%f\n",conp(Ddec[0].objNum,lv2[0].objNum));
    /*char *d1="14";
    char *d2="12345";
    printf("%f",conp(d1,d2));*/
    //int lev=org;
    return 0;
}
