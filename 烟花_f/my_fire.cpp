#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <Mmsystem.h>		
#pragma comment ( lib, "Winmm.lib" )

/******�궨����*****/
#define NUM 13
#define PI 3.1415926
/*****�ṹ������****/

//�̻��ṹ
struct FIRE{
	int r;		//��ǰ��ը�뾶
	int max_r;	//��ը���ľ����Ե���뾶
	int x , y;			//��������Ǵ��ڵ�����
	int cen_x , cen_y;	//���������ͼƬ������
	int xy[240][240];	//�洢�̻�ͼƬ�����ص��СΪ 240 * 240��

	bool show;	//�Ƿ�����
	bool draw;	//��ʼ������ص�
	DWORD t1 , t2 , dt;//	t2-t1=��t������t ��ȷ�������
};

//�̻����ṹ
struct JET{
	int x,y;			//�̻����������
	int hx,hy;			//�̻�����ߵ�����
	int height;			//height = y - hy;
	bool shoot;			//�ܷ��䣿

	DWORD t1 , t2 , dt;	//t2-t1=��t������t ��ȷ�������
	IMAGE img[2];		//�洢��������ͼƬ
	byte n:1;			//����!
};

/*****�ṹ������*****/

struct FIRE fire[NUM];
struct JET  jet [NUM];

/*****����������*****/
void Welcome(void);		//��ʼ������
void Init(int i);		//��ʼ���̻����̻���
void Load(void);		//����ͼƬ
void Chose(DWORD &t1);	//ɸѡ�̻�
void shoot(void);		//�����̻���
void Show(DWORD *pMem);	//��ը�̻�
void Style(DWORD& st1);	//����

//������
int main()
{
	Welcome();
	Load();

	for(int i = 0 ; i < NUM ; i++){
		Init(i);
	}

	DWORD t1 = timeGetTime();
	DWORD st1 = timeGetTime();
	DWORD *pMem = GetImageBuffer();

	BeginBatchDraw(); 
	while( !kbhit() ){
		Sleep(10);
		for(int clr = 0 ; clr < 1000 ; clr++){
			for(int i = 0 ; i < 2 ; i++){
				int x = rand() % 1200;
				int y = rand() % 800;

				if(y<799){
					pMem[y * 1200 + x] = pMem[y * 1200 + x + 1] = BLACK;
				}
			}
		}
		Chose( t1 );
		shoot();
		Show( pMem );
		Style(st1);
		FlushBatchDraw();
	}

	getchar();
	return 0;
}

//��ʼ�� ���ڣ���MP3����ʾ��Ļ
void Welcome(void)
{
	initgraph(1200,800);
	mciSendString("open ./fire/bk.mp3 alias bk", 0 , 0 , 0);
	mciSendString("play bk repeat", 0 , 0 , 0);
	srand((unsigned)time(NULL));

	for(int i = 0 ; i < 50 ; i++){
		settextstyle(i,0,"����");
		settextcolor(RGB(rand()%255,rand()%255,rand()%255));
		int x = 600+int(180 * sin(2 * PI * i / 60));
		int y = 300+int(180 * cos(2 * PI * i / 60));
		cleardevice();
		outtextxy(x,y,"�̻�");
		outtextxy(x+50,y+50,"��printf(dream)");
		Sleep(25);
	}
	getchar();
	cleardevice();

	settextcolor( RGB(rand()%255 , rand()%555 , rand()%255) );
	settextstyle(60,0,"����");
	outtextxy(400,30,"��������");
	settextstyle(30,0,"����");
	outtextxy(400,100,"ʱ�⴩������ת�ڴ�ǰ���̹ǵı�Ǩ����ңԶ");
	outtextxy(400,130,"����һ���꣬����Ҳ����");
	outtextxy(400,160,"�����һ������");	
	outtextxy(400,190,"��������������������ߣ���������Ϊ����Եǳ");
	outtextxy(400,220,"���ٶȳ��֣��ҿ�������");
	outtextxy(400,250,"��ŵ��ˮ��֮��");
	outtextxy(400,280,"��ͷ����������Զ");	
	outtextxy(400,310,"����Ŀ�� ��������");	
	outtextxy(400,340,"Ҫ��ɢ��ϰ�ߣ���ô�㶼̫��");
	outtextxy(400,370,"�ֿ�֮����¸�");	
	outtextxy(400,400,"�Ȳ�������Ȫ���������̣�ǰ���ٻ�����������");
	outtextxy(400,430,"�����˲�䣬���ٱ�����");	
	outtextxy(400,460,"�������������");
	outtextxy(400,490,"��ͷ����������Զ");	
	outtextxy(400,520,"����һ�� ��������");	
	outtextxy(400,550,"������ߵ����");
	outtextxy(400,580,"���·����Ƶ�");
	outtextxy(400,610,"��ͷ����������Զ");
	outtextxy(400,640,"����Ŀ�� ��������");
	outtextxy(400,670,"Ҫ��ɢ��ϰ�ߣ���ô�㶼̫��");
	outtextxy(400,700,"�ֿ�֮����¸�");
	outtextxy(400,730,"Ը�Ⱞ�����ഫ��");

	getchar();
}

