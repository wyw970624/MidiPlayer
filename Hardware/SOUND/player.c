//#include "SoundPlay.h"
//unsigned char hang=0,lie=0,num=0;
//sbit s=P3^7;
//sbit s0=P0^0;
//sbit s1=P0^1;
//sbit s2=P0^2;
//sbit s3=P0^3;
//sbit s4=P0^4;
//sbit s5=P0^5;
//sbit s6=P0^6;
//sbit s7=P0^7;
//void Delay1ms(unsigned int count)
//{
//	unsigned int i,j;
//	for(i=0;i<count;i++)
//	for(j=0;j<120;j++);
//}
//unsigned char code Music1[]={0x15,0x02, 0x00,0x00};
//unsigned char code Music2[]={0x16,0x02, 0x00,0x00};
//unsigned char code Music3[]={0x17,0x02, 0x00,0x00};
//unsigned char code Music4[]={0x18,0x02, 0x00,0x00};
//unsigned char code Music5[]={0x19,0x02, 0x00,0x00};
//unsigned char code Music6[]={0x1A,0x02, 0x00,0x00};
//unsigned char code Music7[]={0x1B,0x02, 0x00,0x00};
////���ų���Ů��
///*unsigned char code Music_Same[]={0x17,0x02, 0x17,0x03, 0x18,0x03, 0x19,0x02, 0x15,0x03,
//                                  0x16,0x03, 0x17,0x03, 0x17,0x03, 0x17,0x03, 0x18,0x03,
//                                  0x19,0x02, 0x16,0x03, 0x17,0x03, 0x18,0x02, 0x18,0x03,
//                                  0x17,0x03, 0x15,0x02, 0x18,0x03, 0x17,0x03, 0x18,0x02,
//                                  0x10,0x03, 0x15,0x03, 0x16,0x02, 0x15,0x03, 0x16,0x03,
//                                  0x17,0x02, 0x17,0x03, 0x18,0x03, 0x19,0x02, 0x1A,0x03,
//                                  0x1B,0x03, 0x1F,0x03, 0x1F,0x03, 0x17,0x03, 0x18,0x03,
//                                  0x19,0x02, 0x16,0x03, 0x17,0x03, 0x18,0x03, 0x17,0x03,
//                                  0x18,0x03, 0x1F,0x03, 0x1F,0x02, 0x16,0x03, 0x17,0x03,
//                                  0x18,0x03, 0x17,0x03, 0x18,0x03, 0x20,0x03, 0x20,0x02,
//                                  0x1F,0x03, 0x1B,0x03, 0x1F,0x66, 0x20,0x03, 0x21,0x03,
//                                  0x20,0x03, 0x1F,0x03, 0x1B,0x03, 0x1F,0x66, 0x1F,0x03,
//                                  0x1B,0x03, 0x19,0x03, 0x19,0x03, 0x15,0x03, 0x1A,0x66,
//                                  0x1A,0x03, 0x19,0x03, 0x15,0x03, 0x15,0x03, 0x17,0x03,
//                                  0x16,0x66, 0x17,0x04, 0x18,0x04, 0x18,0x03, 0x19,0x03,
//                                  0x1F,0x03, 0x1B,0x03, 0x1F,0x66, 0x20,0x03, 0x21,0x03,
//                                  0x20,0x03, 0x1F,0x03, 0x1B,0x03, 0x1F,0x66, 0x1F,0x03,
//                                  0x1B,0x03, 0x19,0x03, 0x19,0x03, 0x15,0x03, 0x1A,0x66,
//                                  0x1A,0x03, 0x19,0x03, 0x19,0x03, 0x1F,0x03, 0x1B,0x03,
//                                  0x1F,0x00, 0x1A,0x03, 0x1A,0x03, 0x1A,0x03, 0x1B,0x03,
//                                  0x1B,0x03, 0x1A,0x03, 0x19,0x03, 0x19,0x02, 0x17,0x03,
//                                  0x15,0x17, 0x15,0x03, 0x16,0x03, 0x17,0x03, 0x18,0x03,
//                                  0x17,0x04, 0x18,0x0E, 0x18,0x03, 0x17,0x04, 0x18,0x0E,
//                                  0x18,0x66, 0x17,0x03, 0x18,0x03, 0x17,0x03, 0x18,0x03,
//                                  0x20,0x03, 0x20,0x02, 0x1F,0x03, 0x1B,0x03, 0x1F,0x66,			 
//                                  0x20,0x03, 0x21,0x03, 0x20,0x03, 0x1F,0x03, 0x1B,0x03,
//                                  0x1F,0x66, 0x1F,0x04, 0x1B,0x0E, 0x1B,0x03, 0x19,0x03,
//                                  0x19,0x03, 0x15,0x03, 0x1A,0x66, 0x1A,0x03, 0x19,0x03,
//                                  0x15,0x03, 0x15,0x03, 0x17,0x03, 0x16,0x66, 0x17,0x04,
//                                  0x18,0x04, 0x18,0x03, 0x19,0x03, 0x1F,0x03, 0x1B,0x03,
//                                  0x1F,0x66, 0x20,0x03, 0x21,0x03, 0x20,0x03, 0x1F,0x03,
//                                  0x1B,0x03, 0x1F,0x66, 0x1F,0x03, 0x1B,0x03, 0x19,0x03,
//                                  0x19,0x03, 0x15,0x03, 0x1A,0x66, 0x1A,0x03, 0x19,0x03,
//                                  0x19,0x03, 0x1F,0x03, 0x1B,0x03, 0x1F,0x00, 0x18,0x02,
//                                  0x18,0x03, 0x1A,0x03, 0x19,0x0D, 0x15,0x03, 0x15,0x02,
//                                  0x18,0x66, 0x16,0x02, 0x17,0x02, 0x15,0x00,0x00,0x00};				*/	
//unsigned char code Music_Same[]={ 0x0F,0x01, 0x15,0x02, 0x16,0x02, 0x17,0x66, 0x18,0x03,
//                                  0x17,0x02, 0x15,0x02, 0x16,0x01, 0x15,0x02, 0x10,0x02,
//                                  0x15,0x00, 0x0F,0x01, 0x15,0x02, 0x16,0x02, 0x17,0x02,
//                                  0x17,0x03, 0x18,0x03, 0x19,0x02, 0x15,0x02, 0x18,0x66,
//                                  0x17,0x03, 0x19,0x02, 0x16,0x03, 0x17,0x03, 0x16,0x00,
//                                  0x17,0x01, 0x19,0x02, 0x1B,0x02, 0x1B,0x70, 0x1A,0x03,
//                                  0x1A,0x01, 0x19,0x02, 0x19,0x03, 0x1A,0x03, 0x1B,0x02,
//                                  0x1A,0x0D, 0x19,0x03, 0x17,0x00, 0x18,0x66, 0x18,0x03,
//                                  0x19,0x02, 0x1A,0x02, 0x19,0x0C, 0x18,0x0D, 0x17,0x03,
//                                  0x16,0x01, 0x11,0x02, 0x11,0x03, 0x10,0x03, 0x0F,0x0C,
//                                  0x10,0x02, 0x15,0x00, 0x1F,0x01, 0x1A,0x01, 0x18,0x66,
//                                  0x19,0x03, 0x1A,0x01, 0x1B,0x02, 0x1B,0x03, 0x1B,0x03,
//                                  0x1B,0x0C, 0x1A,0x0D, 0x19,0x03, 0x17,0x00, 0x1F,0x01,
//                                  0x1A,0x01, 0x18,0x66, 0x19,0x03, 0x1A,0x01, 0x10,0x02,
//                                  0x10,0x03, 0x10,0x03, 0x1A,0x0C, 0x18,0x0D, 0x17,0x03,
//                                  0x16,0x00, 0x0F,0x01, 0x15,0x02, 0x16,0x02, 0x17,0x70,
//                                  0x18,0x03, 0x17,0x02, 0x15,0x03, 0x15,0x03, 0x16,0x66,
//                                  0x16,0x03, 0x16,0x02, 0x16,0x03, 0x15,0x03, 0x10,0x02,
//                                  0x10,0x01, 0x11,0x01, 0x11,0x66, 0x10,0x03, 0x0F,0x0C,
//                                  0x1A,0x02, 0x19,0x02, 0x16,0x03, 0x16,0x03, 0x18,0x66,
//                                  0x18,0x03, 0x18,0x02, 0x17,0x03, 0x16,0x03, 0x19,0x00,
//                                  0x00,0x00 };
//void button()
//{
//    P2=0x0f;
//	if(P2==0x0e)  hang=1;	
//	if(P2==0x0d)  hang=2;
//	if(P2==0x0b)  hang=3;
//	if(P2==0x07)  hang=4;
//	
//	P2=0x0f0;
//	if(P2==0x0e0)  lie=1;	
//	if(P2==0x0d0)  lie=2;
//	if(P2==0x0b0)  lie=3;
//	if(P2==0x70)  lie=4;
//	
//    num=(hang-1)*4+lie;  
//	if(num==-5)	 num=0;
//	if(num==1)
//	  {
//	     Play(Music5,0,2,360);
//		Delay1ms(500);
//		num=0;
//		hang=0;
//		lie=0;
//	  }
//	  if(hang!=0&&lie!=0&&num==2)
//	  {
//	     Play(Music6,0,2,360);
//		Delay1ms(500);
//		num=0;
//		hang=0;
//		lie=0;
//	  }			
//	  if(hang!=0&&lie!=0&&num==3)
//	  {
//	     Play(Music7,0,2,360);
//		Delay1ms(500);
//		num=0;
//		hang=0;
//		lie=0;
//	  }			
//	  if(hang!=0&&lie!=0&&num==4)
//	  {
//	     Play(Music1,0,3,360);
//		Delay1ms(500);
//		num=0;
//		hang=0;
//		lie=0;
//	  }			
//	  if(hang!=0&&lie!=0&&num==5)
//	  {
//	     Play(Music1,0,2,360);
//		Delay1ms(500);
//		num=0;
//		hang=0;
//		lie=0;
//	  }			
//      if(hang!=0&&lie!=0&&num==6)
//	  {
//	     Play(Music2,0,2,360);
//		Delay1ms(500);
//		num=0;
//		hang=0;
//		lie=0;
//	  }			
//	  if(hang!=0&&lie!=0&&num==7)
//	  {
//	     Play(Music3,0,2,360);
//		Delay1ms(500);
//		num=0;
//		hang=0;
//		lie=0;
//	  }			
//	  if(hang!=0&&lie!=0&&num==8)
//	  {
//	     Play(Music4,0,2,360);
//		Delay1ms(500);
//		num=0;
//		hang=0;
//		lie=0;
//	  }			
//	  if(hang!=0&&lie!=0&&num==9)
//	  {
//	     Play(Music5,0,1,360);
//		Delay1ms(500);
//		num=0;
//		hang=0;
//		lie=0;
//	  }			
//	  if(hang!=0&&lie!=0&&num==10)
//	  {
//	     Play(Music6,0,1,360);
//		Delay1ms(500);
//		num=0;
//		hang=0;
//		lie=0;
//	  }								   
//	if(hang!=0&&lie!=0&&num==11)
//	  {
//	     Play(Music7,0,1,360);
//		Delay1ms(500);
//		num=0;
//		hang=0;
//		lie=0;
//	  }			
//	  if(hang!=0&&lie!=0&&num==12)
//	  {
//	     Play(Music1,0,2,360);
//		Delay1ms(500);
//		num=0;
//		hang=0;
//		lie=0;
//	  }			
//	  if(hang!=0&&lie!=0&&num==13)
//	  {
//	     Play(Music1,0,1,360);
//		Delay1ms(500);
//		num=0;
//		hang=0;
//		lie=0;
//	  }			
//	  if(hang!=0&&lie!=0&&num==14)
//	  {
//	     Play(Music2,0,1,360);
//		Delay1ms(500);
//		num=0;
//		hang=0;
//		lie=0;
//	  }			
//	  if(hang!=0&&lie!=0&&num==15)
//	  {
//	     Play(Music3,0,1,360);
//		Delay1ms(500);
//		num=0;
//		hang=0;
//		lie=0;
//	  }			
//	  if(hang!=0&&lie!=0&&num==16)
//	  {
//	     Play(Music4,0,1,360);
//		Delay1ms(500);
//		num=0;
//		hang=0;
//		lie=0;
//	  }
//	  if(hang!=0&&lie!=0&&num==0)
//	  {
//	    s=0;
//		Delay1ms(500);
//		num=0;
//		hang=0;
//		lie=0;
//	  }						  						  		  	
//}
//void button1()
//{
//	 if(s0==0)
//	  {
//	   	Play(Music1,0,3,360);
//		Delay1ms(500);
//	  }
//	  if(s1==0)
//	  {
//	   	Play(Music2,0,3,360);
//		Delay1ms(500);
//	  }				
//	  if(s2==0)
//	  {
//	   	Play(Music3,0,3,360);
//		Delay1ms(500);
//	  }				
//	  if(s3==0)
//	  {
//	   	Play(Music4,0,3,360);
//		Delay1ms(500);
//	  }				
//	  if(s4==0)
//	  {
//	   	Play(Music5,0,3,360);
//		Delay1ms(500);
//	  }				
//	  if(s5==0)
//	  {
//	   	Play(Music6,0,3,360);
//		Delay1ms(500);
//	  }				
//	  if(s6==0)
//	  {
//	   	Play(Music7,0,3,360);
//		Delay1ms(500);
//	  }				
//	  if(s7==0)
//	  {
//	   	Play(Music_Same,0,3,360);
//		Delay1ms(500);
//	  }			
//}
//
//void main()
//{
//	InitialSound();
//	P0=0xff;
//	while(1)
//	{	
//		button();
//		button1();	
//	}
//}

