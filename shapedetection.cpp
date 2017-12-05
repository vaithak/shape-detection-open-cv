#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

/*void creatingtrackbars()
{
  namedWindow("TRACKBARS",WINDOW)
}*/

int main()
{
  Mat source = imread("shapes.jpg");
  Mat grey;
  cvtColor(source,grey,COLOR_RGB2GRAY);
  imshow("source",source);
  Mat thresh;
  threshold(grey,thresh,5.0, 255.0 , THRESH_BINARY);
  //imshow("threshold",thresh);
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  Mat eroded;
  Mat structure = getStructuringElement(MORPH_ELLIPSE,Size(3,7),Point(-1,-1) );
        erode(thresh,eroded,structure);
  findContours( eroded, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
         vector<Point> approx;
         if(contours.size()>0)
        {
        	Scalar color = Scalar(0,255,0);
            for(int i = 0; i< contours.size(); i++ )
	     	{
		    	approxPolyDP(Mat(contours[i]),approx,3,true);
		    	drawContours(source, contours, i, color, 2, 8, hierarchy, 0, Point() );
		    	Moments mom=moments(approx);
		    	Point put = Point((mom.m10/ mom.m00), (mom.m01/mom.m00));
		    	if(approx.size()==3)
		    		{
		    			putText(source, "Triangle", put, FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255, 255, 255), 1);
		    		}
		    	else if(approx.size()==6)
		    		{
 						putText(source, "Hexagon", put, FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255, 255, 255), 1);
		    		}
		    	else if(approx.size()==4)
		    		{
		    			double check1 = sqrt(((approx[1].x-approx[0].x)*(approx[1].x-approx[0].x)) + ((approx[1].y-approx[0].y)*(approx[1].y-approx[0].y)));
		    			double check2 = sqrt(((approx[1].x-approx[2].x)*(approx[1].x-approx[2].x)) + ((approx[1].y-approx[2].y)*(approx[1].y-approx[2].y)));
		    			cout<<check1-check2<<endl;
		    			if(abs(check1-check2)<30)
		    			  putText(source, "Square", put, FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255, 255, 255), 1);
		    			else
		    			  putText(source, "Rectangle", put, FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255, 255, 255), 1);
		    		}
		    	else if(approx.size()==5)
		    	    {
		    	    	putText(source, "Pentagon", put, FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255, 255, 255), 1);
		    	    }	
		    	else if(approx.size()>=10)
		    		{
		    			putText(source, "Circle", put, FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255, 255, 255), 1);
		    		}

            }
    	}
  imwrite("output.jpg",source); 	
  namedWindow("source",WINDOW_AUTOSIZE);  	
  imshow("source",source); 	
  waitKey(0);
}