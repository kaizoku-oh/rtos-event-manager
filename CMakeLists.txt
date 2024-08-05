
idf_component_register (
    SRCS "src/Service.cpp"
         "src/EventManager.cpp"
    INCLUDE_DIRS "include"
)

# Include the project's include directory to ensure UserEvents.h can be found
include_directories("${CMAKE_SOURCE_DIR}/include")
