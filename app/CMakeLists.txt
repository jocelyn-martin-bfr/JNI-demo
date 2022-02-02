cmake_minimum_required(VERSION 3.4.1)
project("DemoJni")

set(CMAKE_CXX_FLAGS "-std=gnu++17 -D_GLIBCXX_USE_CXX11_ABI=0" CACHE STRING "" FORCE)


# Specifies a library name, specifies whether the library is STATIC or
# SHARED, and provides relative paths to the source code. You can
# define multiple libraries by adding multiple add_library() commands,
# and CMake builds them for you. When you build your app, Gradle
# automatically packages shared libraries with your APK.

if (ANDROID)

    find_library( # Sets the name of the path variable.
            android-lib

            # Specifies the name of the NDK library that
            # you want CMake to locate.
            android )

    add_library( # Specifies the name of the library.
          demo-jni

          # Sets the library as a shared library.
          SHARED

          # Provides a relative path to your source file(s).
          "src/main/cpp/androidlog.hpp"
          "src/main/cpp/jni-functions.cpp"
          "src/main/cpp/jobjectsconversions.hpp"
          "src/main/cpp/jobjectsconversions.cpp"
    )

    if (COUT_TO_ANDROID_LOG)
      # Double-check Android log option consistency.
      if (NOT ANDROID)
        message(WARNING "COUT_TO_ANDROID_LOG is ON but ANDROID is OFF, option ignored")
        set(COUT_TO_ANDROID_LOG OFF)
      endif ()

      target_compile_definitions(demo-jni PRIVATE COUT_TO_ANDROID_LOG)
      target_link_libraries(demo-jni PRIVATE log)
    endif ()

    include_directories(
          ${ANDROID_INCLUDE_DIRS}
    )
    target_link_libraries(demo-jni PUBLIC ${JNI_LIBRARIES} ${android-lib})

endif (ANDROID)


