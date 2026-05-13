#include "stdafx.h"
#include "DiplomacyUtils.h"
#include <Spore-Mod-Utils/EmpireUtils/EmpireUtils.h>
namespace SporeModUtils {
    namespace DiplomacyUtils {

        bool EmpireIsAwareOfPlayer(Simulator::cEmpire* empire) {
            return  CALL(Address(ModAPI::ChooseAddress(0xc79900, 0x00c7a910)), bool, Args(Simulator::cPlayer*, int), Args(Simulator::GetPlayer(), empire->mPoliticalID));;
        }

        bool PlayerContactedEmpire(Simulator::cEmpire* empire) {
            return  CALL(Address(ModAPI::ChooseAddress(0xc798a0, 0x00c7a8b0)), bool, Args(Simulator::cPlayer*, int), Args(Simulator::GetPlayer(), empire->mPoliticalID));;
        }

        bool War(Simulator::cEmpire* empire1, Simulator::cEmpire* empire2) {
            for (cEmpirePtr empireEnemy : empire1->mEnemies) {
                if (empireEnemy.get() == empire2) {
                    return true;
                }
            }
            return false;
        }

        bool Alliance(Simulator::cEmpire* empire1, Simulator::cEmpire* empire2) {
            for (cEmpirePtr empireAlly : empire1->mAllies) {
                if (empireAlly.get() == empire2) {
                    return true;
                }
            }
            return false;
        }

        bool AllianceWithAllyOfEmpire(Simulator::cEmpire* empire1, Simulator::cEmpire* empire2) {
            for (cEmpirePtr empireAlly : empire2->mAllies) {
                if (Alliance(empire1, empireAlly.get())) {
                    return true;
                }
            }
            return false;
        }

        bool AllianceWithEnemyOfEmpire(Simulator::cEmpire* empire, Simulator::cEmpire* target) {
            for (cEmpirePtr allyEmpire : empire->mAllies) {
                auto it = eastl::find(target->mEnemies.begin(), target->mEnemies.end(), allyEmpire);
                // an ally is an enemy of the target empire
                if (it != target->mEnemies.end()) { 
                    return true;
                }
            }
            return false;
        }

        void GetAlliesThatAreEnemiesOf(Simulator::cEmpire* empire, Simulator::cEmpire* target, eastl::set<cEmpirePtr>& alliesEnemiesOfTarget) {
            for (cEmpirePtr allyEmpire : empire->mAllies) {
                auto it = eastl::find(target->mEnemies.begin(), target->mEnemies.end(), allyEmpire);
                // an ally is an enemy of the target empire
                if (it != target->mEnemies.end() && EmpireUtils::ValidNpcEmpire(allyEmpire.get(), true)) {
                    alliesEnemiesOfTarget.insert(allyEmpire);
                }
            }
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

        void GetAlliesFromVector(Simulator::cEmpire* empire, eastl::vector<cEmpirePtr>& empires, eastl::vector<cEmpirePtr>& empireAllies) {
            for (cEmpirePtr potencialAlly : empires) {
                if (Alliance(empire, potencialAlly.get())) {
                    empireAllies.push_back(potencialAlly);
                }
            }
        }

        void GetEnemiesFromVector(Simulator::cEmpire* empire, eastl::vector<cEmpirePtr>& empires, eastl::vector<cEmpirePtr>& empireEnemies) {
            for (cEmpirePtr potencialEnemy : empires) {
                if (RelationshipManager.IsAtWar(empire, potencialEnemy.get())) {
                    empireEnemies.push_back(potencialEnemy);
                }
            }
        }

        void GetAlliesInRange(Simulator::cEmpire* empire, float range, eastl::vector<cEmpirePtr>& empireAllies) {
            eastl::vector<cEmpirePtr> empiresInRange;
            EmpireUtils::GetEmpiresInRangeOfEmpire(empire, range, empiresInRange, true);
            GetAlliesFromVector(empire, empiresInRange, empireAllies);
        }

        /**
         * @brief Populates a vector with all enemy empires of the given empire that are within the specified range.
         * @param empire.
         * @param range The maximum range within which enemies are considered.
         * @param empireEnemies The vector to be populated with the found enemy empires.
         */
        void GetEnemiesInRange(Simulator::cEmpire* empire, float range, eastl::vector<cEmpirePtr>& empireEnemies) {
            eastl::vector<cEmpirePtr> empiresInRange;
            EmpireUtils::GetEmpiresInRangeOfEmpire(empire, range, empiresInRange, true);
            GetEnemiesFromVector(empire, empiresInRange, empireEnemies);
        }

        void GetEmpiresInRangeByRelation(
            Simulator::cEmpire* empire,
            float range,
            eastl::vector<cEmpirePtr>& empiresInRange,
            eastl::vector<cEmpirePtr>& empireAllies,
            eastl::vector<cEmpirePtr>& empireEnemies) {

            EmpireUtils::GetEmpiresInRangeOfEmpire(empire, range, empiresInRange, true);
            GetAlliesFromVector(empire, empiresInRange, empireAllies);
            GetEnemiesFromVector(empire, empiresInRange, empireEnemies);
        }

        eastl::string16 GetPlayerRelationString(Simulator::cEmpire* empire) {
            eastl::string16 relationString = u"";
            Simulator::cEmpire* playerEmpire = Simulator::GetPlayerEmpire();
            if (Alliance(playerEmpire, empire)) {
                relationString = u"your ally";
            }
            else if (RelationshipManager.IsAtWar(playerEmpire, empire)) {
                relationString = u"your enemy";
            }
            return relationString;
                
        }
    }
}
