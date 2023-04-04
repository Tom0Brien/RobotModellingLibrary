# tinyroboticsConfig.cmake

include(CMakeFindDependencyMacro)

find_dependency(Catch2)
find_dependency(Eigen3)
find_dependency(autodiff)
find_dependency(ifopt)
find_dependency(nlohmann_json)
find_dependency(TinyXML2)

include("${CMAKE_CURRENT_LIST_DIR}/tinyroboticsTargets.cmake")