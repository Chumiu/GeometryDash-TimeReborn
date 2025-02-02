#include "SelectActPopup.hpp"
#include "../layers/TimeRebornActLayer.hpp"
#include "Utils.hpp"

bool SelectActPopup::setup(std::string const &title)
{
    setTitle("Select Act");

    auto act1 = CCSprite::createWithSpriteFrameName("actBtn_01.png"_spr);
    auto act2 = CCSprite::createWithSpriteFrameName("actBtn_02.png"_spr);
    if (!isActCompleted(1))
        act2->setColor({100, 100, 100});

    auto act3 = CCSprite::createWithSpriteFrameName("actBtn_03.png"_spr);
    if (!isActCompleted(2))
        act3->setColor({100, 100, 100});

    auto button1 = CCMenuItemSpriteExtra::create(act1, this, menu_selector(SelectActPopup::onSelectAct));
    button1->setTag(1);
    button1->setPosition(m_size / 2 + CCPoint(0, 35));
    m_buttonMenu->addChild(button1);

 
    auto button2 = CCMenuItemSpriteExtra::create(act2, this, menu_selector(SelectActPopup::onSelectAct));
    button2->setTag(2);
    button2->setPosition(m_size / 2);
    m_buttonMenu->addChild(button2);

    auto button3 = CCMenuItemSpriteExtra::create(act3, this, menu_selector(SelectActPopup::onSelectAct));
    button3->setTag(3);
    button3->setPosition(m_size / 2 + CCPoint(0, -35));
    m_buttonMenu->addChild(button3);
    
    return true;
};

void SelectActPopup::onSelectAct(CCObject* sender)
{
    if (!isActCompleted(sender->getTag() - 1))
    {
        FLAlertLayer::create("Locked", fmt::format("Complete <cg>ACT {}</c> to <cl>unlock</c> this ACT", sender->getTag() - 1), "OK")->show();
        return;
    }
    auto scene = TimeRebornActLayer::scene(sender->getTag(), 0);
    CCDirector::get()->pushScene(CCTransitionFade::create(0.5f, scene));
}

bool SelectActPopup::isActCompleted(int act)
{
    if (act < 1)
        return true;

    int actLevelID = 3 * act;
    int level1 = GameLevelManager::get()->getMainLevel(actLevelID - 2, true)->m_normalPercent.value();
    int level2 = GameLevelManager::get()->getMainLevel(actLevelID - 1, true)->m_normalPercent.value();
    int level3 = GameLevelManager::get()->getMainLevel(actLevelID , true)->m_normalPercent.value();
    if (level1 == 100 &&
        level2 == 100 &&
        level3 == 100)
        return true;
        
    return false;
}

SelectActPopup *SelectActPopup::create()
{
    auto ret = new SelectActPopup();

    if (ret && ret->initAnchored(150.f, 180.f, ""))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
};