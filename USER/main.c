#include "beep.h"
#include "delay.h"
#include "rgb.h"
#include "adc.h"
#include "timer.h"
#include "digital.h"
#include "math.h"
#include "usart.h"

#define SYSTEM_OSC 		72000000	//���徧��Ƶ��72000000HZ
#define SOUND_SPACE 	4/5 		//������ͨ��������ĳ��ȷ���,//ÿ4���������
#define PSC 7 //Ԥ��Ƶ

#define SONG1 0x10
#define SONG2 0x20
#define PLAY 0x01
#define PAUSE 0x02
#define MUSIC_STOP 0x03
#define MEASURE 0x30
#define STOP_MEASURE 0x31

#define TIME_START 0x40
#define TIME_STOP 0x41
#define TIME_RESET 0x42
u16 m_delay=0;
u16 maxfre(u16 *fre,u8 n);
u16 minfre(u16 *fre,u8 n);

void init(void){
	uart_init(9600);//���ڳ�ʼ��Ϊ9600
	delay_init();  //��ʱ������ʼ��
	BEEP_Init();
	RGB_Init();
	Adc_Init();
	LEDB=1;
	LEDR=0;
	TIM4_Int_Init(999,PSC);
}

int main(void)
{
	u16 p,q=0,msec=9999; // msecΪ���ֵ
	u16 flag=0;
	u8 i,j,rx;
	u8 song=0,song_rx=0,num=3;
	u8 play=0,replay=0,measure=0,time_start=0,play_mode=0,play_s=0;
	u16 MaxFre,MinFre;
	u16 *Sound;u16 Signature;u16 Octachord;u16 Speed;
	u16 FreTab[12]  = { 262,277,294,311,330,349,369,392,415,440,466,494 }; //ԭʼƵ�ʱ�
	u16 SignTab[7]  = { 0,2,4,5,7,9,11 }; 								  //1~7��Ƶ�ʱ��е�λ
	u16 LengthTab[7]= { 1,2,4,8,16,32,64 };	//��������					
	u16 NewFreTab[12];		//�µ�Ƶ�ʱ�
	int len=0;
	u16 Point,LDiv,LDiv0,LDiv1,LDiv2=0,LDiv4,CurrentFre,Temp_T,SoundLength,ledpwm;
	u8 Tone,Length,SL,SH,SM,SLen,XG,FD;
	u16 adcx;
	u16 gaoyuan[]={0x17,0x04, 0x18,0x04, 0x19,0x03, 0x19,0x03, 0x19,0x04,
                                  0x19,0x03, 0x19,0x04, 0x1A,0x04, 0x19,0x04, 0x18,0x03,
                                  0x18,0x03, 0x17,0x04, 0x18,0x04, 0x19,0x03, 0x19,0x03,
                                  0x17,0x04, 0x16,0x04, 0x15,0x03, 0x16,0x02, 0x16,0x03,
                                  0x17,0x04, 0x16,0x04, 0x15,0x04, 0x15,0x03, 0x15,0x04,
                                  0x15,0x04, 0x1F,0x04, 0x1F,0x03, 0x1B,0x04, 0x1B,0x03,
                                  0x1F,0x04, 0x1B,0x04, 0x1A,0x04, 0x19,0x03, 0x1A,0x04,
                                  0x19,0x04, 0x18,0x03, 0x18,0x04, 0x19,0x04, 0x1A,0x04,
                                  0x19,0x04, 0x19,0x01, 0x1F,0x03, 0x1F,0x02, 0x1A,0x04,
                                  0x19,0x04, 0x19,0x03, 0x1A,0x04, 0x19,0x04, 0x19,0x02,
                                  0x1A,0x03, 0x1A,0x03, 0x19,0x04, 0x15,0x03, 0x16,0x04,
                                  0x17,0x66, 0x16,0x03, 0x15,0x67, 0x15,0x04, 0x15,0x04,
                                  0x17,0x03, 0x17,0x04, 0x17,0x04, 0x16,0x04, 0x16,0x03,
                                  0x16,0x67, 0x16,0x04, 0x16,0x03, 0x16,0x03, 0x1B,0x04,
                                  0x1A,0x67, 0x00,0x00 };
	
	
	u16 cityinsky[]={0x1A,0x0D, 0x1B,0x03, 0x1F,0x70, 0x1B,0x03, 0x1F,0x02,
                                  0x21,0x02, 0x1B,0x00, 0x17,0x03, 0x17,0x03, 0x1A,0x70,
                                  0x19,0x03, 0x1A,0x02, 0x1F,0x02, 0x19,0x15, 0x17,0x03,
                                  0x17,0x03, 0x18,0x70, 0x17,0x03, 0x18,0x0D, 0x1F,0x66,
                                  0x17,0x15, 0x1F,0x03, 0x1F,0x03, 0x1F,0x03, 0x1B,0xCA,
                                  0x18,0x67, 0x18,0x0C, 0x1B,0x02, 0x1B,0x15, 0x1A,0x03,
                                  0x1B,0x03, 0x1F,0x66, 0x1B,0x03, 0x1F,0x02, 0x21,0x02,
                                  0x1B,0x15, 0x17,0x03, 0x17,0x03, 0x1A,0x66, 0x19,0x03,
                                  0x1A,0x02, 0x1F,0x02, 0x19,0x14, 0x17,0x03, 0x18,0x02,
                                  0x1F,0x03, 0x1B,0x03, 0x1B,0x02, 0x1F,0x02, 0x20,0x03,
                                  0x20,0x03, 0x21,0x03, 0x1F,0x16, 0x1F,0x0C, 0x1B,0x03,
                                  0x1A,0x03, 0x1A,0x03, 0x1B,0x66, 0x19,0x02, 0x1A,0x02,
                                  0x00,0x00};
	init();

	//��ѭ��
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   
			//�ж��Ƿ񲥷��¸���
			rx=USART_RX_BUF[0];
			
			if(rx==SONG2+1)	 //ѡ�еڶ��׸衰SONG2+Play��
			{	
				song_rx=2;
				rx=rx-SONG2;
				if(!time_start)
				{	msec=23;num=2;}	  //�����ʡ��Զ��壿
			}
			if(rx==SONG1+1)
			{
				song_rx=1;
				rx=rx-SONG1;
				if(!time_start)
				{	msec=24;num=2;}
			}

			if(rx==PLAY) //0x01 ����
			{
				play=1;
			}

			if(rx==PAUSE)
			{
				play=0;
				flag=0;
				LEDR=0;
//				LEDB=1;
				TIM_Cmd(TIM2, DISABLE);
				BEEP=0;
				TIM_Cmd(TIM3, DISABLE);
			}

			if(rx==MUSIC_STOP)
			{
				song_rx=0;
				msec=0;
				countt=0;
				num=1;
//				LEDB=1;
				TIM_Cmd(TIM2, DISABLE);
				BEEP=0;
				TIM_Cmd(TIM3, DISABLE);
			}

			if(rx==MEASURE)
			{
				measure=1;
				countm=0;
			}
			if(rx==STOP_MEASURE)
				measure=0;
			//if(rx==TIME_START)
			if(rx==TIME_START)
			{
				time_start=1;
				num=1;
				msec=0;
				countt=0;
			}
			if(rx==TIME_STOP)
				time_start=2;
			if(rx==TIME_RESET)
			{	
				msec=0;
				countt=0;
				time_start=0;
				num=1;
			}			
			USART_RX_STA=0;
		}
		
		if(song_rx!=song)  //song=0
		{
			if(song_rx!=0)
			{	
				if(song_rx==1)
				{
					Sound=gaoyuan;
					Signature=0;
					Octachord=3;
					Speed=20;

				}
				if(song_rx==2)
				{
					Sound=cityinsky;
					Signature=0;
					Octachord=2;
					Speed=40;

				} 
				for(i=0;i<12;i++) 				// ���ݵ��ż������˶��������µ�Ƶ�ʱ� 
				{
					j = i + Signature;
					if(j > 11)
					{
						j = j-12;
						NewFreTab[i] = FreTab[j]*2;
					}
					else
						NewFreTab[i] = FreTab[j];
			
					if(Octachord == 1)
						NewFreTab[i]>>=1;
					else if(Octachord == 3)
						NewFreTab[i]<<=1;
				}										
				MaxFre=maxfre(NewFreTab,12)<<1;	   //�����ʡ�
				MinFre=minfre(NewFreTab,12)>>1;
				SoundLength = 0;
				while(Sound[SoundLength] != 0x00)	//�����������
				{
					SoundLength+=2;
				}	
				Point = 0;
				LDiv0 = 60000/Speed;				// ���1�������ĳ���(����10ms)  Ϊʲô����12000	
				LDiv4 = LDiv0/4; 					// ���4�������ĳ��� 
				LDiv4 = LDiv4-LDiv4*SOUND_SPACE; 	// ��ͨ��������׼
				m_delay=0;
			}
			else
				LEDR=1;LEDB=1; 
			song=song_rx;
		}
		if(song!=0&&m_delay==0&&play_mode==0)
		{
			BEEP=0;
			if(play==1)
			{
				if(!replay&&LDiv2!=0)
				{
					BEEP=0;
					len+=LDiv2;
					TIM2_Int_Init(65535,287);
					m_delay=LDiv2;
					LDiv2=0;			
				}
				if(replay==1)
				{
					Point=0;
					if(song==1)
					{msec=24;num=2;}  //�����ʡ�
					else
					{msec=23;num=2;}
					replay=0;
				}
				if(m_delay==0)
				{			
					if(Point < SoundLength)
					{
						BEEP=0;	
						Tone=Sound[Point];
						Length=Sound[Point+1];
						Point+=2; 
						SL=Tone%10; 								//��������� 
						SM=Tone/10%10; 								//������ߵ��� 
						SH=Tone/100; 								//������Ƿ����� 
						CurrentFre = NewFreTab[SignTab[SL-1]+SH]; 	//�����Ӧ������Ƶ�� 
						if(SL!=0)
						{
							if (SM==1) CurrentFre >>= 1; 		//���� 
							if (SM==3) CurrentFre <<= 1; 		//����
							Temp_T = 499999/CurrentFre;//�����������ֵ
							LEDB=1;
					        LEDR=0;
							ledpwm=(u16)(1000*((float)(CurrentFre-MinFre)/(float)(MaxFre-MinFre)));//PWM�Ƚ�ֵ ������ɫ�ƹ�ռ�ձ�
							TIM3_Int_Init(1000,ledpwm,PSC);
							TIM2_Int_Init(Temp_T,PSC);
					
						}
						SLen=LengthTab[Length%10]; 	//����Ǽ�������
						XG=Length/10%10; 			//�����������(0��ͨ1����2����) 
						FD=Length/100;
						LDiv=LDiv0/SLen; 			//���������������ĳ���(���ٸ�10ms)
						if (FD==1) 
							LDiv=LDiv+LDiv/2;
						if(XG!=1)	
							if(XG==0) 				//�����ͨ���������೤�� 
								if (SLen<=4)	
									LDiv1=LDiv-LDiv4;
								else
									LDiv1=LDiv*SOUND_SPACE;
							else
								LDiv1=LDiv/2; 		//������������೤�� 
						else
							LDiv1=LDiv;
						if(SL==0) LDiv1=0;
							LDiv2=LDiv-LDiv1; 		//����������ĳ��� 
					  	if (SL!=0)
						{
							m_delay=LDiv1;
							len=len+LDiv1;	
						}
					}
					else
					{
						Point=0;
						play=0;
						msec=len/1000;
						//���Ƽ�ʱ
						if(!time_start)
						{	if(song_rx==1) 
							{msec=24;num=2;}
							if(song_rx==2) 
							{msec=23;num=2;}
						} 
					}
				}
			
			}
		}
		

		//�¶Ȳ���
		if(countm>=200&&measure==1)
		{
			adcx=Get_Adc(ADC_Channel_9);
			USART_SendData(USART1, adcx/256);//�򴮿�1��������
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			USART_SendData(USART1, adcx%256);//�򴮿�1��������
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			countm=0;
		}

