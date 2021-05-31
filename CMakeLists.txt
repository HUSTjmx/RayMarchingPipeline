# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required (VERSION 3.8)

project ("RayMarchingPipeline")


# 设置变量
set(JERROR_DIR ${PROJECT_SOURCE_DIR}/JError)
set(JMATH_DIR ${PROJECT_SOURCE_DIR}/JMath)
set(JSHAPE_DIR ${PROJECT_SOURCE_DIR}/JModel)
set(JMAINLOOP ${PROJECT_SOURCE_DIR}/RayMarchingPipeline)
set(EIGEN_DIR ${PROJECT_SOURCE_DIR}/eigen-3.3.9)
set(JMATERIAL_DIR ${PROJECT_SOURCE_DIR}/JMaterial)
set(JSCENE_DIR ${PROJECT_SOURCE_DIR}/JScene)
set(JSAMPLE_DIR ${PROJECT_SOURCE_DIR}/JSample)
set(JSETUP_DIR ${PROJECT_SOURCE_DIR}/JSetup)
set(JINTEGRATOR_DIR ${PROJECT_SOURCE_DIR}/JIntegrator)
set(JSHADER_DIR ${PROJECT_SOURCE_DIR}/JShader)
set(THIRDPARTY_DIR ${PROJECT_SOURCE_DIR}/ThirdParty)

include_directories(${EIGEN_DIR})

include_directories(${JMATH_DIR} ${JMAINLOOP} ${JERROR_DIR} ${JMATERIAL_DIR} ${JSCENE_DIR} ${JSAMPLE_DIR}
					${JSETUP_DIR} ${JINTEGRATOR_DIR} ${JSHADER_DIR} ${THIRDPARTY_DIR})

# 包含子项目。
add_subdirectory ("JMath")
add_subdirectory ("RayMarchingPipeline")

