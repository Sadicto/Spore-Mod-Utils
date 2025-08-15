#pragma once
#include <Spore/Simulator/cStarRecord.h>

namespace SporeModUtils {
    namespace DiplomacyUtils {

        /**
        * TODO DISK ADDRESS
        */
        bool EmpireIsAwareOfPlayer(Simulator::cEmpire* empire);

        /**
         * TODO DISK ADDRESS
         */
        bool PlayerContactedEmpire(Simulator::cEmpire* empire);

        /**
         * @brief Checks whether empire1 is allied with empire2.
         * @param empire1.
         * @param empire2.
         * @return True if empire1 is allied with empire2, false otherwise.
         */
        bool Alliance(Simulator::cEmpire* empire1, Simulator::cEmpire* empire2);

        /**
         * @brief Checks whether empire1 is allied with an ally of empire2.
         * @param empire1.
         * @param empire2.
         * @return True if empire1 is allied with an ally of empire2, false otherwise.
         */
        bool AllianceWithAllyOfEmpire(Simulator::cEmpire* empire1, Simulator::cEmpire* empire2);

        /**
         * @brief Checks if empire is allied with any enemy of target.
         * @param empire.
         * @param target.
         * @return True if empire is allied with an enemy of target, false otherwise.
         */
        bool AllianceWithEnemyOfEmpire(Simulator::cEmpire* empire, Simulator::cEmpire* target);

        /**
         * @brief Retrieves all empires that are allies of the given empire and enemies of the target empire.
         *
         * @param empire.
         * @param target.
         * @param alliesEnemiesOfTarget set that will contain all empires that are both allied with the given empire and enemies of the target.
         */
        void GetAlliesThatAreEnemiesOf(Simulator::cEmpire* empire, Simulator::cEmpire* target, eastl::set<cEmpirePtr>& alliesEnemiesOfTarget);

        /**
         * @brief Checks if empire1 have a common enemy with empire2
         * @param empire1.
         * @param empire2.
         * @return True if empire1 have a common enemy with empire2, false otherwise.
         */
        bool CommonEnemy(Simulator::cEmpire* empire1, Simulator::cEmpire* empire2);

        /**
         * @brief Populates a vector with all empires from the input vector that are allies of the given empire.
         * @param empire.
         * @param empires The input vector of empires to filter.
         * @param empireAllies The vector to be populated with allied empires found in the empires vector.
         */
        void GetAlliesFromVector(Simulator::cEmpire* empire, eastl::vector<cEmpirePtr>& empires, eastl::vector<cEmpirePtr>& empireAllies);

        /**
         * @brief Populates a vector with all empires from the input vector that are enemies of the given empire.
         * @param empire.
         * @param empires The input vector of empires to filter.
         * @param empireEnemies The vector to be populated with enemy empires found in the empires vector.
         */
        void GetEnemiesFromVector(Simulator::cEmpire* empire, eastl::vector<cEmpirePtr>& empires, eastl::vector<cEmpirePtr>& empireEnemies);

        /**
         * @brief Populates a vector with all allied empires of the given empire that are within the specified range.
         * @param empire.
         * @param range The maximum range within which allies are considered.
         * @param empireAllies The vector to be populated with the found allied empires.
         */
        void GetAlliesInRange(Simulator::cEmpire* empire, float range, eastl::vector<cEmpirePtr>& empireAllies);

        /**
         * @brief Populates a vector with all enemy empires of the given empire that are within the specified range.
         * @param empire.
         * @param range The maximum range within which enemies are considered.
         * @param empireEnemies The vector to be populated with the found enemy empires.
         */
        void GetEnemiesInRange(Simulator::cEmpire* empire, float range, eastl::vector<cEmpirePtr>& empireEnemies);

        /**
         * @brief Retrieves all empires within the specified diplomatic range of the given empire,
         *        and categorizes them into allies and enemies.
         *
         * @param empire.
         * @param range The maximum range for considering other empires.
         * @param empiresInRange Vector to be populated with all empires found within the range.
         * @param empireAllies Vector to be populated with all in-range empires that are allies of the given empire.
         * @param empireEnemies Vector to be populated with all in-range empires that are enemies of the given empire.
         */
        void GetEmpiresInRangeByRelation(
            Simulator::cEmpire* empire,
            float range,
            eastl::vector<cEmpirePtr>& empiresInRange,
            eastl::vector<cEmpirePtr>& empireAllies,
            eastl::vector<cEmpirePtr>& empireEnemies);



    }
}
