# Install script for directory: C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/CGSnakeGame")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/msys64/ucrt64/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp5.4.3-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/cmake-build-debug/external/assimp/lib/libassimpd.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/anim.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/aabb.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/ai_assert.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/camera.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/color4.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/color4.inl"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/cmake-build-debug/external/assimp/code/../include/assimp/config.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/ColladaMetaData.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/commonMetaData.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/defs.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/cfileio.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/light.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/material.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/material.inl"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/matrix3x3.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/matrix3x3.inl"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/matrix4x4.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/matrix4x4.inl"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/mesh.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/ObjMaterial.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/pbrmaterial.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/GltfMaterial.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/postprocess.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/quaternion.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/quaternion.inl"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/scene.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/metadata.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/texture.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/types.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/vector2.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/vector2.inl"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/vector3.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/vector3.inl"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/version.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/cimport.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/AssertHandler.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/importerdesc.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/Importer.hpp"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/DefaultLogger.hpp"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/ProgressHandler.hpp"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/IOStream.hpp"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/IOSystem.hpp"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/Logger.hpp"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/LogStream.hpp"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/NullLogger.hpp"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/cexport.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/Exporter.hpp"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/DefaultIOStream.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/DefaultIOSystem.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/ZipArchiveIOSystem.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/SceneCombiner.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/fast_atof.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/qnan.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/BaseImporter.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/Hash.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/ParsingUtils.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/StreamReader.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/StreamWriter.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/StringComparison.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/StringUtils.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/SGSpatialSort.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/GenericProperty.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/SpatialSort.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/SmallVector.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/SmoothingGroups.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/SmoothingGroups.inl"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/StandardShapes.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/RemoveComments.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/Subdivision.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/Vertex.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/LineSplitter.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/TinyFormatter.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/Profiler.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/LogAux.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/Bitmap.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/XMLTools.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/IOStreamBuffer.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/CreateAnimMesh.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/XmlParser.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/BlobIOSystem.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/MathFunctions.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/Exceptional.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/ByteSwapper.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/Base64.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/Compiler/poppack1.h"
    "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/external/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Bildverarbeitung Computergrafik/git alle objekte zsm/Visual_Computing/cg/cmake-build-debug/external/assimp/code/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
