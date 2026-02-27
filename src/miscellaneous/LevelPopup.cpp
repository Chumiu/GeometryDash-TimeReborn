#pragma once
#include "LevelPopup.hpp"
#include "LevelLoading.hpp"
#include "Utils.hpp"

bool LevelPopup::init()
{
    if(!Popup::init(340, 280, "GJ_square01.png", {0, 0, 80, 80}))
        return false;

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

    if (!m_level->isPlatformer()) {
        auto normalProgress = TimeReborn::createProgressBar(m_level->m_normalPercent, false);
        normalProgress->setPosition({contentSize.width / 2, contentSize.height / 2 - 45.0f});
        m_mainLayer->addChild(normalProgress);

        auto practiceProgress = TimeReborn::createProgressBar(m_level->m_practicePercent, true);
        practiceProgress->setPosition({contentSize.width / 2, normalProgress->getPositionY() - 40.0f});
        m_mainLayer->addChild(practiceProgress);
    }

    // timer for platformer mode
    // instead of best time
    if (m_level->isPlatformer()) {
        std::string timeText;

        if  (m_level->m_bestTime <= 0) {
            timeText = "No Best Time";
        } else {
            int totalMs = m_level->m_bestTime;

            int hours = totalMs / 3600000;
            int minutes = (totalMs / 60000) % 60;
            int seconds = (totalMs / 1000) % 60;
            int milliseconds = totalMs % 1000;

            if (hours > 0) {
                timeText = CCString::createWithFormat(
                    "Best Time: %02d:%02d:%02d.%03d",
                    hours, minutes, seconds, milliseconds
                )->getCString();
            } else {
                timeText = CCString::createWithFormat(
                    "Best Time: %02d:%02d.%03d",
                    minutes, seconds, milliseconds
                )->getCString();
            }
        }

        auto time = CCLabelBMFont::create(
            timeText.c_str(),
            "goldFont.fnt"
        );

        time->setScale(.7);
        time->setPosition({
            contentSize.width / 2,
            contentSize.height / 2 - 60
        });

        m_mainLayer->addChild(time);
    }



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
    // sorry chumiu
    // but I really need to do
    // this :(
    // - ItzZyann

    auto layer = GameLevelOptionsLayer::create(m_level);
        
    CCDirector::get()
        ->getRunningScene()
            ->addChild(layer, 9999);

    // this fixes the bug
    // when opening the options menu
    // in secret level
};

void LevelPopup::onPlay(CCObject* sender)
{
    FMODAudioEngine::sharedEngine()->playEffect("playSound_01.ogg");
    FMODAudioEngine::sharedEngine()->stopAllMusic(true);

    m_buttonMenu->setEnabled(false);
    m_buttonsMenu->setEnabled(false);

    m_playButtonPressed = true;
    setKeypadEnabled(false);

    // display this
    LevelLoading::create()
        ->show();

    runAction(
        CCSequence::createWithTwoActions(
            CCDelayTime::create(5),
            CCCallFunc::create(this, callfunc_selector(LevelPopup::onloadLevel))
        )
    );
}


void LevelPopup::keyDown(cocos2d::enumKeyCodes key, double p1)
{
    if (!m_playButtonPressed)
    {
        if (key == cocos2d::enumKeyCodes::KEY_Escape) return this->onClose(nullptr);
        if (key == cocos2d::enumKeyCodes::KEY_Space) return this->onPlay(nullptr);
        return FLAlertLayer::keyDown(key, p1);
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

    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
};