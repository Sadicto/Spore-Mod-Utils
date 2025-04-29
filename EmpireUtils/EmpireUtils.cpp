#include "stdafx.h"
#include "EmpireUtils.h"
namespace SporeModUtils {
    namespace EmpireUtils {

        void GetEmpiresInRadius(const Vector3& coords, float radius, eastl::vector<cEmpirePtr>& empires, bool includePlayer, bool includeGrox, bool includeOtherSaves) {
			Simulator::StarRequestFilter filter;
			filter.RemoveStarType(Simulator::StarType::None);
			filter.RemoveStarType(Simulator::StarType::GalacticCore);
			filter.RemoveStarType(Simulator::StarType::ProtoPlanetary);
			filter.RemoveStarType(Simulator::StarType::BlackHole);
			filter.techLevels = 0;
			filter.AddTechLevel(Simulator::TechLevel::Empire);
			filter.minDistance = 0;
			filter.maxDistance = radius;

			eastl::vector<cStarRecordPtr> starsColonized;
			StarManager.FindStars(coords, filter, starsColonized);

			// Set prevents duplicates.
			eastl::set<Simulator::cEmpire*> empireSet;

			Simulator::cEmpire* groxEmpire = StarManager.GetEmpire((StarManager.GetGrobEmpireID()));
			Simulator::cEmpire* playerEmpire = Simulator::GetPlayerEmpire();

			for (cStarRecordPtr star : starsColonized) {
				Simulator::cEmpire* starEmpire = StarManager.GetEmpire(star->mEmpireID);
				if (starEmpire != nullptr &&
					(includePlayer || starEmpire != playerEmpire) &&
					(includeGrox || starEmpire != groxEmpire) &&
					(starEmpire->mFlags & (1 << 6)) == 0) /* no empire from other save.*/ {
					empireSet.insert(starEmpire);
				}
			}
			// Get the empire for every id.
			for (Simulator::cEmpire* empire : empireSet) {
				empires.push_back(cEmpirePtr(empire));
			}
        }

		int GetEmpireLevel(Simulator::cEmpire* empire) {
			int numSystems = empire->mStars.size();
			if (numSystems <= 3) {
				return 0;
			}
			else if (numSystems <= 5) {
				return 1;
			}
			else if (numSystems <= 8) {
				return 2;
			}
			else if (numSystems <= 12) {
				return 3;
			}
			else {
				return 4;
			}
		}
    }
}
