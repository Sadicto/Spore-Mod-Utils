#pragma once

namespace SporeModUtils {
    namespace EmpireUtils {
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

    }
}

