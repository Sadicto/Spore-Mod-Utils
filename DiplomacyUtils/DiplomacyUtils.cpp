#include "stdafx.h"
#include "DiplomacyUtils.h"
namespace SporeModUtils {
    namespace DiplomacyUtils {

        bool PlayerInteractedWithEmpire(Simulator::cEmpire* empire) {
            return  CALL(Address(0x00c7a910), bool, Args(Simulator::cPlayer*, int), Args(Simulator::GetPlayer(), empire->mPoliticalID));;
        }

        bool Alliance(Simulator::cEmpire* empire1, Simulator::cEmpire* empire2) {
            for (cEmpirePtr empireAlly : empire1->mAllies) {
                if (empireAlly.get() == empire2) {
                    return true;
                }
            }
            return false;
        }

        bool AllianceWithEnemyOfEmpire(Simulator::cEmpire* empire, Simulator::cEmpire* target) {
            for (cEmpirePtr allyEmpire : empire->mAllies) {
                auto it = eastl::find(target->mEnemies.begin(), target->mEnemies.end(), allyEmpire);
                if (it != target->mEnemies.end()) { // an ally is an enemy of the target empire
                    return true;
                }
            }
            return false;
        }

        bool CommonEnemy(Simulator::cEmpire* empire1, Simulator::cEmpire* empire2) {
            int commonEnemies = 0;
            for (cEmpirePtr enemyEmpire : empire1->mEnemies) {
                auto it = eastl::find(empire2->mEnemies.begin(), empire2->mEnemies.end(), enemyEmpire);
                if (it != empire2->mEnemies.end()) { // an enemy is an enemy of the target empire
                    return true;
                }
            }
            return false;
        }
    }
}
