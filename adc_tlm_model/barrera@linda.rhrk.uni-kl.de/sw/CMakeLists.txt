project (exercise3)

add_executable (test_sw test_sw.cpp)


target_link_libraries( test_sw
	         ${SYSTEMCAMS_LIBRARIES} 
		                     ${SYSTEMC_LIBRARIES}

)				                         
