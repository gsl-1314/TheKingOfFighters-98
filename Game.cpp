//Windows编程  98拳皇Pk背景
//1.创建Windows应用程序窗口
//2.GDI贴图
//3.游戏的逻辑
//4.游戏的音乐

//头文件的包含
#include "windows.h"
#include "resource.h"
#include <MMSystem.h>
//【游戏音乐分两步】:第一步，包含库文件

#pragma  comment(lib,"winmm.lib")
#pragma  comment(lib,"Msimg32.lib")
#pragma comment  (lib,"User32.lib")
#pragma comment  (lib,"Gdi32.lib")
//全局变量的声明
DWORD p_tPre,p_tNow,p_btPre,p_btNow;       //时间间隔
HDC  p_hdc,p_memdc,p_bufdc;  //设备句柄
HBITMAP p_hBKbitmap,p_hPerson,
p_SK1=NULL,p_SK2=NULL,p_SK3=NULL,P_SK4 = NULL,p_Icon;  //位图句柄
int  p_BKNum = 0;
int  p_iBKNum=0 ;//作为背景图片的索引。
int p_flag = 0 ;
int p_intX=0,P_intY=250;  //人物坐标

//全局函数的声明
void Game_Paint(HWND hgw);          //游戏的绘制
BOOL Game_Init(HWND hgw);           //游戏的初始化
LRESULT CALLBACK WndProc(HWND hgw,UINT message,WPARAM wParam,LPARAM lParam);
//主函数
int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR IpCmdLine,
				   int  nShowCmd    )
{  //【窗口的创建分四步】：第一步，设计一个完整的窗口类；
	WNDCLASSEX gpk = {0};               //定义一个窗口类
	gpk.cbSize = sizeof(WNDCLASSEX);   //获取结构体字节数大小
    gpk.hInstance = hInstance;          //获取窗口的实例句柄
    gpk.cbClsExtra = 0;                 //窗口的扩展
    gpk.cbWndExtra = 0;                 //窗口的实例扩展
	gpk.lpfnWndProc = WndProc;          //窗口的过程函数
    gpk.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//  白色的背景        
    gpk.hCursor = NULL;                  //窗口光标为空
    gpk.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));                    //窗口像表为空
	gpk.lpszMenuName= NULL;              //窗口的菜单为空
	gpk.lpszClassName= "拳皇98";        //窗口的类名
	gpk.style = CS_HREDRAW|CS_VREDRAW;     //窗口的样式，水平，垂直
   //【窗口的创建分四步】：第二步，注册窗口  让系统指导我们设计窗口的样子
    if(!RegisterClassEx(&gpk))
      return -1;
    //【窗口的创建分四步】：第三步，创建窗口系统
	HWND hgw =   CreateWindow("拳皇98","拳皇98，你我携手，再战风云",
		           WS_MINIMIZEBOX|WS_SYSMENU ,100,10,
				   600,719,NULL,NULL,hInstance,NULL);
	//【窗口的创建分四步】：第四步，显示\更新窗口
    ShowWindow(hgw,nShowCmd);   //显示窗口
    UpdateWindow(hgw);          //更新窗口
	//【游戏音乐分两步】:第二步，调用函数playsound函数
     PlaySound("金志文 - 远走高飞 (合唱版).wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
	
   //游戏的初始化
     if (!Game_Init(hgw))
     return  -1;
   //return 0;
  //卡屏函数，getch()<=>  getchar(),for,while,do while.
  //消息循环
	MSG msg = {0};              //定义一个结构体
    while(msg.message!=WM_QUIT)   //如果结构体不等于退出键WM_QUIT，则不退出程序。
	{ 
      if (PeekMessage(&msg,0,0,0,PM_REMOVE))   //从消息队列里查找消息
	  {
        TranslateMessage(&msg);       //把虚拟键值转化为字符消息
		DispatchMessage(&msg);         //消息传给系统，系统调用WndProc函数
          
    	  }
	  else
	  {
         p_btNow = GetTickCount(); //再次获取系统时间。
		 if(p_btNow-p_btPre>60) 
        Game_Paint(hgw);
	  }

	}


    return 0;



}
//窗口过程函数
LRESULT CALLBACK WndProc(HWND hgw,UINT message,WPARAM wParam,LPARAM lParam)
{
   switch (message)
   {
     case WM_KEYDOWN:
	  switch (wParam)
			{
	  case  VK_LEFT:                                       //往左走
		     p_flag =0;
			 p_btNow=GetTickCount();               //获取一下系统时间
			 if (p_tNow-p_tPre>60)
			 {
				if(p_intX>0)
					p_intX -=10;
				Game_Paint(hgw);
			 }
			 break;
	  case  VK_RIGHT:                                       //往右走
		  p_flag =0;
		  p_btNow=GetTickCount();               //获取一下系统时间
		  if (p_tNow-p_tPre>60)
		  {
			  if(p_intX<400)
				  p_intX +=10;
			  Game_Paint(hgw);
		  }
		  break;
	         case 0x41:  //a
             p_flag = 1 ;
			 
			  while(1)
			  {
               p_tNow = GetTickCount();
                 if(p_tNow-p_tPre>60)
				 {
                Game_Paint(hgw);
				  p_iBKNum++;
					  if(p_iBKNum==82)
					    break;
			
				 } 
			
			  }
			  
			  p_iBKNum = 0;
			  p_flag = 0 ;
			  break;


      case 0x53:  //s
				 p_flag = 2 ;

				 while(2)
			  {
				  p_tNow = GetTickCount();
				  if(p_tNow-p_tPre>60)
				  {
					  Game_Paint(hgw);
					  p_iBKNum++;
					  if(p_iBKNum==35)
						  break;

				  } 

			  }

				 p_iBKNum = 0;
				 p_flag = 0 ;
				 break; 
	  
	  
	  case 0x57:  //w
		  p_flag = 3 ;

		  while(3)
		  {
			  p_tNow = GetTickCount();
			  if(p_tNow-p_tPre>60)
			  {
				  Game_Paint(hgw);
				  p_iBKNum++;
				  if(p_iBKNum==20)
					  break;
			  } 

		  }

		  p_iBKNum = 0;
		  p_flag = 0 ;
		  break;
	  case 0x44:       //D
              p_flag =4 ;

		while (4)
		{
			p_tNow=GetTickCount();
			if (p_tNow-p_tPre>60)
			{
				Game_Paint(hgw);
				p_iBKNum ++;
				if(p_iBKNum==74)
					break;
			}
		}
	      p_iBKNum = 0;
		  p_flag =0;
		  break;
	  }
	  break;     
	   
      case WM_DESTROY:
	  PostQuitMessage(0);

     	break;
   }




  return DefWindowProc(hgw,message,wParam,lParam);

  

}
//游戏的初始化
BOOL Game_Init(HWND hgw)

