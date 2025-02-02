#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>
#include "../layers/TimeRebornActLayer.hpp"
#include "../miscellaneous/Utils.hpp"

using namespace geode::prelude;

class $modify(GameManager)
{
    bool isColorUnlocked(int p0, UnlockType p1) 
    {   
        return true;
    }

    bool isIconUnlocked(int p0, IconType p1) {
        
        if (p1 == IconType::Cube)
            if (p0 > 4 && p0 < 21 && p0 != 13)
                return GameManager::isIconUnlocked(p0, p1);

        if (p0 == 2 &&
            (p1 == IconType::Ball ||
            p1 == IconType::Ufo ||
            p1 == IconType::Jetpack)
        )
            return GameManager::isIconUnlocked(p0, p1);

        return true;
    }

    void returnToLastScene(GJGameLevel* p0)
     {

        if (p0->m_levelType == GJLevelType::Local)
        {
            //log::info("{}", p0->m_levelID.value());
            auto actScene = TimeRebornActLayer::scene(TimeReborn::actForLevel(p0->m_levelID.value()), p0->m_levelID.value());

            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, actScene));
            return;
        }
        GameManager::returnToLastScene(p0);
    }

    
};