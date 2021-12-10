// 网上书店管理系统.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
    char number[10];//编号
    char name[20];//书名
    char author[20];//作者
    char information[100];//相关信息
    char publish[50];//出版社
	char knum[100];//库存
    float price;//价格
} newbook;
typedef struct node1
{
    int num;  //图书数 
    newbook book[100]; //最大可录入的图书数                                   
} books;
books bookstore;
typedef struct node2//用户购买结构体
{
	int code;//编号
	char name[20];//书名
	float price;//价格
	int bnum;//购买图书数
	float bprice;//购买图书价格
} bbuy;
bbuy goods[20];

void Main();//声明主函数界面
void Main2();//声明主函数界面
void input();//声明导入函数
void Input();//声明导入函数界面
void search();//声明查询
void sch();//书名查询界面
void del();//声明删除
void delbook();//声明删除界面
void save(); //声明保存函数
void regist();//声明注册
void login();//声明登录
void by();//声明购买
void pay();//声明支付
void print();//声明界面
void print2();//声明界面

void save() //保存图书信息
{                                          
    FILE *fp;
    if((fp=fopen("book.txt","w"))==NULL)
	{
        printf("保存图书失败\n");
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
	printf("\t\t*****模式选择界面*****\n");
	printf("\t\t      1.注册          \n");
	printf("\t\t      2.商家登录      \n");
	printf("\t\t      3.用户登录      \n");
	printf("\t\t      4.退出          \n");
	scanf("%d",&i);
	switch(i)
	{
	case 1: regist();
		    break;
	case 2: print();
		    break;
	case 3:print2();
		    break;
    case 4: printf("\n\n退出\n\n");
                break;
            default:
                printf("\n序号不对\n");
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
    printf("\t\t登录界面\n");
    printf("请输入账号:\n");
    gets(name);
    printf("请输入密码:\n");
    gets(pas);
    strcat(name,pas);//合并字符
    strcat(name,"\n");//添加换行字符 
    int len = 0;
    FILE *fp= fopen("user.txt", "r");
    if(NULL == fp)
    {
        printf("打开失败\n");
        return ;
    }

    while(!feof(fp))
    {
        memset(textstring, 0, sizeof(textstring));
        fgets(textstring, sizeof(textstring) - 1, fp); // 包含了\n
        if(strcmp(name,textstring)==0)//判断字符是否相等
		{
           ok=1;
           break;
        }
    }
    if(ok==1)
	{
      printf("登录OK\n");
	  Main();
	}
    else
      printf("登录失败\n");
    fclose(fp);

}

void login2()
{
	printf("\t\t登录界面\n");
    printf("请输入账号:\n");
    gets(name);
    printf("请输入密码:\n");
    gets(pas);
    strcat(name,pas);//合并字符
    strcat(name,"\n");//添加换行字符 
    int len = 0;
    FILE *fp= fopen("user.txt", "r");
    if(NULL == fp)
    {
        printf("打开失败\n");
        return ;
    }

    while(!feof(fp))
    {
        memset(textstring, 0, sizeof(textstring));
        fgets(textstring, sizeof(textstring) - 1, fp); // 包含了\n
        if(strcmp(name,textstring)==0)//判断字符是否相等
		{
           ok=1;
           break;
        }
    }
    if(ok==1)
	{
      printf("登录OK\n");
	  Main2();
	}
    else
      printf("登录失败\n");
    fclose(fp);

}

void print()
{
	FILE *fp;
	int i;
	do
	{
	system("color 06");
    printf("\n\t\t1.注册 2.阅读使用说明 3.登录\n");
	scanf("%d",&i);
	if(i==2)
        {
			if((fp=fopen("使用说明.txt","r"))==NULL)
                {
                printf("\n\t\t打开失败");
                exit(0);
                }
                fread("使用说明.txt",2,20,fp);
                printf("\n\t\t%s","使用说明.txt");
               
        }
	else if(i==1)
    regist();//注册
	else if(i==3)
	  login();//登录
	  }while(strcmp(pas,temp)!=0); 
}

void print2()
{
	FILE *fp;
	int i;
	do
	{
	system("color 06");
    printf("\n\t\t1.注册 2.阅读使用说明 3.登录\n");
	scanf("%d",&i);
	if(i==2)
        {
			if((fp=fopen("使用说明.txt","r"))==NULL)
                {
                printf("\n\t\t打开失败");
                exit(0);
                }
                fread("使用说明.txt",2,20,fp);
                printf("\n\t\t%s","使用说明.txt");
               
        }
	else if(i==1)
    regist();//注册
	else if(i==3)
	  login2();//登录
	  }while(strcmp(pas,temp)!=0); 

}

void regist()//注册
{
    FILE *fp=fopen("user.txt","a");
    printf("请输入账号:");
	scanf("%s",name);
    printf("请输入密码:");
	scanf("%s",pas);
	printf("确认密码:");
	scanf("%s",temp);
    fputs(name,fp);
    fputs(pas,fp);//将名称和密码以字符串形式写入文件
    fputs("\n",fp);
    fflush(stdin);//清除缓存
    fclose(fp);
    login();
}

int dl()//调用注册登录
{
    print();
    int settle=0;
     scanf("%d",&settle);
     fflush(stdin);//清除缓存
    if(settle)
       regist();
    else
        login();
    return 0;
}

void input()//图书录入
{   
    system("cls");
	int t=1;
    bookstore.num=0;
    while(t)
	{
        printf("输入图书编号:");
        scanf("%s",bookstore.book[bookstore.num].number);
        printf("\n输入图书名称:");
        scanf("%s",bookstore.book[bookstore.num].name);
        printf("\n输入图书的作者:");
        scanf("%s",bookstore.book[bookstore.num].author);
        printf("\n请输入图书相关信息:");
        scanf("%s",bookstore.book[bookstore.num].information);
        printf("\n请输入出版社：");
        scanf("%s",bookstore.book[bookstore.num].publish);
		printf("\n请输入库存:");
		scanf("%s",bookstore.book[bookstore.num].knum);
        fflush(stdin);
        printf("\n请输入图书价格：");
        scanf("%f",&bookstore.book[bookstore.num].price);
        bookstore.num++;//实际数比此数少1 
	    printf("\n是否继续输入图书信息(1:是；0：否):");
        scanf("%d",&t);
		if(t==0)
			printf("\n请输入‘2’返回主菜单：");
	}
      save();          
 }
    
void Input()//录入界面
  { 
	  system("cls");
	  int k;
	   ////////////////////////////////////////界面开始////////////////////////////////////////////////////
     printf("////////////////////////////////////////////////////////////////////////////////////////////////////////");
	  printf("\n\n");
	  printf("\t\t\t******               进入书本数据导入界面                ******\n");
	  printf("\n\n");
	  printf("\t\t\t******===================================================******\t\t\t\n");
	
	   printf("\t\t\t******             请输入书本相关信息                    ******\n");
	   printf("\n\n");
	   printf("\t\t\t******                   操作选项                        ******\n");
	   printf("\n\n");
	   printf("\t\t\t******            是否继续输入？1：是；2：否             ******\n");
	   printf("\n\n");
	  printf("////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
       do
	    { 
		  scanf_s("%d",&k);
	      switch(k)
	   {
	   case 1: input();
		   break;
	   case 2:  printf("\t\t\t******             本次输入结束，谢谢使用！              ******\n");
		  return Main();
	    default:  printf("\t\t\t******             您输入信息有误！请重新输入            ******\n");
		    break;
	   }
	  }
	  while(k!=0);
	  printf("\t\t\t                         ****欢迎下次光临****                      \n");
	  ////////////////////////////////////////界面结束////////////////////////////////////////////////////*/
	  }  



void display()//显示全部图书信息
{                                            
    system("cls");
    printf("编号\t书名\t作者\t相关信息\t出版社\t库存\t价格\n");
    fflush(stdin);// 清空输入缓冲区
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
void search()  //图书查询
{                                        
    system("cls");
    fflush(stdin);
    int l;
    char c[20];
    printf("请输入要查找的书名:\n");
    gets(c);
    for(l=0; l<bookstore.num; l++) 
	{
        if(strcmp(c,bookstore.book[l].name)==0) 
		{
            printf("编号\t书名\t作者\t相关信息\t出版社\t库存\t价格\n");
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
        printf("没有此图书\n");
    fflush(stdin);
    getchar();
	printf("\n请输入‘2’返回主菜单：");
}

void sch()//查找界面
 {
	 system("cls");
	 int k;
	   ////////////////////////////////////////界面开始////////////////////////////////////////////////////
     printf("////////////////////////////////////////////////////////////////////////////////////////////////////////");
	  printf("\n\n");
	  printf("\t\t\t******               进入书本查找界面                ******\n");
	  printf("\n\n");
	  printf("\t\t\t******================================================******\t\t\t\n");
	
	   printf("\t\t\t******             请选择书本所需查找信息                ******\n");
	   printf("\n\n");
	   printf("\t\t\t******                   操作选项                        ******\n");
	   printf("\n\n");
	   printf("\t\t\t******            是否继续？1：是；2：否             ******\n");
	   printf("\n\n");
	  printf("////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
       do
	    {
		  scanf("%d",&k);
	      switch(k)
	   {
	   case 1: search();
		   break;
	   case 2:  printf("\t\t\t******             本次输入结束，谢谢使用！              ******\n");
		  return Main();
	    default:  printf("\t\t\t******             您输入信息有误！请重新输入            ******\n");
		   break;
	   }
	  }
	  while(k!=0);
	  printf("\t\t\t                         ****欢迎下次光临****                      \n");
	  ////////////////////////////////////////界面结束////////////////////////////////////////////////////
 }


void del() //图书删除
{                                           
    system("cls");
    fflush(stdin);
	display();
    int l;
    char c[10];
    printf("请输入要删除的书名:\n");
    gets(c);
    for(l=0; l<bookstore.num; l++)
	{
        if(strcmp(c,bookstore.book[l].name)==0)
            break;
    }
    if(l==bookstore.num)
        printf("无此图书\n");
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
        printf("\n按0退出"); 
    fflush(stdin);
    save();
    getchar();
}

void delbook()//书本删除界面
    {
		system("cls");
		int k;
	   ////////////////////////////////////////界面开始////////////////////////////////////////////////////
     printf("////////////////////////////////////////////////////////////////////////////////////////////////////////");
	  printf("\n\n");
	  printf("\t\t\t******               进入书本数据删除界面                ******\n");
	  printf("\n\n");
	  printf("\t\t\t******===================================================******\t\t\t\n");
	
	   printf("\t\t\t******             请选择书本相关信息                    ******\n");
	   printf("\n\n");
	   printf("\t\t\t******                   操作选项                        ******\n");
	   printf("\n\t\t\t******                 是否读取文件：                    ******\n");
	   printf("\n\t\t\t******                 1：是；2：否                      ******\n");
	   printf("\n\n");
	  printf("////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
       do
	    { 
		  scanf("%d",&k);
	      switch(k)
	   {
	   case 1: del();
		   break;
	   case 2:  printf("\t\t\t******             本次输入结束，谢谢使用！              ******\n");
		  return Main();
	    default:  printf("\t\t\t******             您输入信息有误！请重新输入            ******\n");
		   break;
	   }
	  }
	  while(k!=0);
	  printf("\t\t\t                         ****欢迎下次光临****                      \n");
	  ////////////////////////////////////////界面结束////////////////////////////////////////////////////
	  }  


void change() //图书修改
{                                 
    system("cls");
    fflush(stdin);
    int l;
    char c[10];
    printf("请输入要修改的书名-_-:\n");
    gets(c);
    for(l=0; l<bookstore.num; l++)
        if(strcmp(c,bookstore.book[l].name)==0)
            break;
    if(l==bookstore.num)
        printf("没有该图书\n");
    else {
        printf("请输入修改后的图书编号：");
        scanf("%s",bookstore.book[l].number);
        printf("\n请输入修改后的图书书名：");
        scanf("%s",bookstore.book[l].name);
        printf("\n 请输入修改后的作者：");
        scanf("%s",bookstore.book[l].author);
        printf("\n 请输入修改后的相关信息：");
        scanf("%s",bookstore.book[l].information);
        printf("\n 请输入修改后的出版社：");
        scanf("%s",bookstore.book[l].publish);
        printf("\n请输入修改后的出版库存：");
        scanf("%s",bookstore.book[l].knum);
        fflush(stdin);
        printf("\n请输入修改后的图书价格：");
        scanf("%f",&bookstore.book[l].price);
    }
    fflush(stdin);
    save();
}

void cge()//修改界面
 {
	 system("cls");
	 int k;
	   ////////////////////////////////////////界面开始////////////////////////////////////////////////////
     printf("////////////////////////////////////////////////////////////////////////////////////////////////////////");
	  printf("\n\n");
	  printf("\t\t\t******               进入书本数据修改界面                ******\n");
	  printf("\n\n");
	  printf("\t\t\t******===================================================******\t\t\t\n");
	  printf("\t\t\t******             请选择书本相关信息                    ******\n");
	  printf("\n\n");
	  printf("\t\t\t******                   操作选项                        ******\n");
	  printf("\n\n");
	  printf("\t\t\t******            是否继续？1：是；2：否             ******\n");
	  printf("\n\n");
	  printf("////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
       do
	    { 
		  scanf_s("%d",&k);
	      switch(k)
	   {
	   case 1: change();
		   break;
	   case 2:  printf("\t\t\t******             本次输入结束，谢谢使用！              ******\n");
		  return Main();
	    default:  printf("\t\t\t******             您输入信息有误！请重新输入            ******\n");
		   break;
	   }
	  }
	  while(k!=0);
	  printf("\t\t\t                         ****欢迎下次光临****                      \n");
	  ////////////////////////////////////////界面结束////////////////////////////////////////////////////
 }

int n=10;

void add()//添加到购物车
{
    display();
    int code = 0,number = 0;
    printf("请输入书本编号\n");
    scanf("%d",&code);
    printf("请输入该书本购买数量\n");
    scanf("%d",&number);
    int flag = 0;
    for(int i = 0;i < n;i++) 
	{
        if (goods[i].code == code) 
		{
            goods[i].bnum +=number;
            flag = 1;
            printf("添加成功！\n");
            break;
        }
    }
    if (flag == 0) 
	{
        printf("没有该书\n");
    }
}

void cher()//修改列表
{
    int code = 0,number = 0;
    printf("请输入书本编号\n");
    scanf("%d",&code);
    printf("请输入该书本购买数量\n");
    scanf("%d",&number);
    int flag = 0;
    for(int i = 0;i < n;i++)  //循环查找
	{
        if (goods[i].code == code && goods[i].bnum > 0) 
		{
            goods[i].bnum -=number;
            flag = 1;
            printf("修改成功！\n");
            break;
        }
    }
    if (flag == 0) 
	{
        printf("没有加入购物车\n");
    }
}

void remove()//删除商品列表
{
    int code = 0,number = 0;
    printf("请输入书本编号\n");
    scanf("%d",&code);
    printf("请输入该书本购买数量\n");
    scanf("%d",&number);
    int flag = 0;
    for(int i = 0;i < n;i++)
	{
        if (goods[i].code == code&&goods[i].bnum > 0) 
		{
            goods[i].bnum = 0;
            flag = 1;
            printf("删除成功！\n");
            break;
        }
    }
    if (flag == 0)
	{
        printf("没有该书\n");
    }
}

void show()//显示总额
{
    printf("*********当前购物车的商品*****");
    double sum = 0;
    for (int i = 0; i < n; i++)
	{
        if (goods[i].bnum > 0)
		{
            printf("%d\t%s\t%.2lf\t\t%d\t\t%lf\n",goods[i].code,goods[i].name,goods[i].price,goods[i].bnum,goods[i].bprice);
            sum += goods[i].bprice;
        }
    }
    printf("当前总额为%.2f\n",sum);
	pay();
	printf("本次共消费:%.2f元\n",sum);

}

void pay()//用户购买支付
{
		int i ;
		printf("是否支付：1.是，2.否");
		scanf("%d",&i);
		if(i==1)
		printf("支付成功！");
		else by();
	}

 void by()//购买界面
 {
	 system("cls");
	 int k;
	   ////////////////////////////////////////界面开始////////////////////////////////////////////////////
     printf("////////////////////////////////////////////////////////////////////////////////////////////////////////");
	  printf("\n\n");
	  printf("\t\t\t******               进入书本购买界面                ******\n");
	  printf("\t\t\t******===============================================******\t\t\t\n");
	   printf("\t\t\t******             请选择书本相关信息                    ******\n");
	   printf("\n\n");
	   printf("\t\t\t******                   操作选项                        ******\n");
	   printf("\n\n");
	   printf("\t\t\t******            1.添加商品                             ******\n");
	   printf("\t\t\t******            2.修改商品                             ******\n");
	   printf("\t\t\t******            3.删除商品                             ******\n");
	   printf("\t\t\t******            4.显示总额                             ******\n");
	   printf("\t\t\t******            5.支付                                 ******\n");
	   printf("\t\t\t******            6.退出                                 ******\n");
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
	        default:  printf("\t\t\t******             您输入信息有误！请重新输入            ******\n");
		         break;
	   }
	  }
	  while(k!=6);
	  printf("\t\t\t                         ****欢迎下次光临****                      \n");
	  ////////////////////////////////////////界面结束////////////////////////////////////////////////////
 }
 

 void Main()//界面
  {
	   int x;
    do 
	{
	  //system("color 06");
	 printf("\t\t\t      ******========================================================================******\t\t\t\n");
	 printf("\t\t\t    ******      欢迎登录网上书店管理系统            ******\t\t\t\n");
	 printf("\t\t\t    ******          此分区为商家模块                ******\t\t\t\n");
	 printf("\n");
	 printf("            ==========================================================================================\n"); 
	 printf("\n");
	 printf("            ==========================================================================================\n");
	printf("            ==========================================================================================\n");
	 printf("\n");
     printf("\t\t\t******                       操作选项                       ******\n");
	 printf("\n");
     printf("\t\t\t******                  请用数字键选择操作                  ******\n");
	 printf("\n");
	 printf("            ==========================================================================================\n");
	 printf("\n");
	 printf("\t\t\t******                   1：  图书录入                      ******\n");
	 printf("\n");
	 printf("\t\t\t******                   2：  图书信息查询                  ******\n");
	 printf("\n");
	 printf("\t\t\t******                   3：  搜索书本                      ******\n"); 
	 printf("\n");
	 printf("\t\t\t******                   4：  图书删除                      ******\n"); 
	 printf("\n");
	 printf("\t\t\t******                   5：  图书修改                      ******\n"); 
	 printf("\n");
	 printf("\t\t\t******                   6：  图书购买                      ******\n");
	 printf("\n");
	 printf("\t\t\t******                   7：  退出系统                      ******\n");
	 printf("///////////////////////////////////////////////////////////////////////////////////////////////////////\n");
	  printf("请输入数字以选择功能:");
        fflush(stdin);//清除输入缓存
        scanf("%d",&x);
        switch(x) 
		{
            case 1:
                Input();//录入
                break;
            case 2:
               display();//浏览
                break;
            case 3:
                sch();//查询（按书名）
                break;
            case 4:
                delbook();//删除
                break;
            case 5:
                cge();//修改
                break;
            case 6:
				by();//购买
				break;
			case 7:
                printf("\n\n退出\n\n");
                break;
            default:
                printf("\n序号不对\n");
                break;
        }
    } while(x!=7);
    save();
   
}


  void Main2()//界面
  {
	   int x;
    do 
	{
	  //system("color 06");
	 printf("\t\t\t      ******========================================================================******\t\t\t\n");
	 printf("\t\t\t    ******      欢迎登录网上书店管理系统            ******\t\t\t\n");
	 printf("\t\t\t    ******          此分区为用户模块                ******\t\t\t\n");
	 printf("\n");
	 printf("            ==========================================================================================\n"); 
	 printf("\n");
	 printf("            ==========================================================================================\n");
	printf("            ==========================================================================================\n");
	 printf("\n");
     printf("\t\t\t******                       操作选项                       ******\n");
	 printf("\n");
     printf("\t\t\t******                  请用数字键选择操作                  ******\n");
	 printf("\n");
	 printf("            ==========================================================================================\n");
	 printf("\n");
	 printf("\t\t\t******                   1：  图书信息查询                  ******\n");
	 printf("\n");
	 printf("\t\t\t******                   2：  搜索书本                      ******\n");
	 printf("\n");
	 printf("\t\t\t******                   3：  图书购买                      ******\n"); 
	 printf("\n");
	 printf("\t\t\t******                   4：  退出系统                      ******\n"); 
	 printf("\n");
	 printf("\n");
	 printf("///////////////////////////////////////////////////////////////////////////////////////////////////////\n");
	  printf("请输入数字以选择功能:");
        fflush(stdin);//清除输入缓存
        scanf("%d",&x);
        switch(x) 
		{
            case 1:
               display();//浏览
                break;
            case 2:
                sch();//查询
            case 3:
				by();//购买
				break;
			case 4:
                printf("\n\n退出\n\n");
                break;
            default:
                printf("\n序号不对\n");
                break;
        }
    } while(x!=4);
    save();
   
}
     


 //////以下为主函数/////////////////////////////////////////////////////////
	
 /////////////////////////****main***///////////////////////////
	
 //////////////////////////////////////////////////////////////
	

int main()  //主函数 
{                                  
    FILE *fp;
    if((fp=fopen("bookstore.txt","r"))==NULL) 
	{
        printf("不能打开文件信息库\n");
        fp=fopen("bookstore.txt","w+");
        printf("创建文档，请关闭后重启\n");
        bookstore.num=0;
        fwrite(&bookstore.num,sizeof(int),1,fp);
        fclose(fp);
    }
    fread(&bookstore.num,sizeof(int),1,fp);
    fread(bookstore.book,sizeof(bookstore.book[0]),bookstore.num,fp);
    fclose(fp);
	logo();
    
}
