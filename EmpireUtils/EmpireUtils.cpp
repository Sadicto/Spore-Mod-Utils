#include "stdafx.h"
#include "EmpireUtils.h"
#include <Spore-Mod-Utils/PlanetUtils/PlanetUtils.h>
namespace SporeModUtils {
    namespace EmpireUtils {

		bool ValidNpcEmpire(Simulator::cEmpire* empire, bool includePlayer, bool includeGrox, bool includeOtherSaves) {
			return (empire != nullptr &&
				(empire->mStars.size() > 0) &&
				(includePlayer || empire != Simulator::GetPlayerEmpire()) &&
				(includeGrox || empire != StarManager.GetEmpire((StarManager.GetGrobEmpireID()))) &&
				(includeOtherSaves || (empire->mFlags & (1 << 6)) == 0));
		}

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
				if (ValidNpcEmpire(starEmpire, includePlayer, includeGrox, includeOtherSaves)){
					empireSet.insert(starEmpire);
				}
			}
			// Get the empire for every id.
			for (Simulator::cEmpire* empire : empireSet) {
				empires.push_back(cEmpirePtr(empire));
			}
        }

		int GetEmpireLevel(Simulator::cEmpire* empire) {
			empire->field_D8 = -1;
			return CALL(Address(ModAPI::ChooseAddress(0x00c31000, 0x00c31900)), int, Args(Simulator::cEmpire*), Args(empire));
		}

		void GetEmpirePlanets(Simulator::cEmpire* empire, eastl::vector<cPlanetRecordPtr>& planets, bool excludeColonized, bool excludeUncolonized, bool excludeBlueRedOrbit, bool excludeBlueRedOrbitWithBadSpice, bool excludeT0) {
			// We use the base cost of redSpice to determine if a spice is "bad" or "good"
			ResourceKey redSpiceKey =  ResourceKey(0x1ca01562, 0, 0);
			// Caches the base cost of each spice to avoid reading properties on every iteration.
			eastl::map<uint32_t, float> spiceCosts;
			// The spiceCosts only matters in this case.
			if (excludeBlueRedOrbitWithBadSpice && !excludeT0) {
				for (const ResourceKey& spiceKey : SpaceTrading.mSpices) {
					spiceCosts[spiceKey.instanceID] = PlanetUtils::GetSpiceBaseCost(spiceKey);
				}
			}
			for (cStarRecordPtr star : empire->mStars) {
				for (cPlanetRecordPtr planet : star->GetPlanetRecords()) {
					if (PlanetUtils::InteractablePlanet(planet.get())) {
						bool greenOrbit = PlanetUtils::GetPlanetOrbitTemperature(planet.get()) == Simulator::SolarSystemOrbitTemperature::Normal;
						if ((!excludeColonized || planet->GetTechLevel() != Simulator::TechLevel::Empire) &&
							(!excludeUncolonized || planet->GetTechLevel() == Simulator::TechLevel::Empire) &&
							(!excludeBlueRedOrbit || greenOrbit) &&
							(!excludeT0 || planet->mType != Simulator::PlanetType::T0) && 
							(!excludeBlueRedOrbitWithBadSpice || greenOrbit || (planet->mSpiceGen.instanceID != 0 && spiceCosts[planet->mSpiceGen.instanceID] >= spiceCosts[redSpiceKey.instanceID] * 2))) {
							planets.push_back(planet);
						}
					}
				}
			}
		}
    }
}
