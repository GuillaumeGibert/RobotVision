#include <opencv2/aruco.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>


#define MARKER_LENGTH 0.05
#define CAM_PARAMS_FILENAME "./data/hp_embedded_camera_data.xml"
#define FPS 30.0

bool readCameraParameters(std::string filename, cv::Mat &camMatrix, cv::Mat & distCoeffs)
{
	cv::FileStorage fs(filename, cv::FileStorage::READ);
	if (!fs.isOpened())
		return false;
	fs["camera_matrix"] >> camMatrix;
	fs["distortion_coeffcients"] >> distCoeffs;
	return true;
}

int main(int argc, char** argv)
{
	// loads the dictionary of interest
	cv::Ptr<cv::aruco::Dictionary> arucoDictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_100);
	
	// read camera intrinsic parameters
	cv::Mat cameraMatrix, distCoeffs;
	bool isCamParamsSet = readCameraParameters(CAM_PARAMS_FILENAME, cameraMatrix, distCoeffs);
	
	// sets the coordinate system
	cv::Mat objPoints(4, 1, CV_32FC3);
	objPoints.ptr<cv::Vec3f>(0)[0] = cv::Vec3f(-MARKER_LENGTH/2.f, MARKER_LENGTH/2.f, 0);
	objPoints.ptr<cv::Vec3f>(0)[1] = cv::Vec3f(MARKER_LENGTH/2.f, MARKER_LENGTH/2.f, 0);
	objPoints.ptr<cv::Vec3f>(0)[2] = cv::Vec3f(MARKER_LENGTH/2.f, -MARKER_LENGTH/2.f, 0);
	objPoints.ptr<cv::Vec3f>(0)[3] = cv::Vec3f(-MARKER_LENGTH/2.f, -MARKER_LENGTH/2.f, 0);
	
	
	// creates a camera grabber
	cv::VideoCapture camera(0);
	
	// checks if the camera was successfully opened
	if (!camera.isOpened())
	{
		std::cout << "[ERROR] Cannot open the webcam" << std::endl;
		return 1;
	}
	
	while(1)
	{
		// grabs a frame
		cv::Mat currentFrame;
		camera >> currentFrame;
		
		// detects ArUco markers
		std::vector<std::vector<cv::Point2f>> arucoCorners;
		std::vector<int> arucoIDs;
		cv::aruco::detectMarkers(currentFrame, arucoDictionary, arucoCorners, arucoIDs);
	
		// draws the ArUco marker(s) if any on the original image
		if (arucoIDs.size() > 0)
		{
			cv::aruco::drawDetectedMarkers(currentFrame, arucoCorners, arucoIDs);
			
			// computes the pose of each marker
			int nMarkers = arucoCorners.size();
			std::vector<cv::Vec3d> rvecs(nMarkers), tvecs(nMarkers);
			
			if (isCamParamsSet)
			{
			
				//for (int l_marker = 0; l_marker < nMarkers; l_marker++)
				//{
				//	solvePnP(objPoints, arucoCorners.at(l_marker), cameraMatrix, distCoeffs, rvecs.at(l_marker), tvecs.at(l_marker));
				//}
				
				cv::aruco::estimatePoseSingleMarkers(arucoCorners, MARKER_LENGTH, cameraMatrix, distCoeffs, rvecs, tvecs);
				
				// draws the axis for each marker
				for (unsigned int l_marker = 0; l_marker < arucoIDs.size(); l_marker++)
				{
					//cv::drawFrameAxes(currentFrame, cameraMatrix, distCoeffs, rvecs[l_marker], tvecs[l_marker], 0.1);
					cv::aruco::drawAxis(currentFrame, cameraMatrix, distCoeffs, rvecs[l_marker], tvecs[l_marker], MARKER_LENGTH * 0.5f);
				}
			}
		}
		
		// displays the enhanced image
		cv::imshow("ArUco Detection", currentFrame);
	
		// waits for awhile depending on the FPS value
		// checks if ESC was pressed to exit
		char key = (char)cv::waitKey(1000.0/FPS);
		if (key == 27)
			break;
	}
	
	return 0;
}