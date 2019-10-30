#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <Mmsystem.h>		
#pragma comment ( lib, "Winmm.lib" )

/******宏定义区*****/
#define NUM 13
#define PI 3.1415926
/*****结构定义区****/

//烟花结构
struct FIRE{
	int r;		//当前爆炸半径
	int max_r;	//爆炸中心距离边缘最大半径
	int x , y;			//这个坐标是窗口的坐标
	int cen_x , cen_y;	//这个坐标是图片的坐标
	int xy[240][240];	//存储烟花图片的像素点大小为 240 * 240；

	bool show;	//是否绽放
	bool draw;	//开始输出像素点
	DWORD t1 , t2 , dt;//	t2-t1=△t；（△t 是确定间隔）
};

//烟花弹结构
struct JET{
	int x,y;			//烟花弹起点坐标
	int hx,hy;			//烟花弹最高点坐标
	int height;			//height = y - hy;
	bool shoot;			//能否发射？

	DWORD t1 , t2 , dt;	//t2-t1=△t；（△t 是确定间隔）
	IMAGE img[2];		//存储明暗两张图片
	byte n:1;			//不懂!
};

/*****结构声明区*****/

struct FIRE fire[NUM];
struct JET  jet [NUM];

/*****函数申明区*****/
void Welcome(void);		//初始化界面
void Init(int i);		//初始化烟花，烟花弹
void Load(void);		//加载图片
void Chose(DWORD &t1);	//筛选烟花
void shoot(void);		//发射烟花弹
void Show(DWORD *pMem);	//爆炸烟花
void Style(DWORD& st1);	//心形

//主函数
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

//初始化 窗口，打开MP3，显示字幕
void Welcome(void)
{
	initgraph(1200,800);
	mciSendString("open ./fire/bk.mp3 alias bk", 0 , 0 , 0);
	mciSendString("play bk repeat", 0 , 0 , 0);
	srand((unsigned)time(NULL));

	for(int i = 0 ; i < 50 ; i++){
		settextstyle(i,0,"楷体");
		settextcolor(RGB(rand()%255,rand()%255,rand()%255));
		int x = 600+int(180 * sin(2 * PI * i / 60));
		int y = 300+int(180 * cos(2 * PI * i / 60));
		cleardevice();
		outtextxy(x,y,"烟花");
		outtextxy(x+50,y+50,"—printf(dream)");
		Sleep(25);
	}
	getchar();
	cleardevice();

	settextcolor( RGB(rand()%255 , rand()%555 , rand()%255) );
	settextstyle(60,0,"楷体");
	outtextxy(400,30,"此生不换");
	settextstyle(30,0,"楷体");
	outtextxy(400,100,"时光穿不断流转在从前，刻骨的变迁不是遥远");
	outtextxy(400,130,"再有一万年，深情也不变");
	outtextxy(400,160,"爱像烈火般蔓延");	
	outtextxy(400,190,"记忆是条长线盘旋在天边，沉浮中以为情深缘浅");
	outtextxy(400,220,"你再度出现，我看见誓言");
	outtextxy(400,250,"承诺在水天之间");
	outtextxy(400,280,"回头看，不曾走远");	
	outtextxy(400,310,"依依目光 此生不换");	
	outtextxy(400,340,"要分散不习惯，怎么算都太难");
	outtextxy(400,370,"分开之后更勇敢");	
	outtextxy(400,400,"喝不完忘情泉不让你如烟，前尘再怀恋望剑如面");
	outtextxy(400,430,"挥舞的瞬间，别再闭上眼");	
	outtextxy(400,460,"错过惊世的依恋");
	outtextxy(400,490,"回头看，不曾走远");	
	outtextxy(400,520,"眷恋一人 流连忘返");	
	outtextxy(400,550,"听清耳边的呢喃");
	outtextxy(400,580,"别害怕风轻云淡");
	outtextxy(400,610,"回头看，不曾走远");
	outtextxy(400,640,"依依目光 此生不换");
	outtextxy(400,670,"要分散不习惯，怎么算都太难");
	outtextxy(400,700,"分开之后更勇敢");
	outtextxy(400,730,"愿这爱世代相传。");

	getchar();
}

