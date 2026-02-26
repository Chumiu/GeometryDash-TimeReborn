#pragma once
using namespace geode::prelude;

class SelectActPopup : public geode::Popup
{
    bool m_saveFileAlert;
protected:
    bool init();
    void onSelectAct(CCObject*);
    bool isActCompleted(int);
public:
    static SelectActPopup* create();
};