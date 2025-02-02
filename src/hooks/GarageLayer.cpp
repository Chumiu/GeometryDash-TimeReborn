#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>

using namespace geode::prelude;


class $modify(GJGarageLayer)
{
    bool init()
    {
        if (!GJGarageLayer::init())
            return false;

        auto menu = getChildByID("shards-menu");

        if (auto shards = menu->getChildByID("shards-button"))
            shards->setVisible(false);

        if (auto paint = menu->getChildByID("color-button"))
            paint->setPositionY(paint->getPositionY() + 25);

        if (auto userLabel = getChildByID("username-label"))
            userLabel->setVisible(false);

        if (auto userHint = getChildByID("username-hint"))
            userHint->setVisible(false);

        return true;
    }

};