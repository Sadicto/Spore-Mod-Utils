#pragma once
namespace SporeModUtils {
    namespace SpiceUtils {

		/**
		 * @brief Loads all available spices into SpaceTrading.mSpices.
		 * If SpaceTrading.mSpices already contains elements, the function does nothing.
		 * Otherwise, it populates the list with all available spices.
		 */
		void LoadSpices();

		/**
		* @brief Fills the given vector with spices that can spawn on planets.
		 * Iterates over all available spices and adds them to the vector.
		 * @param spices vector to be filled with the spices.
		 */
		void GetSpices(eastl::vector<ResourceKey>& spices);


		/**
		 * @brief Checks whether a spice has a non zero chance of appearing on planets.
		 * @param spiceKey ResourceKey to the given spice.
		 * @return true if the spice can spawn on planets; false otherwise.
		 */
		bool SpiceCanSpawnOnPlanets(ResourceKey spiceKey);

		/**
		* @brief Fills the given vector with spices that can spawn on planets.
		 * Iterates over all available spices and adds them to the vector if SpiceCanSpawnOnPlanets(spice).
		 * @param spices vector to be filled with the spices.
		 */
		void GetSpawnableSpices(eastl::vector<ResourceKey>& spices);

		/**
		 * @brief Returns the base cost of the given spice.
		 * @param spiceKey The ResourceKey of the spice.
		 * @return The base cost of the spice, or 0 if the spice is not valid.
		 */
		float GetSpiceBaseCost(ResourceKey spiceKey);

		/**
		 * @brief Fills the given map with the base costs of all spices.
		 * Iterates through all available spices and adds each one to the map along with its base cost.
		 * The key is the spice resource, and the value is its base cost.
		 *
		 * @param spiceCosts map that will be filled with the spice keys and their base costs.
		 */
		void GetSpiceBaseCosts(eastl::map<ResourceKey, float>& spiceCosts);

		/**
		 * @brief Fills the given map with the base costs of all spices.
		 * Iterates through all available spices and adds those that can spawn on planets along with its base cost.
		 * The key is the spice resource, and the value is its base cost.
		 * @param spiceCosts map that will be filled with the spice keys and their base costs.
		 */
		void GetSpawnableSpiceBaseCosts(eastl::map<ResourceKey, float>& spiceCosts);

		/**
		 * @brief Retrieves the spice with the lowest value from the given map.
		 * Iterates through the provided map of spices and returns the one with the lowest cost.
		 * @param spiceCosts A map where the key is the spice resource and the value is its cost.
		 * @return The key of the spice with the lowest value or ResourceKey(0,0,0) if the map is empty.
		 */
		ResourceKey GetCheapestSpice(const eastl::map<ResourceKey, float>& spiceCosts);

		/*
		 * Returns true if the given spice is considered low-value; that is, if
		 * its cost is less than twice the cost of the cheapest spice.
		 * @param spiceKey
		 * @param spiceCosts A map containing the cost associated with each spice.
		 * @return True if the spice has a cost below the defined threshold, false otherwise.
		 */
		bool LowValueSpice(ResourceKey spiceKey, const eastl::map<ResourceKey, float>& spiceCosts);

		/*
		 * Returns true if the given spice is considered low-value; that is, if
		 * its cost is less than twice the cost of the cheapest spice.
		 * The cost data is retrieved by calling GetSpawnableSpiceBaseCosts().
		 *
		 * @param spiceKey
		 * @return True if the spice has a cost below the defined threshold, false otherwise.
		 */
		bool LowValueSpice(ResourceKey spiceKey);


    }
}
