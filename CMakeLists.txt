####################################################
## library individual settings

#library name (name is appended to "nice_" to form the target library name)
set(the_library "gp-hik-core")

#define variable nice_<libname>_HDR and nice_<libname>_SRC for library header and source files (don't include progs and test source files here)
include( corefiles.cmake)

#define variable nice_<libname>_PROGFILES_HDR and nice_<libname>_PROGFILES_SRC for program header and source files (don't include library and test source files here)
include( progfiles.cmake)

#define variable nice_<libname>_TESTFILES_HDR and nice_<libname>_TESTFILES_SRC for unit test header and source files (don't include library and progs source files here)
include( testfiles.cmake)	

#add linkage dependencies to other libraries here
set("nice_${the_library}_LINKING_DEPENDENCIES" "nice_core")

#####################################################
message(STATUS "adding library ${the_library}")

nice_build_library()

nice_add_progs()

nice_add_unittests()

#####
 set(the_module "nice_${the_library}")
 if(ENABLE_SOLUTION_FOLDERS)
    set_target_properties(${the_module} PROPERTIES FOLDER "modules")
  endif()
	
  set_target_properties(${the_module} PROPERTIES
    OUTPUT_NAME "${the_module}${OPENCV_DLLVERSION}"
    DEBUG_POSTFIX "${OPENCV_DEBUG_POSTFIX}"
    ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH}
    RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
    INSTALL_NAME_DIR lib
  )
  
  if(BUILD_SHARED_LIBS)
    if(MSVC)
      set_target_properties(${the_module} PROPERTIES DEFINE_SYMBOL CVAPI_EXPORTS)
    else()
      add_definitions(-DCVAPI_EXPORTS)
    endif()
  endif()

  if(MSVC)
    if(CMAKE_CROSSCOMPILING)
      set_target_properties(${the_module} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:secchk")
    endif()
    set_target_properties(${the_module} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libc /DEBUG")
  endif()

  install(TARGETS ${the_module}
    RUNTIME DESTINATION bin COMPONENT main
    LIBRARY DESTINATION ${OPENCV_LIB_INSTALL_PATH} COMPONENT main
    ARCHIVE DESTINATION ${OPENCV_LIB_INSTALL_PATH} COMPONENT main
    )

#   # only "public" headers need to be installed
#   if(OPENCV_MODULE_${the_module}_HEADERS AND ";${OPENCV_MODULES_PUBLIC};" MATCHES ";${the_module};")
#     foreach(hdr ${OPENCV_MODULE_${the_module}_HEADERS})
#       string(REGEX REPLACE "^.*opencv2/" "opencv2/" hdr2 "${hdr}")
#       if(hdr2 MATCHES "^(opencv2/.*)/[^/]+.h(..)?$")
#         install(FILES ${hdr} DESTINATION "${OPENCV_INCLUDE_INSTALL_PATH}/${CMAKE_MATCH_1}" COMPONENT main)
#       endif()
#     endforeach()
#   endif()