/*
 * main.cpp
 *
 *  Created on: 2017��8��14��
 *      Author: JYF
 */

#include "landing.h"

int main(int argc, char** argv){
	string image_path="I:/TestOpenCV/Images/white_h_1.jpg";
	string seed="./templates/h_0.jpg";
	string dir="./templates/";
	int ksize=1;

	Mat original=imread(image_path);
	Mat _tmpl;

	blur(original, original, Size(ksize, ksize));
	Mat rgbImage=alignImage(original, MAX_SIZE);
	Mat _s=getHSVImage(rgbImage, "s");
	Mat _v=getHSVImage(rgbImage, "v");
	Mat sv[2];
	Mat bi[2];
	sv[0]=_s;
	sv[1]=_v;
	imshow("hsv", _s);
	for(int i=0;i<2;++i){
		Mat bg(sv[i].size(), CV_8UC1);
		bg.setTo(255);
		threshold(sv[i],bi[i],250,255,THRESH_OTSU);
		subtract(bg,bi[i],bi[i]);

		//createSamples(seed, dir, 30);
		//createTemplate("./file_list.txt", "./templates.txt");
		_tmpl=loadTemplate("./templates.txt");

		vector<Rect> contours;

		getContours(bi[i], contours);

		int H_index=-1;
		if(contours.size()>=1)
			H_index=KNN(bi[i], _tmpl, contours);

		if(H_index>=0)
			rectangle(rgbImage, contours[H_index], Scalar(0,255,255),2);
	}
	imshow("rgb", rgbImage);
	//imshow("thresh", bi);
	waitKey();

	return 0;
}


