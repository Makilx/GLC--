# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/jose/Documents/Projects/GLC++/build/_deps/stbimage-src"
  "/home/jose/Documents/Projects/GLC++/build/_deps/stbimage-build"
  "/home/jose/Documents/Projects/GLC++/build/_deps/stbimage-subbuild/stbimage-populate-prefix"
  "/home/jose/Documents/Projects/GLC++/build/_deps/stbimage-subbuild/stbimage-populate-prefix/tmp"
  "/home/jose/Documents/Projects/GLC++/build/_deps/stbimage-subbuild/stbimage-populate-prefix/src/stbimage-populate-stamp"
  "/home/jose/Documents/Projects/GLC++/build/_deps/stbimage-subbuild/stbimage-populate-prefix/src"
  "/home/jose/Documents/Projects/GLC++/build/_deps/stbimage-subbuild/stbimage-populate-prefix/src/stbimage-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/jose/Documents/Projects/GLC++/build/_deps/stbimage-subbuild/stbimage-populate-prefix/src/stbimage-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/jose/Documents/Projects/GLC++/build/_deps/stbimage-subbuild/stbimage-populate-prefix/src/stbimage-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
