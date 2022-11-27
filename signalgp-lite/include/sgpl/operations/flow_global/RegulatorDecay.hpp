#pragma once
#ifndef SGPL_OPERATIONS_FLOW_GLOBAL_REGULATORDECAY_HPP_INCLUDE
#define SGPL_OPERATIONS_FLOW_GLOBAL_REGULATORDECAY_HPP_INCLUDE

#include <map>
#include <set>
#include <string>

#include "../../../../third-party/conduit/include/uitsl/algorithm/clamp_cast.hpp"
#include "../../../../third-party/conduit/include/uit_emp/tools/hash_namify.hpp"
#include "../../../../third-party/conduit/include/uit_emp/tools/string_utils.hpp"

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {
namespace global {

/**
 * Ages the regulator decay countdown of global jump table tags matching this
 * instruction's tag by the amount `reg[arg_0]`.

 * If `reg[arg_0]` is negative, this can forestall decay.
 *
 * This regulator value affects the outcome of tag lookup for module activation
 * on global jump table `JUMP_TABLE_IDX`.
 */
template< size_t JUMP_TABLE_IDX=0 >
struct RegulatorDecay {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) noexcept {

    auto& jump_table = core.GetGlobalJumpTable( JUMP_TABLE_IDX );
    for ( const auto uid : jump_table.MatchRaw(inst.tag) ) {
      jump_table.DecayRegulator(
        uid,
        uitsl::clamp_cast<int32_t>( core.registers[ inst.args[0] ] )
      );
    }

  }

  static std::string name() {
    if constexpr ( JUMP_TABLE_IDX == 0 ) {
      return "Decay Global Regulator";
    } else if constexpr ( JUMP_TABLE_IDX == 1 ) {
      return "Decay Secondary Global Regulator";
    } else return uit_emp::to_string(
      "Decay ", JUMP_TABLE_IDX, "iary Global Regulator"
    );
  }

  static size_t prevalence() { return 1; }

  template<typename Spec>
  static auto descriptors( const sgpl::Instruction<Spec>& inst ) {

    using tag_t = typename Spec::tag_t;

    return std::map<std::string, std::string>{
      { "argument a", uit_emp::to_string( static_cast<int>( inst.args[0] ) ) },
      { "summary", "decay global regulator value by register a" },
      { "target jump table", uit_emp::to_string( JUMP_TABLE_IDX ) },
      { "tag bits", uit_emp::to_string( inst.tag ) },
      { "tag moniker", uit_emp::hash_namify( std::hash< tag_t >{}( inst.tag ) ) },
    };
  }

  template<typename Spec>
  static std::set<std::string> categories(const sgpl::Instruction<Spec>&) {
    return {
      "intrinsic",
      "op",
      "regulation",
      "global regulation",
    };
  }

};

} // namespace global
} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_FLOW_GLOBAL_REGULATORDECAY_HPP_INCLUDE
