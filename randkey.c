// try_huayuanzhu.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#ifdef _CH_
#pragma package <opencv>
#endif

#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;
#define STEP0 0
#define STEP1 1
#define STEP2 2

IplImage * inpaint_mask = 0;
IplImage * img = 0, *img0 = 0 , * inpainted = 0;
CvPoint prev_pt = {- 1,-1 };
int showw= 0, Step=STEP0 ,stepp= 0;

  //CvPoint P1= cvPoint(90,450);
  //CvPoint P2= cvPoint(90,200);
  //CvPoint P3= cvPoint(220,130);
  //CvPoint P4= cvPoint(460,130);
  //CvPoint P5= cvPoint(460,380);
  //CvPoint P6= cvPoint(310,450);
//         P3
//       /   \
//     P2     P4
//      |\   /|
//     P1  P7 P5
//      \     /
//         P6
//

//    if( !img )
//    return;
//
//    if( event == CV_EVENT_LBUTTONUP || !(flags & CV_EVENT_FLAG_LBUTTON) )
//    prev_pt = cvPoint(-1,-1);
//    else if( event == CV_EVENT_LBUTTONDOWN )
//      {
//                prev_pt = cvPoint(x,y);
//                cout<<"x:"<<prev_pt.x<<" y:"<<prev_pt.y<<" count:"<<clik_count<<endl;
//
//                temp_point[0][clik_count]=prev_pt.x;
//                temp_point[1][clik_count]=prev_pt.y;
//
//                clik_count++;
//                if(clik_count>6)
//                  {
//                               cube kk(temp_point);
//                               kk.to_draw();
//                               clik_count=1;
//                  }
//               }
//    else if( event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) )
//    {
//        CvPoint pt = cvPoint(x,y);
//        //if( prev_pt.x < 0 )
//        //prev_pt = pt;
//        //cvLine( inpaint_mask, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );
//        //cvLine( img, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );
//        //prev_pt = pt;
//        //cvShowImage( "image", img );
//    }
//}
char wndname[] = "Edge" ;
char tbarname[] = "Threshold" ;
int edge_thresh = 100 ;
int test= 100;

int jiange= 10;

//像素精度
int xiangsu= 1;

//弧度精度
int hudujindu= 1;


IplImage *pImg = 0;
IplImage *dst =NULL, *color_dst =NULL,* src1=NULL ;
CvMemStorage * storage =NULL;
CvSeq * lines =NULL;
// define a trackbar callback
CvPoint * point_p =NULL;
CvPoint t_point[7];