//��ʼ��
void Init(int i)
{
	// �ֱ�Ϊ���̻��İ뾶���̻������ڴ��ڵ����꣬��ͬ����ΪͼƬ�е��̻�Ҳ������ͬ
	int r[13] = { 120, 120, 155, 123, 130, 147, 138, 138, 130, 135, 140, 132, 155 };
	int x[13] = { 120, 120, 110, 117, 110, 93, 102, 102, 110, 105, 100, 108, 110 };
	int y[13] = { 120, 120, 85, 118, 120, 103, 105, 110, 110, 120, 120, 104, 85 };

	//�̻���
	jet[i].x = 0;	//�̻�������ʼ�����
	jet[i].y = 0;
	jet[i].hx = 0;	//�յ�
	jet[i].hy = 0;
	jet[i].height = 0;
	jet[i].shoot = false;//��ʼ��Ϊ����
	jet[i].t1 = timeGetTime();
	jet[i].dt = rand() % 10;
	jet[i].n = 0;

	//�̻�
	fire[i].x = 0;			//�̻��ڴ����еı�ը���ĵ㣬Ϊ�̻������յ�
	fire[i].y = 0;
	fire[i].r = 0;			//����̻��İ뾶��С,������ͬ
	fire[i].max_r = r[i];	//��������ͼƬ���̻���λ��
	fire[i].cen_x = x[i];	//�������ǻ�ȡͼƬ�е��̻�
	fire[i].cen_y = y[i];	//���뵽������
	fire[i].show = false;	//��ʼ��Ϊ���ܷ���
	fire[i].dt = rand() % 5;//����ٶ�

}
 
//�����̻����̻�����ͼƬ
void Load(void)
{
	int i;
	/****�����̻�****/
	IMAGE fm, gm;					//fm��������ͼƬ�� gm�ָ�ͼƬ�е�13���̻�
	loadimage(&fm, "./fire/flower.jpg" , 3120 , 240);//����ͼƬ
	for(i = 0 ; i < NUM ; i++){		//ѭ��13���̻�
		SetWorkingImage(&fm);		//���ò�������
		getimage(&gm , 240 * i , 0 , 240 , 240);	//�ڲ��������ϻ�ȡͼƬ
		SetWorkingImage(&gm);		//���ò�������

		for(int x = 0 ; x < 240 ; x++)
			for(int y = 0 ; y < 240 ; y++)
				fire[i].xy[x][y] = getpixel(x , y);	//ѭ����ȡ���ص�
	}

	/****�����̻���****/
	IMAGE sm;
	loadimage(&sm, "./fire/shoot.jpg" , 200 , 50);
	for(i = 0 ; i < NUM ; i++){
		int x = rand() % 5;//һ��10��ͼƬ 5����ɫ���̻� ��ǰ5�����ģ���5������
		SetWorkingImage(&sm);

		getimage(&jet[i].img[0],     x * 20 , 0 , 20 , 50);//��
		getimage(&jet[i].img[1], (x+5) * 20 , 0 , 20 , 50);//��
	}
	SetWorkingImage(NULL);//���û����ǵ���ʾ����

}

