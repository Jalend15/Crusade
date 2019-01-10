#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat img=imread("77.jpg",0);
//Mat img=imread("66.jpg",0);
//Mat img=imread("venn2.png",0);
Mat img1;

int isvalid(int i,int j)
{
    if(((i==0)&&(j==0))||((i==img.rows-1)&&(j==img.cols-1)))
        return 0;
    else if(((i>0)&&(j==0))||((i==0)&&(j>0))||((i<img.rows-1)&&(j==img.cols-1))||((i==img.rows-1)&&(j<img.cols-1)))
        return -1;
    else
        return 1;
}
int erosion(Mat img2,int i, int j)
{
    int x,y;
   
            for(x=0;x<3;x++)
            {
                for(y=0;y<3;y++)
                {
                    if(img2.at<uchar>(i-1+x,j-1+y) == 0)
                        return 1;
                }
            }
       
   
}
int dilation(Mat img2,int i,int j)
{
    int x,y;
   
            for(x=0;x<3;x++)
            {
                for(y=0;y<3;y++)
                {
                    if(img2.at<uchar>(i-1+x,j-1+y) == 255)
                        return 1;
                }
            }
   
   
}

void binary(){
  int i, j;
  img1=img.clone();
  for(i=0;i<img.rows;i++){
    for(j=0;j<img.cols;j++){
      if(img.at<uchar>(i,j)>128)
        img1.at<uchar>(i,j)=255;
      else
        img1.at<uchar>(i,j)=0;
    }
  }
}


int main() {
  int i, j, thresh=200, Y;
  GaussianBlur(img1,img1,Size(3,3),0,0);
  GaussianBlur(img1,img1,Size(3,3),0,0);
  GaussianBlur(img1,img1,Size(3,3),0,0);
  GaussianBlur(img1,img1,Size(3,3),0,0);
  GaussianBlur(img1,img1,Size(3,3),0,0);
  GaussianBlur(img1,img1,Size(3,3),0,0);
  GaussianBlur(img1,img1,Size(3,3),0,0);
  GaussianBlur(img1,img1,Size(3,3),0,0);
  GaussianBlur(img1,img1,Size(3,3),0,0);
  GaussianBlur(img1,img1,Size(3,3),0,0);
  GaussianBlur(img1,img1,Size(3,3),0,0);
  GaussianBlur(img1,img1,Size(3,3),0,0);
  GaussianBlur(img1,img1,Size(3,3),0,0);
  GaussianBlur(img1,img1,Size(3,3),0,0);
  GaussianBlur(img1,img1,Size(3,3),0,0);
  binary();
  dilate(img1, img1, Mat());
  dilate(img1, img1, Mat());
  erode(img1, img1, Mat());
  erode(img1, img1, Mat());
  for(i=0; i<img.rows; i++){
    img1.at<uchar>(i,0)=0;
    img1.at<uchar>(i,img.cols-1)=0;
  }
  for(i=0; i<img.cols; i++){
    img1.at<uchar>(0,i)=0;
    img1.at<uchar>(img.rows-1,i)=0;
  }
  int maxarea=0, index;
  Mat canny_output;
  vector<vector<Point>> contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using canny
  Canny( img1, canny_output, thresh, thresh*2, 3 );
  /// Find contours
  findContours( canny_output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0) );

  /// Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC1);
  //if(contours.size()>0){
  /*for( int i = 0; i< contours.size(); i++ )
     {
      
       //area = cv.contourArea(contours);
       
        //drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
        /*if(contourArea(contours[i])>maxarea){
          maxarea=contourArea(contours[i]);
          index=i;
        }*/
	int idx = 0;
    for( ; idx >= 0; idx = hierarchy[idx][0] )
    {
        Scalar color( 255);
        drawContours( drawing, contours, idx, color, CV_FILLED, 8, hierarchy );
    }
	

vector<Vec4i> lines;
HoughLinesP(drawing, lines, 1, CV_PI/180, 50, 50, 40 );

for( size_t i = 0; i < lines.size(); i++ )
{
  Vec4i l = lines[i];
  line( drawing, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255), 3, CV_AA);
}
  /*vector<vector<Point>> contours;
  vector<Vec4i> hierarchy;
  Canny(img1, img1, thresh, 2*thresh);
  findContours( img1, img1, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC1);
  if(contours.size()>0){
  for( int i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar(255);
     }
     drawContours( drawing, contours, index, color, 2, 8, hierarchy, 0, Point() );*/
  namedWindow("Contours", 1);
  namedWindow("win", 1);
  Moments M = moments(drawing, true);
      int cx = M.m01/M.m00;
      int cy = M.m10/M.m00;
  /// Show in a window
  imshow( "Contours", drawing );
  imshow("win",img1);
  if(abs(cy-img.cols/2)<64)
        Y=0;
      else
        Y=((cy-img.cols/2)*90)/(img.cols/2);
  cout<<maxarea<<" "<<cx<<" "<<cy<<" "<<img.rows<<" "<<img.cols<<" "<<Y<<endl;
  waitKey(0);
  return 0;
}
