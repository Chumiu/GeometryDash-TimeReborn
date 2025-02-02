#pragma once
using namespace geode::prelude;

class PromoPopup : public geode::Popup<std::string const &>
{
protected:
    
    bool setup(std::string const &) override;
    void promoClicked(CCObject*);
    bool ccTouchBegan(cocos2d::CCTouch* p0, cocos2d::CCEvent* p1)
    {
        CCApplication::get()->openURL("https://gamejolt.com/games/geometrydashodyssey/907873");
        return CCLayer::ccTouchBegan(p0, p1);
    }
public:

    static PromoPopup* create();

};