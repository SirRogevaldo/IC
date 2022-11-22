#include <opencv2/opencv.hpp>
using namespace cv;

int main( int argc, char** argv )
{
 	char* ImageFile = argv[1];	              //image file 
 	Mat image;			                     //mat object for storing data
 	image = imread( ImageFile, IMREAD_COLOR );	         //read file
 	if( argc != 2 || !image.data )		
 	{
 	  	printf( " No image data \n " );
 	  	return -1;
 	}
 	namedWindow( ImageFile, WINDOW_AUTOSIZE );	
	
	Mat imageCopy(image.rows, image.cols, image.type());



	uchar r, g, b;
    double mult = 0.2; // set to input
    for (int i = 0; i < image.rows; ++i)
    {
		Vec3b* pixel = image.ptr<Vec3b>(i);
        for (int j = 0; j < image.cols; ++j)
        {
            r = pixel[j][2];
            g = pixel[j][1];
            b = pixel[j][0];

			imageCopy.ptr<Vec3b>(i)[j] = Vec3b(saturate_cast<uchar>(b*mult),saturate_cast<uchar>(g*mult),saturate_cast<uchar>(r*mult));
        }
    }

 	imshow( ImageFile, image );	                   //show window containing images
	imshow( "ImageBright.ppm", imageCopy );	
 	waitKey(0);	     //to exit
 	return 0;
}