void auto_point()
{ 
		pImg = cvCloneImage( img0 );
	    dst = cvCreateImage( cvGetSize( pImg), 8, 1 );
        color_dst = cvCreateImage( cvGetSize( pImg), 8, 3 );
        storage = cvCreateMemStorage(0 );
        lines = 0;
        int i ;
                    src1=cvCreateImage (cvSize( pImg->width ,pImg-> height),IPL_DEPTH_8U ,1);

                                
                    cvCvtColor(pImg , src1 , CV_BGR2GRAY );
    printf( "Hallo keyty: \n" );


    // Create a window
   cvNamedWindow(wndname , 1 );


                                                 // Run the edge detector on grayscale
                                                 cvCanny(src1 , dst , ( float)80 , ( float)80 *3, 3);



        cvCvtColor( dst, color_dst, CV_GRAY2BGR );
                                
                                 lines = cvHoughLines2( dst, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI/180 , 80 , 40 , 40 );
                                 printf("aaf: %d \n" ,lines-> total);

                                 point_p = (CvPoint *)malloc( sizeof(CvPoint )*((int) lines->total ));
                                 int total_point =0;

        for(int i = 0 ; i < lines->total ; i ++ )
        {
            CvPoint* line = (CvPoint *)cvGetSeqElem( lines,i );
            cvLine( color_dst, line[0 ], line [1], CV_RGB( 255,0 ,0), 3, 8 );
                                                 printf("aaf%d: %d, %d   " ,i,( line[0 ]).x, (line [0]). y);
                                                 printf("aaf%d: %d, %d \n" ,i,( line[1 ]).x, (line [1]). y);
                                                 //
                                                 if(total_point ==0) {point_p [total_point]=( line[0 ]);total_point++;}
                                                 else
                                                 {
                                                 CvPoint t_point =cvPoint(( line[0 ]).x, (line [0]). y);
                                                 int i =0;
                                                 for(i =0; i<total_point ;i++)
                                                                 if( ((point_p[ i]).x -t_point. x) > - 10 && ((point_p [i]). x-t_point .x) <10 && (( point_p[i ]).y- t_point.y ) > -10 && ((point_p[ i]).y -t_point. y) <10  )
                                                                                 break;
                                                 if( i==total_point ) {point_p[ total_point]=t_point ;total_point++;}
                                                 t_point=cvPoint ((line[ 1]).x , ( line[1 ]).y);
                                                 i=0 ;
                                                 for(i =0; i<total_point ;i++)
                                                                 if( ((point_p[ i]).x -t_point. x) > - 10 && ((point_p [i]). x-t_point .x) <10 && (( point_p[i ]).y- t_point.y ) > -10 && ((point_p[ i]).y -t_point. y) <10  )
                                                                                 break;
                                                 if( i==total_point ) {point_p[ total_point]=t_point ;total_point++;}
                                                 // printf("%d ", total_point);
                                                 }

        }
                                 for(int i= 0;i <total_point; i++)
                                                 printf("\n %d,%d " , point_p [i]. x,point_p [i]. y);
                                 for(int i= 0;i <total_point; i++)
                                                 for(int j= 0;j <total_point- i-1 ;j++)
                                                                 if(point_p [j]. y > point_p[ j+1 ].y)
                                                                 {
                                                                                 CvPoint temp =cvPoint( point_p[j ].x, point_p[j ].y);
                                                                                 point_p[j ]=point_p[ j+1 ];
                                                                                 point_p[j +1]= temp;
                                                                 }

puts ("");
                                 for(int i= 0;i <total_point; i++)
                                                 printf("\n %d,%d " , point_p [i]. x,point_p [i]. y);
								 t_point[2]=point_p[0]; t_point[5]=point_p[6]; t_point[6]=point_p[3];
								 if(point_p[1].x < point_p[2].x) { t_point[1]=point_p[1]; t_point[3]=point_p[2];}
								 else { t_point[1]=point_p[2]; t_point[3]=point_p[1];}
								 if(point_p[4].x < point_p[5].x) { t_point[0]=point_p[4]; t_point[4]=point_p[5];}
								 else { t_point[0]=point_p[5]; t_point[4]=point_p[4];}
        cvNamedWindow( "Hough" , 1 );
        cvShowImage( "Hough" , color_dst );
		 cvShowImage(wndname , src1 );
}
  class cube
  {
                 private:
                                 CvPoint P1 ;
                                 CvPoint P2 ;
                                 CvPoint P3 ;
                                 CvPoint P4 ;
                                 CvPoint P5 ;
                                 CvPoint P6 ;
                                 CvPoint P7 ;
                 public:
                                 cube()
                                  {
                                                 P1= cvPoint(200 ,500);
                                                 P2= cvPoint(200 ,300);
                                                 P3= cvPoint(300 ,160);
                                                 P4= cvPoint(500 ,160);
                                                 P5= cvPoint(500 ,400);
                                                 P6= cvPoint(400 ,500);          
/*                                 P1= cvPoint(90,450);
                                                 P2= cvPoint(90,200);
                                                 P3= cvPoint(220,130);
                                                 P4= cvPoint(460,130);
                                                 P5= cvPoint(460,380);
                                                 P6= cvPoint(310,450);*/     
                 //temp[i]=cvPoint(200,500);i++;
                 //temp[i]=cvPoint(200,300);i++;
                 //temp[i]=cvPoint(300,160);i++;
                 //temp[i]=cvPoint(500,160);i++;
                 //temp[i]=cvPoint(500,400);i++;
                 //temp[i]=cvPoint(400,500);i++;
                                  };
                                 cube(int tp[ 2][7 ])
                                  {
                                   int i =1;
                                   P1=cvPoint (tp[ 0][i ],tp[ 1][i ]);i++;
                                   P2=cvPoint (tp[ 0][i ],tp[ 1][i ]);i++;
                                   P3=cvPoint (tp[ 0][i ],tp[ 1][i ]);i++;
                                   P4=cvPoint (tp[ 0][i ],tp[ 1][i ]);i++;
                                   P5=cvPoint (tp[ 0][i ],tp[ 1][i ]);i++;
                                   P6=cvPoint (tp[ 0][i ],tp[ 1][i ]);i++;
                                  }
								 cube(CvPoint t_p[7])
                                  {
                                   int i =0;
                                   P1=t_p[i];i++;
                                   P2=t_p[i];i++;
                                   P3=t_p[i];i++;
                                   P4=t_p[i];i++;
                                   P5=t_p[i];i++;
                                   P6=t_p[i];i++;
                                   P7=t_p[i];i++;
                                  }
                                 int to_draw ()
                                  {
                                                                 float x1 =-1, x2=-1 ,y1=- 1,y2 =-1; float x3=-1 ,x4=- 1,y3 =-1, y4=-1 ;
                                                                 x1=P1 .x; x2=P2 .x; y1=P1 .y; y2=P2 .y;
                                                                 float a12 =(x1- x2)/(y1 -y2), b12= x1-a12 *y1;
                                                                 x3=P4 .x; x4=P5 .x; y3=P4 .y; y4=P5 .y;
                                                                 float a45 =(x3- x4)/(y3 -y4), b45= x3-a45 *y3;

                                                                 x1=P2 .x; x2= P3.x ;y1= P2.y ; y2 =P3. y;
                                                                 float k23 =(y1- y2)/(x1 -x2), b23= y1-k23 *x1;
                                                                 x3=P1 .x; x4= P6.x ;y3= P1.y ; y4 =P6. y;
                                                                 float k16 =(y3- y4)/(x3 -x4), b16= y3-k16 *x3;

                                                                 x1=P4 .x; x2= P3.x ;y1= P4.y ; y2 =P3. y;
                                                                 float k34 =(y1- y2)/(x1 -x2), b34= y1-k34 *x1;
                                                                 x3=P5 .x; x4= P6.x ;y3= P5.y ; y4 =P6. y;
                                                                 float k56 =(y3- y4)/(x3 -x4), b56= y3-k56 *x3;
                
                                                                 float b27 =P2. y-P2 .x* k16;
                                                                 float b47 =P4. y-P4 .x* k56;
                                                                 int tempx =(b27- b47)/(k56 -k16);
                                                                 int tempy =k16* tempx+b27 ;
                                                                 CvPoint P7 = cvPoint (tempx, tempy);
                                 //                             printf("%d %d",tempx,tempy);

                                                                 x1=P7 .x; x2=P6 .x; y1=P7 .y; y2=P6 .y;
                                                                 float a67 =(x1- x2)/(y1 -y2), b67= x1-a67 *y1;

                                                                 for(int i= 0;i <inpaint_mask-> height;i ++)
                                                                 {
                                                                                 for ( int j =0; j<inpaint_mask ->width; j++)
                                                                                 {
                                                                                                 int y =i, x=j ;
                                                
                                                                                                 int temp12 =a12* y+b12 ;      
                                                                                                 int temp45 =a45* y+b45 ;
                                                                                                 int temp23 =k23* x+b23 ;      
                                                                                                 int temp16 =k16* x+b16 ;
                                                                                                 int temp34 =k34* x+b34 ;      
                                                                                                 int temp56 =k56* x+b56 ;
                                                                                                 int temp27 =x* k16+b27 ;
                                                                                                 int temp67 =y* a67+b67 ;
                                                                                                 int temp47 =k56* x+b47 ;
                                                                                                 //int d_=
                                                                                                 if( x>temp12 && x<temp45 )
                                                                                                 {
                                                                                                   if(y >temp23 && y <temp16)
                                                                                                   {
                                                                                                                 if(y >temp34 && y <temp56)
                                                                                                                 {
                                                                                                                                 if(y >=temp27 && x < temp67 )
                                                                                                                                 {
                                                                                                                                  float hhh =x- temp67;if (hhh< 0) hhh =0- hhh;
                                                                                                                                  int qqq =temp67- temp12;
                                                                                                                                  if(qqq <0) qqq= 0-qqq ;
                                                                                                                                  float kkk =(200.0- 0.0)/qqq *hhh;
                                                                                                                                  hhh=255 -kkk;
                                                                                                                                 //  printf("%d %d\n",hhh, kkk);
                                                                                                                                  (( uchar*)(inpaint_mask ->imageData + inpaint_mask ->widthStep* i))[j ]=hhh;
                                                                                                                                 }
                                                                                                                                 else  if (y>= temp47 && x>= temp67)
                                                                                                                                 {
                                                                                                                                  float hhh =x- temp67;if (hhh< 0) hhh =0- hhh;
                                                                                                                                  int qqq =temp67- temp45;
                                                                                                                                  if(qqq <0) qqq= 0-qqq ;
                                                                                                                                  float kkk =(200.0- 0.0)/qqq *hhh;
                                                                                                                                  hhh=255 -kkk;
                                                                                                                                 //  printf("%d %d\n",hhh, kkk);
                                                                                                                                  (( uchar*)(inpaint_mask ->imageData + inpaint_mask ->widthStep* i))[j ]=hhh;
                                                                                                                                 }
                                                                                                                                 else
                                                                                                                                 {
                                                                                                                                  float hhh =x- P7.x ;if( hhh<0 ) hhh =0- hhh;
                                                                                                                                  int qqq =P7. x-P1 .x;
                                                                                                                                  if(x >=temp67) qqq= P7.x -P5. x;
                                                                                                                                  if(qqq <0) qqq= 0-qqq ;
                                                                                                                                  float kkk =(200.0- 0.0)/qqq *hhh;
                                                                                                                                  hhh=255 -kkk;
                                                                                                                                  int aaa =y- P3.y ;if( aaa<0 ) aaa =0- aaa;
                                                                                                                                  int sss =P7. y-P3 .y; if( sss<0 ) sss =0- sss;
                                                                                                                                  float ddd =(hhh)/ sss*aaa ;
                                                                                                                                  aaa=ddd ;
                                                                                                                                  (( uchar*)(inpaint_mask ->imageData + inpaint_mask ->widthStep* i))[j ]=aaa;
                                                                                                                                 }
                                                                                                                 }
                                                                                                 else
                                                                                                  ((uchar*)( inpaint_mask->imageData + inpaint_mask ->widthStep* i))[j ]=150;
                                                                                                   }
                                                                                                 else
                                                                                                  ((uchar*)( inpaint_mask->imageData + inpaint_mask ->widthStep* i))[j ]=150;
                                                                                                 }
                                                                                                 else
                                                                                                  ((uchar*)( inpaint_mask->imageData + inpaint_mask ->widthStep* i))[j ]=150;
                                                                                 }


                                                                 }
                                                                 cvLine( inpaint_mask, P1, P2, cvScalarAll(255 ), 1 , 8 , 0 );
                                                                 cvLine( inpaint_mask, P2, P3, cvScalarAll(255 ), 1 , 8 , 0 );
                                                                 cvLine( inpaint_mask, P3, P4, cvScalarAll(255 ), 1 , 8 , 0 );
                                                                 cvLine( inpaint_mask, P4, P5, cvScalarAll(255 ), 1 , 8 , 0 );
                                                                 cvLine( inpaint_mask, P5, P6, cvScalarAll(255 ), 1 , 8 , 0 );
                                                                 cvLine( inpaint_mask, P6, P1, cvScalarAll(255 ), 1 , 8 , 0 );
                                                                 //cvLine( inpaint_mask, P7, P2, cvScalarAll(255), 5, 8, 0 );
                                                                 //cvLine( inpaint_mask, P7, P4, cvScalarAll(255), 5, 8, 0 );
                                                                 //cvLine( inpaint_mask, P7, P6, cvScalarAll(255), 5, 8, 0 );
                                                                 cvShowImage( "image1" , inpaint_mask );
                                 return 0 ;

                                                                                  };
                                 int to_draw_7 ()
                                  {
                                                                 float x1 =-1, x2=-1 ,y1=- 1,y2 =-1; float x3=-1 ,x4=- 1,y3 =-1, y4=-1 ;
                                                                 x1=P1 .x; x2=P2 .x; y1=P1 .y; y2=P2 .y;
                                                                 float a12 =(x1- x2)/(y1 -y2), b12= x1-a12 *y1;
                                                                 x3=P4 .x; x4=P5 .x; y3=P4 .y; y4=P5 .y;
                                                                 float a45 =(x3- x4)/(y3 -y4), b45= x3-a45 *y3;

                                                                 x1=P2 .x; x2= P3.x ;y1= P2.y ; y2 =P3. y;
                                                                 float k23 =(y1- y2)/(x1 -x2), b23= y1-k23 *x1;
                                                                 x3=P1 .x; x4= P6.x ;y3= P1.y ; y4 =P6. y;
                                                                 float k16 =(y3- y4)/(x3 -x4), b16= y3-k16 *x3;

                                                                 x1=P4 .x; x2= P3.x ;y1= P4.y ; y2 =P3. y;
                                                                 float k34 =(y1- y2)/(x1 -x2), b34= y1-k34 *x1;
                                                                 x3=P5 .x; x4= P6.x ;y3= P5.y ; y4 =P6. y;
                                                                 float k56 =(y3- y4)/(x3 -x4), b56= y3-k56 *x3;
                
                                                                 float b27 =P2. y-P2 .x* k16;
                                                                 float b47 =P4. y-P4 .x* k56;
                                                                 int tempx =(b27- b47)/(k56 -k16);
                                                                 int tempy =k16* tempx+b27 ;
                                                                 CvPoint P7 = cvPoint (tempx, tempy);
		//something should be change
                                 //                             printf("%d %d",tempx,tempy);

                                                                 x1=P7 .x; x2=P6 .x; y1=P7 .y; y2=P6 .y;
                                                                 float a67 =(x1- x2)/(y1 -y2), b67= x1-a67 *y1;

                                                                 for(int i= 0;i <inpaint_mask-> height;i ++)
                                                                 {
                                                                                 for ( int j =0; j<inpaint_mask ->width; j++)
                                                                                 {
                                                                                                 int y =i, x=j ;
                                                
                                                                                                 int temp12 =a12* y+b12 ;      
                                                                                                 int temp45 =a45* y+b45 ;
                                                                                                 int temp23 =k23* x+b23 ;      
                                                                                                 int temp16 =k16* x+b16 ;
                                                                                                 int temp34 =k34* x+b34 ;      
                                                                                                 int temp56 =k56* x+b56 ;
                                                                                                 int temp27 =x* k16+b27 ;
                                                                                                 int temp67 =y* a67+b67 ;
                                                                                                 int temp47 =k56* x+b47 ;
                                                                                                 //int d_=
                                                                                                 if( x>temp12 && x<temp45 )
                                                                                                 {
                                                                                                   if(y >temp23 && y <temp16)
                                                                                                   {
                                                                                                                 if(y >temp34 && y <temp56)
                                                                                                                 {
                                                                                                                                 if(y >=temp27 && x < temp67 )
                                                                                                                                 {
                                                                                                                                  float hhh =x- temp67;if (hhh< 0) hhh =0- hhh;
                                                                                                                                  int qqq =temp67- temp12;
                                                                                                                                  if(qqq <0) qqq= 0-qqq ;
                                                                                                                                  float kkk =(200.0- 0.0)/qqq *hhh;
                                                                                                                                  hhh=255 -kkk;
                                                                                                                                 //  printf("%d %d\n",hhh, kkk);
                                                                                                                                  (( uchar*)(inpaint_mask ->imageData + inpaint_mask ->widthStep* i))[j ]=hhh;
                                                                                                                                 }
                                                                                                                                 else  if (y>= temp47 && x>= temp67)
                                                                                                                                 {
                                                                                                                                  float hhh =x- temp67;if (hhh< 0) hhh =0- hhh;
                                                                                                                                  int qqq =temp67- temp45;
                                                                                                                                  if(qqq <0) qqq= 0-qqq ;
                                                                                                                                  float kkk =(200.0- 0.0)/qqq *hhh;
                                                                                                                                  hhh=255 -kkk;
                                                                                                                                 //  printf("%d %d\n",hhh, kkk);
                                                                                                                                  (( uchar*)(inpaint_mask ->imageData + inpaint_mask ->widthStep* i))[j ]=hhh;
                                                                                                                                 }
                                                                                                                                 else
                                                                                                                                 {
                                                                                                                                  float hhh =x- P7.x ;if( hhh<0 ) hhh =0- hhh;
                                                                                                                                  int qqq =P7. x-P1 .x;
                                                                                                                                  if(x >=temp67) qqq= P7.x -P5. x;
                                                                                                                                  if(qqq <0) qqq= 0-qqq ;
                                                                                                                                  float kkk =(200.0- 0.0)/qqq *hhh;
                                                                                                                                  hhh=255 -kkk;
                                                                                                                                  int aaa =y- P3.y ;if( aaa<0 ) aaa =0- aaa;
                                                                                                                                  int sss =P7. y-P3 .y; if( sss<0 ) sss =0- sss;
                                                                                                                                  float ddd =(hhh)/ sss*aaa ;
                                                                                                                                  aaa=ddd ;
                                                                                                                                  (( uchar*)(inpaint_mask ->imageData + inpaint_mask ->widthStep* i))[j ]=aaa;
                                                                                                                                 }
                                                                                                                 }
                                                                                                 else
                                                                                                  ((uchar*)( inpaint_mask->imageData + inpaint_mask ->widthStep* i))[j ]=150;
                                                                                                   }
                                                                                                 else
                                                                                                  ((uchar*)( inpaint_mask->imageData + inpaint_mask ->widthStep* i))[j ]=150;
                                                                                                 }
                                                                                                 else
                                                                                                  ((uchar*)( inpaint_mask->imageData + inpaint_mask ->widthStep* i))[j ]=150;
                                                                                 }


                                                                 }
                                                                 cvLine( inpaint_mask, P1, P2, cvScalarAll(255 ), 1 , 8 , 0 );
                                                                 cvLine( inpaint_mask, P2, P3, cvScalarAll(255 ), 1 , 8 , 0 );
                                                                 cvLine( inpaint_mask, P3, P4, cvScalarAll(255 ), 1 , 8 , 0 );
                                                                 cvLine( inpaint_mask, P4, P5, cvScalarAll(255 ), 1 , 8 , 0 );
                                                                 cvLine( inpaint_mask, P5, P6, cvScalarAll(255 ), 1 , 8 , 0 );
                                                                 cvLine( inpaint_mask, P6, P1, cvScalarAll(255 ), 1 , 8 , 0 );
                                                                 //cvLine( inpaint_mask, P7, P2, cvScalarAll(255), 5, 8, 0 );
                                                                 //cvLine( inpaint_mask, P7, P4, cvScalarAll(255), 5, 8, 0 );
                                                                 //cvLine( inpaint_mask, P7, P6, cvScalarAll(255), 5, 8, 0 );
                                                                 cvShowImage( "image1" , inpaint_mask );
                                 return 0 ;

                                                                                  };
                                 int to_move (CvPoint to_where[], int move_time )
                                  {
                                   CvPoint move_dis [7]; int i =1;
                                   move_dis[i ]=cvPoint(( to_where[i ]).x- P1.x , ( to_where[i ]).y- P1.y );i++;
                                   move_dis[i ]=cvPoint(( to_where[i ]).x- P2.x , ( to_where[i ]).y- P2.y );i++;
                                   move_dis[i ]=cvPoint(( to_where[i ]).x- P3.x , ( to_where[i ]).y- P3.y );i++;
                                   move_dis[i ]=cvPoint(( to_where[i ]).x- P4.x , ( to_where[i ]).y- P4.y );i++;
                                   move_dis[i ]=cvPoint(( to_where[i ]).x- P5.x , ( to_where[i ]).y- P5.y );i++;
                                   move_dis[i ]=cvPoint(( to_where[i ]).x- P6.x , ( to_where[i ]).y- P6.y );i++;
                                   float d_dis [2][ 7];
                                   for(int i= 1;i <=6; i++)
                                                 {
                                                  d_dis[0 ][i]=( move_dis[i ]).x/ move_time;
                                                  d_dis[1 ][i]=( move_dis[i ]).y/ move_time;
                                                 }
                                   for(int j= 0;j <=move_time; j++)
                                     {
                                                  int i =1; float tempx ,tempy;
                                                  tempx=P1 .x+ d_dis[0 ][i]; tempy=P1 .y+ d_dis[1 ][i]; P1=cvPoint (tempx, tempy);i ++;
                                                  tempx=P2 .x+ d_dis[0 ][i]; tempy=P2 .y+ d_dis[1 ][i]; P2=cvPoint (tempx, tempy);i ++;
                                                  tempx=P3 .x+ d_dis[0 ][i]; tempy=P3 .y+ d_dis[1 ][i]; P3=cvPoint (tempx, tempy);i ++;
                                                  tempx=P4 .x+ d_dis[0 ][i]; tempy=P4 .y+ d_dis[1 ][i]; P4=cvPoint (tempx, tempy);i ++;
                                                  tempx=P5 .x+ d_dis[0 ][i]; tempy=P5 .y+ d_dis[1 ][i]; P5=cvPoint (tempx, tempy);i ++;
                                                  tempx=P6 .x+ d_dis[0 ][i]; tempy=P6 .y+ d_dis[1 ][i]; P6=cvPoint (tempx, tempy);i ++;
                                                  cvZero( inpaint_mask );
                                                  to_draw();
                                                  Sleep(100 );
                                                  printf("%d " ,j);
                                     }
                                   return 0 ;
                                  }
  }
  ;

