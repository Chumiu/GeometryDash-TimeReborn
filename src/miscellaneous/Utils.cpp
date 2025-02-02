#include "Utils.hpp"

CCSprite* TimeReborn::longButtonSprite(const char* caption, ccColor3B color, bool disabled, float fontScale, const char* font)
{
    auto baseSprite = CCSprite::createWithSpriteFrameName("GJ_longBtn01_001.png");

    auto text = CCLabelBMFont::create(caption, font);
    text->setScale(fontScale);
    text->setAnchorPoint({ .5f, .5f });
    text->setPosition(baseSprite->getContentSize() / 2 + CCPoint(0, 2));
    
    if (disabled) 
    {
        color = ccColor3B(color.r - 100, color.g - 100, color.b - 100);
        baseSprite->setColor({ 100, 100, 100 });
    }
    text->setColor(color);

    baseSprite->addChild(text);
    
    return baseSprite;
}

void TimeReborn::addCorners(CCLayer *layer, const char *cornerSprite, float offset)
{
    //  Corners
    auto m_cornerBL = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerBL->setAnchorPoint({0, 0});
    m_cornerBL->setPosition({0 - offset, 0 - offset});
    m_cornerBL->setID("corner-bl"_spr);

    auto m_cornerBR = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerBR->setPosition({layer->getContentWidth() + offset, 0 - offset});
    m_cornerBR->setAnchorPoint({1, 0});
    m_cornerBR->setFlipX(true);
    m_cornerBR->setID("corner-br"_spr);

    auto m_cornerTL = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerTL->setAnchorPoint({0, 1});
    m_cornerTL->setPosition({0 - offset, layer->getContentHeight() + offset});
    m_cornerTL->setFlipY(true);
    m_cornerTL->setID("corner-tl"_spr);

    auto m_cornerTR = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerTR->setPosition({layer->getContentWidth() + offset, layer->getContentHeight() + offset});
    m_cornerTR->setAnchorPoint({1, 1});
    m_cornerTR->setFlipX(true);
    m_cornerTR->setFlipY(true);
    m_cornerTR->setID("corner-tr"_spr);

    layer->addChild(m_cornerBL);
    layer->addChild(m_cornerBR);
    layer->addChild(m_cornerTL);
    layer->addChild(m_cornerTR);
};

CCNode* TimeReborn::createDifficultyNode(GJGameLevel* level)
{
    auto node = CCNode::create();
    node->setContentSize({22.f, 32.5f});

    std::string difficultyName = fmt::format("diffIcon_{:02}_btn_001.png", static_cast<int>(level->m_difficulty));
    auto diffSprite = CCSprite::createWithSpriteFrameName(difficultyName.c_str());
    diffSprite->setPosition({node->getContentWidth() / 2, node->getContentHeight()});
    //diffSprite->setScale(1.25f);

    auto moonLabel = CCLabelBMFont::create(std::to_string(level->m_stars.value()).c_str(), "bigFont.fnt");
    moonLabel->limitLabelWidth(25, 0.6f, 0.1f);
    moonLabel->setPosition({0, 0});

    auto moonSprite = CCSprite::createWithSpriteFrameName(
        level->isPlatformer() ?
        "GJ_bigMoon_noShadow_001.png"
        :
        "GJ_bigStar_noShadow_001.png"
        );
        
    moonSprite->setPosition({node->getContentWidth(), 0});
    moonSprite->setScale(0.5f);

    auto coinMenu = CCMenu::create();
    coinMenu->setPosition({node->getContentWidth() / 2, -25});

    for (int i = 0; i < 3; i++)
    {
        bool isCollected = GameStatsManager::sharedState()->hasSecretCoin(fmt::format("{}_{}", level->m_levelID.value(), i + 1).c_str());

        auto coin = CCSprite::createWithSpriteFrameName(isCollected ? "GJ_coinsIcon_001.png" : "GJ_coinsIcon_gray_001.png");
        coinMenu->addChild(coin);
    }

    coinMenu->alignItemsHorizontally();
    
    node->addChild(coinMenu);
    node->addChild(diffSprite);
    node->addChild(moonSprite);
    node->addChild(moonLabel);

    
    return node;
}

