#pragma once
#include "Utils.hpp"

using namespace geode::prelude;

class CreditsPopup : public geode::Popup<std::string const &>
{
protected:
    int m_currentPage = 0;
    int m_pages = 0;
    std::vector<UserInfo> m_userInfoArray;
    CCMenu* m_usersContainer;
    CCLabelBMFont* m_pageLabel;

    bool setup(std::string const &) override;
    void updateLayer();
    void onUserProfile(CCObject*);
    void onNextPage(CCObject*);
    void onBackPage(CCObject*);
    void addUser(const char*, std::string, int, int, int col2, int col3 = -1, int accountID = 71);

public:
    static CreditsPopup* create();

};