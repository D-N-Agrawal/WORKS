//REQUIRED HEADER FILES

#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>

//REQUIRED MACROS
#define round(a) ((int)(a+0.5))

//REQUIRED INITIALIZATIONS OF FUNCTIONS for drawing

void calllineDDA();
void lineDDA(int,int,int,int);

void calllineBRES();
void lineBRES();

void calllineGENBRES();
void lineGENBRES();

void callcircleMID();
void circlemidpoint();
void circleplotpoint();

//REQUIRED INITIALIZATIONS OF FUNCTIONS for transformations
void calltranslateTRI();
void callscaleTRI();
void callrotateTRI();
void callreflectionTRI();
void callshearRECT();

//important initializations for cohen line clipping
void callcohenCLIP();
int regcod(int,int);
void doclip(int,int,int,int);
void  dline();

struct dev
  {
    int X1;
    int Y1;
    int X2;
    int Y2;
    int r1;
    int r2;
  } lin[100];
 int itr,nol;
//**************************************************************

//********************THE MAIN FUNCTION*****************************

void main()
 {
  char ch,ci;
  int gd=DETECT,gm;
  initgraph(&gd,&gm,"C:\\TC\\BGI");
  printf("\t \t*********** COMPUTER GRAPHICS ALGORITHMS IMPLEMENTATIONS **************\n");
  printf("WHAT DO YOU WANT TO PERFORM\n");
  printf("******************CHOSE ONE********************\n ");
  printf(" \n\n\n\n\t\t   PRESS D \t\tPRESS T ");
  printf("\n\n\t\t    FOR \t\t FOR");
  printf("\n\t\t   DRAWING \t   TRANSFORMATION/CLIPPING");

  rectangle(100,200,250,100);
  rectangle(270,200,480,100);

  scanf("%c",&ch);

  if(ch=='d' || ch=='D')
  {
   printf("\n\n\n PRESS d for D.D.A. LINE DRAWING");
   printf("\n PRESS g for Genaralized BRESENHEM Line drawing");
   printf("\n PRESS c for CIRCLE drawing \n ");

   scanf("%c",&ci);
   scanf("%c",&ci);

   switch(ci)
    {
    case 'd':
    calllineDDA();
    break;

    case 'b':
    calllineBRES();
    break;

    case 'g':
    calllineGENBRES();
    break;

    case 'c':
    callcircleMID();
    break;

    default:
    printf("PLEASE INSERT THE RIGHT CHOICE");

     }
  }

  else if(ch=='t' || ch=='T')
  {

    printf("\n\n\n PRESS x for TRANSLATION of tringle");
    printf("\n PRESS s for for SCALLING of triangle");
    printf("\n PRESS r for for ROTATION of triangle");
    printf("\n PRESS m for for REFLECTION of triangle");
    printf("\n PRESS h for for SHEARING of rectangle");
	printf("\n PRESS z for for COHEN LINE CLIPPING");

  scanf("%c",&ci);
  scanf("%c",&ci);

  switch(ci)
  {
    case 'x':
    calltranslateTRI();
    break;

    case 's':
    callscaleTRI();
    break;

    case 'r':
    callrotateTRI();
    break;

    case 'm':
    callreflectionTRI();
    break;

    case 'h':
    callshearRECT();
    break;

    case 'z':
    callcohenCLIP();
    break;

    default:
    printf("PLESAE INSERT THE RIGHT CHOICE");

	}
}
getch();
}

//********************D.D.A. LINE DRAWING**************************
void calllineDDA()
 {
  int xa,ya,xb,yb;
  int gd=DETECT,gm;
  initgraph(&gd,&gm,"C:\\TC\\BGI");

  outtextxy(550,450,"DEVYANSH");
  outtextxy(550,460,"1514310071");

  printf("enter the co ordinates");
  scanf("%d%d%d%d",&xa,&ya,&xb,&yb);

  lineDDA(xa,ya,xb,yb);
 }

void lineDDA(int xa,int ya,int xb,int yb)
 {
  int dx=xb-xa;
  int dy=yb-ya;
  int steps,k;
  float xinc,yinc,x=xa,y=ya;

  if(abs(dx)>abs(dy))
    steps=abs(dx);

  else steps=abs(dy);

  xinc=dx/(float)steps;
  yinc=dy/(float)steps;
  putpixel(round(x),round(y),15);

  for(k=0;k<steps;k++)
  { x+=xinc;
    y+=yinc;
    putpixel(round(x),round(y),15);

  }
   getch();
 }

