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
    Mat imageCopy2(image.rows, image.cols, image.type());
    Mat imageCopy3(image.rows, image.cols, image.type());

	uchar r, g, b;
    for (int i = 0; i < image.rows; ++i)
    {
		Vec3b* pixel = image.ptr<Vec3b>(i);
        for (int j = 0; j < image.cols; ++j)
        {
            r = pixel[j][2];
            g = pixel[j][1];
            b = pixel[j][0];

			imageCopy.ptr<Vec3b>(image.rows -j)[i] = Vec3b(b,g,r);
            imageCopy2.ptr<Vec3b>(image.rows -i)[image.cols - j] = Vec3b(b,g,r);
            imageCopy3.ptr<Vec3b>(j)[image.rows - i] = Vec3b(b,g,r);
        }
    }

 	imshow( ImageFile, image );	                   //show window containing images
	imshow( "ImageRotate90.ppm", imageCopy );	
    imshow( "ImageRotate180.ppm", imageCopy2 );	
    imshow( "ImageRotate270.ppm", imageCopy3 );	
 	waitKey(0);	     //to exit
 	return 0;
}