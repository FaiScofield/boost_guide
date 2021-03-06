cmake_minimum_required(VERSION 3.2)

project(boot_guide)

set(CMAKE_BUILD_TYPE "Release")
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost COMPONENTS
    date_time container
    regex system
    REQUIRED
)
include_directories(${Boost_INCLUDE_DIRS})
link_libraries(${Boost_LIBRARIES})

MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")

# Chapter 2 - date_time
add_executable(date1 date_time/date1.cpp)
target_link_libraries(date1 ${Boost_LIBRARIES})
add_executable(date2 date_time/date2.cpp)
target_link_libraries(date2 ${Boost_LIBRARIES})
add_executable(datetime date_time/datetime.cpp)
target_link_libraries(datetime ${Boost_LIBRARIES})
add_executable(posix_time date_time/posix_time.cpp)
target_link_libraries(posix_time ${Boost_LIBRARIES})
add_executable(progress_display date_time/progress_display.cpp)
target_link_libraries(progress_display ${Boost_LIBRARIES})
add_executable(progress_timer date_time/progress_timer.cpp)
target_link_libraries(progress_timer ${Boost_LIBRARIES})
add_executable(timer date_time/timer.cpp)
target_link_libraries(timer ${Boost_LIBRARIES})

# Chapter 3 - memory
add_executable(intrusive_ptr memory/intrusive_ptr.cpp)
target_link_libraries(intrusive_ptr ${Boost_LIBRARIES})
add_executable(pool memory/pool.cpp)
target_link_libraries(pool ${Boost_LIBRARIES})
add_executable(scoped_array memory/scoped_array.cpp)
target_link_libraries(scoped_array ${Boost_LIBRARIES})
add_executable(scoped_ptr memory/scoped_ptr.cpp)
target_link_libraries(scoped_ptr ${Boost_LIBRARIES})
add_executable(shared_array memory/shared_array.cpp)
target_link_libraries(shared_array ${Boost_LIBRARIES})
add_executable(shared_ptr1 memory/shared_ptr1.cpp)
target_link_libraries(shared_ptr1 ${Boost_LIBRARIES})
add_executable(shared_ptr2 memory/shared_ptr2.cpp)
target_link_libraries(shared_ptr2 ${Boost_LIBRARIES})
add_executable(weak_ptr memory/weak_ptr.cpp)
target_link_libraries(weak_ptr ${Boost_LIBRARIES})

# Chapter 4 - utility
add_executable(assign utility/assign.cpp)
target_link_libraries(assign ${Boost_LIBRARIES})
add_executable(config utility/config.cpp)
target_link_libraries(config ${Boost_LIBRARIES})
add_executable(exception utility/exception.cpp)
target_link_libraries(exception ${Boost_LIBRARIES})
add_executable(operators utility/operators.cpp)
target_link_libraries(operators ${Boost_LIBRARIES})
add_executable(optional utility/optional.cpp)
target_link_libraries(optional ${Boost_LIBRARIES})
add_executable(tribool utility/tribool.cpp)
target_link_libraries(tribool ${Boost_LIBRARIES})
add_executable(utility utility/utility.cpp)
target_link_libraries(utility ${Boost_LIBRARIES})
add_executable(uuid utility/uuid.cpp)
target_link_libraries(uuid ${Boost_LIBRARIES})

# Chapter 5 - string
add_executable(format string/format.cpp)
target_link_libraries(format ${Boost_LIBRARIES})
add_executable(lexical_cast string/lexical_cast.cpp)
target_link_libraries(assign ${Boost_LIBRARIES})
add_executable(string_algo string/string_algo.cpp)
target_link_libraries(string_algo ${Boost_LIBRARIES})
add_executable(string_ref string/string_ref.cpp)
target_link_libraries(string_ref ${Boost_LIBRARIES})
add_executable(tokenizer string/tokenizer.cpp)
target_link_libraries(tokenizer ${Boost_LIBRARIES})
add_executable(xpressive string/xpressive.cpp)
target_link_libraries(xpressive ${Boost_LIBRARIES})

# Chapter 7 - container
add_executable(array container/array.cpp)
target_link_libraries(array ${Boost_LIBRARIES})
add_executable(dynamic_bitset container/dynamic_bitset.cpp)
target_link_libraries(dynamic_bitset ${Boost_LIBRARIES})
add_executable(unordered container/unordered.cpp)
target_link_libraries(unordered ${Boost_LIBRARIES})
add_executable(any container/any.cpp)
target_link_libraries(any ${Boost_LIBRARIES})
add_executable(bimap container/bimap.cpp)
target_link_libraries(bimap ${Boost_LIBRARIES})
add_executable(circular_buffer container/circular_buffer.cpp)
target_link_libraries(circular_buffer ${Boost_LIBRARIES})
add_executable(multi_array container/multi_array.cpp)
target_link_libraries(multi_array ${Boost_LIBRARIES})
add_executable(property_tree container/property_tree.cpp)
target_link_libraries(property_tree ${Boost_LIBRARIES})
add_executable(tuple container/tuple.cpp)
target_link_libraries(tuple ${Boost_LIBRARIES})
add_executable(variant container/variant.cpp)
target_link_libraries(variant ${Boost_LIBRARIES})
