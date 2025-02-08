#pragma once
using namespace geode::prelude;

class LevelPopup : public geode::Popup<std::string const &>
{
    int m_levelID;
    GJGameLevel* m_level;
    CCMenu* m_buttonsMenu;
    bool m_playButtonPressed;
private:
    bool setup(std::string const &) override;
    void onPlay(CCObject*);
    void onloadLevel();
    void onSettings(CCObject*);
    void onSong(CCObject*);
    void keyDown(cocos2d::enumKeyCodes key) override;
public:
    static LevelPopup* create(int);

};

