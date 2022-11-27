#pragma once
#ifndef SGPL_OPERATIONS_BITWISE_BITWISEAND_HPP_INCLUDE
#define SGPL_OPERATIONS_BITWISE_BITWISEAND_HPP_INCLUDE

#include <algorithm>
#include <cstddef>
#include <map>
#include <set>
#include <string>

#include "../../../../third-party/conduit/include/uit_emp/tools/string_utils.hpp"

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {

/**
 * Performs a bitwise AND of `reg[arg_1]` and `reg[arg_2]` then stores the
 * result in `reg[arg_0]`.
 */
struct BitwiseAnd {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) noexcept {
    const size_t a = inst.args[0], b = inst.args[1], c = inst.args[2];

    std::transform(
      reinterpret_cast<std::byte*>( &core.registers[b] ),
      reinterpret_cast<std::byte*>( &core.registers[b] )
        + sizeof( core.registers[b] ),
      reinterpret_cast<std::byte*>( &core.registers[c] ),
      reinterpret_cast<std::byte*>( &core.registers[a] ),
      [](const std::byte b, const std::byte c){ return b & c; }
    );
  }

  static std::string name() { return "Bitwise And"; }

  static size_t prevalence() { return 1; }

  template<typename Spec>
  static auto descriptors( const sgpl::Instruction<Spec>& inst ) {

    return std::map<std::string, std::string>{
      { "argument a", uit_emp::to_string( static_cast<int>( inst.args[0] ) ) },
      { "argument b", uit_emp::to_string( static_cast<int>( inst.args[1] ) ) },
      { "argument c", uit_emp::to_string( static_cast<int>( inst.args[2] ) ) },
      { "summary", "a = b & c" },
    };
  }

  template<typename Spec>
  static std::set<std::string> categories(const sgpl::Instruction<Spec>&) {
    return {
      "bitwise",
      "calculation",
      "intrinsic",
      "op",
    };
  }

};

} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_BITWISE_BITWISEAND_HPP_INCLUDE
