#include <fstream>
#include <iostream>
#include <string>
#include <sstream> 
#include "opencv\cv.h"
#include "opencv\highgui.h"
using namespace cv;
using namespace std;
extern int readDir(char *dirName, vector<string> &filesName);
int test18(int argc, char *argv[])
{
                      
	string  dirName = "G:/F/YOLO/yolo-v2/darknet-master/train-plate-2class/car0-hong-doublewhite-11-biaoji-train";
                                    
	int class1=1;
	string  imagepath = "G:/F/YOLO/yolo-v2/darknet-master/train-plate-2class/VOCdevkit/VOC2007/JPEGImages";
	string  labelpath = "G:/F/YOLO/yolo-v2/darknet-master/train-plate-2class/VOCdevkit/VOC2007/labels";

	vector<string> filesName;
	readDir((char*)dirName.c_str(), filesName);

	
	for (int i = 0; i<filesName.size(); i++)
	{
		string imgPath = filesName[i];
		int pos = imgPath.find_last_of('/');
		int pos2 = imgPath.find_first_of('.');
		string name1 = imgPath.substr(pos + 1, pos2 - pos - 1);
		string imgPath1 = imgPath.substr(0, pos);
		pos = imgPath1.find_last_of('/');

		//ostringstream os;
		//os << i + 4134;
		

		Mat img = imread(imgPath.c_str());
		if (img.data == NULL)
		{
			printf("img.data null:%s\n", imgPath.c_str());
			system("pause");
			return 0;
		}

		string temp = imgPath;
		temp.replace(imgPath.find_last_of("."), 4, ".txt");
		fstream fin1;
		fin1.open(temp);
		if (!fin1.is_open())
		{
			cout << "fin1 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}

		string str; int label; int x1, y1, x2, y2;

		fin1 >> str>> label >> x1 >> y1 >> x2 >> y2;
		int width = img.cols; int height = img.rows;
		float cenx;  float ceny; float cenw; float cenh;
		cenx = (x1 + x2)*1.0 / 2/width;
		ceny = (y1 + y2)*1.0 / 2/height;
		cenw = (x2 - x1 + 1)*1.0 / width;
		cenh = (y2-y1+1)*1.0 / height;

		
		string labelname = labelpath + "/" + name1 + ".txt";

		
      
		

		fstream flabel;
		flabel.open(labelname, ios::out);
		if (!flabel.is_open())
		{
			cout << "flabel 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}
		flabel << class1 << " " << cenx << " " << ceny << " " << cenw << " " << cenh<<endl;
		flabel.close();

		

		string imagename = imagepath + "/" + name1 + ".jpg";

		imwrite(imagename, img);
	}


	return 0;
}
int test18_1(int argc, char *argv[])
{

	string  dirName = "G:/F/YOLO/yolo-v2/darknet-master/test-plate-2class/car0-hong-singlewhite-10-biaoji-test";

	int class1 = 0; int src_class1 = 10;
	string  imagepath = "G:/F/YOLO/yolo-v2/darknet-master/test-plate-2class/image";
	string  labelpath = "G:/F/YOLO/yolo-v2/darknet-master/test-plate-2class/labels";

	vector<string> filesName;
	readDir((char*)dirName.c_str(), filesName);


	for (int i = 0; i<filesName.size(); i++)
	{
		string imgPath = filesName[i];
		int pos = imgPath.find_last_of('/');
		int pos2 = imgPath.find_first_of('.');
		string name1 = imgPath.substr(pos + 1, pos2 - pos - 1);
		string imgPath1 = imgPath.substr(0, pos);
		pos = imgPath1.find_last_of('/');

		//ostringstream os;
		//os << i + 4134;

		cout << imgPath.c_str()<<endl;
		Mat img = imread(imgPath.c_str());
		if (img.data == NULL)
		{
			printf("img.data null:%s\n", imgPath.c_str());
			system("pause");
			return 0;
		}

		string temp = imgPath;
		temp.replace(imgPath.find_last_of("."), 4, ".txt");
		fstream fin1;
		fin1.open(temp);
		if (!fin1.is_open())
		{
			cout << "fin1 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}

		string line1;
		while (getline(fin1, line1))
		{
			string str; int label; int x1, y1, x2, y2;
			stringstream str_s(line1);
			str_s >> str >> label >> x1 >> y1 >> x2 >> y2;
			int width = img.cols; int height = img.rows;
			float cenx;  float ceny; float cenw; float cenh;
			cenx = (x1 + x2)*1.0 / 2 / width;
			ceny = (y1 + y2)*1.0 / 2 / height;
			cenw = (x2 - x1 + 1)*1.0 / width;
			cenh = (y2 - y1 + 1)*1.0 / height;
			if (label == src_class1)
			{
				string labelname = labelpath + "/" + name1 + ".txt";
				fstream flabel;
				flabel.open(labelname, ios::out);
				if (!flabel.is_open())
				{
					cout << "flabel 文件数据打开错误！" << endl;
					system("pause");
					return false;
				}
				flabel << class1 << " " << cenx << " " << ceny << " " << cenw << " " << cenh << endl;
				flabel.close();
			}
		}
		


		



		string imagename = imagepath + "/" + name1 + ".jpg";

		imwrite(imagename, img);
	}


	return 0;
}

int test18_2(int argc, char *argv[])
{
	////train
	//int class2 = 3;
	//int class1[3] = {10,11,5};//0,1,2;
	//string  dirName = "G:/F/YOLO/yolo-v2/darknet-master/train-plate-3class/car0-hong-doublewhite-11-biaoji-train";
	//string  imagepath = "G:/F/YOLO/yolo-v2/darknet-master/train-plate-3class/VOCdevkit/VOC2007/JPEGImages";
	//string  labelpath = "G:/F/YOLO/yolo-v2/darknet-master/train-plate-3class/VOCdevkit/VOC2007/labels";

	////test
	int class2 = 3;
	int class1[3] = { 10, 11, 5 };//0,1,2;
	string  dirName = "G:/F/YOLO/yolo-v2/darknet-master/test-plate-3class/car0-hong-singlewhite-10-biaoji-test";
	string  imagepath = "G:/F/YOLO/yolo-v2/darknet-master/test-plate-3class/image";
	string  labelpath = "G:/F/YOLO/yolo-v2/darknet-master/test-plate-3class/labels";

	vector<string> filesName;
	readDir((char*)dirName.c_str(), filesName);


	for (int i = 0; i<filesName.size(); i++)
	{
		string imgPath = filesName[i];
		int pos = imgPath.find_last_of('/');
		int pos2 = imgPath.find_first_of('.');
		string name1 = imgPath.substr(pos + 1, pos2 - pos - 1);
		string imgPath1 = imgPath.substr(0, pos);
		pos = imgPath1.find_last_of('/');

		//ostringstream os;
		//os << i + 4134;

		cout << imgPath.c_str() << endl;
		Mat img = imread(imgPath.c_str());
		if (img.data == NULL)
		{
			printf("img.data null:%s\n", imgPath.c_str());
			system("pause");
			return 0;
		}

		string temp = imgPath;
		temp.replace(imgPath.find_last_of("."), 4, ".txt");
		fstream fin1;
		fin1.open(temp);
		if (!fin1.is_open())
		{
			cout << "fin1 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}

		string labelname = labelpath + "/" + name1 + ".txt";
		fstream flabel;
		flabel.open(labelname, ios::out);
		if (!flabel.is_open())
		{
			cout << "flabel 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}

		string line1;
		while (getline(fin1, line1))
		{
			string str; int label; int x1, y1, x2, y2;
			stringstream str_s(line1);
			str_s >> str >> label >> x1 >> y1 >> x2 >> y2;
			int width = img.cols; int height = img.rows;
			float cenx;  float ceny; float cenw; float cenh;
			cenx = (x1 + x2)*1.0 / 2 / width;
			ceny = (y1 + y2)*1.0 / 2 / height;
			cenw = (x2 - x1 + 1)*1.0 / width;
			cenh = (y2 - y1 + 1)*1.0 / height;
			for (int j = 0; j < class2; j++)
			{
				if (label == class1[j])
				{
					
					flabel << j << " " << cenx << " " << ceny << " " << cenw << " " << cenh << endl;
					
				}
			}
			
		}

		flabel.close();





		string imagename = imagepath + "/" + name1 + ".jpg";

		imwrite(imagename, img);
	}


	return 0;
}

