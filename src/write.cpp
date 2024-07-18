#include <iostream>
#include <string>
#include "opencv2/core.hpp"

// see https://docs.opencv.org/3.4/d4/da4/group__core__xml.html for more infos

int main (int argc, char** argv)
{
	// default filename
	std::string filename = "../data/test_writing.yml";
	
	// checks if an argument was passed to the program to rewrite filename
	if (argc == 2)
	{
		filename = argv[1];
	}
	
        // creates a writer
        cv::FileStorage fs(filename, cv::FileStorage::WRITE);
	
	// checks if the file storage is opened before continuing
	if (fs.isOpened() == false)
	{
		std::cout << "[ERROR] Could not open the file storage: " <<  filename << " !"<< std::endl;
		return 1;
	}
	else
	{
		std::cout << "[INFO] The file storage: " << filename << " was opened successfully!" << std::endl;
	}

        // saves an int value in the field FPS
        int fps = 5;
        fs << "FPS" << fps;
	
	// saves a text string in the field Time
	time_t rawtime; time(&rawtime);
	fs << "Time" << asctime(localtime(&rawtime));
	
        // saves a matrix in the field Result
        cv::Mat m = cv::Mat::eye(2,3, CV_32F);
        fs << "Result" << m;

        // releases the writer
        fs.release();

        return 0;
}