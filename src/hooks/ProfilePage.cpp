#include <Geode/Geode.hpp>
#include <Geode/modify/ProfilePage.hpp>

using namespace geode::prelude;

class $modify(GDOProfilePage, ProfilePage)
{
    void loadPageFromUserInfo(GJUserScore *p0)
    {
        ProfilePage::loadPageFromUserInfo(p0);

        /*
        log::info(
            "\nData for {}\n"
            "Icon ID: {}\n"
            "Col 1: {}\n"
            "Col 2: {}\n"
            "Col 3: {}\n"
            "Account ID:{}\n",
            p0->m_userName, p0->m_playerCube, p0->m_color1, p0->m_color2, p0->m_color3, p0->m_accountID
        );

        clipboard::write(fmt::format(
            "\"{}\", "
            "\"desc\", "
            "{}, "
            "{}, "
            "{}, "
            "{}, "
            "{}",
            p0->m_userName, p0->m_playerCube, p0->m_color1, p0->m_color2, p0->m_color3, p0->m_accountID
            )
        );
        */

        //  Esconde los hints dado a que no se pueden acceder estos lugares
        if (auto myLevelsHint = m_mainLayer->getChildByID("my-levels-hint"))
            myLevelsHint->setVisible(false);

        if (auto myListsHint = m_mainLayer->getChildByID("my-lists-hint"))
            myListsHint->setVisible(false);

        if (auto commentHistoryBtn = m_mainLayer->getChildByIDRecursive("comment-history-button"))
            commentHistoryBtn->setVisible(false);

        //  Esconde los botones que permita el Jugador acceder al resto del juego
        if (auto menu = m_mainLayer->getChildByID("main-menu"))
        {
            if (auto levelsButton = menu->getChildByID("my-levels-button"))
                levelsButton->setVisible(false);
            if (auto listsButton = menu->getChildByID("my-lists-button"))
                listsButton->setVisible(false);
        }


        
    }
};