//************************BRESENHEM SIMPLE LINE DRAWING*****************
 void calllineBRES()
 {
  int xa,ya,xb,yb;
  int gd=DETECT,gm;
  initgraph(&gd,&gm,"C:\\TC\\BGI");

  outtextxy(550,450,"DEVYANSH");
  outtextxy(550,460,"1514310071");

  printf("start & end points are");
  scanf("%d %d %d %d",&xa,&ya,&xb,&yb);
  lineBRES(xa,ya,xb,yb);
  getch();
 }

void lineBRES(int xa,int ya,int xb,int yb)
{
  int x,y,xend;
  int dx=abs(xb-xa);
  int dy=abs(yb-ya);
  int p=2*dy-dx;
  int twody=2*dy;
  int twodydx=2*(dy-dx);

  if(xa>xb)
    {
    x=xb;
    y=yb;
    xend=xa;
    }

    else
    {
     x=xa;
     y=ya;
     xend=xb;
     }

     putpixel(x,y,15);

    while(x<xend)
    {
     x++;
     if(p<0)
     p+=twody;

     else
    { y++;
    p+=twodydx;
    }

    putpixel(x,y,15);
   }
   getch();
 }

 //****************GENERALIZED BRESENHAM LENE DRAWING**************
void calllineGENBRES()
{
 int x1,y1,x2,y2;
 int gd=DETECT,gm=DETECT;
 initgraph(&gd,&gm,"c:\\TC\\bgi");

  outtextxy(550,450,"DEVYANSH");
  outtextxy(550,460,"1514310071");

 printf("starting & end points are");
 scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
 lineGENBRES(x1,y1,x2,y2);
 getch();
}

void lineGENBRES(int xa,int ya,int xb,int yb)
 {
  int dx=abs(xa-xb);
  int dy=abs(ya-yb);
  int x=xa;
  int y=ya;
  int s1,s2,temp,ID,p,i;

  if((xb-xa)>0)
   s1=1;

  else s1=(-1);

  if((yb-ya)>0)
   s2=1;

  else s2=(-1);

  if(dy>dx)
  {
   temp=dx;
   dx=dy;
   dy=temp;

   ID=1;
  }

  else  ID=0;

  p=(2*dy)-dx;
  i=1;

  putpixel(x,y,15);

abc :
     {
      while(p>=0)
       {
	if(ID==1)
	x=x+s1;

	else
	y=y+s2;

	p=p-(2*dx);
       }

 if(ID==1)
 y=y+s2;

 else
 x=x+s1;

 p=p+(2*dy);

 putpixel(x,y,15);

 i++;

 if(i<=dx)
 goto abc;

 else
 return;
}

 getch();
}

//******************CIRCLE DRAWING***********************************
void callcircleMID()
 {
  int xa,ya,xb,yb;
  int xc,yc,r;
  int gd=DETECT,gm;
  initgraph(&gd,&gm,"C:\\TC\\BGI");

  outtextxy(550,450,"DEVYANSH");
  outtextxy(550,460,"1514310071");

  printf("center");
  scanf("%d %d",&xc,&yc);

  printf("radius");
  scanf("%d",&r);

  circlemidpoint(xc,yc,r);

  getch();
}

void circlemidpoint(int xcenter,int ycenter,int radius)
{
  int x=0, y=radius;
  int p=1-radius;

  circleplotpoint(xcenter,ycenter,x,y);

  while(x<y)
  {
  x++;

  if(p<0)  p=p+2*x+1;

  else
  {
  y--;
  p=p+2*(x-y)+1;
  }

  circleplotpoint(xcenter,ycenter,x,y);
 }
}

void circleplotpoint(int xcenter ,int ycenter ,int x,int y )
{
  putpixel(xcenter+x,ycenter+y,1);
  putpixel(xcenter-x,ycenter+y,2);
  putpixel(xcenter+x,ycenter-y,3);
  putpixel(xcenter-x,ycenter-y,4);
  putpixel(xcenter+y,ycenter+x,11);
  putpixel(xcenter-y,ycenter+x,12);
  putpixel(xcenter+y,ycenter-x,13);
  putpixel(xcenter-y,ycenter-x,14);
}

