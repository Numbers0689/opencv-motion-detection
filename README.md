# opencv-motion-detection

The project uses OpenCV 2.4 to detect any motion in a video stream from a camera, when a movement is detected, the frame is saved as an image file. Its part of Head First C's C Lab 2(opencv).

## Requirements

- OpenCV 2.4 (later versions don't support C)
- GCC / Linux

## Installation

### Install OpenCV 2.4

1. Install dependencies:
    ```sh
    sudo apt-get update
    sudo apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
    sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libdc1394-22-dev
    ```

2. Download and install OpenCV 2.4:
    ```sh
    git clone -b 2.4 https://github.com/opencv/opencv.git
    cd opencv
    ```

    ```sh
    mkdir build
    cd build
    cmake ..
    ```

    ```sh
    make -j4
    sudo make install
    sudo ldconfig
    ```

## Usage

1. Clone this repository:
    ```sh
    git clone https://github.com/Numbers0689/opencv-motion-detection
    cd opencv-motion-detection
    ```

2. Run the Makefile:
    ```sh
    make
    ```

3. Run the program:
    ```sh
    ./detect
    ```

## Working

- The program captures video from the default camera.
- It calculates the dense optical flow between consecutive frames using the Farneback method (cvCalcOpticalFlowFarneback()).
- If the motion detected between the two frames exceeds the given threshold value, the current frame is saved as an image file.
- The program also has a delay of 10secs which can be configured or removed as needed.

