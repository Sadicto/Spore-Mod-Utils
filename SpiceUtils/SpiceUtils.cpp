#include "stdafx.h"
#include "SpiceUtils.h"
namespace SporeModUtils {
    namespace SpiceUtils {

        void LoadSpices() {
            CALL(Address(ModAPI::ChooseAddress(0x0103D650, 0x0103C950)), void, Args(Simulator::cSpaceTrading*), Args(Simulator::cSpaceTrading::Get()));
        }

        void GetSpices(eastl::vector<ResourceKey>& spices) {
            SpiceUtils::LoadSpices();
            for (const ResourceKey& spiceKey : SpaceTrading.mSpices) {
                spices.push_back(spiceKey);
            }
        }

        bool SpiceCanSpawnOnPlanets(ResourceKey spiceKey) {
            PropertyListPtr propList;
            uint32_t spaceTradingId = 0x034D97FA;
            if (PropManager.GetPropertyList(spiceKey.instanceID, spaceTradingId, propList)) {
                uint32_t spaceTradingChanceBlueEasy = 0x068B6579;
                uint32_t spaceTradingChanceBlueHard = 0x068B657A;
                uint32_t spaceTradingChanceRedEasy = 0x068B657B;
                uint32_t spaceTradingChanceRedHard = 0x068B657C;
                uint32_t spaceTradingChanceYellowEasy = 0x068B657D;
                uint32_t spaceTradingChanceYellowHard = 0x068B657E;

                float chanceBlueEasy;
                float chanceBlueHard;
                float chanceRedEasy;
                float chanceRedHard;
                float chanceYellowEasy;
                float chanceYellowHard;

                App::Property::GetFloat(propList.get(), spaceTradingChanceBlueEasy, chanceBlueEasy);
                App::Property::GetFloat(propList.get(), spaceTradingChanceBlueHard, chanceBlueHard);
                App::Property::GetFloat(propList.get(), spaceTradingChanceRedEasy, chanceRedEasy);
                App::Property::GetFloat(propList.get(), spaceTradingChanceRedHard, chanceRedHard);
                App::Property::GetFloat(propList.get(), spaceTradingChanceYellowEasy, chanceYellowEasy);
                App::Property::GetFloat(propList.get(), spaceTradingChanceYellowHard, chanceYellowHard);
                return (chanceBlueEasy != 0.0f ||
                    chanceBlueHard != 0.0f ||
                    chanceRedEasy != 0.0f ||
                    chanceRedHard != 0.0f ||
                    chanceYellowEasy != 0.0f ||
                    chanceYellowHard != 0.0f);
            }
            return false;
        }

        void GetSpawnableSpices(eastl::vector<ResourceKey>& spices) {
            SpiceUtils::LoadSpices();
            for (const ResourceKey& spiceKey : SpaceTrading.mSpices) {
                if (SpiceCanSpawnOnPlanets(spiceKey)) {
                    spices.push_back(spiceKey);
                }
            }
        }

        float GetSpiceBaseCost(ResourceKey spiceKey) {
            float cost = 0;
            if (spiceKey.instanceID != 0) {
                PropertyListPtr propList;
                uint32_t spaceTradingId = 0x034D97FA;
                if (PropManager.GetPropertyList(spiceKey.instanceID, spaceTradingId, propList)) {
                    uint32_t spaceTradingBaseCostId = 0x034F1A4A;
                    App::Property::GetFloat(propList.get(), spaceTradingBaseCostId, cost);
                }
            }
            return cost;
        }

        void GetSpiceBaseCosts(eastl::map<ResourceKey, float>& spiceCosts) {
            eastl::vector<ResourceKey> spices;
            GetSpices(spices);
            for (const ResourceKey& spice : spices) {
                spiceCosts[spice] = GetSpiceBaseCost(spice);
            }
        }

        void GetSpawnableSpiceBaseCosts(eastl::map<ResourceKey, float>& spiceCosts) {
            eastl::vector<ResourceKey> spices;
            GetSpawnableSpices(spices);
            for (const ResourceKey& spice : spices) {
                spiceCosts[spice] = GetSpiceBaseCost(spice);
            }
        }

        ResourceKey GetCheapestSpice(const eastl::map<ResourceKey, float>& spiceCosts) {
            if (!spiceCosts.empty()) {
                auto minIt = spiceCosts.begin();
                for (auto it = spiceCosts.begin(); it != spiceCosts.end(); ++it) {
                    if (it->second < minIt->second) {
                        minIt = it;
                    }
                }
                return minIt->first;
            }
            return ResourceKey(0, 0, 0);
        }

        bool LowValueSpice(ResourceKey spiceKey, const eastl::map<ResourceKey, float>& spiceCosts) {
            ResourceKey cheapestSpice = GetCheapestSpice(spiceCosts);
            auto it = spiceCosts.find(cheapestSpice);
            if (it == spiceCosts.end()) {
                // This should never happen.
                return false;
            }
            float cheapestSpiceCost = it->second;
            it = spiceCosts.find(spiceKey);
            if (it == spiceCosts.end()) {
                return true;
            }
            float spiceCost = it->second;
            return (cheapestSpiceCost * 2 > spiceCost);
        }

        bool LowValueSpice(ResourceKey spiceKey) {
            eastl::map<ResourceKey, float> spiceCosts;
            GetSpawnableSpiceBaseCosts(spiceCosts);
            return LowValueSpice(spiceKey, spiceCosts);
        }
    }
}
