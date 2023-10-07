install(
    TARGETS CheapAteDebugger_exe
    RUNTIME COMPONENT CheapAteDebugger_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
