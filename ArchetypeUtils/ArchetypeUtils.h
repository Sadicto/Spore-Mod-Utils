#pragma once
#include <Spore/Simulator/cStarRecord.h>
namespace SporeModUtils {
    namespace ArchetypeUtils {

        /// @brief Returns the base (non-player) archetype corresponding to a given archetype value.
        /// @param archetype The input value from the Archetypes enum.
        /// @return The corresponding base archetype if input is a player archetype,
        /// or the original value if no mapping is necessary.
        Simulator::Archetypes GetBaseArchetype(Simulator::Archetypes archetype);

        /// @brief Converts an empire archetype enum value to its string representation.
        /// @param archetype
        /// @return The name of the archetype as a eastl::string16
        eastl::string16 ArchetypeToString(Simulator::Archetypes archetype);
    }
}

