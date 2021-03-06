#
# PythonQt
#
SET(PythonQt_DEPENDS)
ctkMacroShouldAddExternalProject(PYTHONQT_LIBRARIES add_project)
IF(${add_project})
  
  # Sanity checks
  IF(DEFINED PYTHONQT_INSTALL_DIR AND NOT EXISTS ${PYTHONQT_INSTALL_DIR})
    MESSAGE(FATAL_ERROR "PYTHONQT_INSTALL_DIR variable is defined but corresponds to non-existing directory")
  ENDIF()
  
  SET(proj PythonQt)
  SET(proj_DEPENDENCIES)
  
  SET(PythonQt_DEPENDS ${proj})
  
  IF(NOT DEFINED PYTHONQT_INSTALL_DIR)
  #   MESSAGE(STATUS "Adding project:${proj}")
    
    # Generate ep_PythonQt_args
    SET(ep_PythonQt_args)
    foreach(qtlib gui network opengl sql svg uitools webkit xml xmlpatterns)
      STRING(TOUPPER ${qtlib} qtlib_uppercase)
      LIST(APPEND ep_PythonQt_args -DPythonQt_Wrap_Qt${qtlib}:BOOL=${CTK_LIB_Scripting/Python/Core_PYTHONQT_WRAP_QT${qtlib_uppercase}})
    endforeach()

    # Python is required
    FIND_PACKAGE(PythonLibs)
    IF(NOT PYTHONLIBS_FOUND)
      MESSAGE(FATAL_ERROR "error: Python is required to build ${PROJECT_NAME}")
    ENDIF()
      
    ExternalProject_Add(${proj}
      GIT_REPOSITORY "${git_protocol}://github.com/commontk/PythonQt.git"
      GIT_TAG "patched"
      CMAKE_GENERATOR ${gen}
      BUILD_COMMAND ""
      CMAKE_ARGS
        ${ep_common_args}
        -DQT_QMAKE_EXECUTABLE:FILEPATH=${QT_QMAKE_EXECUTABLE}
        -DPYTHON_INCLUDE_DIR:PATH=${PYTHON_INCLUDE_DIR}
        -DPYTHON_LIBRARY:FILEPATH=${PYTHON_LIBRARY}
        ${ep_PythonQt_args}
      DEPENDS
        ${proj_DEPENDENCIES}
      )
    SET(PYTHONQT_INSTALL_DIR ${ep_install_dir})
    
    # Since the full path of PythonQt library is used, there is not need to add 
    # its corresponding library output directory to CTK_EXTERNAL_LIBRARY_DIRS
  
  ELSE()
    ctkMacroEmptyExternalProject(${proj} "${proj_DEPENDENCIES}")
  ENDIF()
ENDIF()
