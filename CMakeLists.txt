cmake_minimum_required(VERSION 3.13)
project(Textures)

set(CMAKE_CXX_STANDARD 14)

find_package(TIFF REQUIRED)
if(${TIFF_FOUND})
    include_directories(${TIFF_INCLUDE_DIRS})
    link_libraries(${TIFF_LIBRARIES})
else(${TIFF_FOUND})
    message("libtiff n'a pas été trouvé sur votre système.")
endif()

find_package(X11 REQUIRED)
if(${X11_FOUND})
    include_directories(${X11_INCLUDE_DIR})
    link_libraries(${X11_LIBRARIES})
else(${X11_FOUND})
    message("X11 n'a pas été trouvé sur votre système.")
endif()

add_executable(Textureur
        image_4b.cpp
        matrix2d.cpp
        raccordeur_iteratif.cpp
        raccordeur_recursif.cpp
        raccordeur_simple.cpp
        permuteur.cpp
        textureur.cpp
        x11display_code.cpp
        main_tp.cpp CoupeOptimale.cpp CoupeOptimale.h)

add_executable(TestPermuteur
        permuteur.cpp
        main_testpermut.cpp
)