//************************TRANSLATION OF TRINGLE***********************
void calltranslateTRI()
 {
 int gd=DETECT,gm=DETECT;
 int tx,ty,i,j,k,sum;
 int tri[3][3],dist[3][3],res[3][3];
 initgraph(&gd,&gm,"c:\\TC\\bgi");

  outtextxy(550,450,"DEVYANSH");
  outtextxy(550,460,"1514310071");

 printf("enetr the co ordinates of triangle");

 //values in object matrix of triangle
 scanf("%d %d",&tri[0][0],&tri[1][0]);
 scanf("%d %d",&tri[0][1],&tri[1][1]);
 scanf("%d %d",&tri[0][2],&tri[1][2]);
 tri[2][0]=1;
 tri[2][1]=1;
 tri[2][2]=1;


  line(tri[0][0],tri[1][0],tri[0][2],tri[1][2]);
  line(tri[0][1],tri[1][1],tri[0][2],tri[1][2]);
  line(tri[0][0],tri[1][0],tri[0][1],tri[1][1]);

  printf("enter the tx ty ");
  scanf("%d %d",&tx,&ty);

 //values in translation matrix
 dist[0][0]=1;
 dist[0][1]=0;
 dist[0][2]=tx;
 dist[1][0]=0;
 dist[1][1]=1;
 dist[1][2]=ty;
 dist[2][0]=0;
 dist[2][1]=0;
 dist[2][2]=1;


for(i=0;i<=2;i++)
{
  for(j=0;j<=2;j++)
  {
   sum=0;
   for(k=0;k<=2;k++)
    {
     sum=sum+dist[i][k]*tri[k][j];
    }
   res[i][j]=sum;
  }
}

  line(res[0][0],res[1][0],res[0][2],res[1][2]);
  line(res[0][1],res[1][1],res[0][2],res[1][2]);
  line(res[0][0],res[1][0],res[0][1],res[1][1]);
  getch();
}

//**************************SCALING OF TRIANGLE***************
void callscaleTRI()
{
int gd=DETECT,gm=DETECT;
int i,j,k;
float sum,sx,sy,x1,y1;

float tri[3][3],dist[3][3],res[3][3];
initgraph(&gd,&gm,"c:\\TC\\bgi");
  outtextxy(550,450,"DEVYANSH");
  outtextxy(550,460,"1514310071");

printf("enetr the co ordinates of triangle");

//values in object matrix of triangle
scanf("%f %f",&tri[0][0],&tri[1][0]);
scanf("%f %f",&tri[0][1],&tri[1][1]);
scanf("%f %f",&tri[0][2],&tri[1][2]);
tri[2][0]=1;
tri[2][1]=1;
tri[2][2]=1;

 x1=(tri[0][0]+tri[0][1]+tri[0][2])/3;
 y1=(tri[1][0]+tri[1][1]+tri[1][2])/3;

line(tri[0][0],tri[1][0],tri[0][2],tri[1][2]);
line(tri[0][1],tri[1][1],tri[0][2],tri[1][2]);
line(tri[0][0],tri[1][0],tri[0][1],tri[1][1]);

printf("\n\n\nenter the sx sy ");
scanf("%f %f",&sx,&sy);

//values in translati
dist[0][0]=sx;
 dist[0][1]=0;
 dist[0][2]=x1*(1-sx);
 dist[1][0]=0;
 dist[1][1]=sy;
 dist[1][2]=y1*(1-sy);
 dist[2][0]=0;
 dist[2][1]=0;
 dist[2][2]=1;

for(i=0;i<=2;i++)
{
  for(j=0;j<=2;j++)
  {
   sum=0;
   for(k=0;k<=2;k++)
   {
   sum=sum+dist[i][k]*tri[k][j];
   }
   res[i][j]=sum;
   }
  }

  line(res[0][0],res[1][0],res[0][2],res[1][2]);
  line(res[0][1],res[1][1],res[0][2],res[1][2]);
  line(res[0][0],res[1][0],res[0][1],res[1][1]);

  getch();
 }

//*********************ROTATION OF TRIANGLE**********************