CCNode *TimeReborn::createProgressBar(int percentage, bool isPractice)
{
    auto node = CCNode::create();

    int rgbValue = isPractice ? 255 : 0;
    ccColor3B color = {0, 255, (GLubyte)rgbValue};

    auto bgBar = CCSprite::create("GJ_progressBar_001.png");
    bgBar->setColor({0, 0, 0});
    bgBar->setOpacity(100);
    bgBar->setScale(0.9f);
    bgBar->setZOrder(1);

    node->addChild(bgBar);

    auto progressBar = CCSprite::create("GJ_progressBar_001.png");
    auto rectX = (progressBar->getContentWidth() * percentage) / 100;
    progressBar->setTextureRect({0, .5f, rectX, progressBar->getContentHeight()});
    progressBar->setScaleX(0.89f);
    progressBar->setScaleY(0.75f);
    progressBar->setColor(color);
    progressBar->setZOrder(2);

    progressBar->setAnchorPoint({0, 0.5});
    progressBar->setPositionX(-151.3f);

    node->addChild(progressBar);

    std::string progressNumber = std::to_string(percentage);
    auto progressLabel = CCLabelBMFont::create(fmt::format("{}%", progressNumber).c_str(), "bigFont.fnt");
    progressLabel->setPositionY(0.5f);
    progressLabel->setScale(0.325f);
    progressLabel->setZOrder(3);

    node->addChild(progressLabel);

    const char *mode = isPractice ? "Practice Mode" : "Normal Mode";
    auto label = CCLabelBMFont::create(mode, "bigFont.fnt");
    label->setPositionY(18.0f);
    label->setScale(0.45f);
    node->addChild(label);

    return node;
};


void TimeReborn::insertAssetsToMap(bool isSong, std::vector<int> IDs)
{
    for (int assetID : IDs)
    {
        if (isSong)
            MusicDownloadManager::sharedState()->m_resourceSongUnorderedSet.insert(assetID);
        else
            MusicDownloadManager::sharedState()->m_resourceSfxUnorderedSet.insert(assetID);
    }
}

std::vector<std::string> TimeReborn::defaultTexturesForIcon(int iconID)
{
    std::string modSprite = "";

    if (iconID > 4 && iconID < 21 && iconID != 13)
        modSprite = ""_spr;

    std::string part1 = fmt::format("{}player_{:02}_001.png", modSprite, iconID);
    std::string part2 = fmt::format("{}player_{:02}_2_001.png",modSprite, iconID);
    std::string part3 = fmt::format("{}player_{:02}_extra_001.png", modSprite, iconID);
    std::string partglow = fmt::format("{}player_{:02}_glow_001.png", modSprite, iconID);

    /*log::info("\nplayer frames:\n"
    "{}\n{}\n{}\n{}\n", part1, part2, part3, partglow
    );*/

    return {part1, part2, part3, partglow};
}

void TimeReborn::updateIconToDefault(SimplePlayer* player, int iconID)
{
    if (iconID < 5 || iconID > 20 || iconID == 13)
        return;

    //log::info("passed!");

    auto frames = defaultTexturesForIcon(iconID);
    auto frame1Texture = frames[0];
    auto frame2Texture = frames[1];
    auto extraTexture = frames[2];
    auto glowTexture = frames[3];

    auto frameCache = CCSpriteFrameCache::get();
    auto frameDict = frameCache->m_pSpriteFrames;

    auto firstLayer = player->m_firstLayer;
    auto secondLayer = player->m_secondLayer;
    auto extraLayer = player->m_detailSprite;
    auto glowLayer = player->m_outlineSprite;

    if (frameDict->objectForKey(frame1Texture))
    {
        firstLayer->setDisplayFrame(frameCache->spriteFrameByName(frame1Texture.c_str()));
    }

    if (frameDict->objectForKey(frame2Texture))
    {
        secondLayer->setDisplayFrame(frameCache->spriteFrameByName(frame2Texture.c_str()));
        secondLayer->setPosition(firstLayer->getContentSize() / 2);
    }

    if (frameDict->objectForKey(extraTexture))
    {
        extraLayer->setVisible(true);
        extraLayer->setDisplayFrame(frameCache->spriteFrameByName(extraTexture.c_str()));
        extraLayer->setPosition(firstLayer->getContentSize() / 2);
    }
    else
        extraLayer->setVisible(false);

    if (frameDict->objectForKey(glowTexture))
    {
        glowLayer->setDisplayFrame(frameCache->spriteFrameByName(glowTexture.c_str()));
    }
    

}

int TimeReborn::actForLevel(int levelID)
{
    int act = 1;
    while (levelID > 3)
    {
        levelID -= 3;
        act++;
    }

    return act;
    
}