//void on_mouse( int event, int x, int y, int flags, void* )
//{
// //   if( !img )
// //   return;
//             //if( event == CV_EVENT_LBUTTONUP || !(flags & CV_EVENT_FLAG_LBUTTON) )
//             // prev_pt = cvPoint(-1,-1);
//             //else if( event == CV_EVENT_LBUTTONDOWN );
//             //float K12=(P1.y-P2.y)/(P1.x-P2.x);
//             //float K23= (P2.y-P3.y)/(P2.x-P3.x);
//             //float B5= P5.y-(P5.x)*K12;
//             //float B6= P6.y-(P6.x)*K23;
//             //P4.x= (B6-B5)/(K12-K23);
//             //P4.y= K12*(P4.x)+B5;
//             //float K24= (P2.y-P4.y)/(P2.x-P4.x);
//             //float B4= P4.y-(P4.x)*K24;
//
//             
//    //cvShowImage( "image1", inpaint_mask );
//
//
//             //switch (Step)
//             //{
//             //case STEP0:
//             //             if( event == CV_EVENT_LBUTTONUP || !(flags & CV_EVENT_FLAG_LBUTTON) )
//             //             {
//             //                             if(stepp==1)
//             //                             {Step=STEP1;stepp=0;cout<<Step;
//             //             //prev_pt = cvPoint(-1,-1);
//             //                             showw=0;
//             //                             p1=prev_pt;p2=pt;
//             //                             cvLine( img0, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );
//             //                             prev_pt = cvPoint(-1,-1);
//             //                             pt= cvPoint(-1,-1);
//             //                             cvShowImage( "image", img );}
//             //             }
//             //             else if( event == CV_EVENT_LBUTTONDOWN )
//             //             {if(!showw) {prev_pt = cvPoint(x,y);showw=1;}
//             //             }
//             //             else if( event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) )
//             //             {
//             //                             pt = cvPoint(x,y);
//             //                             if( prev_pt.x < 0 )
//             //                             prev_pt = pt;
//             // /*       cvLine( inpaint_mask, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );*/
//             //                             img= cvCloneImage( img0 );
//             //                             cvLine( img, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );
//             //                /* prev_pt = pt;*/
//             //                             cvShowImage( "image", img );
//             //                             stepp=1;
//             //             }
//             //             break;
//             //case STEP1:
//             //             if( event == CV_EVENT_LBUTTONUP || !(flags & CV_EVENT_FLAG_LBUTTON) )
//             //             {
//             //                             if(stepp==1)
//             //                             {Step=STEP2;stepp=0;
//             //                             cvLine( img0, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );cout<<Step;
//             //                             cvShowImage( "image", img );
//             //                             showw=0;
//             //                             p3=pt;
//             //                 prev_pt = cvPoint(-1,-1);
//             //                             pt= cvPoint(-1,-1);
//             //                             pf1.x=p3.x;
//             //                             pf1.y=(p3.x-p1.x)*(p2.y-p1.y)/(p2.x-p1.x)+p1.y;
//             //                             pf2.x=p1.x+p2.x-p3.x;
//             //                             pf2.y=p2.y-(p3.x-p1.x)*(p2.y-p1.y)/(p2.x-p1.x);
//             //                             cout<<endl<<p1.x<<" "<<p1.y<<" "<<p2.x<<" "<<p2.y<<" "<<p3.x<<" "<<p3.y<<endl;
//             //                             cout<<endl<<pf1.x<<" "<<pf1.y<<" "<<pf2.x<<" "<<pf2.y<<endl;
//
//             //                             double aa=sqrt( (double)pow((p2.x-p1.x),2)+(double)pow((p2.y-p1.y),2) );
//             //                             printf("\n%lf\n",aa);
//             //                             for(int x=1;x<=cvGetSize(img).width;x++)
//             //                                             for(int y=1;y<=cvGetSize(img).height;y++)
//             //                                             {
//             //                                                             if(y==cvGetSize(img).height) cout<<endl<<x<<"/"<<cvGetSize(img).width<<" "<<y<<endl;
//             //                                                             double bb=sqrt((double)pow((x-pf1.x),2)+(double)pow((y-pf1.y),2) ) +sqrt( (double)pow((pf2.x-x),2)+(double)pow((pf2.y-y),2) );
//             //                                             /*            if(bb<200) cout<<bb<<" ";*/
//             //                                                             if(bb <aa)
//             //                                                             {
//             //                                                                             ((uchar*)(img0->imageData + img0->widthStep*y))[x*3] = 30;
//             //                                                                             ((uchar*)(img0->imageData + img0->widthStep*y))[x*3+1] = 30;
//             //                                                                             ((uchar*)(img0->imageData + img0->widthStep*y))[x*3+2] = 30;
//             //                                                                             //cout<<"a";
//             //                                         cvShowImage( "image", img0 );
//             //                                                 }
//             //                                             }
//             //                             }
//             //                                                                             cvWaitKey();
//             //             }
//             //             else if( event == CV_EVENT_LBUTTONDOWN )
//             //             {if(!showw) {prev_pt = cvPoint(x,y);showw=1;}
//             //             }
//             //             else if( event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) )
//             //             {
//             //                             pt = cvPoint(x,y);
//             //                             if( prev_pt.x < 0 )
//             //                             prev_pt = pt;
//             // /*       cvLine( inpaint_mask, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );*/
//             //                             img= cvCloneImage( img0 );
//             //                             cvLine( img, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );
//             //                /* prev_pt = pt;*/
//             //                             cvShowImage( "image", img );
//             //                             stepp=1;
//             //             }
//             //             break;
//             //case STEP2:
//             //             
//             //             if( event == CV_EVENT_LBUTTONUP || !(flags & CV_EVENT_FLAG_LBUTTON) )
//             //             {
//             //                             if(stepp==1)
//             //                             {Step=3;stepp=0;
//             //                             cvLine( img0, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );cout<<Step;
//             //                             showw=0;
//             //                             p4=pt;
//             //                 prev_pt = cvPoint(-1,-1);
//             //                             pt= cvPoint(-1,-1);
//             //                             cvShowImage( "image", img );
//             //                             cout<<endl<<p1.x<<" "<<p1.y<<" "<<p2.x<<" "<<p2.y<<" "<<p3.x<<" "<<p3.y<<" "<<p4.x<<" "<<p4.y<<endl;
//             //                             
//             //                             double aa=sqrt( (double)pow((p2.x-p1.x),2)+(double)pow((p2.y-p1.y),2) );
//             //                             CvPoint tf1=pf1,tf2=pf2;
//             //                             printf("\n%lf\n",aa);
//             //                             for(int temp=0;temp<=p4.y-p2.y;temp++)
//             //                             {cout<<"qrrqtytyyre"<<endl;
//             //                             int ytemp=temp,xtemp=temp*(p2.y-p1.y)/(p2.x-p1.x);
//             //                             pf1.x=tf1.x-xtemp;pf2.x=tf2.x-xtemp;
//             //                             pf1.y=tf1.y-ytemp;pf2.y=tf2.y-ytemp;
//             //                             for(int x=1;x<=cvGetSize(img).width;x++)
//             //                                             for(int y=1;y<=cvGetSize(img).height;y++)
//             //                                             {
//             //                                                             if(y==cvGetSize(img).height) cout<<endl<<x<<"/"<<cvGetSize(img).width<<" "<<y<<endl;
//             //                                                             double bb=sqrt((double)pow((x-pf1.x),2)+(double)pow((y-pf1.y),2) ) +sqrt( (double)pow((pf2.x-x),2)+(double)pow((pf2.y-y),2) );
//             //                                             /*            if(bb<200) cout<<bb<<" ";*/
//             //                                                             if(bb <aa)
//             //                                                             {
//             //                                                                             ((uchar*)(img0->imageData + img0->widthStep*y))[x*3] = 30;
//             //                                                                             ((uchar*)(img0->imageData + img0->widthStep*y))[x*3+1] = 30;
//             //                                                                             ((uchar*)(img0->imageData + img0->widthStep*y))[x*3+2] = 30;
//             //                                                                             //cout<<"a";
//             //                                         cvShowImage( "image", img0 );
//             //                                                 }
//             //                                             }
//             //                             }
//             //                             }
//
//
//             //             }
//             //             else if( event == CV_EVENT_LBUTTONDOWN )
//             //             {if(!showw) {prev_pt = cvPoint(x,y);showw=1;}
//             //             }
//             //             else if( event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) )
//             //             {
//             //                             pt = cvPoint(x,y);
//             //                             if( prev_pt.x < 0 )
//             //                             prev_pt = pt;
//             // /*       cvLine( inpaint_mask, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );*/
//             //                             img= cvCloneImage( img0 );
//             //                             cvLine( img, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );
//             //                /* prev_pt = pt;*/
//             //                             cvShowImage( "image", img );
//             //                             stepp=1;
//             //             }
//             //             break;
//             //default:
//             //             cout<<"somethingwrong"<<endl;
//             //             break;
//             //}
//}
int clik_count= 1;
int temp_point[ 2][7 ];
//void on_mouse( int event, int x , int y, int flags, void* )
//{
//    if( !img )
//    return;
//
//    if( event == CV_EVENT_LBUTTONUP || !(flags & CV_EVENT_FLAG_LBUTTON ) )
//    prev_pt = cvPoint(- 1,-1 );
//    else if ( event == CV_EVENT_LBUTTONDOWN )
//      {
//                   prev_pt = cvPoint( x,y );
//                   cout<<"x:" <<prev_pt. x<<" y:" <<prev_pt. y<<" count:" <<clik_count<< endl;
//
//                   temp_point[0 ][clik_count]= prev_pt.x ;
//                   temp_point[1 ][clik_count]= prev_pt.y ;
//
//                   clik_count++;
//                   if(clik_count >6)
//                     {
//                                  cube kk (temp_point);
//                                  kk.to_draw ();
//                                  clik_count=1 ;
//                     }
//                  }
//    else if ( event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON ) )
//    {
//        CvPoint pt = cvPoint(x ,y);
//        //if( prev_pt.x < 0 )
//        //prev_pt = pt;
//        //cvLine( inpaint_mask, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );
//        //cvLine( img, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );
//        //prev_pt = pt;
//        //cvShowImage( "image", img );
//    }
//}

