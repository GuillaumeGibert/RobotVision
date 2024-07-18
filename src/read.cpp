#include <iostream>
#include <string>
#include "opencv2/core.hpp"

// see https://docs.opencv.org/3.4/d4/da4/group__core__xml.html for more infos

int main (int argc, char** argv)
{
	// default filename
	std::string filename = "../data/test_reading.yml";
	
	// checks if an argument was passed to the program to rewrite filename
	if (argc == 2)
	{
		filename = argv[1];
	}
	
        // creates a reader
	cv::FileStorage fs(filename, cv::FileStorage::READ);
	
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
		
	// first method: use (type) operator on FileNode.
	int fps = (int)fs["FPS"];
	std::cout << "fps= " << fps << std::endl;
	
	// second method: use FileNode::operator >>
	cv::String date;
	fs["Time"] >> date;
	std::cout << "date= " << date << std::endl;
	
	// reads the data (Matrix) in the field "Result" from the file
        cv::Mat r;
	fs["Result"] >> r;
	std::cout << "result= " << r << std::endl;
	
	// releases the reader
        fs.release();
	
        return 0;
}