# Inspired by https://www.glfw.org/docs/3.3/build_guide.html#build_link_cmake_package
# With CMake and GLFW source
# and https://github.com/meemknight/cmakeSetup as an example for a CMake setup
# and https://www.youtube.com/watch?v=2CUar61taZA for a OpenCV setup with MinGW-w64
# Edited by Merijam Gotzes
# 13.03.2024, 12.04.2024

# WICHTIG TODO:
# opencv-4.9.0-mingw.7z von der Lernplattform herunterladen und
# im neuen Verzeichnis C:\Program Files\Cplusplus\ entpacken
# Dann SYSTEMUMGEBUNGSVARIABLEN in PATH hinzufügen:
# C:\Program Files\Cplusplus\opencv-4.9.0-mingw\install\x64\mingw\lib
# C:\Program Files\Cplusplus\opencv-4.9.0-mingw\install\x64\mingw\bin
# Danach CLion IDE neu starten
# Alternativ: DIY mit https://www.youtube.com/watch?v=2CUar61taZA

cmake_minimum_required(VERSION 3.27)

project(VideoProcessingStartCode)

set(OpenCV_DIR "C:/opencv/opencv-411-mingw/install/x64/mingw/lib")

find_package(OpenCV REQUIRED)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# MY_SOURCE_FILES is a list of all the source files for my implementation
# located at directory src/
file(GLOB_RECURSE MY_SOURCE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}")

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 23)

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCE_FILES} )

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/" ${OpenCV_INCLUDE_DIRS})

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_calib3d opencv_video opencv_features2d opencv_ml opencv_highgui opencv_objdetect)# opencv_contrib opencv_legacy opencv_gpu)
target_link_libraries("${CMAKE_PROJECT_NAME}" ${OpenCV_LIBS})
