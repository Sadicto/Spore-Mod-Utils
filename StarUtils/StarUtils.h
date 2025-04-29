#pragma once
#include <Spore/Simulator/cStarRecord.h>

namespace SporeModUtils {
    namespace StarUtils {
		/**
		 * @brief Assign spices to all planets in the stars and generates its orbits.
		 * @param star The star system in which the planets will be generated
		 */
		void GeneratePlanets(Simulator::cStarRecord* star);

		/**
		 * @brief Retrieves all unclaimed stars within a specified radius of given coordinates.
		 * Optionally, it can include stars with tribes or civilizations, based on the provided flags.
		 * @param coords A `Vector3` representing the center coordinates.
		 * @param radius A `float` representing the search radius in parsecs.
		 * @param stars Vector to store the list of unclaimed stars found within the radius.
		 * @param includeTribes If `true`, stars with tribes will be included in the results.
		 * @param includeCivs If `true`, stars with civilizations will be included in the results.
		 */
		void GetUnclaimedStarsInRadius(const Vector3& coords, float radius, eastl::vector<cStarRecordPtr>& stars, bool includeTribes = false, bool includeCivs = false);

		/**
		 * @brief Calculates the distance between two star systems.
		 * @param star1
		 * @param star2
		 * @return float representing the distance between the two stars in parsecs.
		 */
		float GetDistanceBetweenStars(Simulator::cStarRecord* star1, Simulator::cStarRecord* star2);


    }
}

