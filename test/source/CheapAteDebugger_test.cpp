#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "CheapAteDebugger" ? 0 : 1;
}
