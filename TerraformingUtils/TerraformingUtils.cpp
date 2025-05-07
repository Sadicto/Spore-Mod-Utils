#include "stdafx.h"
#include "TerraformingUtils.h"
#include <Spore-Mod-Utils/PlanetUtils/PlanetUtils.h>

const float T0Threshold = 0.6f;
const float T1Threshold = 0.4f;
const float T2Threshold = 0.25f;
const float T3Threshold = 0.1f;
const float TCenter = 0.5f;

namespace SporeModUtils {
    namespace TerraformingUtils {

        Polar cartesianToPolar(const Point& p) {
            float dx = p.x - TCenter;
            float dy = p.y - TCenter;
            Polar polar;
            if (dx == 0 && dy == 0) {
                polar.r = 0.0f;
                polar.theta = 0.0f;
            }
            else {
                polar.r = std::sqrt(dx * dx + dy * dy);
                polar.theta = std::atan2(dy, dx);
            }
            return polar;
        }

        Point polarToCartesian(const Polar& polar) {
            Point p;
            p.x = TCenter + polar.r * std::cos(polar.theta);
            p.y = TCenter + polar.r * std::sin(polar.theta);
            return p;
        }

        TerraformingObstacle GetTerraformingObstacle(Simulator::cPlanetRecord* planet, Simulator::PlanetType targetTerrascore) {
            // I'm very sorry for anyone who read this method.
            float threshold;
            switch (targetTerrascore) {
            case(Simulator::PlanetType::T1): {
                threshold = T1Threshold;
                break;
            }
            case(Simulator::PlanetType::T2): {
                threshold = T2Threshold;
                break;
            }
            case(Simulator::PlanetType::T3): {
                threshold = T3Threshold;
                break;
            }
            default: {
                return TerraformingObstacle::None;
            }
            }

            const float ideal = TCenter;

            float temp = planet->mTemperatureScore;
            float atmos = planet->mAtmosphereScore;

            bool tooCold = temp < ideal - threshold;
            bool tooHot = temp > ideal + threshold;
            bool tooThin = atmos < ideal - threshold;
            bool tooDense = atmos > ideal + threshold;

            if (tooCold && tooThin) return TerraformingObstacle::ColdLowAtmosphere;
            if (tooCold && tooDense) return TerraformingObstacle::ColdHighAtmosphere;
            if (tooHot && tooThin) return TerraformingObstacle::HotLowAtmosphere;
            if (tooHot && tooDense) return TerraformingObstacle::HotHighAtmosphere;

            if (tooCold) return TerraformingObstacle::Cold;
            if (tooHot) return TerraformingObstacle::Hot;
            if (tooThin) return TerraformingObstacle::LowAtmosphere;
            if (tooDense) return TerraformingObstacle::HighAtmosphere;

            return TerraformingObstacle::None;

        }

        void SetAtmosphereAndTemperatureToTerrascore(Simulator::cPlanetRecord* planet, Simulator::PlanetType terrascore) {
            float radious;
            switch (terrascore) {
            case(Simulator::PlanetType::T0): {
                radious = T0Threshold;
                break;
            }
            case(Simulator::PlanetType::T1): {
                radious = T1Threshold;
                break;
            }
            case(Simulator::PlanetType::T2): {
                radious = T2Threshold;
                break;
            }
            case(Simulator::PlanetType::T3): {
                radious = T3Threshold;
                break;
            }
            default: {
                return;
            }
            }
            Point planetTerrascoreCartesian;
            planetTerrascoreCartesian.x = planet->mTemperatureScore;
            planetTerrascoreCartesian.y = planet->mAtmosphereScore;

            Polar planetTerrascorePolar = cartesianToPolar(planetTerrascoreCartesian);

            planetTerrascorePolar.r = radious - 0.1f;
            planetTerrascoreCartesian = polarToCartesian(planetTerrascorePolar);

            planet->mTemperatureScore = planetTerrascoreCartesian.x;
            planet->mAtmosphereScore = planetTerrascoreCartesian.y;


        }

        void TerraformToTerrascore(Simulator::cPlanetRecord* planet, Simulator::PlanetType terrascore) {
            if (PlanetUtils::InteractablePlanet(planet) &&
                (terrascore == Simulator::PlanetType::T0 ||
                 terrascore == Simulator::PlanetType::T1 || 
                 terrascore == Simulator::PlanetType::T2 || 
                 terrascore == Simulator::PlanetType::T3 )) {
                SetAtmosphereAndTemperatureToTerrascore(planet, terrascore);
                planet->mType = terrascore;
                PlanetUtils::FillPlanetEcosystem(planet);
            }
        }
    }
}
