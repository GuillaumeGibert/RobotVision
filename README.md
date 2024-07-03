# RobotVision

## About The Project

[![Project Screen Shot][project-screenshot]]()

This repository contains a series of code for Robot vision using the  [OpenCV library](https://opencv.org/) to deal with mono- and stereo- camera calibration, servoing...

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With

* [![C++][cpp-shield]][cpp-url]
* [![OpenCV][opencv-shield]][opencv-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

To set up the project locally, you need to install (if not already the case) some dependencies.
To get a local copy up and running follow these steps.

### Prerequisites

* C++ Compiler

Install the build-essential package
  ```sh
  sudo apt install build-essential 
  ```
  
* OpenCV

Install the dev library
  ```sh
  sudo apt install libopencv-dev 
  ```
  
### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/GuillaumeGibert/RobotVision.git
   ```
2. Open a terminal
3. Compile/Link by calling the makefile
 ```sh
   make
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- USAGE EXAMPLES -->
## Usage

### Mono Camera Calibration

1. Open a terminal
2. Launch the camera calibration executable
```sh
./bin/CameraCalibration data/default.xml 
```
3. Press g to start grabbing images, move the chessboard to capture images with different viewpoints
4. Press u to display the distorted/undistorted images alternatively

### Color detection

1. Open a terminal
2. Launch the color detection executable
```sh
./bin/RedBallDetection -o <color_param_filename> -f <fps> -i <camera_param_filename> -s <structural_elem_size>
```
By using arguments, you can modify the output filename (-o), the framerate (-f), the camera params filename (-i), and the size of the structural elements (-s).
3. Use the trackbars to select the ranges of the H, S and V channels
4. Press s to save them in a file

### Color tracking

1. Open a terminal
2. Launch the color tracking executable
```sh
./bin/RedBallTracking -c <color_param_filename> -f <fps> -a <area_threshold> -s <structural_elem_size> -i <camera_param_filename>
```
By using arguments, you can modify the color params filename (-c), the framerate (-f), the  area threshold (-a), the size of the structural elements (-s) and the camera params filename (-i).


<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Robot servoing

1. Open a terminal
2. Launch the robot servoing executable
```sh
./bin/RobotServoing -c <color_param_filename> -f <fps> -a <area_threshold> -s <structural_elem_size> -i <camera_param_filename>
```
By using arguments, you can modify the color params filename (-c), the framerate (-f), the  area threshold (-a), the size of the structural elements (-s) and the camera params filename (-i).


<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- LICENSE -->
## License

Distributed under the GPL License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CONTACT -->
## Contact

Guillaume Gibert

Project Link: [https://github.com/GuillaumeGibert/RobotVision](https://github.com/GuillaumeGibert/RobotVision)

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[arduino-shield]: https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white
[arduino-url]: https://www.arduino.cc/
[python-shield]: https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white
[python-url]: https://www.python.org/
[opencv-shield]: https://img.shields.io/badge/OpenCV-27338e?style=for-the-badge&logo=OpenCV&logoColor=white
[opencv-url]: https://opencv.org/
[cpp-shield]: https://img.shields.io/badge/-C++-blue?logo=cplusplus
[cpp-url]: https://isocpp.org/

[project-screenshot]: images/screenshot.png

[contributors-shield]: https://img.shields.io/github/contributors/GuillaumeGibert/RobotVision.svg?style=for-the-badge
[contributors-url]: https://github.com/GuillaumeGibert/RobotVision/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/GuillaumeGibert/RobotVision.svg?style=for-the-badge
[forks-url]: https://github.com/GuillaumeGibert/RobotVision/network/members
[stars-shield]: https://img.shields.io/github/stars/GuillaumeGibert/RobotVision.svg?style=for-the-badge
[stars-url]: https://github.com/GuillaumeGibert/RobotVision/stargazers
[issues-shield]: https://img.shields.io/github/issues/GuillaumeGibert/RobotVision.svg?style=for-the-badge
[issues-url]: https://github.com/GuillaumeGibert/RobotVision/issues
[license-shield]: https://img.shields.io/github/license/GuillaumeGibert/RobotVision.svg?style=for-the-badge
[license-url]: https://github.com/GuillaumeGibert/RobotVision/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/guillaume-gibert-06502ba4