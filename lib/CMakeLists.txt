set(SOURCES errors.cpp
            init.cpp
            hmac-md5.cpp
            krb5-wrapper.cpp
            libsmb2.cpp
            md4c.cpp
            md5.cpp
            ntlmssp.cpp
            pdu.cpp
            smb2-cmd-close.cpp
            smb2-cmd-create.cpp
            smb2-cmd-echo.cpp
            smb2-cmd-error.cpp
            smb2-cmd-flush.cpp
            smb2-cmd-logoff.cpp
            smb2-cmd-negotiate.cpp
            smb2-cmd-query-directory.cpp
            smb2-cmd-query-info.cpp
            smb2-cmd-read.cpp
            smb2-cmd-session-setup.cpp
            smb2-cmd-set-info.cpp
            smb2-cmd-tree-connect.cpp
            smb2-cmd-tree-disconnect.cpp
            smb2-cmd-write.cpp
            smb2-cmd-ioctl.cpp
            smb2-data-file-info.cpp
            smb2-data-filesystem-info.cpp
            smb2-data-security-descriptor.cpp
            socket.cpp
            sync.cpp
            timestamps.cpp
            unicode.cpp
            dcerpc.cpp)

if(OPENSSL_FOUND)
  list(APPEND SOURCES smb2-signing.cpp)
endif()

add_library(smb2 ${SOURCES})
target_link_libraries(smb2 PUBLIC ${core_DEPENDS} ${CORE_LIBRARIES})
set_target_properties(smb2 PROPERTIES
                           VERSION ${PROJECT_VERSION}
                           SOVERSION ${SOVERSION})
if(NOT MSVC)
  add_definitions("-D_U_=__attribute__((unused))")
else()
  add_definitions("-D_U_=")
  if(CMAKE_SYSTEM_NAME STREQUAL WindowsStore)
    add_definitions("-D_MSC_UWP")
  endif()
endif()

install(TARGETS smb2 EXPORT smb2
                     RUNTIME DESTINATION bin
                     ARCHIVE DESTINATION lib
                     LIBRARY DESTINATION lib)
