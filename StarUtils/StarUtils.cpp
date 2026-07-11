#include "stdafx.h"
#include "StarUtils.h"
#include <EASTL/sort.h>
#include <Spore-Mod-Utils/PlanetUtils/PlanetUtils.h>
namespace SporeModUtils {
    namespace StarUtils {

		bool ValidStar(Simulator::cStarRecord* star, bool atLeastOneInteractablePlanet, bool notSol, bool noMonolith, bool noSavegame, bool noPotentialSavegame) {
			if (star != nullptr) {
				if (atLeastOneInteractablePlanet) {
					bool foundInteractablePlanet = false;
					for (cPlanetRecordPtr planet : star->GetPlanetRecords()) {
						if (PlanetUtils::InteractablePlanet(planet.get())) {
							foundInteractablePlanet = true;
							break;
						}
					}
					if (!foundInteractablePlanet) {
						return false;
					}
				}
				Simulator::StarType type = star->GetType();
				return(type != Simulator::StarType::GalacticCore &&
					type != Simulator::StarType::BlackHole &&
					type != Simulator::StarType::ProtoPlanetary &&
					(!notSol || star != StarManager.GetSol()) &&
					(!noMonolith || (star->mFlags & (1 << 3)) == 0) &&
					(!noSavegame || (star->mFlags & (1 << 1)) == 0) &&
					(!noPotentialSavegame || (star->mFlags & (1 << 0)) == 0));
			}
			return false;
		}

        void GeneratePlanets(Simulator::cStarRecord* star) {
			eastl::vector<cPlanetRecordPtr> planets = star->GetPlanetRecords();
			Simulator::cStar * starT = static_cast<Simulator::cStar*>(GameNounManager.CreateInstance(Simulator::cStar::NOUN_ID));
			starT->mpStarRecord = star;
			starT->GetSolarSystem();
			GameNounManager.DestroyInstance(starT);
        }

		void DeleteTribeFromStar(Simulator::cStarRecord* star) {
			star->mTechLevel = Simulator::TechLevel::Creature;
			star->mCitizenSpeciesKey.instanceID = 0;
			star->mCitizenSpeciesKey.typeID = 0;
			star->mCitizenSpeciesKey.groupID = 0;
			star->mpSpeciesProfile = NULL;

			//find the planet with the tribe and edit it .
			for (cPlanetRecordPtr planet : star->GetPlanetRecords()) {
				if (planet->GetTechLevel() == Simulator::TechLevel::Tribe) {
					planet->mTechLevel = Simulator::TechLevel::Creature;
					planet->mTribeData.clear();
					break;
				}
			}
		}

		void DeleteCivFromStar(Simulator::cStarRecord* star) {
			star->mTechLevel = Simulator::TechLevel::Creature;
			star->mCitizenSpeciesKey.instanceID = 0;
			star->mCitizenSpeciesKey.typeID = 0;
			star->mCitizenSpeciesKey.groupID = 0;
			star->mpSpeciesProfile = NULL;

			//find the planet with the civ and edit it. 
			for (cPlanetRecordPtr planet : star->GetPlanetRecords()) {
				if (planet->GetTechLevel() == Simulator::TechLevel::Civilization) {
					planet->mTechLevel = Simulator::TechLevel::Creature;
					planet->mCivData.clear();
					break;
				}
			}
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

		Simulator::cStarRecord* GetClosestStarToStar(Simulator::cStarRecord* star, float searchRadius, bool atLeastOneInteractablePlanet, bool notSol, bool noMonolith, bool noSavegame, bool noPotentialSavegame){
			eastl::vector<cStarRecordPtr> closestStars;
			GetClosestStarsToStar(star, 1, closestStars, searchRadius, atLeastOneInteractablePlanet, notSol, noMonolith, noSavegame, noPotentialSavegame);
			if (!closestStars.empty()) {
				return closestStars[0].get();
			}
			else {
				return nullptr;
			}
		}

		void GetClosestStarsToStar(
			Simulator::cStarRecord* star,
			int maxCount,
			eastl::vector<cStarRecordPtr>& closestStars,
			float searchRadius,
			bool atLeastOneInteractablePlanet,
			bool notSol,
			bool noMonolith,
			bool noSavegame,
			bool noPotentialSavegame){

			Simulator::StarRequestFilter filter;
			filter.RemoveStarType(Simulator::StarType::None);
			filter.RemoveStarType(Simulator::StarType::GalacticCore);
			filter.RemoveStarType(Simulator::StarType::ProtoPlanetary);
			filter.RemoveStarType(Simulator::StarType::BlackHole);
			filter.minDistance = 0;

			eastl::vector<eastl::pair<float, cStarRecordPtr>> starsWithDistance;
			eastl::set<cStarRecordPtr> alreadyFound;

			float currentSearchRadius = min(3.0f, searchRadius);

			while (currentSearchRadius <= searchRadius && (int)alreadyFound.size() < maxCount){
				filter.maxDistance = currentSearchRadius;
				eastl::vector<cStarRecordPtr> nearbyStars;
				StarManager.FindStars(star->mPosition, filter, nearbyStars);
				for (const cStarRecordPtr& nearbyStar : nearbyStars){

					if (nearbyStar == star) {
						continue;
					}

					if (!ValidStar(
						nearbyStar.get(),
						atLeastOneInteractablePlanet,
						notSol,
						noMonolith,
						noSavegame,
						noPotentialSavegame)){
						continue;
					}

					// Duplicate check.
					if (!alreadyFound.insert(nearbyStar).second) {
						continue;
					}

					float distance = GetDistanceBetweenStars(star, nearbyStar.get());

					starsWithDistance.push_back({ distance, nearbyStar });
				}
				currentSearchRadius += 2.0f;
			}

			// Sort the vector from smallest distance to largest distance.
			eastl::sort(
				starsWithDistance.begin(),
				starsWithDistance.end(),
				[](const auto& a, const auto& b)
				{
					return a.first < b.first;
				});

			int count = min(maxCount, (int)starsWithDistance.size());

			for (int i = 0; i < count; i++)
			{
				closestStars.push_back(starsWithDistance[i].second);
			}
		}
    }
}