//初始化
void Init(int i)
{
	// 分别为：烟花的半径、烟花中心在窗口的坐标，不同是因为图片中的烟花也各不相同
	int r[13] = { 120, 120, 155, 123, 130, 147, 138, 138, 130, 135, 140, 132, 155 };
	int x[13] = { 120, 120, 110, 117, 110, 93, 102, 102, 110, 105, 100, 108, 110 };
	int y[13] = { 120, 120, 85, 118, 120, 103, 105, 110, 110, 120, 120, 104, 85 };

	//烟花弹
	jet[i].x = 0;	//烟花弹的起始发射点
	jet[i].y = 0;
	jet[i].hx = 0;	//终点
	jet[i].hy = 0;
	jet[i].height = 0;
	jet[i].shoot = false;//初始化为发射
	jet[i].t1 = timeGetTime();
	jet[i].dt = rand() % 10;
	jet[i].n = 0;

	//烟花
	fire[i].x = 0;			//烟花在窗口中的爆炸中心点，为烟花弹的终点
	fire[i].y = 0;
	fire[i].r = 0;			//这个烟花的半径大小,各不相同
	fire[i].max_r = r[i];	//这三个是图片中烟花的位置
	fire[i].cen_x = x[i];	//根据他们获取图片中的烟花
	fire[i].cen_y = y[i];	//导入到程序中
	fire[i].show = false;	//初始化为不能发射
	fire[i].dt = rand() % 5;//随机速度

}
 
//加载烟花和烟花弹的图片
void Load(void)
{
	int i;
	/****加载烟花****/
	IMAGE fm, gm;					//fm加载整张图片， gm分割图片中的13个烟花
	loadimage(&fm, "./fire/flower.jpg" , 3120 , 240);//加载图片
	for(i = 0 ; i < NUM ; i++){		//循环13张烟花
		SetWorkingImage(&fm);		//设置操作对象
		getimage(&gm , 240 * i , 0 , 240 , 240);	//在操作对象上获取图片
		SetWorkingImage(&gm);		//设置操作对象

		for(int x = 0 ; x < 240 ; x++)
			for(int y = 0 ; y < 240 ; y++)
				fire[i].xy[x][y] = getpixel(x , y);	//循环获取像素点
	}

	/****加载烟花弹****/
	IMAGE sm;
	loadimage(&sm, "./fire/shoot.jpg" , 200 , 50);
	for(i = 0 ; i < NUM ; i++){
		int x = rand() % 5;//一共10张图片 5种颜色的烟花 ，前5个暗的，后5个亮的
		SetWorkingImage(&sm);

		getimage(&jet[i].img[0],     x * 20 , 0 , 20 , 50);//暗
		getimage(&jet[i].img[1], (x+5) * 20 , 0 , 20 , 50);//明
	}
	SetWorkingImage(NULL);//设置回我们的显示窗口

}

