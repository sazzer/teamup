PROJECT(Teamup CXX)
    CMAKE_MINIMUM_REQUIRED(VERSION 3.2.0 FATAL_ERROR)

    SET(CMAKE_CXX_STANDARD 14)
    SET(CMAKE_CXX_STANDARD_REQUIRED ON)
    ENABLE_TESTING()

    ADD_EXECUTABLE(Teamup modules/teamup/main/main.cpp)

    ADD_EXECUTABLE(TeamupTest global/bandit/main.cpp
        modules/teamup/test/test.cpp)
    TARGET_INCLUDE_DIRECTORIES(TeamupTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/bandit)
    ADD_TEST(NAME Teamup COMMAND TeamupTest)
