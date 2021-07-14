project(minitube)
cmake_minimum_required(VERSION 3.10)

link_directories(/usr/local/lib /usr/lib)
include_directories(/usr/local/include /usr/include)

include(FindPkgConfig)
pkg_check_modules(CURLPP REQUIRED curlpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Iinclude")
set(CMAKE_SHARED_LINKER_FLAGS "-L/usr/lib -Wl,-O1,--sort-common,--as-needed,-z,relro,-z,now -Llib64 -lcurl -lnghttp2 -lssl -lcrypto -lssl -lcrypto -lz -lcurlpp")

file(GLOB minitube_SRC 
  "src/*.cpp"
  "src/tui/*.cpp"
  "src/tui/tabs/*.cpp"
  "videx/src/*.cpp")

add_executable(minitube ${minitube_SRC})
target_link_libraries(minitube ${CURLPP_LDFLAGS})

install(TARGETS ${PROJECT_NAME})
