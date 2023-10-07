# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(CheapAteDebuggerTests LANGUAGES CXX)

# ---- Tests ----

add_executable(CheapAteDebugger_test source/CheapAteDebugger_test.cpp)
target_link_libraries(CheapAteDebugger_test PRIVATE CheapAteDebugger_lib)
target_compile_features(CheapAteDebugger_test PRIVATE cxx_std_17)

add_test(NAME CheapAteDebugger_test COMMAND CheapAteDebugger_test)

# ---- End-of-file commands ----

add_folders(Test)
