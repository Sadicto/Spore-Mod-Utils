#pragma once
#include <Spore/Simulator/cStarRecord.h>

namespace SporeModUtils {
    namespace DiplomacyUtils {

        bool EmpireEncountered(cEmpire* empire);

        bool Alliance(cEmpire* empire1, cEmpire* empire2);

        bool AllianceWithEnemyOfEmpire(cEmpire* empire, cEmpire* target);

        bool CommonEnemy(cEmpire* empire1, cEmpire* empire2);
    }
}
