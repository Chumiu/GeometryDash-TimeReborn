#pragma once
using namespace geode::prelude;

class TimeRebornActLayer : public CCLayer
{
    CCSize m_winSize;
    int m_currentPage;
    int m_currentAct;   
    CCSprite* m_background;
    CCSprite* m_islandSprite;
    CCSprite* m_titleSprite;
    CCMenuItemSprite* m_islandButton;
protected:
    bool init(int);
    void keyBackClicked();
    void onLevel(CCObject*);
    void onBack(CCObject*);
    void updatePage(int);
    void onNextPage(CCObject*);
    void onBackPage(CCObject*);
    int backgroundForPage(int);
    ccColor3B colorForPage(int);
    float scaleForIsland(int);
public:
    static TimeRebornActLayer* create(int, int);
    static CCScene* scene(int, int);
};

