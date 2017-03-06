cmake_minimum_required(VERSION 3.6)

project(NN_C)

set(SOURCE_FILES
    main.cpp
    network/Network.cpp
    network/Network.h
    network/Nodes.cpp
    network/Nodes.h
    network/NodesLayer.cpp
    network/NodesLayer.h
    utils/MathNN.cpp
    utils/MathNN.h
    utils/mnist.cpp
    utils/mnist.h
    utils/MnistReader.cpp
    utils/mnistReader.h
)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE network utils)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14)
