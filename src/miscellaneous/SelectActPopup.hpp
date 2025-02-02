#pragma once
using namespace geode::prelude;

class SelectActPopup : public geode::Popup<std::string const &>
{
    bool m_saveFileAlert;
protected:
    bool setup(std::string const &) override;
    void onSelectAct(CCObject*);
    bool isActCompleted(int);
public:
    static SelectActPopup* create();
};