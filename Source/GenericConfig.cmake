map()
  key(plugins)
  key(tracing)
  key(version)
  val(${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REVISION})
end()
ans(CONFIG)

map_set(${CONFIG} port ${PORT})
map_set(${CONFIG} binding ${BINDING})
map_set(${CONFIG} ipv6 ${IPV6_SUPPORT})
map_set(${CONFIG} idletime ${IDLE_TIME})
map_set(${CONFIG} persistentpath ${PERSISTENT_PATH})
map_set(${CONFIG} volatilepath ${VOLATILE_PATH})
map_set(${CONFIG} datapath ${DATA_PATH})
map_set(${CONFIG} systempath ${SYSTEM_PATH})
map_set(${CONFIG} proxystubpath ${PROXYSTUB_PATH})
map_set(${CONFIG} redirect "/Service/Controller/UI")

map()
    kv(priority ${PRIORITY})
    kv(policy ${POLICY})
    kv(oomadjust ${OOMADJUST})
    kv(stacksize ${STACKSIZE})
end()
ans(PROCESS_CONFIG)
map_append(${CONFIG} process ${PROCESS_CONFIG})

map()
    kv(callsign Controller)
    key(configuration)
end()
ans(PLUGIN_CONTROLLER)

map()
    kv(subsystems)
    key(resumes)
end()
ans(PLUGIN_CONTROLLER_CONFIGURATION)

list(LENGTH EXTERN_EVENT_LIST EXTERN_EVENT_LIST_LENGTH)
if (EXTERN_EVENT_LIST_LENGTH GREATER 0)
    map_append(${PLUGIN_CONTROLLER_CONFIGURATION} subsystems ___array___)

    foreach(SUBSYSTEM IN LISTS EXTERN_EVENT_LIST)
        map_append(${PLUGIN_CONTROLLER_CONFIGURATION} subsystems ${SUBSYSTEM})
    endforeach(SUBSYSTEM)
endif()

if (PLUGIN_WEBSERVER OR PLUGIN_WEBKITBROWSER OR PLUGIN_ESPIAL)
    #Add ___array___ to the key to force json array creation.
    map_append(${PLUGIN_CONTROLLER_CONFIGURATION} resumes ___array___)

    if (PLUGIN_WEBKITBROWSER)
        map_append(${PLUGIN_CONTROLLER_CONFIGURATION} resumes WebKitBrowser)
    endif (PLUGIN_WEBKITBROWSER)

    if (PLUGIN_ESPIAL)
        map_append(${PLUGIN_CONTROLLER_CONFIGURATION} resumes EspialBrowser)
    endif (PLUGIN_ESPIAL)

    if (PLUGIN_WEBSERVER)
        map_append(${PLUGIN_CONTROLLER_CONFIGURATION} resumes WebServer)
    endif (PLUGIN_WEBSERVER)
endif()

map()
    kv(category "Startup")
    kv(module "SysLog")
    kv(enabled true)
end()
ans(PLUGIN_STARTUP_TRACING)

map()
    kv(category "Shutdown")
    kv(module "SysLog")
    kv(enabled true)
end()
ans(PLUGIN_SHUTDOWN_TRACING)

map()
    kv(category "Notification")
    kv(module "SysLog")
    kv(enabled true)
end()
ans(PLUGIN_NOTIFICATION_TRACING)


map()
    kv(category "Fatal")
    kv(enabled true)
end()
ans(PLUGIN_FATAL_TRACING)


if(NOT VIRTUALINPUT)
    map()
    kv(locator "/dev/uinput")
    kv(type "device")
    end()
    ans(PLUGIN_INPUT_DEVICE)

    map_append(${CONFIG} input ${PLUGIN_INPUT_DEVICE})
endif(NOT VIRTUALINPUT)


map_append(${CONFIG} tracing ___array___)
map_append(${CONFIG} tracing ${PLUGIN_STARTUP_TRACING})
map_append(${CONFIG} tracing ${PLUGIN_SHUTDOWN_TRACING})
map_append(${CONFIG} tracing ${PLUGIN_NOTIFICATION_TRACING})
map_append(${CONFIG} tracing ${PLUGIN_FATAL_TRACING})


map_append(${PLUGIN_CONTROLLER} configuration ${PLUGIN_CONTROLLER_CONFIGURATION})

map_append(${CONFIG} plugins ___array___)
map_append(${CONFIG} plugins ${PLUGIN_CONTROLLER})

#[[ ================================ Add additional config above this line  ================================ ]]

json_write("${CMAKE_BINARY_DIR}/Config.json" ${CONFIG})

install(
        FILES ${CMAKE_BINARY_DIR}/Config.json
        DESTINATION ${CMAKE_INSTALL_PREFIX}/../etc/WPEFramework/
        RENAME config.json
        COMPONENT ${MODULE_NAME})
