all:  CameraCalibration RedBallDetection RedBallTracking Kinematics Dxl Servoing ChessboardOrientationTracking ArUcoDetection read write
	g++ lib/CameraCalibration.o -o bin/CameraCalibration -L/usr/lib/x86_64-linux-gnu -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_aruco -lopencv_videoio -lopencv_objdetect -lopencv_imgcodecs -lopencv_features2d -lopencv_calib3d
	g++ lib/RedBallDetection.o -o bin/RedBallDetection -L/usr/lib/x86_64-linux-gnu -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_aruco -lopencv_videoio -lopencv_objdetect -lopencv_imgcodecs -lopencv_features2d -lopencv_calib3d
	g++ lib/RedBallTracking.o -o bin/RedBallTracking -L/usr/lib/x86_64-linux-gnu -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_aruco -lopencv_videoio -lopencv_objdetect -lopencv_imgcodecs -lopencv_features2d -lopencv_calib3d
	g++ -o bin/RobotServoing lib/RobotServoing.o lib/Kinematics.o lib/DynamixelHandler.o -L/usr/local/lib/ -ldxl_x64_cpp -lrt -L/usr/lib/x86_64-linux-gnu `pkg-config --libs opencv4`
	g++ lib/ChessboardOrientationTracking.o -o bin/ChessboardOrientationTracking -L/usr/lib/x86_64-linux-gnu -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_aruco -lopencv_videoio -lopencv_objdetect -lopencv_imgcodecs -lopencv_features2d -lopencv_calib3d
	g++ lib/ArUcoDetection.o -o bin/ArUcoDetection -L/usr/lib/x86_64-linux-gnu -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_aruco -lopencv_videoio -lopencv_objdetect
	g++ lib/read.o  -o bin/read -L/usr/lib/x86_64-linux-gnu -lopencv_core
	g++ lib/write.o  -o bin/write -L/usr/lib/x86_64-linux-gnu -lopencv_core
	
CameraCalibration: src/CameraCalibration.cpp
	g++ -c src/CameraCalibration.cpp -o lib/CameraCalibration.o -I./include -I/usr/include/opencv4
	
RedBallDetection: src/RedBallDetection.cpp
	g++ -c src/RedBallDetection.cpp -o lib/RedBallDetection.o -I./include -I/usr/include/opencv4
	
RedBallTracking: src/RedBallTracking.cpp
	g++ -c src/RedBallTracking.cpp -o lib/RedBallTracking.o -I./include -I/usr/include/opencv4
	
Kinematics: src/Kinematics.cpp
	g++ -c src/Kinematics.cpp -o lib/Kinematics.o -I./include -I/usr/include/opencv4

Dxl: src/DynamixelHandler.cpp
	g++ -c src/DynamixelHandler.cpp -o lib/DynamixelHandler.o -I./include -I/usr/local/include
	
Servoing: src/RobotServoing.cpp
	g++ -c src/RobotServoing.cpp -o lib/RobotServoing.o -I./include -I/usr/include/opencv4

ChessboardOrientationTracking: src/ChessboardOrientationTracking.cpp
	g++ -c src/ChessboardOrientationTracking.cpp -o lib/ChessboardOrientationTracking.o -I./include -I/usr/include/opencv4

ArUcoDetection: src/ArUcoDetection.cpp
	g++ -c src/ArUcoDetection.cpp -o lib/ArUcoDetection.o -I./include -I/usr/include/opencv4

read: src/read.cpp
	g++ -c src/read.cpp -o lib/read.o -I./include -I/usr/include/opencv4
	
write: src/write.cpp
	g++ -c src/write.cpp -o lib/write.o -I./include -I/usr/include/opencv4
clean:
	rm lib/*.o
	rm bin/*