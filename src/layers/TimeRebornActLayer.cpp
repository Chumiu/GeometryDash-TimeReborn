
#include "TimeRebornActLayer.hpp"
#include "../miscellaneous/LevelPopup.hpp"
#include "../miscellaneous/Utils.hpp"

bool TimeRebornActLayer::init(int currentAct)
{
    m_winSize = CCDirector::get()->getWinSize();

    setContentSize(m_winSize);

    m_currentAct = currentAct;

    if (m_currentPage == 0)
        m_currentPage = 1 + 3 * (currentAct - 1);

    m_background = CCSprite::create();
    addChild(m_background, -2);

    TimeReborn::addCorners(this, "GJ_sideArt_001.png", 0);

    auto backMenu = CCMenu::create();
    backMenu->setPosition(24, m_winSize.height - 24);

    auto backSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    auto backButton = CCMenuItemSpriteExtra::create(backSpr, this, menu_selector(TimeRebornActLayer::onBack));

    backMenu->addChild(backButton);
    addChild(backMenu);

    auto menu = CCMenu::create();
    

    m_islandSprite = CCSprite::createWithSpriteFrameName("island_01.png"_spr);
    m_islandSprite->setScale(.5f);

    m_islandButton = CCMenuItemSpriteExtra::create(m_islandSprite, this, menu_selector(TimeRebornActLayer::onLevel));
    m_islandButton->setPositionY(m_islandButton->getPositionY() - 25);
    menu->addChild(m_islandButton);


     auto navSprite = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    navSprite->setFlipX(true);

    auto navSprite2 = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");

    auto leftButton = CCMenuItemSpriteExtra::create(navSprite, this, menu_selector(TimeRebornActLayer::onBackPage));
    leftButton->setPositionX(-m_winSize.width / 2 + 45);
    menu->addChild(leftButton);

    auto rightButton = CCMenuItemSpriteExtra::create(navSprite2, this, menu_selector(TimeRebornActLayer::onNextPage));
    rightButton->setPositionX(m_winSize.width / 2 - 45);
    menu->addChild(rightButton);


    addChild(menu);


    m_titleSprite = CCSprite::create();
    m_titleSprite->setScale(.8f);

    addChild(m_titleSprite, 10);


    updatePage(m_currentPage);

    setKeypadEnabled(true);
    setTouchEnabled(true);

    return true;
}


void TimeRebornActLayer::updatePage(int currentLevel)
{
    m_currentPage = currentLevel;

    int bgID = backgroundForPage(currentLevel);
    m_background->setDisplayFrame(CCSprite::create(GameManager::sharedState()->getBGTexture(bgID))->displayFrame());
    m_background->setColor(colorForPage(currentLevel));
    m_background->setAnchorPoint({0, 0});
    m_background->setPositionY(-100);
    m_background->setScale(m_winSize.width / m_background->getContentWidth());

    auto title = CCSprite::createWithSpriteFrameName(fmt::format("island_{:02}_logo.png"_spr, currentLevel).c_str());
    m_titleSprite->setDisplayFrame(title->displayFrame());
    m_titleSprite->setOpacity(0);
    m_titleSprite->runAction(CCFadeTo::create(.5f, 255));

    auto island = CCSprite::createWithSpriteFrameName(fmt::format("island_{:02}.png"_spr, currentLevel).c_str());
    m_islandSprite->setDisplayFrame(island->displayFrame());
    m_islandSprite->setOpacity(0);
    m_islandSprite->runAction(CCFadeTo::create(.5f, 255));

    float scale = .7f;
    float logoScale = .8f;
    CCPoint logoOffset = {0, 0};

    switch (currentLevel)
    {
    case 2:
        scale = 1.5f;
        break;
    case 6:
    case 7:
        scale = 1;
        break;
    case 8:
        logoScale = .65f;
        break;
    case 9:
        logoScale = .6f;
        logoOffset = ccp(0, -10);
        break;
    }
    if (currentLevel == 2) scale = 1.5f;
    m_islandSprite->setScale(scale);

    m_islandButton->setTag(currentLevel);

    m_titleSprite->setScale(logoScale);
    m_titleSprite->setPosition(ccp(m_winSize.width / 2, m_winSize.height - 45) + logoOffset);

}

void TimeRebornActLayer::onLevel(CCObject* sender)
{
    LevelPopup::create(sender->getTag())->show();
}

void TimeRebornActLayer::onBackPage(CCObject*)
{
    if (m_currentPage < (3 * m_currentAct) - 1)
        m_currentPage = 3 * m_currentAct;
    else m_currentPage--;

    updatePage(m_currentPage);

}

void TimeRebornActLayer::onNextPage(CCObject*)
{
    if (m_currentPage > (3 * m_currentAct) - 1)
        m_currentPage = 1 + 3 * (m_currentAct - 1);
    else m_currentPage++;

    updatePage(m_currentPage);
}

ccColor3B TimeRebornActLayer::colorForPage(int currentLevel)
{
    std::vector<ccColor3B> colors = {
            {9, 49, 64},
            {0, 100, 0},
            {0, 0, 139},
            {47, 00, 83},
            {56, 40, 90},
            {12, 44, 94},
            {17, 57, 37},
            {30, 3, 33},
            {28, 32, 72}
        };

    return colors[currentLevel - 1];
}

int TimeRebornActLayer::backgroundForPage(int currentLevel)
{
    std::vector<int> backgrounds = {35, 26, 28, 17, 29, 23, 28, 27, 32 };
    return backgrounds[currentLevel - 1];
}

void TimeRebornActLayer::keyBackClicked()
{
    CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(0.5, MenuLayer::scene(false)));
}

void TimeRebornActLayer::onBack(CCObject*)
{
    keyBackClicked();
}

TimeRebornActLayer* TimeRebornActLayer::create(int currentAct, int currentPage)
{
    TimeRebornActLayer *pRet = new TimeRebornActLayer();

    pRet->m_currentPage = currentPage;

    if (pRet->init(currentAct))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

CCScene* TimeRebornActLayer::scene(int currentAct, int currentPage)
{
    auto scene = CCScene::create();
    scene->addChild(TimeRebornActLayer::create(currentAct, currentPage));

    return scene;
}