void callrotateTRI()
 {
  int gd=DETECT,gm=DETECT;
  int sy,i,j,k;

  float tri[3][3],rot[3][3],res[3][3];
  float th,sx,sum,x1,y1;

  initgraph(&gd,&gm,"c:\\TC\\bgi");

  outtextxy(550,450,"DEVYANSH");
  outtextxy(550,460,"1514310071");

printf("enetr the co ordinates of triangle");
scanf("%f %f",&tri[0][0],&tri[1][0]);
scanf("%f %f",&tri[0][1],&tri[1][1]);
scanf("%f %f",&tri[0][2],&tri[1][2]);

tri[2][0]=1;
tri[2][1]=1;
tri[2][2]=1;


 x1=(tri[0][0]+tri[0][1]+tri[0][2])/3;
 y1=(tri[1][0]+tri[1][1]+tri[1][2])/3;



line(tri[0][0],tri[1][0],tri[0][2],tri[1][2]);
line(tri[0][1],tri[1][1],tri[0][2],tri[1][2]);
line(tri[0][0],tri[1][0],tri[0][1],tri[1][1]);


printf("\n\n\nenter the ANGLE in degrees ");
scanf("%f",&sx);

th=(sx*22)/(180*7);

printf("%f",th);

//values in rotation matrix after perfoeming +ve,-ve translation

rot[0][0]=cos(th);
rot[0][1]=-sin(th);
rot[0][2]=(x1*(1-cos(th))+y1*sin(th));
rot[1][0]=sin(th);
rot[1][1]=cos(th);
rot[1][2]=(y1*(1-cos(th))-x1*sin(th));
rot[2][0]=0;
rot[2][1]=0;
rot[2][2]=1;

for(i=0;i<=2;i++)
{
  for(j=0;j<=2;j++)
  {
   sum=0;
   for(k=0;k<=2;k++)
   {
   sum=sum+rot[i][k]*tri[k][j];
   }
   res[i][j]=sum;
   }
  }

  line(res[0][0],res[1][0],res[0][2],res[1][2]);
  line(res[0][1],res[1][1],res[0][2],res[1][2]);
  line(res[0][0],res[1][0],res[0][1],res[1][1]);

  getch();
}

//*********************REFLECTION**************************
  void callreflectionTRI()
{
int gd=DETECT,gm=DETECT;
int sy,i,j,k;

float sum,tri[3][3],rot[3][3],res[3][3];

float th,sx,x1,y1;

initgraph(&gd,&gm,"c:\\TC\\bgi");

  outtextxy(550,450,"DEVYANSH");
  outtextxy(550,460,"1514310071");

line(0,0,450,450);

printf("enetr the co ordinates of triangle");
printf("\t LET THE MIRROR IS AT LINE Y-X=0 ");
scanf("%f %f",&tri[0][0],&tri[1][0]);
scanf("%f %f",&tri[0][1],&tri[1][1]);
scanf("%f %f",&tri[0][2],&tri[1][2]);
tri[2][0]=1;
tri[2][1]=1;
tri[2][2]=1;

line(tri[0][0],tri[1][0],tri[0][2],tri[1][2]);
line(tri[0][1],tri[1][1],tri[0][2],tri[1][2]);
line(tri[0][0],tri[1][0],tri[0][1],tri[1][1]);


//values in any point reflaction matrix wrt x axis
rot[0][0]=0;
rot[0][1]=1;
rot[0][2]=0;
rot[1][0]=1;
rot[1][1]=0;
rot[1][2]=0;
rot[2][0]=0;
rot[2][1]=0;
rot[2][2]=1;

for(i=0;i<=2;i++)
{
  for(j=0;j<=2;j++)
  {
   sum=0;
   for(k=0;k<=2;k++)
   {
   sum=sum+rot[i][k]*tri[k][j];
   }
   res[i][j]=sum;
   }
  }

  printf("press any key for reflection");
  getch();

  line(res[0][0],res[1][0],res[0][2],res[1][2]);
  line(res[0][1],res[1][1],res[0][2],res[1][2]);
  line(res[0][0],res[1][0],res[0][1],res[1][1]);

  getch();

}

void callshearRECT()
{
int gd=DETECT,gm=DETECT;
int i,j,k;

float sum,tri[3][4],rot[3][3],res[3][4];
float shy,shx,x,y;

initgraph(&gd,&gm,"c:\\TC\\bgi");

 outtextxy(550,450,"DEVYANSH");
  outtextxy(550,460,"1514310071");


printf("enetr the lower left & upper right points of rectangle");

scanf("%f %f",&tri[0][0],&tri[1][0]);
scanf("%f %f",&tri[0][1],&tri[1][1]);

x=tri[0][0];
y=tri[1][1];

tri[0][2]=tri[0][0];
tri[1][2]=tri[1][1];
tri[0][3]=tri[0][1];
tri[1][3]=tri[1][0];
tri[2][3]=1;
tri[2][0]=1;
tri[2][1]=1;
tri[2][2]=1;

line(tri[0][0],tri[1][0],tri[0][2],tri[1][2]);
line(tri[0][2],tri[1][2],tri[0][1],tri[1][1]);
line(tri[0][1],tri[1][1],tri[0][3],tri[1][3]);
line(tri[0][3],tri[1][3],tri[0][0],tri[1][0]);

line(x,y,x,500);
line(x,y,700,y);

outtextxy(550,y-10,"x-axis");
outtextxy(x+10,450,"y-axis");

scanf("%f %f",&shx,&shy);

rot[0][0]=1;
rot[0][1]=shx;
rot[0][2]=-y*shx;
rot[1][0]=shy;
rot[1][1]=1;
rot[1][2]=-x*shy;
rot[2][0]=0;
rot[2][1]=0;
rot[2][2]=1;

for(i=0;i<=2;i++)
{
  for(j=0;j<=3;j++)
  {
   sum=0;
   for(k=0;k<=2;k++)
   {
   sum=sum+rot[i][k]*tri[k][j];
   }
   res[i][j]=sum;
   }
  }

  line(res[0][0],res[1][0],res[0][2],res[1][2]);
  line(res[0][2],res[1][2],res[0][1],res[1][1]);
  line(res[0][1],res[1][1],res[0][3],res[1][3]);
  line(res[0][3],res[1][3],res[0][0],res[1][0]);

  getch();
}

