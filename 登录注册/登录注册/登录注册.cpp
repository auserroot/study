// ��¼ע��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"




#include <stdio.h>
#include <string.h>
char name[80] ,pas[80],temp[80];
char textstring[80];
int ok=0;
void login(){
    printf("��¼����\n");
    printf("�������˺�");
    gets(name);
    printf("����������");
    gets(pas); /*�������ƺ�����*/
    strcat(name,pas);//�ϲ��ַ�
    strcat(name,"\n");//��ӻ����ַ�
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
        fgets(textstring, sizeof(textstring) - 1, fp); // ������\n
        if(strcmp(name,textstring)==0){//�ж��ַ��Ƿ����
           ok=1;
           break;
        }
    }
    if(ok)
      printf("��¼OK");
    else
      printf("��¼ʧ��");
    fclose(fp);

}
void print() {
    printf("   _______________________________________\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |                ��ѡ��                |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |         ����ע��������밴 0         |\n");
    printf("   |                                      |\n");
    printf("   |         �������û������밴 1         |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |______________________________________|\n");
     printf("������");
}
void regist(){
    FILE *fp=fopen("user.txt","a");/*��дģʽ("w")���ļ�user.txt,���������,���Զ�����*/
    printf("�������˺�");
    gets(name);
    printf("����������");
    gets(pas); /*�������ƺ�����*/
    fputs(name,fp);
    fputs(pas,fp);/*�����ƺ��������ַ�����ʽд���ļ�*/
    fputs("\n",fp);
    fflush(stdin);//�������
    fclose(fp);/*�ر��ļ�*/
    login();//ע����ת����¼����
}
int main()
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