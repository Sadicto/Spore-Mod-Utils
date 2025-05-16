#pragma once
#include <Spore/Simulator/cStarRecord.h>

namespace SporeModUtils {
    namespace EmpireUtils {


		/**
		 * An empire is considered valid if it is not null, owns at least one system,
		 * and passes the optional filter conditions.
		 * @param empire Vector3 representing the center coordinates.
		 * @param includePlayer If set to `false`, the player empire will be excluded.
		 * @param includeGrox If set to `false`, the Grox empire will be excluded.
		 * @param includeOtherSaves If set to `false`, empires from other savegames will be excluded.
		 * @return true if the empire is a valid NPC empire; false otherwise.
		 */
		bool ValidNpcEmpire(Simulator::cEmpire* empire, bool includePlayer = false, bool includeGrox = false, bool includeOtherSaves = false);

		/**
		 * Returns the home star system of the given empire, assigning one if necessary.
		 * @param empire.
		 * @return Pointer to the home star system of the specified empire, or nullptr if the empire is null.
		 */
		Simulator::cStarRecord* GetHomeStar(Simulator::cEmpire* empire);


		/**
		 * @brief Retrieves all empires within a given radius of coordinates,
		 * @param coords Vector3 representing the center coordinates.
		 * @param radius float representing the search radius in parsecs.
		 * @param empires Vector to store the list of empires found within the radius.
		 * @param includePlayer If set to `false`, the player empire will not be included in the list of empires, even if found.
		 * @param includeGrox If set to `false`, the Grox empire will not be included in the list of empires, even if found.
		 * @param includeOtherSaves If set to `false`, empires from other savegames will not be included, even if found.
		 */
		void GetEmpiresInRadius(const Vector3& coords, float radius, eastl::vector<cEmpirePtr>& empires, bool includePlayer = false, bool includeGrox = false, bool includeOtherSaves = false);

		/**
		 * @brief Returns the power level of an empire.
		 *
		 * In vanilla, the empire's power level is based on the number of systems it controls.
		 * The level displayed in the game is one more than the returned value:
		 * @param empire
		 * @return An integer representing the empire's power level.
		 */
		int GetEmpireLevel(Simulator::cEmpire* empire);

		/**
		 * Fills the provided vector with the planets from the empire's systems, applying optional filters.
		 * @param empire
		 * @param planets The vector to be filled with planets matching the specified filters.
		 * @param excludeColonized If true, excludes planets that are already colonized by the empire.
		 * @param excludeUncolonized If true, skips uncolonized planets.
		 * @param excludeBlueRedOrbitWithLowValueSpice If true, excludes planets in blue or red orbits that have low-value spices.
		 * @param excludeT0 If true, excludes all T0 planets regardless of spice type.
		 */
		void GetEmpirePlanets(Simulator::cEmpire* empire, eastl::vector<cPlanetRecordPtr>& planets, const eastl::map<ResourceKey, float>& spiceCosts, bool excludeColonized = false, bool excludeUncolonized = false, bool excludeBlueRedOrbit = false, bool excludeBlueRedOrbitWithLowValueSpice = false, bool excludeT0 = false);

		/**
		 * Fills the provided vector with the planets from the empire's systems, applying optional filters.
		 *
		 * @param empire
		 * @param planets The vector to be filled with planets that match the specified filters.
		 * @param spiceCosts A map containing the cost of different spice types, used to filter planets with low-value spices.
		 * @param excludeColonized If true, excludes planets that are already colonized by the empire.
		 * @param excludeUncolonized If true, excludes uncolonized planets from the result.
		 * @param excludeBlueRedOrbit If true, excludes planets in blue or red orbits from the result.
		 * @param excludeBlueRedOrbitWithLowValueSpice If true, excludes planets in blue or red orbits that have low-value spices.
		 * @param excludeT0 If true, excludes all T0 planets, regardless of spice type or other conditions.
		 */
		void GetEmpirePlanets(Simulator::cEmpire* empire, eastl::vector<cPlanetRecordPtr>& planets, bool excludeColonized = false, bool excludeUncolonized = false, bool excludeBlueRedOrbit = false, bool excludeBlueRedOrbitWithLowValueSpice = false, bool excludeT0 = false);


    }
}

