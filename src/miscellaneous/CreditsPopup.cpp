#pragma once
#include "CreditsPopup.hpp"
#include "Utils.hpp"


bool CreditsPopup::setup(std::string const &title)
{
    setTitle("Credits", "bigFont.fnt");

    m_usersContainer = CCMenu::create();
    m_usersContainer->setPosition(0, 0);
    m_mainLayer->addChild(m_usersContainer);

    addUser("RobTop", "Geometry Dash\nDeveloper", 275, 6, 3, 1, 71);
    addUser("Chumiu", "Developer", 457, 94, 52, 12, 25521533);
    addUser("GenaMorphosis", "Level 1/4/5/6/8/9\nIsland Sprites\nLevel Layouts", 467, 6, 74, 72, 10026833);
    addUser("Dum0gus", "Island Sprites\nLevel 2/8", 107, 12, 12, 11, 24249778);
    addUser("Seannnn", "Level 3/8", 114, 77, 70, 8, 16494507);
    addUser("MXSTEY", "Level 4\nPolishing levels.", 275, 89, 48, 63, 30685975);
    addUser("AzCl", "Level 7", 35, 77, 2, 72, 11812786);
    addUser("Mee8", "Level 8", 107, 29, 11, 9, 14135795);
    addUser("PotatoTatoe", "Icons 8/9/10/12/14\n15/17/18/19/20/12", 408, 17, 12, 12, 13268135);
    addUser("cyanflower", "Icons 5/6/7/8/11/16\nBall, UFO & Jetpack 2", 2, 12, 3, 3, 21113321);
    addUser("zerextt", "Level Logos\nLevel 8", 51, 94, 12, 9, 24944488);
    addUser("TheNewForest", "Level 7 Layout", 59, 18, 1, 12, 20809503);
    addUser("JustADudeJX3", "Level 8 Layout", 160, 4, 11, 1, 25964272);
    addUser("ExMarker", "Level 8", 420, 0, 3, 11, 17414683);
    addUser("DanKy99", "Boss design for\n\"The Star Realm\"", 11, 9, 11, 3, 14178231);
    addUser("Capeling", "Additional Modding\nHelp", 12, 11, 12, 12, 18226543);

    int count = m_userInfoArray.size();

    while (count > 0)
    {
        //log::info("{}\n", count);
        count -= 6;
        m_pages++;
    }

    auto backArrow = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    auto nextArrow = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    nextArrow->setFlipX(true);

    auto backButton = CCMenuItemSpriteExtra::create(backArrow, this, menu_selector(CreditsPopup::onBackPage));
    backButton->setPosition({-25, m_size.height / 2});

    auto nextButton = CCMenuItemSpriteExtra::create(nextArrow, this, menu_selector(CreditsPopup::onNextPage));
    nextButton->setPosition({m_size.width + 25, m_size.height / 2});

    m_buttonMenu->addChild(backButton);
    m_buttonMenu->addChild(nextButton);

    m_pageLabel = CCLabelBMFont::create(" ", "goldFont.fnt");
    m_pageLabel->setAnchorPoint({1, .5f});

    m_pageLabel->setPosition(CCDirector::get()->getWinSize() - ccp(15, 15));

    addChild(m_pageLabel);

    updateLayer();

    return true;
}

void CreditsPopup::addUser(const char* userName, std::string description, int iconID, int col1, int col2, int col3, int accountID)
{
    if (col3 == -1)
        col3 = col2;
    
    m_userInfoArray.push_back({userName, description, accountID, iconID, col1, col2, col3});
}

void CreditsPopup::onUserProfile(CCObject* sender)
{
    ProfilePage::create(sender->getTag(), false)->show();
}

void CreditsPopup::onNextPage(CCObject*)
{
    m_currentPage++;
    updateLayer();
}

void CreditsPopup::onBackPage(CCObject*)
{
    m_currentPage--;
    updateLayer();
}

void CreditsPopup::updateLayer()
{
    auto gm = GameManager::get();

    if (m_currentPage > m_pages - 1)
        m_currentPage = 0;

    if (m_currentPage < 0)
        m_currentPage = m_pages - 1;

    m_usersContainer->removeAllChildrenWithCleanup(true);

    int padX = 0, padY = 0;
    int page = m_currentPage + 1;

    m_pageLabel->setString(fmt::format("Page {} of {}", page, m_pages).c_str());
    m_pageLabel->setScale(.7f);

    CCPoint labelPosition = {m_size.width / 2 - 95, m_size.height - 55};
    CCPoint iconPosition =  labelPosition - ccp(0, 30);
    CCPoint desclPosition = labelPosition - ccp(0, 55);

    for (int i = page * 6 - 6; i < 6 * page; i++)
    {
        if (i + 1 > m_userInfoArray.size())
            break;

        auto user = m_userInfoArray[i];
        CCPoint padding =  ccp(95 * padX, - 100 * padY);
        
        auto label = CCLabelBMFont::create(user.userName, "goldFont.fnt");
        label->limitLabelWidth(90, .7f, .1f);

        auto labelButton = CCMenuItemSpriteExtra::create(label, this, menu_selector(CreditsPopup::onUserProfile));
        labelButton->setTag(user.accountID);
        labelButton->setPosition(labelPosition + padding);
        m_usersContainer->addChild(labelButton);

        // icon
        auto icon = SimplePlayer::create(user.iconID);
        icon->setColors(gm->colorForIdx(user.col1), gm->colorForIdx(user.col2));
        icon->setGlowOutline(gm->colorForIdx(user.col3));
        icon->enableCustomGlowColor(gm->colorForIdx(user.col3));
        icon->setPosition(iconPosition + padding);
        m_usersContainer->addChild(icon);

        TimeReborn::updateIconToDefault(icon, user.iconID);

        //description
        auto description = CCLabelBMFont::create(user.description.c_str(), "chatFont.fnt");
        description->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
        description->setAnchorPoint({.5f, 1});
        description->limitLabelWidth(90, .7f, .1f);
        description->setPosition(desclPosition + padding);
        m_usersContainer->addChild(description);

        padX++;

        if ((i + 1) % 3 == 0)
        {
            padX = 0;
            padY = 1;
        }


    }
    
}

CreditsPopup *CreditsPopup::create()
{
    auto ret = new CreditsPopup();

    if (ret && ret->initAnchored(300.f, 250.f, ""))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
};