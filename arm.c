#include<nxp\iolpc2148.h>
#include "intrinsics.h"
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"uart.h"
#include"fuzzy.h"
#include"stdlib.h"
#include "interrupt.h"
#define sw1 IO0PIN_bit.P0_10
#define sw2 IO0PIN_bit.P0_11
int set_speed,dis_spd,val,value1,speed,fb1=0,kay,cnt=0;
int x=0,x1,x2,x3,x4,a1,a2,a3,a4,f,w;
char out[20];
float in=0,fb=0,der,prop,output,error,lasterror=0,kp=0.08,ki=0.000001;
float P,I,output;
void pwm_initial()
{
PINSEL0 = 0X000A0025;
PWMPR = 0X00000000;
PWMPCR = 0X00005000;
PWMMCR = 0X00000002;
PWMMR0 = 1200;
PWMMR6 = 600;
PWMTCR = 0X00000002;
PWMTCR = 0X00000009; }
void pwm(int x)
{
PWMMR4 = x;
PWMLER = 0X7f;}
void irq(void)
{
__disable_interrupt();
while((T0IR&0x10)!=0x10);
val=T0CR0;
T0IR = 0X10;
while((T0IR&0x10)!=0x10);
val = T0CR0-val;
value1=90000000/val;
T0IR = 0X10;
VICVectAddr = 0x00;}
void timer_Init(void)
{
T0PR=0;
T0PC=0;
T0CCR=0x0005;
VICIntSelect|=0X00000000
VICIntEnable|=0x00000010;
VICVectCntl1|=0x24;
VICVectAddr1|=(unsigned int)&irq;}
void PLL_Init(void)
{
PLLCFG=0x80; //multiple & divide value
PLLCON=0x01; //enable pll
PLLFEED=0xAA;
PLLFEED=0x55;
while(!(PLLSTAT & 0x00000400)); //lock value
PLLCON=0x03; //pll configured enable
PLLFEED=0xAA;
PLLFEED=0x55;
VPBDIV=0x01;}
void main()
{
uart0_init();
msg_received=0;
U0IER=1;
U1IER=1;
serialenable();
pwm_initial();
PLL_Init();
PINSEL0_bit.P0_10=0;
IO0DIR_bit.P0_10=0;
PINSEL0_bit.P0_11=0;
IO0DIR_bit.P0_11=0;
__enable_interrupt();
timer_Init();
T0TCR=0x01;
//cnt=580;
x=0;
pwm(0);
while(1)
{
if(msg_received==1)
{
U0IER=0;
serial_transmit(s1);
msg_received=0;
U0IER=1;}
set_speed=atoi(s1);
//set_speed=cnt;
if(sw1==0)
{
while(1)
{
if(msg_received==1)
{
U0IER=0;
serial_transmit(s1);
msg_received=0;
U0IER=1;}
set_speed=atoi(s1);
error=set_speed-speed;
in=(in+(error*0.5));
der=error-lasterror;
lasterror=error;
prop=kp*error;
fb=((kp*error)+(ki*in);
fb1=(int)fb;
if(x<0)
x=0;
speed=value1;
if(error<20 || error>-20)
{
if(error!=0)
{
dis_spd=set_speed;}}
if(error>20 || error<-20)
{
x=x+fb1;
dis_spd=speed;}
if(x<0)
x=0;
pwm(x);
speed=value1;
printf(" \nspd=%d setspd:%d X=%d",dis_spd,set_speed,x);
printf("@%d#",dis_spd);}}
if(sw2==0)
{
while(1)
{
if(msg_received==1)
{ U0IER=0;
serial_transmit(s1);
msg_received=0;
U0IER=1;}
set_speed=atoi(s1);
speed=value1;
fuzzifier();
dis_spd=set_speed;
x=cn-(int)d2;
if(x<0)
x=0;
pwm(x);
speed=value1;
printf(" \nspd=%d setspd:%d X=%d",dis_spd,set_speed,x);
printf("@%d#",dis_spd);}}}}
int putchar(int ch)
{
while(!(U0LSR&0X20));
return(U0THR=ch);}
