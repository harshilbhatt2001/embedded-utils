cmake_minimum_required(VERSION 3.20)
# specify cross compilers and tools
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# project settings
project(include/embedded_utils LANGUAGES C)
set(CMAKE_C_STANDARD 11)

include_directories(include)
add_library(ring_buffer_lib STATIC include/embedded_utils/ring_buffer.h include/embedded_utils/utils.h src/ring_buffer.c)
add_library(queue_lib STATIC include/embedded_utils/queue.h include/embedded_utils/utils.h  src/queue.c)
target_include_directories(ring_buffer_lib PUBLIC include/embedded_utils)
target_include_directories(queue_lib PUBLIC include/embedded_utils)
target_link_libraries(ring_buffer_lib PUBLIC queue_lib)

#add_executable(embedded_utils src/main.c src/ring_buffer.c)