int main( int argc, char** argv )
{
    char* filename = argc >= 2 ? argv[1 ] : (char *)"i:\\1.jpg";

    if( (img0 = cvLoadImage (filename,- 1)) == 0 )
    return 0 ;

    printf( "Hallo keyty: \n" );
                
    cvNamedWindow( "image" , 1 );
    cvNamedWindow( "image1" , 1 );

//                 cvSetMouseCallback ( "image" , on_mouse , 0 );

    img = cvCloneImage( img0 );
    inpainted = cvCloneImage( img0 );
    inpaint_mask = cvCreateImage( cvGetSize( img), IPL_DEPTH_8U, 1 );
                 //img0 原始图像 img 原始图像备份
                 //inpainted 操作图像
                 //inpaint_mask 灰度操作图像
    cvZero( inpaint_mask );
    //cvZero( inpainted );

	auto_point();
                 //cube hhhhh(t_point) ;
                 //hhhhh.to_draw ();
              
	
				//CvPoint temp[7];
                 //int i=1;
                 //temp[i]=cvPoint(200,500);i++;
                 //temp[i]=cvPoint(200,300);i++;
                 //temp[i]=cvPoint(300,160);i++;
                 //temp[i]=cvPoint(500,160);i++;
                 //temp[i]=cvPoint(500,400);i++;
                 //temp[i]=cvPoint(400,500);i++;

                 //hhhhh.to_move(temp,100);
                 //CvPoint P1= cvPoint(90,450);
  //CvPoint P2= cvPoint(90,200);
  //CvPoint P3= cvPoint(220,130);
  //CvPoint P4= cvPoint(460,130);
  //CvPoint P5= cvPoint(460,380);
  //CvPoint P6= cvPoint(310,450);
    cvShowImage( "image" , img );
  /*   cvShowImage( "watershed transform", inpainted );*/
    //cvSetMouseCallback( "image", on_mouse, 0 );
//
//             for(int i=0;i<inpaint_mask->height;i++)
//             {
//                             for (int j=0;j<inpaint_mask->width;j++)
//                  {
//                                              int y=i,x=j;
//                                              float k1=(0-70.0)/130.0, k2=-70.0/130.0;
//                                              float b1=200-90*k1, b2=380-460*k2;
//                                              if( x<460 && x>90 && y<450 && y>130 )
//                                              {
//                                              int temp1=k1*x+b1, temp2=k2*x+b2;
////printf("%d %d\n",y,temp1);
//                                               if( y>temp1 && y<temp2)
//                                                ((uchar*)(inpaint_mask->imageData + inpaint_mask->widthStep*i))[j]=155;
//                                              }
//                                              else
//                                               ((uchar*)(inpaint_mask->imageData + inpaint_mask->widthStep*i))[j]=0;
//                             }
//
//
//             }
//     cvShowImage( "image1", inpaint_mask );
                 //float x1=-1,x2=-1,y1=-1,y2=-1; float x3=-1,x4=-1,y3=-1,y4=-1;
                 //x1=P1.x;x2=P2.x;y1=P1.y;y2=P2.y;
                 //float a12=(x1-x2)/(y1-y2), b12=x1-a12*y1;
                 //x3=P4.x;x4=P5.x;y3=P4.y;y4=P5.y;
                 //float a45=(x3-x4)/(y3-y4), b45=x3-a45*y3;

                 //x1=P2.x; x2=P3.x;y1=P2.y; y2=P3.y;
                 //float k23=(y1-y2)/(x1-x2), b23=y1-k23*x1;
                 //x3=P1.x; x4=P6.x;y3=P1.y; y4=P6.y;
                 //float k16=(y3-y4)/(x3-x4), b16=y3-k16*x3;

                 //x1=P4.x; x2=P3.x;y1=P4.y; y2=P3.y;
                 //float k34=(y1-y2)/(x1-x2), b34=y1-k34*x1;
                 //x3=P5.x; x4=P6.x;y3=P5.y; y4=P6.y;
                 //float k56=(y3-y4)/(x3-x4), b56=y3-k56*x3;
                 //
                 //float b27=P2.y-P2.x*k16;
                 //float b47=P4.y-P4.x*k56;
                 //int tempx=(b27-b47)/(k56-k16);
                 //int tempy=k16*tempx+b27;
                 //CvPoint P7= cvPoint(tempx,tempy);
                 //printf("%d %d",tempx,tempy);

                 //x1=P7.x;x2=P6.x;y1=P7.y;y2=P6.y;
                 //float a67=(x1-x2)/(y1-y2), b67=x1-a12*y1;

                 //for(int i=0;i<inpaint_mask->height;i++)
                 //{
                 //             for (int j=0;j<inpaint_mask->width;j++)
                 //     {
                 //                              int y=i,x=j;
                 //                             
                 //                              int temp1=a12*y+b12;        
                 //                              int temp2=a45*y+b45;
                 //                              if( x>temp1 && x<temp2)
                 //                              {
                 //                               
                 //                                int temp1=k23*x+b23;      
                 //                                int temp2=k16*x+b16;
                 //                                if(y>temp1 && y<temp2)
                 //                                {
                 //                                             int temp1=k34*x+b34;         
                 //                                             int temp2=k56*x+b56;
                 //                                             if(y>temp1 && y<temp2)
                 //                                             {
                 //                                                             int temp1=x*k16+b27;
                 //                                                             int temp2=y*a67+b67;
                 //                                                             int temp3=k56*x+b47;
                 //                                                             if((y>=temp1 && x< temp2) || (y>=temp3 && x>=temp2))
                 //                                                             {
                 //                                                               int hhh=x-P7.x;if(hhh<0) hhh=0-hhh;
                 //                                                               int qqq=P7.x-P1.x;
                 //                                                               if(y>=temp3 && x>=temp2) qqq=P7.x-P5.x;
                 //                                                               if(qqq<0) qqq=0-qqq;
                 //                                                               float kkk=(200.0-0.0)/qqq*hhh;
                 //                                                               hhh=255-kkk;
                 //                                                             //  printf("%d %d\n",hhh, kkk);
                 //                                                               ((uchar*)(inpaint_mask->imageData + inpaint_mask->widthStep*i))[j]=hhh;
                 //                                                             }
                 //                                                             else
                 //                                                             {
                 //                                                               int temp2=y*a67+b67;
                 //                                                               float hhh=x-P7.x;if(hhh<0) hhh=0-hhh;
                 //                                                               int qqq=P7.x-P1.x;
                 //                                                               if(x>=temp2) qqq=P7.x-P5.x;
                 //                                                               if(qqq<0) qqq=0-qqq;
                 //                                                               float kkk=(200.0-0.0)/qqq*hhh;
                 //                                                               hhh=255-kkk;
                 //                                                               int aaa=y-P3.y;if(aaa<0) aaa=0-aaa;
                 //                                                               int sss=P7.y-P3.y; if(sss<0) sss=0-sss;
                 //                                                               float ddd=(hhh)/sss*aaa;
                 //                                                               aaa=ddd;
                 //                                       ((uchar*)(inpaint_mask->imageData + inpaint_mask->widthStep*i))[j]=aaa;
                 //                                                             }
                 //                                             }
                 //                              else
                 //                               ((uchar*)(inpaint_mask->imageData + inpaint_mask->widthStep*i))[j]=150;
                 //                                }
                 //                              else
                 //                               ((uchar*)(inpaint_mask->imageData + inpaint_mask->widthStep*i))[j]=150;
                 //                              }
                 //                              else
                 //                               ((uchar*)(inpaint_mask->imageData + inpaint_mask->widthStep*i))[j]=150;
                 //             }


                 //}
  //    cvShowImage( "image1", inpaint_mask );


    for(;;)
    {
        cvWaitKey(0 );
    }

return 1;
}
 
  
