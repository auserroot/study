// ����������ϵͳ.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


// ����������ϵͳ.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
    char number[10];//���
    char name[20];//����
    char author[20];//����
    char information[100];//�����Ϣ
    char publish[50];//������
	char knum[100];//���
    float price;//�۸�
} newbook;
typedef struct node1
{
    int num;  //ͼ���� 
    newbook book[100]; //����¼���ͼ����                                   
} books;
books bookstore;
typedef struct node2//�û�����ṹ��
{
	int code;//���
	char name[20];//����
	float price;//�۸�
	int bnum;//����ͼ����
	float bprice;//����ͼ��۸�
} bbuy;
bbuy goods[20];

void Main();//��������������
void Main2();//��������������
void input();//�������뺯��
void Input();//�������뺯������
void search();//������ѯ
void sch();//������ѯ����
void del();//����ɾ��
void delbook();//����ɾ������
void save(); //�������溯��
void regist();//����ע��
void login();//������¼
void by();//��������
void pay();//����֧��
void print();//��������
void print2();//��������

void save() //����ͼ����Ϣ
{                                          
    FILE *fp;
    if((fp=fopen("book.txt","w"))==NULL)
	{
        printf("����ͼ��ʧ��\n");
        return;
    }
    fwrite(&bookstore.num,sizeof(int),1,fp);
    fwrite(bookstore.book,sizeof(bookstore.book[0]),bookstore.num,fp);
	fclose(fp);
}


void logo()
{
	int i;
	system("color 06");
	do
	{
	printf("\t\t*****ģʽѡ�����*****\n");
	printf("\t\t      1.ע��          \n");
	printf("\t\t      2.�̼ҵ�¼      \n");
	printf("\t\t      3.�û���¼      \n");
	printf("\t\t      4.�˳�          \n");
	scanf("%d",&i);
	switch(i)
	{
	case 1: regist();
		    break;
	case 2: print();
		    break;
	case 3:print2();
		    break;
    case 4: printf("\n\n�˳�\n\n");
                break;
            default:
                printf("\n��Ų���\n");
                break;
        }
    } while(i!=4);
    save();
}

char name[80] ,pas[80],temp[80];
char textstring[80];
int ok=0;
void login()
{  
    printf("\t\t��¼����\n");
    printf("�������˺�:\n");
    gets(name);
    printf("����������:\n");
    gets(pas);
    strcat(name,pas);//�ϲ��ַ�
    strcat(name,"\n");//��ӻ����ַ� 
    int len = 0;
    FILE *fp= fopen("user.txt", "r");
    if(NULL == fp)
    {
        printf("��ʧ��\n");
        return ;
    }

    while(!feof(fp))
    {
        memset(textstring, 0, sizeof(textstring));
        fgets(textstring, sizeof(textstring) - 1, fp); // ������\n
        if(strcmp(name,textstring)==0)//�ж��ַ��Ƿ����
		{
           ok=1;
           break;
        }
    }
    if(ok==1)
	{
      printf("��¼OK\n");
	  Main();
	}
    else
      printf("��¼ʧ��\n");
    fclose(fp);

}

void login2()
{
	printf("\t\t��¼����\n");
    printf("�������˺�:\n");
    gets(name);
    printf("����������:\n");
    gets(pas);
    strcat(name,pas);//�ϲ��ַ�
    strcat(name,"\n");//��ӻ����ַ� 
    int len = 0;
    FILE *fp= fopen("user.txt", "r");
    if(NULL == fp)
    {
        printf("��ʧ��\n");
        return ;
    }

    while(!feof(fp))
    {
        memset(textstring, 0, sizeof(textstring));
        fgets(textstring, sizeof(textstring) - 1, fp); // ������\n
        if(strcmp(name,textstring)==0)//�ж��ַ��Ƿ����
		{
           ok=1;
           break;
        }
    }
    if(ok==1)
	{
      printf("��¼OK\n");
	  Main2();
	}
    else
      printf("��¼ʧ��\n");
    fclose(fp);

}

