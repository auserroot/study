// 登录注册.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"




#include <stdio.h>
#include <string.h>
char name[80] ,pas[80],temp[80];
char textstring[80];
int ok=0;
void login(){
    printf("登录界面\n");
    printf("请输入账号");
    gets(name);
    printf("请输入密码");
    gets(pas); /*输入名称和密码*/
    strcat(name,pas);//合并字符
    strcat(name,"\n");//添加换行字符
     int len = 0;

    FILE *fp = fopen("user.txt", "r");
    if(NULL == fp)
    {
        printf("failed to open dos.txt\n");
        return ;
    }

    while(!feof(fp))
    {
        memset(textstring, 0, sizeof(textstring));
        fgets(textstring, sizeof(textstring) - 1, fp); // 包含了\n
        if(strcmp(name,textstring)==0){//判断字符是否相等
           ok=1;
           break;
        }
    }
    if(ok)
      printf("登录OK");
    else
      printf("登录失败");
    fclose(fp);

}
void print() {
    printf("   _______________________________________\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |                请选择                |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |         我已注册过——请按 0         |\n");
    printf("   |                                      |\n");
    printf("   |         我是新用户——请按 1         |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |______________________________________|\n");
     printf("请输入");
}
void regist(){
    FILE *fp=fopen("user.txt","a");/*以写模式("w")打开文件user.txt,如果不存在,会自动创建*/
    printf("请输入账号");
    gets(name);
    printf("请输入密码");
    gets(pas); /*输入名称和密码*/
    fputs(name,fp);
    fputs(pas,fp);/*将名称和密码以字符串形式写入文件*/
    fputs("\n",fp);
    fflush(stdin);//清除缓存
    fclose(fp);/*关闭文件*/
    login();//注册完转到登录界面
}
int main()
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