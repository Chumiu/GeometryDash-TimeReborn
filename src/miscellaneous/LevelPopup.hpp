#pragma once
using namespace geode::prelude;

class LevelPopup : public geode::Popup<std::string const &>
{
    int m_levelID;
    GJGameLevel* m_level;
    CCMenu* m_buttonsMenu;
private:
    bool setup(std::string const &) override;
    void onPlay(CCObject*);
    void onSettings(CCObject*);
    void onSong(CCObject*);
public:
    static LevelPopup* create(int);

};

