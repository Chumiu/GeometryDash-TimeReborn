#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include "../miscellaneous/Utils.hpp"

using namespace geode::prelude;

class $modify(LoadingLayerExt, LoadingLayer)
{
    bool init(bool fromRefresh)
    {
        if (!LoadingLayer::init(fromRefresh))
            return false;


        auto SFC = CCSpriteFrameCache::get();
        auto searchPathRoot = dirs::getModRuntimeDir() / Mod::get()->getID() / "resources";

        CCFileUtils::sharedFileUtils()->addSearchPath(searchPathRoot.string().c_str());
        SFC->addSpriteFramesWithFile("GD_timeRebornSheet.plist"_spr);

        SFC->addSpriteFramesWithFile("iconSheet.plist"_spr);

        LoadingLayerExt::loadAudioAssets();

        auto mainTitle = static_cast<CCSprite *>(this->getChildByID("gd-logo"));
        if (mainTitle)
        {
          	auto smallTitle = CCSprite::createWithSpriteFrameName("GJ_tr_001.png"_spr);
			smallTitle->setScale(.8f);
			smallTitle->setPosition({ mainTitle->getPositionX() + 125, mainTitle->getPositionY() - 40 });

			addChild(smallTitle);
        }

        if (!GameManager::get()->getUGV("30"))
            GameManager::get()->setUGV("30", true);

        return true;
    }

    void loadAudioAssets()
    {
         MusicDownloadManager::sharedState()->m_resourceSongUnorderedSet.clear();
         MusicDownloadManager::sharedState()->m_resourceSfxUnorderedSet.clear();

        TimeReborn::insertAssetsToMap(true, {987228, 10000033, 10001132, 10001605, 10003633, 10003705, 10004124, 10004164, 10004600, 10004602, 10005238, 10005797, 
        10005985, 10005986, 10005987, 10005990, 10006555, 10006659, 10006733, 10011543});

        TimeReborn::insertAssetsToMap(false, {468, 499, 502, 503, 504, 505, 537, 566, 599, 710, 717, 886, 994, 1024, 1048, 1072, 1074, 1315, 1318, 1319, 1582, 1583,
         1739, 1747, 1748, 1751, 2033, 2037, 2235, 2237, 2238, 2265, 2267, 2268, 2269, 2270, 2271, 2272, 2274, 2297, 2298, 2367, 2374, 2701, 2852, 2867, 2978, 3074,
          3116, 3125, 3200, 3203, 3208, 3400, 3447, 3894, 4024, 4025, 4026, 4273, 4290, 4328, 4337, 4338, 4339, 4394, 4397, 4400, 4404, 4452, 5222, 5498, 5551, 6244,
           6248, 6269, 6271, 6290, 6621, 6882, 7243, 7247, 7455, 7456, 7581, 7604, 7605, 7718, 7719, 7720, 7721, 7885, 7896, 7934, 7944, 9280, 9463, 9465, 9483,
           9837, 10022, 10023, 10114, 10643, 10775, 11262, 11425, 11509, 11510, 13143, 13161, 13213, 13851, 13855, 16622, 16623, 16665, 16666, 16667, 16668, 16669,
           16673, 16674, 16674, 16687, 16688, 16689, 16694, 16695, 16696, 16697, 16698, 16699, 16700, 17406, 17407, 17419, 17617, 17628, 18267, 18268, 19499, 19648,
           19654, 19698, 22869, 22879, 23305});
    }
};