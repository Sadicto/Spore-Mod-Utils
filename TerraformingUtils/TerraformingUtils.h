#pragma once
namespace SporeModUtils {
    namespace TerraformingUtils {
        struct Point {
            float x, y;
        };

        struct Polar {
            float r, theta;
        };

        enum class TerraformingObstacle {
            Cold,
            Hot,
            LowAtmosphere,
            HighAtmosphere,
            ColdLowAtmosphere,
            ColdHighAtmosphere,
            HotLowAtmosphere,
            HotHighAtmosphere,
            None
        };

        // @brief Converts a cartesian point (x, y) to polar coordinates (r, theta)
        // relative to a polar coordinate system centered at (TCenter, TCenter).
        Polar cartesianToPolar(const Point& p);

        // @brief Converts a polar coordinate (r, theta) to a cartesian point (x, y),
        // assuming the polar origin is at (TCenter, TCenter).
        Point polarToCartesian(const Polar& polar);


        /**
         * @brief Determines the main obstacle preventing the given planet
         * from reaching the specified terraforming score.
         * @param planet
         * @param targetTScore
         * @return The TerraformingObstacle that prevents the planet from reaching targetTerrascore.
         */
        TerraformingObstacle GetTerraformingObstacle(Simulator::cPlanetRecord* planet, Simulator::PlanetType targetTerrascore);

        /**
         * @brief Adjusts the planet's atmosphere and temperature to match  the specified terrascore level.
         * @param planet Pointer to the planet record to be modified.
         * @param terrapuntuation Target terrascore level to have (T0, T1, T2, or T3).
         */
        void SetAtmosphereAndTemperatureToTerrascore(Simulator::cPlanetRecord* planet, Simulator::PlanetType terrascore);

        /**
         * @brief Fully terraforms the planet by adjusting atmosphere, temperature,
         * and populating the ecosystem to match the specified terrascore level.
         * @param planet.
         * @param terrapuntuation Target terrascore level to have (T0, T1, T2, or T3).
         */
        void TerraformToTerrascore(Simulator::cPlanetRecord* planet, Simulator::PlanetType terrascore);



    }
}