{  //三缓冲体系
  p_hdc =  GetDC(hgw);   //获取到设备句柄  “三缓冲体系一”
  p_memdc = CreateCompatibleDC(p_hdc); //创建一个兼容dc  内存设备 “三缓冲体系二”
  p_bufdc = CreateCompatibleDC(p_hdc); //创建一个缓冲dc    “三缓冲体系三”
 //创建空的位图，把它兼容到p_hdc设备上下文句柄中
  HBITMAP bmp = CreateCompatibleBitmap(p_hdc,600,719);//  相当于一块画布  创建位图一
  SelectObject(p_memdc,bmp);  //把空的位图bmp选到内存设备中。
  p_hBKbitmap =(HBITMAP)LoadImage(NULL,"00.bmp",IMAGE_BITMAP,7200,800,
                          LR_LOADFROMFILE);  //加载位图
  p_hPerson = (HBITMAP)LoadImage(NULL,"站立.bmp",IMAGE_BITMAP,900,250,
	                               LR_LOADFROMFILE);//加载人物位图
  p_SK1 =(HBITMAP)LoadImage(NULL,"SKBitmap.bmp",IMAGE_BITMAP,16436,400,
	                             LR_LOADFROMFILE);//加载技能位图	
  p_SK2 =(HBITMAP)LoadImage(NULL,"技能1.bmp",IMAGE_BITMAP,11200,480,
	  LR_LOADFROMFILE);//加载技能位图
  p_SK3 = (HBITMAP)LoadImage(NULL,"技能2.bmp",IMAGE_BITMAP,4140,345,
	  LR_LOADFROMFILE);//加载技能位图
  P_SK4 =(HBITMAP)LoadImage(NULL,"技能3.bmp",IMAGE_BITMAP,17600,400,
	  LR_LOADFROMFILE);//加载技能位图
  return TRUE;
}

