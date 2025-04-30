#include "stdafx.h"
#include "PlanetUtils.h"
namespace SporeModUtils {
	namespace PlanetUtils {

		bool InteractablePlanet(Simulator::cPlanetRecord* planet) {
			ResourceKey adventureIconKey;
			ResourceKey::Parse(adventureIconKey, u"0x0199b485!0x881aeb0a.0x2f7d0004");
			Simulator::PlanetType type = planet->mType;
			return ((type == Simulator::PlanetType::T3 ||
				type == Simulator::PlanetType::T2 ||
				type == Simulator::PlanetType::T1 ||
				type == Simulator::PlanetType::T0) &&
				(Simulator::cPlanetRecord::GetTypeIconKey(planet) != adventureIconKey && //not adventure, idk if there's a better way to do this
					!planet->IsDestroyed()));
		}

		Simulator::SolarSystemOrbitTemperature GetPlanetOrbitTemperature(Simulator::cPlanetRecord* planet) {
			if (planet->mFlags & Simulator::PlanetFlags::kPlanetFlagBlueOrbit) {
				return Simulator::SolarSystemOrbitTemperature::Cold;
			}
			else if (planet->mFlags & Simulator::PlanetFlags::kPlanetFlagRedOrbit) {
				return Simulator::SolarSystemOrbitTemperature::Hot;
			}
			else {
				return Simulator::SolarSystemOrbitTemperature::Normal;
			}
		}
		bool PlanetHasCompletePlantEcosystem(Simulator::cPlanetRecord* planet) {
			Simulator::PlanetType planetType = planet->mType;
			int plantSpeciesNum = planet->mPlantSpecies.size();
			return (planetType == Simulator::PlanetType::T0) ||
				(planetType == Simulator::PlanetType::T1 && plantSpeciesNum == 3) ||
				(planetType == Simulator::PlanetType::T2 && plantSpeciesNum == 6) ||
				(planetType == Simulator::PlanetType::T3 && plantSpeciesNum == 9);
		}
		bool PlanetHasCompleteAnimalEcosystem(Simulator::cPlanetRecord* planet) {
			Simulator::PlanetType planetType = planet->mType;
			int animalSpeciesNum = planet->mAnimalSpecies.size();
			return (planetType == Simulator::PlanetType::T0) ||
				(planetType == Simulator::PlanetType::T1 && animalSpeciesNum == 3) ||
				(planetType == Simulator::PlanetType::T2 && animalSpeciesNum == 6) ||
				(planetType == Simulator::PlanetType::T3 && animalSpeciesNum == 9);
		}
		bool PlanetHasCompleteEcosystem(Simulator::cPlanetRecord* planet) {
			return PlanetHasCompletePlantEcosystem(planet) && PlanetHasCompleteAnimalEcosystem(planet);
		}
		void FillPlanetPlants(Simulator::cPlanetRecord* planet) {
			if ((planet->mType == Simulator::PlanetType::T3 ||
				planet->mType == Simulator::PlanetType::T2 ||
				planet->mType == Simulator::PlanetType::T1) &&
				!PlanetHasCompletePlantEcosystem(planet)) {
				ResourceKey terrainScript = planet->GetGeneratedTerrainKey();
				eastl::vector<ResourceKey> scriptPlants;
				CALL(Address(ModAPI::ChooseAddress(0x00BABFF0, 0x00BAD210)), void, Args(Simulator::cStarManager*, ResourceKey*, eastl::vector<ResourceKey>*),
					Args(Simulator::cStarManager::Get(), &terrainScript, &scriptPlants));

				int planetTerrascore = static_cast<int>(planet->mType) - 2;
				CALL(Address(ModAPI::ChooseAddress(0x00BAB7A0, 0x00BAC9C0)), void, Args(Simulator::cStarManager*, eastl::vector<ResourceKey>*, int, int, int, int, eastl::vector<ResourceKey>*),
					Args(Simulator::cStarManager::Get(), &scriptPlants, planetTerrascore, planetTerrascore - 1, 3, 0, &planet->mPlantSpecies));
			}
		}
		void FillPlanetCreatures(Simulator::cPlanetRecord* planet) {
			if ((planet->mType == Simulator::PlanetType::T3 ||
				planet->mType == Simulator::PlanetType::T2 ||
				planet->mType == Simulator::PlanetType::T1) &&
				!PlanetHasCompleteAnimalEcosystem(planet)) {

				int planetTerrascore = static_cast<int>(planet->mType) - 2;
				eastl::vector<ResourceKey> priorityCreatures; // empty, we don't care about specific creatures.
				CALL(Address(ModAPI::ChooseAddress(0x00BABC40, 0x00BACE60)), void, Args(Simulator::cStarManager*, eastl::vector<ResourceKey>*, int, int, int, int, eastl::vector<ResourceKey>*),
					Args(Simulator::cStarManager::Get(), &priorityCreatures, planetTerrascore, planetTerrascore - 1, 2, 1, &planet->mAnimalSpecies));
			}
		}
		void FillPlanetEcosystem(Simulator::cPlanetRecord* planet) {
			if (!PlanetHasCompletePlantEcosystem(planet)) {
				FillPlanetPlants(planet);
			}
			if (!PlanetHasCompleteAnimalEcosystem(planet)) {
				FillPlanetCreatures(planet);
			}
		}
	}
}