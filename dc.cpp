#include<bits/stdc++.h>
using namespace std;
#define org 4//��������
#define objn 6//�������
#define ub 0.75//�Ͻ�
#define lb 0.4//�½�
#define lvofd 3//���Ȳ���
#define dNum 1//���߱�ǩ
struct dobj{
    float data[org];
    int sum=0;
    int flag=0;
    int state=0;//���
    int statelv0=0;//��һ�����ȵı��
    int statelv1=0;
    int statelv2=0;
    int region;//���ֵ����� -1������ 0���߽��� 1������
    float valp;
};
struct divdec{//���߱�ǩ�����Ȼ���
    char objNum[objn];//�����
    int numofobj=0;
    int numofbq;

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
struct setregion bndR[objn];//�߽���
struct setregion negR[objn];//����
struct setregion posR[objn];//����
char result[objn] ;//����������Ľ�����
char *last;
void tc()//���Դ���
{
//=========
}
void dc()//�ӳٴ���
{
//
}
void inp()//��������
{
    for (ii=0;ii<objn;ii++)
        for(jj=0;jj<org;jj++)
            scanf("%f",&obj[ii].data[jj]);
}
void outp()//�������
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
void dvd()//���־��߱�ǩ
{
    int i,j;//i�����
    //int p=0;//���ж���ĸ���
    int c=0;//���߱�ǩ����
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
    int h1,h2,h3;//������������Ա�ǩ���ֶ���ĵȼ���   �����
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
float conp(char *d,char *lv)//������������
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
void gran1()//��һ������
{
int i,j;//i�����
    //int p=0;//���ж���ĸ���
    int c=0;//���߱�ǩ����
    for(i=0;i<objn;i++)
    {
        int xx=i;
        if(i==0)
            {
                lv0[c].objNum[lv0[c].numofobj]=i+48;//ascii������
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

    int cotlv0;
    int posC=0;//�������
    int negC=0;
    int bndC=0;
    for( cotlv0=0;cotlv0<objn;cotlv0++)
    {
        if(conp(Ddec[dNum].objNum,lv0[obj[cotlv0].statelv0].objNum)>ub)//���ݾ��߱�ǩ������obj[cotlv0].statelv0
        {
            obj[cotlv0].region=1;
            obj[cotlv0].flag++;//�߼���
            posR[0].objNum[posC]=cotlv0;
            posC++;
            posR[0].numofobj++;
        }
        else if(conp(Ddec[dNum].objNum,lv0[obj[cotlv0].statelv0].objNum)<lb)
        {
            obj[cotlv0].region=-1;
            obj[cotlv0].flag--;//�߼���
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
            for(int v=0;v<lv0[h1].numofobj;v++)
                    printf("X%c ",lv0[h1].objNum[v]);
                lv0[h1].numofobj--;
        printf("\t\t\t");
    }
    printf("\n");
}
void gran2()//�ڶ�������
{
    int i,j;//i�����
    //int p=0;//���ж���ĸ���
    int c=0;//���߱�ǩ����
    for(i=0;i<objn;i++)
    {
        int xx=i;
        if(i==0)
            {
                lv1[c].objNum[lv1[c].numofobj]=i+48;//ascii������
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
    int posC=0;//�������
    int negC=0;
    int bndC=0;
    for( cotlv1=0;cotlv1<objn;cotlv1++)
    {
        if(conp(Ddec[dNum].objNum,lv1[obj[cotlv1].statelv1].objNum)>ub)//Ddec[obj[cotlv1].statelv1].objNum
        {
            obj[cotlv1].region=1;
            obj[cotlv1].flag++;//�߼���
            posR[1].objNum[posC]=cotlv1;
            posC++;
            posR[1].numofobj++;
        }
        else if(conp(Ddec[dNum].objNum,lv1[obj[cotlv1].statelv1].objNum)<lb)//
        {
            obj[cotlv1].region=-1;
            obj[cotlv1].flag--;//�߼���
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
}
void gran3()//��
{
    int i,j;//i�����
    //int p=0;//���ж���ĸ���
    int c=0;//���߱�ǩ����
    for(i=0;i<objn;i++)
    {
        int xx=i;
        if(i==0)
            {
                lv2[c].objNum[lv2[c].numofobj]=i+48;//ascii������
                obj[i].statelv2=c;
                lv2[c].numofobj++;
                }
        else
        {

            for(j=0;j<i;j++)
               {
                if(obj[i].data[0]==obj[j].data[0])
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
    int posC=0;//�������
    int negC=0;
    int bndC=0;
    for( cotlv2=0;cotlv2<objn;cotlv2++)
    {
        if(conp(Ddec[dNum].objNum,lv2[obj[cotlv2].statelv2].objNum)>ub)//Ddec[obj[cotlv2].statelv2].objNum
        {
            obj[cotlv2].region=1;
            obj[cotlv2].flag++;//�߼���
            posR[2].objNum[posC]=cotlv2;
            posC++;
            posR[2].numofobj++;
        }
        else if(conp(Ddec[dNum].objNum,lv2[obj[cotlv2].statelv2].objNum)<lb)//
        {
            obj[cotlv2].region=-1;
            obj[cotlv2].flag--;//�߼���
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

void csos()//��֧���ߺ�Ľ��
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
    inp();
    outp();
    dvd();
    gran1();
    gran2();
    gran3();
    csos();
    mixresult();
    printf("%d",posR[0].objNum[0]);
    printf("%d",posR[0].objNum[1]);
    printf("%d",posR[0].objNum[2]);
    printf("%d",posR[1].objNum[0]);
    printf("%d",posR[1].objNum[1]);
    printf("%d",posR[1].objNum[2]);
    printf("%d",bndR[0].objNum[0]);
    printf("%d",bndR[0].objNum[1]);
    printf("%d",bndR[0].objNum[2]);
    printf("%d",bndR[1].objNum[0]);
    printf("%d",bndR[1].objNum[1]);
    printf("%d",bndR[1].objNum[2]);

   // printf("%f\n",conp(Ddec[0].objNum,lv0[0].objNum));
   // printf("%f\n",conp(Ddec[0].objNum,lv1[0].objNum));
   // printf("%f\n",conp(Ddec[0].objNum,lv2[0].objNum));
    /*char *d1="14";
    char *d2="12345";
    printf("%f",conp(d1,d2));*/
    //int lev=org;
    return 0;
}
