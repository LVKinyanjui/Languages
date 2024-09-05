FROM ubuntu:20.04

WORKDIR /app

# Install minimal prerequisites (Ubuntu 18.04 as reference)
RUN apt-get update && apt-get install -y cmake g++ wget unzip

# Download and unpack sources
RUN wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip && \unzip opencv.zip && \
    # Create build directory
    mkdir -p build && cd build && \
    # Configure
    cmake  ../opencv-4.x && \
    # Build
    cmake --build .

CMD [  "dpkg", "-l", "|", "grep", "libopencv" ]
