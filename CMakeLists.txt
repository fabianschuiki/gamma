cmake_minimum_required(VERSION 2.8)
project(gamma)

install(DIRECTORY gamma/ DESTINATION include/gamma)

find_package(Boost COMPONENTS unit_test_framework OPTIONAL)
if (Boost_UNIT_TEST_FRAMEWORK_FOUND)
	include_directories(. ${Boost_INCLUDE_DIRS})
	add_definitions(-DBOOST_TEST_DYN_LINK)

	add_executable(tests tests.cpp)
	target_link_libraries(tests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

	enable_testing()
	add_test(tests tests)
endif()