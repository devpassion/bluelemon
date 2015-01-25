SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_C_COMPILER ${RASPTOOLS_PATH}/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER ${RASPTOOLS_PATH}/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-g++)
SET(CMAKE_FIND_ROOT_PATH ${RASPTOOLS_PATH}/rootfs)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)



macro(add_upload)
    add_custom_target( upload
                    COMMAND scp ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME} ${RASP_USER}@${RASP_HOST}:/tmp 
                    DEPENDS ${CMAKE_PROJECT_NAME}
                    COMMENT "upload... " VERBATIM)
endmacro(add_upload)


macro(add_run)
    add_custom_target( run
                    COMMAND ssh ${RASP_USER}@${RASP_HOST} "/tmp/${CMAKE_PROJECT_NAME}"
                    DEPENDS upload
                    COMMENT "run... " VERBATIM)
endmacro(add_run)

