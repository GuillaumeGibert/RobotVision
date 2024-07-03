#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/calib3d.hpp>

#define CAM_PARAMS_FILENAME "./data/microsoft_livecam_hd3000.xml"
#define FPS 30.0
#define BOARDSIZE_WIDTH 9
#define BOARDSIZE_HEIGHT 7
#define WIN_SIZE 11
#define BOARD_SQUARE_SIZE 2

bool readCameraParameters(std::string filename, cv::Mat &camMatrix, cv::Mat & distCoeffs)
{
	cv::FileStorage fs(filename, cv::FileStorage::READ);
	if (!fs.isOpened())
	{
		std::cout << "[ERROR] Could not open the camera parameter file storage: " <<  filename << " !"<< std::endl;
		return false;
	}
	
	fs["camera_matrix"] >> camMatrix;
	fs["distortion_coefficients"] >> distCoeffs;
	
	return true;
}

int main( int argc, char** argv )
{
	// initializes main parameters
	std::string sCameraParamFilename = CAM_PARAMS_FILENAME;
	float fFPS = FPS;
	int iBoardSizeWidth = BOARDSIZE_WIDTH;
	int iBoardSizeHeight = BOARDSIZE_HEIGHT;
	int iWinSize = WIN_SIZE;
	int iSquareSize = BOARD_SQUARE_SIZE;
	
	// updates main parameters from arguments
	int opt;
	while ((opt = getopt (argc, argv, ":c:f:s:a:i:")) != -1)
	{
		switch (opt)
		{
			case 'f':
				fFPS = atof(optarg); 
				break;
			case 'i':
				sCameraParamFilename = optarg;
				break;
			case '?':
				if (optopt == 'f' || optopt == 'i')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
				return 1;
			default:
				abort ();
		}
	}
	
	// reads camera intrinsic parameters
	cv::Mat cameraMatrix, distCoeffs;
	bool isCamParamsSet = readCameraParameters(sCameraParamFilename, cameraMatrix, distCoeffs);
	
	// checks if the camera parameters were successfully read
	if (!isCamParamsSet)
	{
		std::cout << "[WARNING] Camera intrinsic parameters could not be loaded!" << std::endl;
	}
	 
	// creates a camera grabber
	cv::VideoCapture cap(0, cv::CAP_V4L2); //capture the video from webcam
	
	// checks if the camera was successfully opened
	if ( !cap.isOpened() )  // if not success, exit program
	{
		std::cout << "[ERROR] Could not open the camera!" << std::endl;
		return -1;
	}
	
	// distorted/undistorted image
	bool bIsImageUndistorted = true;
	
	// main loop launched every FPS
	while (true)
	{
		// reads a new frame from video
		cv::Mat imgOriginal;
		bool bSuccess = cap.read(imgOriginal);

		// checks if a new frame was grabbed
		if (!bSuccess) //if not success, break loop
		{
			std::cout << "[WARNING] Could not read a new frame from video stream" << std::endl;
			break;
		}
		
		if (bIsImageUndistorted && isCamParamsSet)
		{
			cv::Mat temp = imgOriginal.clone();
			cv::undistort(temp, imgOriginal, cameraMatrix, distCoeffs);
		}
		
		// finds chessboard in the grabbed frame
		std::vector<cv::Point2f> imagePoints;
		int chessBoardFlags = cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE;
		bool isChessboardFound = findChessboardCorners( imgOriginal, cv::Size(iBoardSizeWidth, iBoardSizeHeight), imagePoints, chessBoardFlags);
		
		
		if (isChessboardFound)
		{
			// improve the found corners' coordinate accuracy for chessboard
			cv::Mat imgGray;
			cvtColor(imgOriginal, imgGray, cv::COLOR_BGR2GRAY);
			cornerSubPix( imgGray, imagePoints, cv::Size(iWinSize,iWinSize), cv::Size(-1,-1), cv::TermCriteria( cv::TermCriteria::EPS+cv::TermCriteria::COUNT, 30, 0.0001 ));
			
			// draws the corners.
			//cv::drawChessboardCorners( imgOriginal, cv::Size(iBoardSizeWidth, iBoardSizeHeight), cv::Mat(imagePoints), isChessboardFound );
		
			// generates the chessboard 3D points
			std::vector<cv::Point3f> objectPoints;
			for( int i = 0; i < iBoardSizeHeight; ++i )
				for( int j = 0; j < iBoardSizeWidth; ++j )
					objectPoints.push_back(cv::Point3f(j*iSquareSize, i*iSquareSize, 0));
			
			//std::cout << "objectPoints = " << objectPoints << std::endl;
			//std::cout << "imagePoints = " << imagePoints << std::endl;
			
			// estimates the transform matrix: translation + rotation
			cv::Mat rvec(3,1,cv::DataType<double>::type);
			cv::Mat tvec(3,1,cv::DataType<double>::type);
			cv::solvePnP(objectPoints, imagePoints, cameraMatrix, distCoeffs, rvec, tvec);
			
			//std::cout << "rvec: " << rvec << std::endl;
			//std::cout << "tvec: " << tvec << std::endl;
			
			// generates the axes 3D points
			std::vector<cv::Point3f> axesPoints = {cv::Point3f(iSquareSize, 0.0, 0.0),  cv::Point3f(0.0, iSquareSize, 0.0), cv::Point3f(0.0, 0.0, -iSquareSize)};
			
			// projects them on the image plane
			std::vector<cv::Point2f> projectedAxesPoints;
			cv::projectPoints(axesPoints, rvec, tvec, cameraMatrix, distCoeffs, projectedAxesPoints);
			
			// draws the axes on the image plane
			cv::line(imgOriginal, imagePoints[0], projectedAxesPoints[0], cv::Scalar(0, 0, 255), 5);
			cv::line(imgOriginal, imagePoints[0], projectedAxesPoints[1], cv::Scalar(0, 255, 0), 5);
			cv::line(imgOriginal, imagePoints[0], projectedAxesPoints[2], cv::Scalar(255, 0, 0), 5);
			//cv::drawFrameAxes(imgOriginal, cameraMatrix, distCoeffs, rvec, tvec, 1);
			
			cv::Mat R;
			cv::Rodrigues(rvec, R); // R is 3x3
			
			cv::Mat Rinv = R.t();
			std::cout << "Rinv= " << Rinv << std::endl;
			
			cv::Mat tinv = -Rinv * tvec;
			std::cout << "tinv= " << tinv << std::endl;
			
			cv::Mat Tinv = cv::Mat::eye(4, 4, R.type());
			Tinv(cv::Range(0,3), cv::Range(0,3)) = Rinv*1;
			Tinv(cv::Range(0,3), cv::Range(3,4)) = tinv*1;
			std::cout << "Tinv=" << Tinv << std::endl;
		}
		
		// shows the original image with the tracking (red) lines
		imshow("Original", imgOriginal); 

		// waits for awhile depending on the FPS value
		char key = (char)cv::waitKey(1000.0/fFPS);
		// checks if ESC was pressed to exit
		if (key == 27) // if 'esc' key is pressed, break loop
		{
			std::cout << "[INFO] esc key is pressed by user -> Shuting down!" << std::endl;
			break; 
		}
		if (key == 'u')
		{
			bIsImageUndistorted = !bIsImageUndistorted;
			std::cout << "[INFO] Image undistorted: " <<  bIsImageUndistorted<< std::endl;
		}
		
	}
	
	return 0;
}