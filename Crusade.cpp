#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	
	namedWindow("cam",0);

	VideoCapture botvision(0);       //video captured by the bot camera
	Mat frame;			 //frames obtained from the bot camera
	while(1)
	{
		botvision>>frame;

//the video feed frames obtained are converted to gray scale

		Mat grayscaleImage;	       
		cvtColor(frame,grayscaleImage,CV_RGB2GRAY);	
//converting grayscale image to binary with threshold 100

		Mat binaryImage(grayscaleImage.rows,grayscaleImage.cols,CV_8UC1,Scalar(0));
		for(int i=0;i<grayscaleImage.rows;i++)
			for(int j=0;i<grayscaleImage.cols;j++)
				if(grayscaleImage<uchar>(i,j)<100)
					binaryImage<uchar>(i,j)=0;
				else
					binaryImage<uchar>(i,j)=255;

		//dilating and eroding the binary image						  
		dilate(binaryImage, binaryImage, Mat());
		dilate(binaryImage, binaryImage, Mat());
		erode(binaryImage, binaryImage, Mat());
		erode(binaryImage, binaryImage, Mat());
		  
		//making the edges black
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
		  Canny( binaryImage, canny_output, thresh, thresh*2, 3 );
		  /// Find contours
		  findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE, Point(0, 0) );

		  /// Draw contours
		  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC1);
		  if(contours.size()>0){
		  for( int i = 0; i< contours.size(); i++ )
		     {
		       Scalar color = Scalar(255);
		       //area = cv.contourArea(contours);
		       
			//drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
			if(contourArea(contours[i])>maxarea){
			  maxarea=contourArea(contours[i]);
			  index=i;
			}
		      drawContours( drawing, contours, index, color, 2, 8, hierarchy, 1, Point() );
		      }
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
		  namedWindow("Contours", WINDOW_NORMAL);
		  namedWindow("win", WINDOW_NORMAL);
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
}	