//筛选false烟花，重置其内容并标记为true
void Chose(DWORD &t1)
{
	DWORD t2 = timeGetTime();

	if(t2 - t1 > 100){

		int n = rand() % 20 ;

		//烟花和烟花弹都不可发射？
		if(n < NUM && jet[n].shoot == false && fire[n].show == false){

			jet[n].x = rand() % 1200;		//起点横坐标随机
			jet[n].y = rand() % 100 + 600;	//起点纵坐标随机，但是必须处在下方
			jet[n].hx = jet[n].x;			//终点横坐标和起点一样
			jet[n].hy = rand() % 400;		//终点纵坐标不能太下面
			jet[n].height = jet[n].y - jet[n].hy;//不知道有什么用，删了也没关系
			jet[n].shoot = true;			//将不可发射的标记为可发射

			putimage(jet[n].x , jet[n].y , &jet[n].img[ jet[n].n ],SRCINVERT);//输出图片
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
//释放烟花弹
void shoot(void)
{
	int i;

	for(i = 0 ; i < NUM ; i++){

		jet[i].t2 = timeGetTime();

		if(jet[i].t2 - jet[i].t1 > jet[i].dt && jet[i].shoot == true ){

			//输出烟花弹
			putimage(jet[i].x , jet[i].y , &jet[i].img[ jet[i].n ],SRCINVERT);

			//改变明暗，位置上升
			if(jet[i].y > jet[i].hy){
				jet[i].n++;
				jet[i].y -= 5;
			}
			putimage(jet[i].x , jet[i].y , &jet[i].img[ jet[i].n ],SRCINVERT);

			//高度到3/4就减速，时间间隔dt变大
			if((jet[i].y - jet[i].hy) * 4 < jet[i].height)
			jet[i].dt = rand() % 5 + 10;

			//到达最大高度
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

				fire[i].x = jet[i].hx;	//把坐标赋值给烟花结构
				fire[i].y = jet[i].hy;	//
				fire[i].show = true ;	//将烟花结构设定为可表演
				jet[i].shoot = false;	//结束烟花弹的表演
			}

			jet[i].t1 = jet[i].t2;
		}
	}
}
 
void Show(DWORD *pMem)
{
	//变速
	int drt[16] = { 5, 5, 5, 5, 5, 6, 25, 25, 25, 25, 55, 55, 55, 55, 55 };

	int i;
	for(i = 0 ; i < NUM ; i++)
	{

		fire[i].t2 = timeGetTime();

		if(fire[i].t2 - fire[i].t1 > fire[i].dt && fire[i].show == true)
		{
			if(fire[i].r < fire[i].max_r)		//输出半径为到最大
			{
				fire[i].r++;			//输出半径增大
				fire[i].draw = true;	//设定为可以绽放
				fire[i].dt = drt[fire[i].r / 10];//变速
			}

			if(fire[i].r >= fire[i].max_r)		//输出半径达到最大
			{
				fire[i].draw = false;	//设定为不在绽放了
				Init(i);				//绽放完了，初始化掉烟花
			}
		}

		if(fire[i].draw)						//能否绽放？
		{

			double a;
			for(a = 0 ; a < 6.28 ; a += 0.01)
			{

				int x = (int) (fire[i].cen_x + fire[i].r * cos(a));
				int y = (int) (fire[i].cen_x - fire[i].r * sin(a));
				//获得一个呼啦圈中的一个像素点，循环628次会把整个呼啦圈的像素点全部拿到
				//每拿出一个像素点都要检测范围是否在图片以内
				//圆圈势必要不图片大因为正方型和圈不能重叠，我们筛选的圈一定要比正方型大
				//否则图片中的某些像素点就不会被囊括进去，所以圆圈一定大于正方形
				//圆大于正方形就像一个正方形在圆里面，圆的其他地方肯定是空的多余了
				//所以我们加xy在240*240范围内，只拿取图片内的像素点
				//cen-x ，cen-y，就是图片的中心，以它们为中心在240*240图片中扩张开来取的像素点 
				if(x > 0 && x < 240 && y > 0 && y < 240)
				{
					int b = fire[i].xy[x][y] & 0xff;
					int r = ( fire[i].xy[x][y] >> 8) & 0xff;
					int g = ( fire[i].xy[x][y] >> 16);
					//获取像素点的三原色就是像素点的颜色

					int xx = (int) (fire[i].x + fire[i].r * cos(a));
					int yy = (int) (fire[i].y - fire[i].r * sin(a));
					//此xy已经被烟花弹的hx，hy赋值了，在烟花弹消失的地方开始爆炸
					//以这个点为中心，把每次循环获得的一个个像素点一个个的写出来
					//以这个点为中心，就像获取像素点一样一圈圈扩张开来
					//图片中心获得的每一圈的像素点 显示在xy为中心起点的屏幕上


					//    这段较暗的像素点不输出        ||         这段防止越界
					if(b > 0x20 && r > 0x20 && g > 0x20 && xx > 0 && xx < 1200 && yy > 0 && yy < 800)
					{
						pMem[yy * 1200 + xx] = BGR(fire[i].xy[x][y]);//输出像素
					}
				}
			}
			fire[i].draw = false;
		}
	}
}

// 显示花样
void Style(DWORD& st1)
{
	DWORD st2 = timeGetTime();

	if (st2 - st1 > 20000)		// 一首歌的时间
	{
		// 心形坐标
		int x[13] = { 60, 75, 91, 100, 95, 75, 60, 45, 25, 15, 25, 41, 60 };
		int y[13] = { 65, 53, 40, 22, 5, 4, 20, 4, 5, 22, 40, 53, 65 };

		int i;
		for (i = 0; i < NUM; i++)
		{
			//cleardevice();
			/**** 规律分布烟花弹 ***/
			jet[i].x = x[i] * 10;
			jet[i].y = (y[i] + 75) * 10;
			jet[i].hx = jet[i].x;
			jet[i].hy = y[i] * 10;
			jet[i].height = jet[i].y - jet[i].hy;
			jet[i].shoot = true;
			jet[i].dt = 7;
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);	// 显示烟花弹

			/**** 设置烟花参数 ***/
			fire[i].x = jet[i].x + 10;
			fire[i].y = jet[i].hy;
			fire[i].show = false;
			fire[i].r = 0;

			/**** 播放发射声音 ***/
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