//�������ʾ
		if(countt!=q)
			{
			if(msec>9999) 
			{
				msec=0;
				num=1;
			}
			if(time_start==1)
			{
				if(countt>=100)
				{	msec++;countt=0;}
				if(msec==pow(10,num)) 
					num++;
			}
			else
			{
			if(msec==0)
				num=1;
				else
			{
			if(msec>0&&countt>=1000)
			{	
				msec--;
				countt=0;
				if(play==0) msec++;
			} 
			if(num>1&&msec==pow(10,num-1)-1) 
				num--;
			
			}
			}

			p=countt%num;
	
			if(p==0)
			{	
				ShowData(msec,0,time_start);
				DIG1=0;DIG2=1;DIG3=1;DIG4=1;				
			}
			if(p==1)
			{	
				ShowData(msec,1,time_start);
				DIG1=1;DIG2=0;DIG3=1;DIG4=1;										
			}
			if(p==2)
			{	 
				ShowData(msec,2,time_start);
				DIG1=1;DIG2=1;DIG3=0;DIG4=1;
				
			}
			if(p==3)
			{	
				ShowData(msec,3,time_start);
				DIG1=1;DIG2=1;DIG3=1;DIG4=0;			
			}
			q=countt;
		}
			
	}
}


u16 maxfre(u16 *fre,u8 n)
{
	u8 i;
	u16 max;
	max=fre[0];
	for(i=1;i<n;i++)
	{
		if(max<fre[i])
		 	max=fre[i];
	}
	return max;	
}

u16 minfre(u16 *fre,u8 n)
{
	u8 i;
	u16 min;
	min=fre[0];
	for(i=1;i<n;i++)
	{
		if(min>fre[i])
		 	min=fre[i];
	}
	return min;	
}

