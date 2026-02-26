#include "PromoPopup.hpp"

bool PromoPopup::init()
{
    if(!Popup::init(340, 280, "GJ_square01.png", {0, 0, 80, 80}))
        return false;
    
    setTitle(" ");

    m_bgSprite->removeFromParentAndCleanup(true);

    auto promoBG = CCSprite::create("GJ_popupOD.png"_spr);

    m_size = promoBG->getContentSize();

    m_mainLayer->setContentSize(m_size);
    //m_mainLayer->setPosition(m_size / 2);
    promoBG->setPosition(m_size / 2);

    m_buttonMenu->setContentSize(m_size);
    m_buttonMenu->setPosition(m_size / 2);

    m_closeBtn->setPosition(15, m_size.height - 15);

    m_mainLayer->addChild(promoBG, -10);
    return true;
}

PromoPopup *PromoPopup::create()
{
    auto ret = new PromoPopup();

    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
};