//ɸѡfalse�̻������������ݲ����Ϊtrue
void Chose(DWORD &t1)
{
	DWORD t2 = timeGetTime();

	if(t2 - t1 > 100){

		int n = rand() % 20 ;

		//�̻����̻��������ɷ��䣿
		if(n < NUM && jet[n].shoot == false && fire[n].show == false){

			jet[n].x = rand() % 1200;		//�����������
			jet[n].y = rand() % 100 + 600;	//�����������������Ǳ��봦���·�
			jet[n].hx = jet[n].x;			//�յ����������һ��
			jet[n].hy = rand() % 400;		//�յ������겻��̫����
			jet[n].height = jet[n].y - jet[n].hy;//��֪����ʲô�ã�ɾ��Ҳû��ϵ
			jet[n].shoot = true;			//�����ɷ���ı��Ϊ�ɷ���

			putimage(jet[n].x , jet[n].y , &jet[n].img[ jet[n].n ],SRCINVERT);//���ͼƬ
			//
			char c1[50] , c2[30] , c3[30];

			sprintf(c1,"open ./fire/shoot.mp3 alias s%d",n);
			sprintf(c2,"play s%d",n);
			sprintf(c3,"close s%d",n);

			mciSendString(c3 , 0 , 0 , 0);
			mciSendString(c1 , 0 , 0 , 0);
			mciSendString(c2 , 0 , 0 , 0);
		
		}
		t1 = t2;
	}
}
//�ͷ��̻���
void shoot(void)
{
	int i;

	for(i = 0 ; i < NUM ; i++){

		jet[i].t2 = timeGetTime();

		if(jet[i].t2 - jet[i].t1 > jet[i].dt && jet[i].shoot == true ){

			//����̻���
			putimage(jet[i].x , jet[i].y , &jet[i].img[ jet[i].n ],SRCINVERT);

			//�ı�������λ������
			if(jet[i].y > jet[i].hy){
				jet[i].n++;
				jet[i].y -= 5;
			}
			putimage(jet[i].x , jet[i].y , &jet[i].img[ jet[i].n ],SRCINVERT);

			//�߶ȵ�3/4�ͼ��٣�ʱ����dt���
			if((jet[i].y - jet[i].hy) * 4 < jet[i].height)
			jet[i].dt = rand() % 5 + 10;

			//�������߶�
			if(jet[i].y <= jet[i].hy){
				//
				char c1[50] , c2[30] , c3[30];

				sprintf(c1,"open ./fire/bomb.wav alias s%d",i);
				sprintf(c2,"play s%d",i);
				sprintf(c3,"close s%d",i);

				mciSendString(c3 , 0 , 0 , 0);
				mciSendString(c1 , 0 , 0 , 0);
				mciSendString(c2 , 0 , 0 , 0);
				
				putimage(jet[i].x , jet[i].y , &jet[i].img[ jet[i].n ],SRCINVERT);

				fire[i].x = jet[i].hx;	//�����긳ֵ���̻��ṹ
				fire[i].y = jet[i].hy;	//
				fire[i].show = true ;	//���̻��ṹ�趨Ϊ�ɱ���
				jet[i].shoot = false;	//�����̻����ı���
			}

			jet[i].t1 = jet[i].t2;
		}
	}
}
 
