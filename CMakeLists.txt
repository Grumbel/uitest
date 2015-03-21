# UITest - Simple testing framework for interactive tests
# Copyright (C) 2015 Ingo Ruhnke <grumbel@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.0)
project(uitest)

find_package(Threads)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Wshadow -Wno-unused-parameter")

# build gtest
add_library(gtest STATIC external/googletest/src/gtest-all.cc)
target_include_directories(gtest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/googletest/)

add_library(gtest_main STATIC external/googletest/src/gtest_main.cc)
target_include_directories(gtest_main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/googletest/)

# build uitest
add_library(uitest STATIC src/arg_info.cpp src/uitest.cpp)
target_include_directories(uitest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(uitest_main STATIC src/uitest_main.cpp)
target_include_directories(uitest_main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# build examples
add_executable(example_test examples/examples.cpp)
target_link_libraries(example_test LINK_PUBLIC uitest uitest_main)
target_include_directories(example_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# build tests
add_executable(uitest_test test/arg_info_test.cpp)
target_include_directories(uitest_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(uitest_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/googletest/)
target_link_libraries(uitest_test LINK_PUBLIC uitest gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})

# EOF #
