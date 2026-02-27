#pragma once
using namespace geode::prelude;

class LevelPopup : public geode::Popup
{
    int m_levelID;
    GJGameLevel* m_level;
    CCMenu* m_buttonsMenu;
    bool m_playButtonPressed;
private:
    bool init();
    void onPlay(CCObject*);
    void onloadLevel();
    void onSettings(CCObject*);
    void onSong(CCObject*);
    void keyDown(cocos2d::enumKeyCodes key, double p1) override;
    void keyBackClicked() override;
public:
    static LevelPopup* create(int);

};

