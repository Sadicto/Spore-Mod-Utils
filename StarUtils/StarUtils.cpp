#include "stdafx.h"
#include "StarUtils.h"

namespace SporeModUtils {
    namespace StarUtils {

        void GeneratePlanets(Simulator::cStarRecord* star) {
			eastl::vector<cPlanetRecordPtr> planets = star->GetPlanetRecords();
			Simulator::cStar* starT = simulator_new<Simulator::cStar>();
			starT->mpStarRecord = star;
			starT->GetSolarSystem();
			GameNounManager.DestroyInstance(starT);
        }

		void GetUnclaimedStarsInRadius(const Vector3& coords, float radius, eastl::vector<cStarRecordPtr>& stars, bool includeTribes, bool includeCivs) {
			Simulator::StarRequestFilter filter;
			filter.RemoveStarType(Simulator::StarType::None);
			filter.RemoveStarType(Simulator::StarType::GalacticCore);
			filter.RemoveStarType(Simulator::StarType::ProtoPlanetary);
			filter.RemoveStarType(Simulator::StarType::BlackHole);
			filter.techLevels = 0;

			//even stars with all planet in T0 have this techLevel
			filter.AddTechLevel(Simulator::TechLevel::Creature);

			if (includeTribes) {
				filter.AddTechLevel(Simulator::TechLevel::Tribe);
			}
			if (includeCivs) {
				filter.AddTechLevel(Simulator::TechLevel::Civilization);
			}
			filter.minDistance = 0;
			filter.maxDistance = radius;
			Simulator::cStarManager* starManager = Simulator::cStarManager::Get();
			starManager->FindStars(coords, filter, stars);
		}

		float GetDistanceBetweenStars(Simulator::cStarRecord* star1, Simulator::cStarRecord* star2) {
			return (star1->mPosition - star2->mPosition).Length();
		}
    }
}