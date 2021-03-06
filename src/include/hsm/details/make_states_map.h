#pragma once

#include "hsm/details/collect_states.h"
#include "hsm/details/to_pairs.h"

#include <boost/hana/append.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/transform.hpp>
#include <boost/hana/zip.hpp>

namespace hsm {

namespace bh {
using namespace boost::hana;
}

/***
 * Returns a map from typeid(state<State>) -> State
 * of all states found recursive under parentState
 *
 */
constexpr auto make_states_map = [](auto&& parentState) {
    auto collectedStateTypeids = collect_state_typeids_recursive(parentState);
    auto collectedStates = bh::transform(
        remove_duplicate_types(
            bh::append(collect_child_states_recursive(parentState), parentState)),
        unwrap_typeid_to_shared_ptr);
    return bh::to_map(to_pairs(bh::zip(collectedStateTypeids, collectedStates)));
};
}