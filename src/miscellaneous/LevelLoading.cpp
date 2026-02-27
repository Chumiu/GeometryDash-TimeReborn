#include "LevelLoading.hpp"

LevelLoading::~LevelLoading() {
    CCTouchDispatcher::get()
        ->unregisterForcePrio(this);
}

void LevelLoading::registerWithTouchDispatcher() {
    CCTouchDispatcher::get()
        ->addTargetedDelegate(this, -500, true);
}

bool LevelLoading::init() {
    if(!CCLayerColor::initWithColor({0, 0, 0, 255}))
        return false;

    auto dir = CCDirector::get();
    auto winSize = dir->getWinSize();

    CCTouchDispatcher::get()
        ->registerForcePrio(this, 2);


    // ui elements
    // i added this for indicator
    // Loading circle (your existing indicator)
    auto loading = LoadingCircle::create();
    loading->setPositionY(loading->getPositionY() + 10);
    loading->show();
    
    m_loadingLabel = CCLabelBMFont::create(
        "LOADING.",
        "bigFont.fnt"
    );

    m_loadingLabel->setScale(.5);
    m_loadingLabel->setPosition({
        winSize.width / 2,
        winSize.height / 2 - 40
    });

    addChild(loading);
    addChild(m_loadingLabel);
    schedule(schedule_selector(LevelLoading::updateLoadingText), .4);

    setTouchEnabled(true);

    return true;
}

void LevelLoading::updateLoadingText(float dt) {
    m_dotCount++;

    if(m_dotCount > 3)
        m_dotCount = 1;

    std::string text = "LOADING";

    for(int i = 0; i < m_dotCount; i++)
        text += ".";

    m_loadingLabel->setString(text.c_str());
}

void LevelLoading::keyBackClicked() { }

void LevelLoading::show() {
    CCDirector::get()
        ->getRunningScene()
            ->addChild(
                LevelLoading::create(),
                9999
            );

    return;
}