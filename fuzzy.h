int x;

void fuzzifier()
{

p=0,q=0,r2=0,s=0;
if(set_speed<600)
{
  p=1,q=0,r2=0,s=0;//pwml=280;pwmm=560;pwmh=840;
  if(set_speed>200)
    xol=(float)(600-set_speed)/(float)(600-200);
}
if((set_speed>=200)&&(set_speed<1000))
{
  if(p)p=1;
  else
  {p=0,q=1,r2=0,s=0;}
  //pwml=280;pwmm=560;pwmh=840;
  if(set_speed<600)
    xl=(float)abs(200-set_speed)/(float)abs(200-600);
  else if (set_speed>600)
    xl=((float)(1000-set_speed)/(float)(1000-600));
  //single_data('1',0xce);
}

if((set_speed>600)&&(set_speed<1400))
{
  if(q)q=1;
  else
  {p=0,q=0,r2=1,s=0;}
  //pwml=560;pwmm=840;pwmh=1120;
  if(set_speed<1000)
    xm=(float)abs(600-set_speed)/(float)abs(600-1000);
  else if (set_speed>1000)
    xm=(float)(1400-set_speed)/(float)(1400-1000);
  //single_data('2',0xcd);
}

if((set_speed>1000)&&(set_speed<1800))
{
  if(r2)r2=1;
  else
  {p=0,q=0,r2=0,s=1;}
  //pwml=840;pwmm=1120;pwmh=1400;
  if(set_speed<1400)
    xh=(float)abs(1000-set_speed)/(float)abs(1000-1400);
  else if (set_speed>1400)
    xh=(float)(1800-set_speed)/(float)(1800-1400);
}
if(set_speed>=1400)
{
  if(s)s=1;


  //pwml=280;pwmm=560;pwmh=840;
 if (set_speed<1800)
    xoh=((float)abs(1400-set_speed)/(float)abs(1400-1800));
  //single_data('1',0xce);
}

if(p){an=xol;bn=xl;cn=552;}
if(q){an=xl;bn=xm;cn=828;}
if(r2){an=xm;bn=xh;cn=1104;}
if(s){an=xh;bn=xoh;cn=1380;}

//printf("xl  = %6.2f",xl);
//printf("\n\r");
//printf("xm  = %6.2f",xm);
//printf("xm");
//printf("\n\r");
d2=(276*an)/(an+bn);
d1=276-d2;

}
