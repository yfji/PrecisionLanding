/*
 * main.cpp
 *
 *  Created on: 2017Äê8ÔÂ14ÈÕ
 *      Author: JYF
 */

#include "landing.h"
typedef unsigned int uint;

int main(int argc, char** argv){
	string image_path="I:/TestOpenCV/Images/H_label.jpg";
	string seed="./templates/h_0.jpg";
	string dir="./templates/";
	int ksize=7;

	Mat original=imread(image_path);
	Mat _tmpl;

	blur(original, original, Size(ksize, ksize));
	Mat rgbImage=alignImage(original, MAX_SIZE);
	Mat sa=getHSVImage(rgbImage);
	Mat bi;
	Mat bg(sa.size(), CV_8UC1);
	bg.setTo(255);
	threshold(sa,bi,1,255,THRESH_OTSU);
	subtract(bg,bi,bi);

	//createSamples(seed, dir, 30);
	//createTemplate("./file_list.txt", "./templates.txt");
	//Mat _tmpl=loadTemplate("./templates.txt");

	vector<Rect> contours;
	Mat dummy;
	bi.copyTo(dummy);
	getContours(dummy, contours);

	int H_index=0;

	if(contours.size()>1)
		H_index=KNN(bi, _tmpl, contours);

	for(uint k=0;k<contours.size();++k){
		rectangle(rgbImage, contours[k], Scalar(0,255,255),2);
	}

	imshow("rgb", rgbImage);
	imshow("hsv", bi);

	waitKey();

	return 0;
}