//游戏的绘制
void Game_Paint(HWND hgw)
{   if (p_flag==0)
{
	//贴上背景图片
	SelectObject(p_bufdc,p_hBKbitmap);
	BitBlt(p_memdc,0,0,600,719,p_bufdc, p_BKNum*800,0,SRCCOPY);
	//站立图。
	SelectObject(p_bufdc,p_hPerson);
	TransparentBlt(p_memdc,p_intX+50,490,80,190,p_bufdc,p_iBKNum*100,0,100,250,RGB(255,255,0));
	//背景图片循环
	BitBlt(p_hdc,0,0,600,800,p_memdc,0,0,SRCCOPY);
	p_BKNum++;
	if(p_BKNum>9)     //如果大于9则进行下面的处理，图片是由十张组成的，不可大于10
		p_BKNum=0;     //返回第一张图片 
	p_iBKNum++;
	if(p_iBKNum>9)     //如果大于9则进行下面的处理，图片是由十张组成的，不可大于10
		p_iBKNum=0;     //返回第一张图片
	p_btPre = GetTickCount();
    p_tPre = GetTickCount();
}
	
  else	 if (p_flag==1)
	{
		//贴上背景图片
		SelectObject(p_bufdc,p_hBKbitmap);
		BitBlt(p_memdc,0,0,600,719,p_bufdc, p_BKNum*800,0,SRCCOPY);
		//贴上人物图
		SelectObject(p_bufdc,p_SK1);
		TransparentBlt(p_memdc,p_intX,290,200,400,p_bufdc,p_iBKNum*200,0,200,400,RGB(255,255,0));
		//背景图片循环
		BitBlt(p_hdc,0,0,600,800,p_memdc,0,0,SRCCOPY);
		p_BKNum++;
		if(p_BKNum>9)     //如果大于9则进行下面的处理，图片是由十张组成的，不可大于10
			p_BKNum=0;     //返回第一张图片 
		
		//p_iBKNum++; //人物图片循环。
		//if(p_iBKNum>=82)
		//	p_iBKNum=0;
		 p_btPre = GetTickCount();
         p_tPre = GetTickCount();//获取一下系统时间 ，技能。 
	    }
  else	 if (p_flag==2)
  {
	  //贴上背景图片
	  SelectObject(p_bufdc,p_hBKbitmap);
	  BitBlt(p_memdc,0,0,600,719,p_bufdc, p_BKNum*800,0,SRCCOPY);
	  //贴上人物图
	  SelectObject(p_bufdc,p_SK2);
	  TransparentBlt(p_memdc,p_intX,P_intY-40,320,480,p_bufdc,p_iBKNum*320,0,320,480,RGB(255,255,0));
	  //背景图片循环
	  BitBlt(p_hdc,0,0,600,800,p_memdc,0,0,SRCCOPY);
	  p_BKNum++;
	  if(p_BKNum>9)     //如果大于9则进行下面的处理，图片是由十张组成的，不可大于10
		  p_BKNum=0;     //返回第一张图片 

	  //p_iBKNum++; //人物图片循环。
	  //if(p_iBKNum>=82)
		 // p_iBKNum=0;
	  p_btPre = GetTickCount();
	  p_tPre = GetTickCount();//获取一下系统时间 ，技能。 
  }
  else if (p_flag==3)
  {
	  //贴上背景图片
	  SelectObject(p_bufdc,p_hBKbitmap);
	  BitBlt(p_memdc,0,0,600,719,p_bufdc, p_BKNum*800,0,SRCCOPY);
	  //贴上人物图
	  SelectObject(p_bufdc,p_SK3);
	  TransparentBlt(p_memdc,p_intX+30,290,200,400,p_bufdc,p_iBKNum*207,0,200,345,RGB(255,255,0));
	  //背景图片循环
	  BitBlt(p_hdc,0,0,600,800,p_memdc,0,0,SRCCOPY);
	  p_BKNum++;
	  if(p_BKNum>9)     //如果大于9则进行下面的处理，图片是由十张组成的，不可大于10
		  p_BKNum=0;     //返回第一张图片 

	  //p_iBKNum++; //人物图片循环。
	  //if(p_iBKNum>=82)
	  // p_iBKNum=0;
	  p_btPre = GetTickCount();
	  p_tPre = GetTickCount();//获取一下系统时间 ，技能。
  }
  else if (p_flag==4)
  {
	  
	  //贴上背景图片
	  SelectObject(p_bufdc,p_hBKbitmap);
	  BitBlt(p_memdc,0,0,600,719,p_bufdc, p_BKNum*800,0,SRCCOPY);
	  //贴上人物图
	  SelectObject(p_bufdc,P_SK4);
	  TransparentBlt(p_memdc,350,350,300,400,p_bufdc,p_iBKNum*237,0,230,400,RGB(255,255,0));
	  //背景图片循环
	  BitBlt(p_hdc,0,0,600,800,p_memdc,0,0,SRCCOPY);
	  p_BKNum++;
	  if(p_BKNum>9)     //如果大于9则进行下面的处理，图片是由十张组成的，不可大于10
		  p_BKNum=0;     //返回第一张图片 

	  //p_iBKNum++; //人物图片循环。
	  //if(p_iBKNum>=82)
	  // p_iBKNum=0;
	  p_btPre = GetTickCount();
	  p_tPre = GetTickCount();//获取一下系统时间 ，技能。
  }
}

