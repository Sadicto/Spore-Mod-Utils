#pragma once
#include <Spore/Simulator/cPlanetRecord.h>

namespace SporeModUtils {
    namespace PlanetUtils {
		/**
		 * @brief Deletes a tribal species from a star system.
		 * @param star
		 */
		void DeleteTribeFromStar(Simulator::cStarRecord* star);

		/**
		 * @brief Deletes a civilization from a star system.
		 * @param star
		 */
		void DeleteCivFromStar(Simulator::cStarRecord* star);

		/**
		* @brief Returns the orbit's type of a planet (hot, cold or normal).
		* @param planet
		* @return the orbit's type
		*/
		Simulator::SolarSystemOrbitTemperature GetPlanetOrbitTemperature(Simulator::cPlanetRecord* planet);

		/**
		 * @brief Checks whether the planet has a complete plant ecosystem according to its terraScore.
		 * @param planet
		 * @return true if the planet has all required plant species, false otherwise.
		 */
		bool PlanetHasCompletePlantEcosystem(Simulator::cPlanetRecord* planet);

		/**
		 * @brief Checks whether the planet has a complete animal ecosystem according to its terraScore.
		 * @param planet
		 * @return true if the planet has all required animal species, false otherwise.
		 */
		bool PlanetHasCompleteAnimalEcosystem(Simulator::cPlanetRecord* planet);

		/**
		 * @brief Checks whether the planet has a complete ecosystem (both plants and animals) according to its terraScore.
		 * @param planet
		 * @return true if the planet has a full plant and animal ecosystem, false otherwise.
		 */
		bool PlanetHasCompleteEcosystem(Simulator::cPlanetRecord* planet);


		/**
		 * @brief Populates the planet's plant species based on the maximum capacity determined by the terrascore.
		 * @param planet
		 */
		void FillPlanetPlants(Simulator::cPlanetRecord* planet);

		/**
		 * @brief Populates the planet's creature species based on the maximum capacity determined by the terrascore.
		 * @param planet
		 */
		void FillPlanetCreatures(Simulator::cPlanetRecord* planet);

		/**
		 * @brief Populates the planet's ecosystem with both plant and creature species based on the maximum capacity determined by the terrascore.
		 * @param planet
		 */
		void FillPlanetEcosystem(Simulator::cPlanetRecord* planet);
    }
}

