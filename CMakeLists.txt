cmake_minimum_required(VERSION 3.15)
project(mini_meteo_model C)

set(CMAKE_C_STANDARD 99)

find_package(MPI REQUIRED)
find_package(OpenMP REQUIRED)

include_directories(${MPI_INCLUDE_PATH} include)

add_executable(meteo
    src/main.c
    src/grid.c
    src/advection.c
    src/diffusion.c
    src/boundary.c
    src/io.c
    src/parallel.c
)

target_link_libraries(meteo PRIVATE
    OpenMP::OpenMP_C
    ${MPI_C_LIBRARIES}
    m           # <- math.h, doit être à la fin
)