void print()
{
	FILE *fp;
	int i;
	do
	{
	system("color 06");
    printf("\n\t\t1.ע�� 2.�Ķ�ʹ��˵�� 3.��¼\n");
	scanf("%d",&i);
	if(i==2)
        {
			if((fp=fopen("ʹ��˵��.txt","r"))==NULL)
                {
                printf("\n\t\t��ʧ��");
                exit(0);
                }
                fread("ʹ��˵��.txt",2,20,fp);
                printf("\n\t\t%s","ʹ��˵��.txt");
               
        }
	else if(i==1)
    regist();//ע��
	else if(i==3)
	  login();//��¼
	  }while(strcmp(pas,temp)!=0); 
}

void print2()
{
	FILE *fp;
	int i;
	do
	{
	system("color 06");
    printf("\n\t\t1.ע�� 2.�Ķ�ʹ��˵�� 3.��¼\n");
	scanf("%d",&i);
	if(i==2)
        {
			if((fp=fopen("ʹ��˵��.txt","r"))==NULL)
                {
                printf("\n\t\t��ʧ��");
                exit(0);
                }
                fread("ʹ��˵��.txt",2,20,fp);
                printf("\n\t\t%s","ʹ��˵��.txt");
               
        }
	else if(i==1)
    regist();//ע��
	else if(i==3)
	  login2();//��¼
	  }while(strcmp(pas,temp)!=0); 

}

void regist()//ע��
{
    FILE *fp=fopen("user.txt","a");
    printf("�������˺�:");
	scanf("%s",name);
    printf("����������:");
	scanf("%s",pas);
	printf("ȷ������:");
	scanf("%s",temp);
    fputs(name,fp);
    fputs(pas,fp);//�����ƺ��������ַ�����ʽд���ļ�
    fputs("\n",fp);
    fflush(stdin);//�������
    fclose(fp);
    login();
}

int dl()//����ע���¼
{
    print();
    int settle=0;
     scanf("%d",&settle);
     fflush(stdin);//�������
    if(settle)
       regist();
    else
        login();
    return 0;
}

void input()//ͼ��¼��
{   
    system("cls");
	int t=1;
    bookstore.num=0;
    while(t)
	{
        printf("����ͼ����:");
        scanf("%s",bookstore.book[bookstore.num].number);
        printf("\n����ͼ������:");
        scanf("%s",bookstore.book[bookstore.num].name);
        printf("\n����ͼ�������:");
        scanf("%s",bookstore.book[bookstore.num].author);
        printf("\n������ͼ�������Ϣ:");
        scanf("%s",bookstore.book[bookstore.num].information);
        printf("\n����������磺");
        scanf("%s",bookstore.book[bookstore.num].publish);
		printf("\n��������:");
		scanf("%s",bookstore.book[bookstore.num].knum);
        fflush(stdin);
        printf("\n������ͼ��۸�");
        scanf("%f",&bookstore.book[bookstore.num].price);
        bookstore.num++;//ʵ�����ȴ�����1 
	    printf("\n�Ƿ��������ͼ����Ϣ(1:�ǣ�0����):");
        scanf("%d",&t);
		if(t==0)
			printf("\n�����롮2���������˵���");
	}
      save();          
 }
    
