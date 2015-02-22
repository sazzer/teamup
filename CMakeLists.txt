PROJECT(Teamup CXX)
    CMAKE_MINIMUM_REQUIRED(VERSION 3.2.0 FATAL_ERROR)

    #------------------------------------------------------------------------------
    # Set up the general configuration
    #------------------------------------------------------------------------------
    SET(CMAKE_CXX_STANDARD 14)
    SET(CMAKE_CXX_STANDARD_REQUIRED ON)
    ENABLE_TESTING()

    #------------------------------------------------------------------------------
    # Set up any library dependencies that we are going to need
    #------------------------------------------------------------------------------
    FIND_PACKAGE(PkgConfig)
    FIND_PACKAGE(Curses)

    #------------------------------------------------------------------------------
    # The library that is the majority of the code
    #------------------------------------------------------------------------------
    ADD_LIBRARY(TeamupLib STATIC modules/teamup/main/entry.cpp)
    TARGET_INCLUDE_DIRECTORIES(TeamupLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/modules/teamup/main)
    TARGET_INCLUDE_DIRECTORIES(TeamupLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/easyloggingpp/src)
    TARGET_INCLUDE_DIRECTORIES(TeamupLib PUBLIC ${CURSES_INCLUDE_DIRS})
    TARGET_LINK_LIBRARIES(TeamupLib ${CURSES_LIBRARIES})

    #------------------------------------------------------------------------------
    # The executable that ties it all together
    #------------------------------------------------------------------------------
    ADD_EXECUTABLE(Teamup modules/teamup/main/main.cpp)
    TARGET_INCLUDE_DIRECTORIES(Teamup PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/modules/teamup/main)
    TARGET_INCLUDE_DIRECTORIES(Teamup PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/easyloggingpp/src)
    TARGET_LINK_LIBRARIES(Teamup TeamupLib)

    #------------------------------------------------------------------------------
    # The unit tests
    #------------------------------------------------------------------------------
    ADD_EXECUTABLE(TeamupTest global/bandit/main.cpp
        modules/teamup/test/test.cpp)
    TARGET_INCLUDE_DIRECTORIES(TeamupTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/modules/teamup/main)
    TARGET_INCLUDE_DIRECTORIES(TeamupTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/bandit)
    ADD_TEST(NAME Teamup COMMAND TeamupTest)

    #------------------------------------------------------------------------------
    # The integration tests
    #------------------------------------------------------------------------------
    ADD_EXECUTABLE(ScreenshotTest modules/teamup/test/screenshot.cpp)
    TARGET_INCLUDE_DIRECTORIES(ScreenshotTest PUBLIC ${CURSES_INCLUDE_DIRS})
    TARGET_LINK_LIBRARIES(ScreenshotTest ${CURSES_LIBRARIES})

    ADD_EXECUTABLE(ColoursTest modules/teamup/test/colours.cpp)
    TARGET_INCLUDE_DIRECTORIES(ColoursTest PUBLIC ${CURSES_INCLUDE_DIRS})
    TARGET_LINK_LIBRARIES(ColoursTest ${CURSES_LIBRARIES})

    #------------------------------------------------------------------------------
    # Copy some files into the build area for running with
    #------------------------------------------------------------------------------
    CONFIGURE_FILE(files/dev/logging.conf logging.conf COPYONLY)
