cmake_minimum_required(VERSION 3.0)
project(SpaceInvaders)

# set directories
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include")
set(LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Libraries")
set(ECS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include/ECS")
set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Assets")

# Add all the source files to the executable (for building the exe)
file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${INCLUDE_DIR}/*.h")
file(GLOB_RECURSE ECS_HEADER "${ECS_DIR}/*.h")
file(GLOB_RECURSE ECS_CPP "${ECS_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${ECS_HEADER} ${ECS_CPP})

# Include directories for the executable target
target_include_directories(${PROJECT_NAME} PRIVATE
    ${INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Src
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/ECS
)

# Organize source files into virtual folders in the IDE solution
source_group("Source Files" FILES ${SOURCE_FILES})
source_group("Header Files" FILES ${HEADER_FILES})
source_group("ECS" FILES ${ECS_HEADER} files ${ECS_CPP})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_ttf::SDL2_ttf
    SDL2_image::SDL2_image
)

# Add hints for finding the SDL2 and SDL2_ttf libraries
list(APPEND CMAKE_PREFIX_PATH
    ${LIBRARY_DIR}/SDL2-2.28.1
    ${LIBRARY_DIR}/SDL2_ttf-2.20.2
    ${LIBRARY_DIR}/SDL2_image-2.6.3
)

# Find the SDL2 package
find_package(SDL2 REQUIRED)

# Link the found SDL2 library to the target
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

# Find the SDL2_ttf package
find_package(SDL2_ttf REQUIRED)

# Link the found SDL2_ttf library to the target
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_ttf::SDL2_ttf)

# Find the SDL2_image package
find_package(SDL2_image REQUIRED)

# Link the found SDL2_image library to the target
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image)

# Copy SDL2 DLLs to the output directory (for running the executable)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${LIBRARY_DIR}/SDL2-2.28.1/lib/x64/SDL2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Copy SDL2_ttf DLLs to the output directory (for running the executable)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${LIBRARY_DIR}/SDL2_ttf-2.20.2/lib/x64/SDL2_ttf.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Copy SDL2_image DLLs to the output directory (for running the executable)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${LIBRARY_DIR}/SDL2_image-2.6.3/lib/x64/SDL2_image.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Copy assets folder to the output directory (for running the executable)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ASSETS_DIR}"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/Assets
)

# Set the working directory to the top-level binary output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
