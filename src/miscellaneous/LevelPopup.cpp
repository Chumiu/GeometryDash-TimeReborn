#pragma once
#include "LevelPopup.hpp"
#include "Utils.hpp"

bool LevelPopup::setup(std::string const &title)
{
    m_level = GameLevelManager::get()->getMainLevel(m_levelID, true);

    auto contentSize = m_mainLayer->getContentSize();

    // title
    setTitle(m_level->m_levelName);
    m_title->limitLabelWidth(180, .85f, .1f);
    m_title->setPositionY(m_title->getPositionY() - 5.0f);

    // close button
    m_closeBtn->setPosition(m_closeBtn->getPositionX() + 5, m_closeBtn->getPositionY() - 5);

    auto difficultyNode = TimeReborn::createDifficultyNode(m_level);
    difficultyNode->setPosition({contentSize.width / 5, contentSize.height / 2 + 35});
    difficultyNode->setAnchorPoint({0.5f, 0.5f});
    difficultyNode->setID("difficulty-node"_spr);
    m_mainLayer->addChild(difficultyNode);

    auto normalProgress = TimeReborn::createProgressBar(m_level->m_normalPercent, false);
    normalProgress->setPosition({contentSize.width / 2, contentSize.height / 2 - 45.0f});
    m_mainLayer->addChild(normalProgress);

    auto practiceProgress = TimeReborn::createProgressBar(m_level->m_practicePercent, true);
    practiceProgress->setPosition({contentSize.width / 2, normalProgress->getPositionY() - 40.0f});
    m_mainLayer->addChild(practiceProgress);

    m_buttonsMenu = CCMenu::create();
    m_buttonsMenu->setContentSize(m_mainLayer->getContentSize());
    m_buttonsMenu->setPosition({0, 0});

    auto playButton = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png"),
        this,
        menu_selector(LevelPopup::onPlay));
    playButton->setPosition({m_buttonsMenu->getContentWidth() / 2, m_buttonsMenu->getContentHeight() / 2 + 40.f});


    auto optionsSprite = CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
    optionsSprite->setScale(.8f);

    auto optionsButton = CCMenuItemSpriteExtra::create(
        optionsSprite,
        this,
        menu_selector(LevelPopup::onSettings));
    optionsButton->setPosition({8, 8});

    std::string levelInfo = fmt::format(
        "<cy>{}</c>\n"
        "<cg>Total Attempts</c>: {}\n"
        "<cl>Total Jumps</c>: {}\n"
        "<cp>Normal</c>: {}%\n"
        "<co>Practice</c>: {}%\n",
        m_level->m_levelName, m_level->m_attempts.value(), m_level->m_jumps.value(), m_level->m_normalPercent.value(), m_level->m_practicePercent
    );

    auto infoButton = InfoAlertButton::create("Level Stats", levelInfo, 1);
    infoButton->setPosition({m_buttonsMenu->getContentWidth() - 20.f, m_buttonsMenu->getContentHeight() - 20.f});

    auto songSprite = CCSprite::createWithSpriteFrameName("GJ_playMusicBtn_001.png");
    songSprite->setScale(.5f);

    //  Adding the buttons
    m_buttonsMenu->addChild(playButton);
    m_buttonsMenu->addChild(infoButton);
    m_buttonsMenu->addChild(optionsButton);

    TimeReborn::addCorners(m_mainLayer, "dailyLevelCorner_001.png", 0);

    m_mainLayer->addChild(m_buttonsMenu);

    return true;
}

void LevelPopup::onSettings(CCObject *sender)
{
    auto layer = GameLevelOptionsLayer::create(m_level);
    layer->show();
};

void LevelPopup::onPlay(CCObject* sender)
{
    m_buttonMenu->setEnabled(false);
    FMODAudioEngine::sharedEngine()->playEffect("playSound_01.ogg");
    m_buttonsMenu->setEnabled(false);

    m_playButtonPressed = true;
    //setKeyboardEnabled(false);

    runAction(
        CCSequence::createWithTwoActions(
            CCDelayTime::create(FMODAudioEngine::sharedEngine()->fadeOutMusic(0.5f, 0)),
            CCCallFunc::create(this, callfunc_selector(LevelPopup::onloadLevel))
        )
    );
}


void LevelPopup::keyDown(cocos2d::enumKeyCodes key)
{
    if (!m_playButtonPressed)
    {
        if (key == cocos2d::enumKeyCodes::KEY_Escape) return this->onClose(nullptr);
        if (key == cocos2d::enumKeyCodes::KEY_Space) return this->onPlay(nullptr);
        return FLAlertLayer::keyDown(key);
    }
    
}

void LevelPopup::onloadLevel()
{
    m_level->m_levelString = LocalLevelManager::get()->getMainLevelString(m_levelID);

    CCDirector::get()->replaceScene(CCTransitionFade::create(0.5f, PlayLayer::scene(m_level, false, false)));
}

LevelPopup *LevelPopup::create(int levelID)
{
    auto ret = new LevelPopup();
    ret->m_levelID = levelID;

    if (ret && ret->initAnchored(340.f, 280.f, ""))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
};