void Input()//¼�����
  { 
	  system("cls");
	  int k;
	   ////////////////////////////////////////���濪ʼ////////////////////////////////////////////////////
     printf("////////////////////////////////////////////////////////////////////////////////////////////////////////");
	  printf("\n\n");
	  printf("\t\t\t******               �����鱾���ݵ������                ******\n");
	  printf("\n\n");
	  printf("\t\t\t******===================================================******\t\t\t\n");
	
	   printf("\t\t\t******             �������鱾�����Ϣ                    ******\n");
	   printf("\n\n");
	   printf("\t\t\t******                   ����ѡ��                        ******\n");
	   printf("\n\n");
	   printf("\t\t\t******            �Ƿ�������룿1���ǣ�2����             ******\n");
	   printf("\n\n");
	  printf("////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
       do
	    { 
		  scanf_s("%d",&k);
	      switch(k)
	   {
	   case 1: input();
		   break;
	   case 2:  printf("\t\t\t******             �������������ллʹ�ã�              ******\n");
		  return Main();
	    default:  printf("\t\t\t******             ��������Ϣ��������������            ******\n");
		    break;
	   }
	  }
	  while(k!=0);
	  printf("\t\t\t                         ****��ӭ�´ι���****                      \n");
	  ////////////////////////////////////////�������////////////////////////////////////////////////////*/
	  }  



void display()//��ʾȫ��ͼ����Ϣ
{                                            
    system("cls");
    printf("���\t����\t����\t�����Ϣ\t������\t���\t�۸�\n");
    fflush(stdin);// ������뻺����
    for(int l=0; l<bookstore.num; l++) 
	{
        printf("%s\t",bookstore.book[l].number);
        printf("%s\t",bookstore.book[l].name);
        printf("%s\t",bookstore.book[l].author);
        printf("%s\t",bookstore.book[l].information);
        printf("\t%s\t",bookstore.book[l].publish);
		printf(" %s\t",bookstore.book[l].knum);
        printf("%.2f\t\n",bookstore.book[l].price);
    }
    getchar();
}
void search()  //ͼ���ѯ
{                                        
    system("cls");
    fflush(stdin);
    int l;
    char c[20];
    printf("������Ҫ���ҵ�����:\n");
    gets(c);
    for(l=0; l<bookstore.num; l++) 
	{
        if(strcmp(c,bookstore.book[l].name)==0) 
		{
            printf("���\t����\t����\t�����Ϣ\t������\t���\t�۸�\n");
            printf("%s\t",bookstore.book[l].number);
            printf("%s\t",bookstore.book[l].name);
            printf("%s\t",bookstore.book[l].author);
            printf("%s\t",bookstore.book[l].information);
            printf("\t%s\t",bookstore.book[l].publish);
            printf(" %s\t",bookstore.book[l].knum);
            printf("%.2f\t",bookstore.book[l].price);
            break;
        }
    }
    if(l==bookstore.num)
        printf("û�д�ͼ��\n");
    fflush(stdin);
    getchar();
	printf("\n�����롮2���������˵���");
}

void sch()//���ҽ���
 {
	 system("cls");
	 int k;
	   ////////////////////////////////////////���濪ʼ////////////////////////////////////////////////////
     printf("////////////////////////////////////////////////////////////////////////////////////////////////////////");
	  printf("\n\n");
	  printf("\t\t\t******               �����鱾���ҽ���                ******\n");
	  printf("\n\n");
	  printf("\t\t\t******================================================******\t\t\t\n");
	
	   printf("\t\t\t******             ��ѡ���鱾���������Ϣ                ******\n");
	   printf("\n\n");
	   printf("\t\t\t******                   ����ѡ��                        ******\n");
	   printf("\n\n");
	   printf("\t\t\t******            �Ƿ������1���ǣ�2����             ******\n");
	   printf("\n\n");
	  printf("////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
       do
	    {
		  scanf("%d",&k);
	      switch(k)
	   {
	   case 1: search();
		   break;
	   case 2:  printf("\t\t\t******             �������������ллʹ�ã�              ******\n");
		  return Main();
	    default:  printf("\t\t\t******             ��������Ϣ��������������            ******\n");
		   break;
	   }
	  }
	  while(k!=0);
	  printf("\t\t\t                         ****��ӭ�´ι���****                      \n");
	  ////////////////////////////////////////�������////////////////////////////////////////////////////
 }


void del() //ͼ��ɾ��
{                                           
    system("cls");
    fflush(stdin);
	display();
    int l;
    char c[10];
    printf("������Ҫɾ��������:\n");
    gets(c);
    for(l=0; l<bookstore.num; l++)
	{
        if(strcmp(c,bookstore.book[l].name)==0)
            break;
    }
    if(l==bookstore.num)
        printf("�޴�ͼ��\n");
    else
        for(int j=l; j<bookstore.num-1; j++)
		{
            strcpy(bookstore.book[j].number,bookstore.book[j+1].number);
            strcpy(bookstore.book[j].name,bookstore.book[j+1].name);
            strcpy(bookstore.book[j].author,bookstore.book[j+1].author);
            strcpy(bookstore.book[j].information,bookstore.book[j+1].information);
            strcpy(bookstore.book[j].publish,bookstore.book[j+1].publish);
            strcpy(bookstore.book[j].knum,bookstore.book[j+1].knum);
            bookstore.book[j].price=bookstore.book[j+1].price;
        } 
        bookstore.num--;
        printf("\n��0�˳�"); 
    fflush(stdin);
    save();
    getchar();
}

void delbook()//�鱾ɾ������
    {
		system("cls");
		int k;
	   ////////////////////////////////////////���濪ʼ////////////////////////////////////////////////////
     printf("////////////////////////////////////////////////////////////////////////////////////////////////////////");
	  printf("\n\n");
	  printf("\t\t\t******               �����鱾����ɾ������                ******\n");
	  printf("\n\n");
	  printf("\t\t\t******===================================================******\t\t\t\n");
	
	   printf("\t\t\t******             ��ѡ���鱾�����Ϣ                    ******\n");
	   printf("\n\n");
	   printf("\t\t\t******                   ����ѡ��                        ******\n");
	   printf("\n\t\t\t******                 �Ƿ��ȡ�ļ���                    ******\n");
	   printf("\n\t\t\t******                 1���ǣ�2����                      ******\n");
	   printf("\n\n");
	  printf("////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
       do
	    { 
		  scanf("%d",&k);
	      switch(k)
	   {
	   case 1: del();
		   break;
	   case 2:  printf("\t\t\t******             �������������ллʹ�ã�              ******\n");
		  return Main();
	    default:  printf("\t\t\t******             ��������Ϣ��������������            ******\n");
		   break;
	   }
	  }
	  while(k!=0);
	  printf("\t\t\t                         ****��ӭ�´ι���****                      \n");
	  ////////////////////////////////////////�������////////////////////////////////////////////////////
	  }  


void change() //ͼ���޸�
{                                 
    system("cls");
    fflush(stdin);
    int l;
    char c[10];
    printf("������Ҫ�޸ĵ�����-_-:\n");
    gets(c);
    for(l=0; l<bookstore.num; l++)
        if(strcmp(c,bookstore.book[l].name)==0)
            break;
    if(l==bookstore.num)
        printf("û�и�ͼ��\n");
    else {
        printf("�������޸ĺ��ͼ���ţ�");
        scanf("%s",bookstore.book[l].number);
        printf("\n�������޸ĺ��ͼ��������");
        scanf("%s",bookstore.book[l].name);
        printf("\n �������޸ĺ�����ߣ�");
        scanf("%s",bookstore.book[l].author);
        printf("\n �������޸ĺ�������Ϣ��");
        scanf("%s",bookstore.book[l].information);
        printf("\n �������޸ĺ�ĳ����磺");
        scanf("%s",bookstore.book[l].publish);
        printf("\n�������޸ĺ�ĳ����棺");
        scanf("%s",bookstore.book[l].knum);
        fflush(stdin);
        printf("\n�������޸ĺ��ͼ��۸�");
        scanf("%f",&bookstore.book[l].price);
    }
    fflush(stdin);
    save();
}

void cge()//�޸Ľ���
 {
	 system("cls");
	 int k;
	   ////////////////////////////////////////���濪ʼ////////////////////////////////////////////////////
     printf("////////////////////////////////////////////////////////////////////////////////////////////////////////");
	  printf("\n\n");
	  printf("\t\t\t******               �����鱾�����޸Ľ���                ******\n");
	  printf("\n\n");
	  printf("\t\t\t******===================================================******\t\t\t\n");
	  printf("\t\t\t******             ��ѡ���鱾�����Ϣ                    ******\n");
	  printf("\n\n");
	  printf("\t\t\t******                   ����ѡ��                        ******\n");
	  printf("\n\n");
	  printf("\t\t\t******            �Ƿ������1���ǣ�2����             ******\n");
	  printf("\n\n");
	  printf("////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
       do
	    { 
		  scanf_s("%d",&k);
	      switch(k)
	   {
	   case 1: change();
		   break;
	   case 2:  printf("\t\t\t******             �������������ллʹ�ã�              ******\n");
		  return Main();
	    default:  printf("\t\t\t******             ��������Ϣ��������������            ******\n");
		   break;
	   }
	  }
	  while(k!=0);
	  printf("\t\t\t                         ****��ӭ�´ι���****                      \n");
	  ////////////////////////////////////////�������////////////////////////////////////////////////////
 }

int n=10;

void add()//��ӵ����ﳵ
{
    display();
    int code = 0,number = 0;
    printf("�������鱾���\n");
    scanf("%d",&code);
    printf("��������鱾��������\n");
    scanf("%d",&number);
    int flag = 0;
    for(int i = 0;i < n;i++) 
	{
        if (goods[i].code == code) 
		{
            goods[i].bnum +=number;
            flag = 1;
            printf("��ӳɹ���\n");
            break;
        }
    }
    if (flag == 0) 
	{
        printf("û�и���\n");
    }
}

void cher()//�޸��б�
{
    int code = 0,number = 0;
    printf("�������鱾���\n");
    scanf("%d",&code);
    printf("��������鱾��������\n");
    scanf("%d",&number);
    int flag = 0;
    for(int i = 0;i < n;i++)  //ѭ������
	{
        if (goods[i].code == code && goods[i].bnum > 0) 
		{
            goods[i].bnum -=number;
            flag = 1;
            printf("�޸ĳɹ���\n");
            break;
        }
    }
    if (flag == 0) 
	{
        printf("û�м��빺�ﳵ\n");
    }
}

void remove()//ɾ����Ʒ�б�
{
    int code = 0,number = 0;
    printf("�������鱾���\n");
    scanf("%d",&code);
    printf("��������鱾��������\n");
    scanf("%d",&number);
    int flag = 0;
    for(int i = 0;i < n;i++)
	{
        if (goods[i].code == code&&goods[i].bnum > 0) 
		{
            goods[i].bnum = 0;
            flag = 1;
            printf("ɾ���ɹ���\n");
            break;
        }
    }
    if (flag == 0)
	{
        printf("û�и���\n");
    }
}

void show()//��ʾ�ܶ�
{
    printf("*********��ǰ���ﳵ����Ʒ*****");
    double sum = 0;
    for (int i = 0; i < n; i++)
	{
        if (goods[i].bnum > 0)
		{
            printf("%d\t%s\t%.2lf\t\t%d\t\t%lf\n",goods[i].code,goods[i].name,goods[i].price,goods[i].bnum,goods[i].bprice);
            sum += goods[i].bprice;
        }
    }
    printf("��ǰ�ܶ�Ϊ%.2f\n",sum);
	pay();
	printf("���ι�����:%.2fԪ\n",sum);

}

void pay()//�û�����֧��
{
		int i ;
		printf("�Ƿ�֧����1.�ǣ�2.��");
		scanf("%d",&i);
		if(i==1)
		printf("֧���ɹ���");
		else by();
	}

 void by()//�������
 {
	 system("cls");
	 int k;
	   ////////////////////////////////////////���濪ʼ////////////////////////////////////////////////////
     printf("////////////////////////////////////////////////////////////////////////////////////////////////////////");
	  printf("\n\n");
	  printf("\t\t\t******               �����鱾�������                ******\n");
	  printf("\t\t\t******===============================================******\t\t\t\n");
	   printf("\t\t\t******             ��ѡ���鱾�����Ϣ                    ******\n");
	   printf("\n\n");
	   printf("\t\t\t******                   ����ѡ��                        ******\n");
	   printf("\n\n");
	   printf("\t\t\t******            1.�����Ʒ                             ******\n");
	   printf("\t\t\t******            2.�޸���Ʒ                             ******\n");
	   printf("\t\t\t******            3.ɾ����Ʒ                             ******\n");
	   printf("\t\t\t******            4.��ʾ�ܶ�                             ******\n");
	   printf("\t\t\t******            5.֧��                                 ******\n");
	   printf("\t\t\t******            6.�˳�                                 ******\n");
	   printf("\n\n");
	  printf("////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
       do
	    { 
		  scanf("%d",&k);
	      switch(k)
	   {
	  case 1:
                add();
                break;
            case 2:
                cher();
                break;
            case 3:
                remove();
                break;
            case 4:
                show();
                break;
            
	        case 5:
		         pay();
		         break;
	        default:  printf("\t\t\t******             ��������Ϣ��������������            ******\n");
		         break;
	   }
	  }
	  while(k!=6);
	  printf("\t\t\t                         ****��ӭ�´ι���****                      \n");
	  ////////////////////////////////////////�������////////////////////////////////////////////////////
 }
 

 void Main()//����
  {
	   int x;
    do 
	{
	  //system("color 06");
	 printf("\t\t\t      ******========================================================================******\t\t\t\n");
	 printf("\t\t\t    ******      ��ӭ��¼����������ϵͳ            ******\t\t\t\n");
	 printf("\t\t\t    ******          �˷���Ϊ�̼�ģ��                ******\t\t\t\n");
	 printf("\n");
	 printf("            ==========================================================================================\n"); 
	 printf("\n");
	 printf("            ==========================================================================================\n");
	printf("            ==========================================================================================\n");
	 printf("\n");
     printf("\t\t\t******                       ����ѡ��                       ******\n");
	 printf("\n");
     printf("\t\t\t******                  �������ּ�ѡ�����                  ******\n");
	 printf("\n");
	 printf("            ==========================================================================================\n");
	 printf("\n");
	 printf("\t\t\t******                   1��  ͼ��¼��                      ******\n");
	 printf("\n");
	 printf("\t\t\t******                   2��  ͼ����Ϣ��ѯ                  ******\n");
	 printf("\n");
	 printf("\t\t\t******                   3��  �����鱾                      ******\n"); 
	 printf("\n");
	 printf("\t\t\t******                   4��  ͼ��ɾ��                      ******\n"); 
	 printf("\n");
	 printf("\t\t\t******                   5��  ͼ���޸�                      ******\n"); 
	 printf("\n");
	 printf("\t\t\t******                   6��  ͼ�鹺��                      ******\n");
	 printf("\n");
	 printf("\t\t\t******                   7��  �˳�ϵͳ                      ******\n");
	 printf("///////////////////////////////////////////////////////////////////////////////////////////////////////\n");
	  printf("������������ѡ����:");
        fflush(stdin);//������뻺��
        scanf("%d",&x);
        switch(x) 
		{
            case 1:
                Input();//¼��
                break;
            case 2:
               display();//���
                break;
            case 3:
                sch();//��ѯ����������
                break;
            case 4:
                delbook();//ɾ��
                break;
            case 5:
                cge();//�޸�
                break;
            case 6:
				by();//����
				break;
			case 7:
                printf("\n\n�˳�\n\n");
                break;
            default:
                printf("\n��Ų���\n");
                break;
        }
    } while(x!=7);
    save();
   
}


  void Main2()//����
  {
	   int x;
    do 
	{
	  //system("color 06");
	 printf("\t\t\t      ******========================================================================******\t\t\t\n");
	 printf("\t\t\t    ******      ��ӭ��¼����������ϵͳ            ******\t\t\t\n");
	 printf("\t\t\t    ******          �˷���Ϊ�û�ģ��                ******\t\t\t\n");
	 printf("\n");
	 printf("            ==========================================================================================\n"); 
	 printf("\n");
	 printf("            ==========================================================================================\n");
	printf("            ==========================================================================================\n");
	 printf("\n");
     printf("\t\t\t******                       ����ѡ��                       ******\n");
	 printf("\n");
     printf("\t\t\t******                  �������ּ�ѡ�����                  ******\n");
	 printf("\n");
	 printf("            ==========================================================================================\n");
	 printf("\n");
	 printf("\t\t\t******                   1��  ͼ����Ϣ��ѯ                  ******\n");
	 printf("\n");
	 printf("\t\t\t******                   2��  �����鱾                      ******\n");
	 printf("\n");
	 printf("\t\t\t******                   3��  ͼ�鹺��                      ******\n"); 
	 printf("\n");
	 printf("\t\t\t******                   4��  �˳�ϵͳ                      ******\n"); 
	 printf("\n");
	 printf("\n");
	 printf("///////////////////////////////////////////////////////////////////////////////////////////////////////\n");
	  printf("������������ѡ����:");
        fflush(stdin);//������뻺��
        scanf("%d",&x);
        switch(x) 
		{
            case 1:
               display();//���
                break;
            case 2:
                sch();//��ѯ
            case 3:
				by();//����
				break;
			case 4:
                printf("\n\n�˳�\n\n");
                break;
            default:
                printf("\n��Ų���\n");
                break;
        }
    } while(x!=4);
    save();
   
}
     


 //////����Ϊ������/////////////////////////////////////////////////////////
	
 /////////////////////////****main***///////////////////////////
	
 //////////////////////////////////////////////////////////////
	

int main()  //������ 
{                                  
    FILE *fp;
    if((fp=fopen("bookstore.txt","r"))==NULL) 
	{
        printf("���ܴ��ļ���Ϣ��\n");
        fp=fopen("bookstore.txt","w+");
        printf("�����ĵ�����رպ�����\n");
        bookstore.num=0;
        fwrite(&bookstore.num,sizeof(int),1,fp);
        fclose(fp);
    }
    fread(&bookstore.num,sizeof(int),1,fp);
    fread(bookstore.book,sizeof(bookstore.book[0]),bookstore.num,fp);
    fclose(fp);
	logo();
    
}