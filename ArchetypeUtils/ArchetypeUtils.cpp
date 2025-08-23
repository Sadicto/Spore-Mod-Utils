#include "stdafx.h"
#include "ArchetypeUtils.h"
namespace SporeModUtils {
    namespace ArchetypeUtils {
        Simulator::Archetypes GetBaseArchetype(Simulator::Archetypes archetype, bool preservePlayerSubtypes) {
            switch (archetype)
            {
            case  Simulator::Archetypes::kArchetypePlayerKnight: {
                if (preservePlayerSubtypes) {
                    return Simulator::Archetypes::kArchetypePlayerWarrior;
                }
                else {
                    return Simulator::Archetypes::kArchetypeWarrior;
                }
            }
                
            case Simulator::Archetypes::kArchetypePlayerWanderer: {
                if (preservePlayerSubtypes) {
                    return Simulator::Archetypes::kArchetypeGrob;
                }
                else {
                    return Simulator::Archetypes::kArchetypeDiplomat;
                }
            }
                

            case Simulator::Archetypes::kArchetypePlayerWarrior:
                return Simulator::Archetypes::kArchetypeWarrior;
            case Simulator::Archetypes::kArchetypePlayerTrader:
                return Simulator::Archetypes::kArchetypeTrader;
            case Simulator::Archetypes::kArchetypePlayerScientist:
                return Simulator::Archetypes::kArchetypeScientist;
            case Simulator::Archetypes::kArchetypePlayerShaman:
                return Simulator::Archetypes::kArchetypeShaman;
            case Simulator::Archetypes::kArchetypePlayerBard:
                return Simulator::Archetypes::kArchetypeBard;
            case Simulator::Archetypes::kArchetypePlayerZealot:
                return Simulator::Archetypes::kArchetypeZealot;
            case Simulator::Archetypes::kArchetypePlayerDiplomat:
                return Simulator::Archetypes::kArchetypeDiplomat;
            case Simulator::Archetypes::kArchetypePlayerEcologist:
                return Simulator::Archetypes::kArchetypeEcologist;

            default:
                return archetype;
            }
        }
    }
}