//******************************COHEN CLIPPING ALGORITHM***************************
void callcohenCLIP()
 {
  int c,x1,y1,x2,y2;
  float m;

 int gd=DETECT,gm=DETECT;
 initgraph(&gd,&gm,"c:\\TC\\bgi");
 rectangle(150,350,450,100);

 printf("enter the number of lines");
 scanf("%d",&nol);

 printf("give the co ordinates of %d lines",nol);

 for(itr=1;itr<=nol;itr++)
 {
 scanf("%d %d %d %d",&lin[itr].X1,&lin[itr].Y1,&lin[itr].X2,&lin[itr].Y2);
 line(lin[itr].X1,lin[itr].Y1,lin[itr].X2,lin[itr].Y2);
 }

 for(itr=1;itr<=nol;itr++)
 {
 lin[itr].r1=regcod(lin[itr].X1,lin[itr].Y1);
 lin[itr].r2=regcod(lin[itr].X2,lin[itr].Y2);

 if((lin[itr].r1==0)&&(lin[itr].r2==0))
 { printf("do nothing0");
 }

 else
 {
   //THE END OPERATION
   c=(lin[itr].r1)&(lin[itr].r2);

   if(c==0)
   doclip(lin[itr].X1,lin[itr].Y1,lin[itr].X2,lin[itr].Y2);

   else
   {
   //DISCARDING LINE
   lin[itr].X1=0;
   lin[itr].Y1=0;
   lin[itr].X2=0;
   lin[itr].Y2=0;
   }

 }
}

dline();
getch();
}

void doclip(int xa,int ya,int xb,int yb)
   {
     float x1=xa;
     float y1=ya;
     float x2=xb;
     float y2=yb;
      float m;
	  m=(y2-y1)/(x2-x1);

	  if(x1<150)
	  {
	  y1=y1+m*(150-x1);
	  x1=150;
	  }

	  if(x1>450)
	  {
	   y1=y1+m*(x1);
	  x1=450;
	  }

	  if(y1<100)
	  {
	  x1=x1+(100-y1)/m;
	  y1=100;
	  }

	  if(y1>350)
	  {
	  x1=x1+(350-y1)/m;
	  y1=350;
	  }

	  if(x2<150)
	  {
	  y2=y2+m*(150-x2);
	  x2=150;
	  }

	  if(x2>450)
	  {
	  y2=y2+m*(450-x2);
	  x2=450;
	  }

	  if(y2<100)
	  {
	  x2=x2+(100-y2)/m;
	  y2=100;
	  }

	  if(y1>350)
	  {
	  x2=x2+(350-y2)/m;
	  y2=350;
	  }

	  lin[itr].X1=x1;
	  lin[itr].Y1=y1;
	  lin[itr].X2=x2;
	  lin[itr].Y2=y2;

      delay(1000);
     }

void  dline()
{
 int gd=DETECT,gm=DETECT;
 initgraph(&gd,&gm,"c:\\TC\\bgi");
 rectangle(150,350,450,100);

  for(itr=1;itr<=nol;itr++)
 line(lin[itr].X1,lin[itr].Y1,lin[itr].X2,lin[itr].Y2);

}

int regcod(int x1,int y1)
 {
   if((x1<150)&&(y1<100))  return 9;

   if((x1<150)&&(y1>350))  return 5;

   if((x1>450)&&(y1<100))  return 10;

   if((x1>450)&&(y1>350))  return 6;

   if((x1>150)&&(y1<100)&&(x1<450))  return 8;

   if((x1<150)&&(y1>100)&&(y1<350))  return 1;

   if((x1>150)&&(y1>350)&&(x1<450))  return 4;

   if((x1>450)&&(y1>100)&&(y1<350))  return 2;

   return 0;
   }
