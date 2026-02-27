#pragma once
using namespace geode::prelude;

class LevelLoading : public CCLayerColor {
private:
    CCLabelBMFont* m_loadingLabel = nullptr;
    int m_dotCount = 0;

public:
    ~LevelLoading();
    virtual bool init();
    virtual void registerWithTouchDispatcher();
    virtual void keyBackClicked();
    
    void show();
    void updateLoadingText(float dt);
        
    CREATE_FUNC(LevelLoading);
};