void Show(DWORD *pMem)
{
	//����
	int drt[16] = { 5, 5, 5, 5, 5, 6, 25, 25, 25, 25, 55, 55, 55, 55, 55 };

	int i;
	for(i = 0 ; i < NUM ; i++)
	{

		fire[i].t2 = timeGetTime();

		if(fire[i].t2 - fire[i].t1 > fire[i].dt && fire[i].show == true)
		{
			if(fire[i].r < fire[i].max_r)		//����뾶Ϊ�����
			{
				fire[i].r++;			//����뾶����
				fire[i].draw = true;	//�趨Ϊ��������
				fire[i].dt = drt[fire[i].r / 10];//����
			}

			if(fire[i].r >= fire[i].max_r)		//����뾶�ﵽ���
			{
				fire[i].draw = false;	//�趨Ϊ����������
				Init(i);				//�������ˣ���ʼ�����̻�
			}
		}

		if(fire[i].draw)						//�ܷ����ţ�
		{

			double a;
			for(a = 0 ; a < 6.28 ; a += 0.01)
			{

				int x = (int) (fire[i].cen_x + fire[i].r * cos(a));
				int y = (int) (fire[i].cen_x - fire[i].r * sin(a));
				//���һ������Ȧ�е�һ�����ص㣬ѭ��628�λ����������Ȧ�����ص�ȫ���õ�
				//ÿ�ó�һ�����ص㶼Ҫ��ⷶΧ�Ƿ���ͼƬ����
				//ԲȦ�Ʊ�Ҫ��ͼƬ����Ϊ�����ͺ�Ȧ�����ص�������ɸѡ��Ȧһ��Ҫ�������ʹ�
				//����ͼƬ�е�ĳЩ���ص�Ͳ��ᱻ������ȥ������ԲȦһ������������
				//Բ���������ξ���һ����������Բ���棬Բ�������ط��϶��ǿյĶ�����
				//�������Ǽ�xy��240*240��Χ�ڣ�ֻ��ȡͼƬ�ڵ����ص�
				//cen-x ��cen-y������ͼƬ�����ģ�������Ϊ������240*240ͼƬ�����ſ���ȡ�����ص� 
				if(x > 0 && x < 240 && y > 0 && y < 240)
				{
					int b = fire[i].xy[x][y] & 0xff;
					int r = ( fire[i].xy[x][y] >> 8) & 0xff;
					int g = ( fire[i].xy[x][y] >> 16);
					//��ȡ���ص����ԭɫ�������ص����ɫ

					int xx = (int) (fire[i].x + fire[i].r * cos(a));
					int yy = (int) (fire[i].y - fire[i].r * sin(a));
					//��xy�Ѿ����̻�����hx��hy��ֵ�ˣ����̻�����ʧ�ĵط���ʼ��ը
					//�������Ϊ���ģ���ÿ��ѭ����õ�һ�������ص�һ������д����
					//�������Ϊ���ģ������ȡ���ص�һ��һȦȦ���ſ���
					//ͼƬ���Ļ�õ�ÿһȦ�����ص� ��ʾ��xyΪ����������Ļ��


					//    ��νϰ������ص㲻���        ||         ��η�ֹԽ��
					if(b > 0x20 && r > 0x20 && g > 0x20 && xx > 0 && xx < 1200 && yy > 0 && yy < 800)
					{
						pMem[yy * 1200 + xx] = BGR(fire[i].xy[x][y]);//�������
					}
				}
			}
			fire[i].draw = false;
		}
	}
}

// ��ʾ����
void Style(DWORD& st1)
{
	DWORD st2 = timeGetTime();

	if (st2 - st1 > 20000)		// һ�׸��ʱ��
	{
		// ��������
		int x[13] = { 60, 75, 91, 100, 95, 75, 60, 45, 25, 15, 25, 41, 60 };
		int y[13] = { 65, 53, 40, 22, 5, 4, 20, 4, 5, 22, 40, 53, 65 };

		int i;
		for (i = 0; i < NUM; i++)
		{
			//cleardevice();
			/**** ���ɷֲ��̻��� ***/
			jet[i].x = x[i] * 10;
			jet[i].y = (y[i] + 75) * 10;
			jet[i].hx = jet[i].x;
			jet[i].hy = y[i] * 10;
			jet[i].height = jet[i].y - jet[i].hy;
			jet[i].shoot = true;
			jet[i].dt = 7;
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);	// ��ʾ�̻���

			/**** �����̻����� ***/
			fire[i].x = jet[i].x + 10;
			fire[i].y = jet[i].hy;
			fire[i].show = false;
			fire[i].r = 0;

			/**** ���ŷ������� ***/
	//
			char c1[50], c2[30], c3[30];
			sprintf(c1, "open ./fire/shoot.mp3 alias s%d", i);
			sprintf(c2, "play s%d", i);
			sprintf(c3, "close n%d", i);

			mciSendString(c3, 0, 0, 0);
			mciSendString(c1, 0, 0, 0);
			mciSendString(c2, 0, 0, 0);
		//
		}
		st1 = st2;
	}
}

