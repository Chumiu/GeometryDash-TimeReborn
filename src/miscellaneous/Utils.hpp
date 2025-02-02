#pragma once
using namespace geode::prelude;

struct UserInfo 
{
    const char* userName;
    std::string description;
    int accountID;
    int iconID;
    int col1;
    int col2;
    int col3;
};

namespace TimeReborn
{

    CCSprite* longButtonSprite(const char*, ccColor3B, bool, float fontScale =  1.f, const char* font = "bigFont.fnt");
    void addCorners(CCLayer*, const char*, float);
    CCNode* createDifficultyNode(GJGameLevel*);
    CCNode* createProgressBar(int, bool);
    void insertAssetsToMap(bool, std::vector<int>);
    std::vector<std::string> defaultTexturesForIcon(int);
    void updateIconToDefault(SimplePlayer*, int);
    int actForLevel(int);

}