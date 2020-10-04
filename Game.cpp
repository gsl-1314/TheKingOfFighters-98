//Windows���  98ȭ��Pk����
//1.����WindowsӦ�ó��򴰿�
//2.GDI��ͼ
//3.��Ϸ���߼�
//4.��Ϸ������

//ͷ�ļ��İ���
#include "windows.h"
#include "resource.h"
#include <MMSystem.h>
//����Ϸ���ַ�������:��һ�����������ļ�

#pragma  comment(lib,"winmm.lib")
#pragma  comment(lib,"Msimg32.lib")
#pragma comment  (lib,"User32.lib")
#pragma comment  (lib,"Gdi32.lib")
//ȫ�ֱ���������
DWORD p_tPre,p_tNow,p_btPre,p_btNow;       //ʱ����
HDC  p_hdc,p_memdc,p_bufdc;  //�豸���
HBITMAP p_hBKbitmap,p_hPerson,
p_SK1=NULL,p_SK2=NULL,p_SK3=NULL,P_SK4 = NULL,p_Icon;  //λͼ���
int  p_BKNum = 0;
int  p_iBKNum=0 ;//��Ϊ����ͼƬ��������
int p_flag = 0 ;
int p_intX=0,P_intY=250;  //��������

//ȫ�ֺ���������
void Game_Paint(HWND hgw);          //��Ϸ�Ļ���
BOOL Game_Init(HWND hgw);           //��Ϸ�ĳ�ʼ��
LRESULT CALLBACK WndProc(HWND hgw,UINT message,WPARAM wParam,LPARAM lParam);
//������
int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR IpCmdLine,
				   int  nShowCmd    )
{  //�����ڵĴ������Ĳ�������һ�������һ�������Ĵ����ࣻ
	WNDCLASSEX gpk = {0};               //����һ��������
	gpk.cbSize = sizeof(WNDCLASSEX);   //��ȡ�ṹ���ֽ�����С
    gpk.hInstance = hInstance;          //��ȡ���ڵ�ʵ�����
    gpk.cbClsExtra = 0;                 //���ڵ���չ
    gpk.cbWndExtra = 0;                 //���ڵ�ʵ����չ
	gpk.lpfnWndProc = WndProc;          //���ڵĹ��̺���
    gpk.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//  ��ɫ�ı���        
    gpk.hCursor = NULL;                  //���ڹ��Ϊ��
    gpk.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));                    //�������Ϊ��
	gpk.lpszMenuName= NULL;              //���ڵĲ˵�Ϊ��
	gpk.lpszClassName= "ȭ��98";        //���ڵ�����
	gpk.style = CS_HREDRAW|CS_VREDRAW;     //���ڵ���ʽ��ˮƽ����ֱ
   //�����ڵĴ������Ĳ������ڶ�����ע�ᴰ��  ��ϵͳָ��������ƴ��ڵ�����
    if(!RegisterClassEx(&gpk))
      return -1;
    //�����ڵĴ������Ĳ���������������������ϵͳ
	HWND hgw =   CreateWindow("ȭ��98","ȭ��98������Я�֣���ս����",
		           WS_MINIMIZEBOX|WS_SYSMENU ,100,10,
				   600,719,NULL,NULL,hInstance,NULL);
	//�����ڵĴ������Ĳ��������Ĳ�����ʾ\���´���
    ShowWindow(hgw,nShowCmd);   //��ʾ����
    UpdateWindow(hgw);          //���´���
	//����Ϸ���ַ�������:�ڶ��������ú���playsound����
     PlaySound("��־�� - Զ�߸߷� (�ϳ���).wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
	
   //��Ϸ�ĳ�ʼ��
     if (!Game_Init(hgw))
     return  -1;
   //return 0;
  //����������getch()<=>  getchar(),for,while,do while.
  //��Ϣѭ��
	MSG msg = {0};              //����һ���ṹ��
    while(msg.message!=WM_QUIT)   //����ṹ�岻�����˳���WM_QUIT�����˳�����
	{ 
      if (PeekMessage(&msg,0,0,0,PM_REMOVE))   //����Ϣ�����������Ϣ
	  {
        TranslateMessage(&msg);       //�������ֵת��Ϊ�ַ���Ϣ
		DispatchMessage(&msg);         //��Ϣ����ϵͳ��ϵͳ����WndProc����
          
    	  }
	  else
	  {
         p_btNow = GetTickCount(); //�ٴλ�ȡϵͳʱ�䡣
		 if(p_btNow-p_btPre>60) 
        Game_Paint(hgw);
	  }

	}


    return 0;



}
//���ڹ��̺���
LRESULT CALLBACK WndProc(HWND hgw,UINT message,WPARAM wParam,LPARAM lParam)
{
   switch (message)
   {
     case WM_KEYDOWN:
	  switch (wParam)
			{
	  case  VK_LEFT:                                       //������
		     p_flag =0;
			 p_btNow=GetTickCount();               //��ȡһ��ϵͳʱ��
			 if (p_tNow-p_tPre>60)
			 {
				if(p_intX>0)
					p_intX -=10;
				Game_Paint(hgw);
			 }
			 break;
	  case  VK_RIGHT:                                       //������
		  p_flag =0;
		  p_btNow=GetTickCount();               //��ȡһ��ϵͳʱ��
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
//��Ϸ�ĳ�ʼ��
BOOL Game_Init(HWND hgw)

{  //��������ϵ
  p_hdc =  GetDC(hgw);   //��ȡ���豸���  ����������ϵһ��
  p_memdc = CreateCompatibleDC(p_hdc); //����һ������dc  �ڴ��豸 ����������ϵ����
  p_bufdc = CreateCompatibleDC(p_hdc); //����һ������dc    ����������ϵ����
 //�����յ�λͼ���������ݵ�p_hdc�豸�����ľ����
  HBITMAP bmp = CreateCompatibleBitmap(p_hdc,600,719);//  �൱��һ�黭��  ����λͼһ
  SelectObject(p_memdc,bmp);  //�ѿյ�λͼbmpѡ���ڴ��豸�С�
  p_hBKbitmap =(HBITMAP)LoadImage(NULL,"00.bmp",IMAGE_BITMAP,7200,800,
                          LR_LOADFROMFILE);  //����λͼ
  p_hPerson = (HBITMAP)LoadImage(NULL,"վ��.bmp",IMAGE_BITMAP,900,250,
	                               LR_LOADFROMFILE);//��������λͼ
  p_SK1 =(HBITMAP)LoadImage(NULL,"SKBitmap.bmp",IMAGE_BITMAP,16436,400,
	                             LR_LOADFROMFILE);//���ؼ���λͼ	
  p_SK2 =(HBITMAP)LoadImage(NULL,"����1.bmp",IMAGE_BITMAP,11200,480,
	  LR_LOADFROMFILE);//���ؼ���λͼ
  p_SK3 = (HBITMAP)LoadImage(NULL,"����2.bmp",IMAGE_BITMAP,4140,345,
	  LR_LOADFROMFILE);//���ؼ���λͼ
  P_SK4 =(HBITMAP)LoadImage(NULL,"����3.bmp",IMAGE_BITMAP,17600,400,
	  LR_LOADFROMFILE);//���ؼ���λͼ
  return TRUE;
}

//��Ϸ�Ļ���
void Game_Paint(HWND hgw)
{   if (p_flag==0)
{
	//���ϱ���ͼƬ
	SelectObject(p_bufdc,p_hBKbitmap);
	BitBlt(p_memdc,0,0,600,719,p_bufdc, p_BKNum*800,0,SRCCOPY);
	//վ��ͼ��
	SelectObject(p_bufdc,p_hPerson);
	TransparentBlt(p_memdc,p_intX+50,490,80,190,p_bufdc,p_iBKNum*100,0,100,250,RGB(255,255,0));
	//����ͼƬѭ��
	BitBlt(p_hdc,0,0,600,800,p_memdc,0,0,SRCCOPY);
	p_BKNum++;
	if(p_BKNum>9)     //�������9���������Ĵ���ͼƬ����ʮ����ɵģ����ɴ���10
		p_BKNum=0;     //���ص�һ��ͼƬ 
	p_iBKNum++;
	if(p_iBKNum>9)     //�������9���������Ĵ���ͼƬ����ʮ����ɵģ����ɴ���10
		p_iBKNum=0;     //���ص�һ��ͼƬ
	p_btPre = GetTickCount();
    p_tPre = GetTickCount();
}
	
  else	 if (p_flag==1)
	{
		//���ϱ���ͼƬ
		SelectObject(p_bufdc,p_hBKbitmap);
		BitBlt(p_memdc,0,0,600,719,p_bufdc, p_BKNum*800,0,SRCCOPY);
		//��������ͼ
		SelectObject(p_bufdc,p_SK1);
		TransparentBlt(p_memdc,p_intX,290,200,400,p_bufdc,p_iBKNum*200,0,200,400,RGB(255,255,0));
		//����ͼƬѭ��
		BitBlt(p_hdc,0,0,600,800,p_memdc,0,0,SRCCOPY);
		p_BKNum++;
		if(p_BKNum>9)     //�������9���������Ĵ���ͼƬ����ʮ����ɵģ����ɴ���10
			p_BKNum=0;     //���ص�һ��ͼƬ 
		
		//p_iBKNum++; //����ͼƬѭ����
		//if(p_iBKNum>=82)
		//	p_iBKNum=0;
		 p_btPre = GetTickCount();
         p_tPre = GetTickCount();//��ȡһ��ϵͳʱ�� �����ܡ� 
	    }
  else	 if (p_flag==2)
  {
	  //���ϱ���ͼƬ
	  SelectObject(p_bufdc,p_hBKbitmap);
	  BitBlt(p_memdc,0,0,600,719,p_bufdc, p_BKNum*800,0,SRCCOPY);
	  //��������ͼ
	  SelectObject(p_bufdc,p_SK2);
	  TransparentBlt(p_memdc,p_intX,P_intY-40,320,480,p_bufdc,p_iBKNum*320,0,320,480,RGB(255,255,0));
	  //����ͼƬѭ��
	  BitBlt(p_hdc,0,0,600,800,p_memdc,0,0,SRCCOPY);
	  p_BKNum++;
	  if(p_BKNum>9)     //�������9���������Ĵ���ͼƬ����ʮ����ɵģ����ɴ���10
		  p_BKNum=0;     //���ص�һ��ͼƬ 

	  //p_iBKNum++; //����ͼƬѭ����
	  //if(p_iBKNum>=82)
		 // p_iBKNum=0;
	  p_btPre = GetTickCount();
	  p_tPre = GetTickCount();//��ȡһ��ϵͳʱ�� �����ܡ� 
  }
  else if (p_flag==3)
  {
	  //���ϱ���ͼƬ
	  SelectObject(p_bufdc,p_hBKbitmap);
	  BitBlt(p_memdc,0,0,600,719,p_bufdc, p_BKNum*800,0,SRCCOPY);
	  //��������ͼ
	  SelectObject(p_bufdc,p_SK3);
	  TransparentBlt(p_memdc,p_intX+30,290,200,400,p_bufdc,p_iBKNum*207,0,200,345,RGB(255,255,0));
	  //����ͼƬѭ��
	  BitBlt(p_hdc,0,0,600,800,p_memdc,0,0,SRCCOPY);
	  p_BKNum++;
	  if(p_BKNum>9)     //�������9���������Ĵ���ͼƬ����ʮ����ɵģ����ɴ���10
		  p_BKNum=0;     //���ص�һ��ͼƬ 

	  //p_iBKNum++; //����ͼƬѭ����
	  //if(p_iBKNum>=82)
	  // p_iBKNum=0;
	  p_btPre = GetTickCount();
	  p_tPre = GetTickCount();//��ȡһ��ϵͳʱ�� �����ܡ�
  }
  else if (p_flag==4)
  {
	  
	  //���ϱ���ͼƬ
	  SelectObject(p_bufdc,p_hBKbitmap);
	  BitBlt(p_memdc,0,0,600,719,p_bufdc, p_BKNum*800,0,SRCCOPY);
	  //��������ͼ
	  SelectObject(p_bufdc,P_SK4);
	  TransparentBlt(p_memdc,350,350,300,400,p_bufdc,p_iBKNum*237,0,230,400,RGB(255,255,0));
	  //����ͼƬѭ��
	  BitBlt(p_hdc,0,0,600,800,p_memdc,0,0,SRCCOPY);
	  p_BKNum++;
	  if(p_BKNum>9)     //�������9���������Ĵ���ͼƬ����ʮ����ɵģ����ɴ���10
		  p_BKNum=0;     //���ص�һ��ͼƬ 

	  //p_iBKNum++; //����ͼƬѭ����
	  //if(p_iBKNum>=82)
	  // p_iBKNum=0;
	  p_btPre = GetTickCount();
	  p_tPre = GetTickCount();//��ȡһ��ϵͳʱ�� �����ܡ�
  }
}

