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

        eastl::string16 ArchetypeToString(Simulator::Archetypes archetype) {
            switch (archetype) {
            case Simulator::Archetypes::kArchetypeWarrior: case Simulator::Archetypes::kArchetypePlayerWarrior: return u"Warrior";
            case Simulator::Archetypes::kArchetypeTrader: case Simulator::Archetypes::kArchetypePlayerTrader: return u"Trader";
            case Simulator::Archetypes::kArchetypeScientist: case Simulator::Archetypes::kArchetypePlayerScientist: return u"Scientist";
            case Simulator::Archetypes::kArchetypeShaman: case Simulator::Archetypes::kArchetypePlayerShaman: return u"Shaman";
            case Simulator::Archetypes::kArchetypeBard: case Simulator::Archetypes::kArchetypePlayerBard: return u"Bard";
            case Simulator::Archetypes::kArchetypeZealot: case Simulator::Archetypes::kArchetypePlayerZealot: return u"Zealot";
            case Simulator::Archetypes::kArchetypeDiplomat: case Simulator::Archetypes::kArchetypePlayerDiplomat: return u"Diplomat";
            case Simulator::Archetypes::kArchetypeEcologist: case Simulator::Archetypes::kArchetypePlayerEcologist: return u"Ecologist";
            case Simulator::Archetypes::kArchetypeGrob: return u"Grob";
            case Simulator::Archetypes::kArchetypePlayerWanderer: return u"Wanderer";
            case Simulator::Archetypes::kArchetypePlayerKnight: return u"Knight";
            default: return u"Unknown";
            }
        }
    }
}
