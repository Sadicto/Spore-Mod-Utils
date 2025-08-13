#pragma once
#include <Spore/Simulator/cStarRecord.h>

namespace SporeModUtils {
    namespace DiplomacyUtils {

        /**
         * TODO DISK ADDRESS
         */
        bool PlayerInteractedWithEmpire(Simulator::cEmpire* empire);

        /**
         * @brief Checks whether empire1 is allied with empire2.
         * @param empire1.
         * @param empire2.
         * @return True if empire1 is allied with empire2, false otherwise.
         */
        bool Alliance(Simulator::cEmpire* empire1, Simulator::cEmpire* empire2);

        /**
         * @brief Checks if empire is allied with any enemy of target.
         * @param empire.
         * @param target.
         * @return True if empire is allied with an enemy of target, false otherwise.
         */
        bool AllianceWithEnemyOfEmpire(Simulator::cEmpire* empire, Simulator::cEmpire* target);

        /**
         * @brief Checks if empire1 have a common enemy with empire2
         * @param empire1.
         * @param empire2.
         * @return True if empire1 have a common enemy with empire2, false otherwise.
         */
        bool CommonEnemy(Simulator::cEmpire* empire1, Simulator::cEmpire* empire2);
    }
}
