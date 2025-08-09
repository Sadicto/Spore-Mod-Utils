#pragma once
#include <Spore/Simulator/cStarRecord.h>

namespace SporeModUtils {
    namespace DiplomacyUtils {

        bool EmpireEncountered(Simulator::cEmpire* empire);

        bool Alliance(Simulator::cEmpire* empire1, Simulator::cEmpire* empire2);

        bool AllianceWithEnemyOfEmpire(Simulator::cEmpire* empire, Simulator::cEmpire* target);

        bool CommonEnemy(Simulator::cEmpire* empire1, Simulator::cEmpire* empire2);
    }
}
