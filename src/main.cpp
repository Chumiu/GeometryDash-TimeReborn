#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/GManager.hpp>
#include <Geode/modify/OptionsLayer.hpp>
#include <Geode/modify/LocalLevelManager.hpp>
#include <Geode/modify/MusicDownloadManager.hpp>
#include <Geode/modify/SongsLayer.hpp>
#include <Geode/modify/CCSprite.hpp>
#include "miscellaneous/SelectActPopup.hpp"
#include "layers/TimeRebornActLayer.hpp"
#include "miscellaneous/CreditsPopup.hpp"
#include "miscellaneous/PromoPopup.hpp"
#include "miscellaneous/Utils.hpp"


using namespace geode::prelude;

class $modify(GManager)
{
	void setup()
	{
		auto compare = std::string(m_fileName);
		compare.insert(std::string_view(compare).find(".dat"), "TimeReborn");
		m_fileName = compare;
		GManager::setup();
	}
};


class $modify(MenuLayerExt, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		auto size = CCDirector::get()->getWinSize();

		auto mainTitle = getChildByID("main-title");

		//add the 'Time Reborn' title
		if (mainTitle && !Loader::get()->isModLoaded("ninxout.redash"))
		{
			
			auto smallTitle = CCSprite::createWithSpriteFrameName("GJ_tr_001.png"_spr);
			smallTitle->setScale(.8f);
			smallTitle->setPosition({ mainTitle->getPositionX() + 125, mainTitle->getPositionY() - 40 });

			addChild(smallTitle);
		}

		//hides the original 'more games' menu
		if (auto moreGamesMenu = getChildByID("more-games-menu"))
			moreGamesMenu->setVisible(false);

		auto mainMenu = getChildByID("main-menu");

		//new 'more games' button
		if (auto editorButton =  static_cast<CCMenuItemSpriteExtra*>(mainMenu->getChildByID("editor-button")))
			editorButton->setNormalImage(CCSprite::createWithSpriteFrameName("GJ_moreGamesBtn_001.png"));

  		auto rightMenu = static_cast<CCMenu*>(this->getChildByID("right-side-menu"));

		//new texture for the daily chests button
		auto creditSprite = CCSprite::createWithSpriteFrameName("communityCreditsBtn_001.png");

        if (auto dailyCButton = static_cast<CCMenuItemSpriteExtra *>(rightMenu->getChildByID("daily-chest-button")))
            dailyCButton->setNormalImage(creditSprite);

		rightMenu->updateLayout();

		//hides the editor text at the beginning of the game
		if (auto levelEditorHint = static_cast<CCSprite *>(this->getChildByID("level-editor-hint")))
           levelEditorHint->setVisible(false);

		if (!Mod::get()->getSavedValue<bool>("saveAlertClicked"))
		{
			runAction(CCCallFunc::create(this, callfunc_selector(MenuLayerExt::showSaveAlert)));
			Mod::get()->setSavedValue<bool>("saveAlertClicked", true);
		}

		// Redash fixes

		if (Loader::get()->isModLoaded("ninxout.redash"))
		{
			std::string redashId = "ninxout.redash/";

			if (auto remenu = getChildByID("ninxout.redash/redash-menu"))
			{
				if (auto dailiesMenu = remenu->getChildByID("ninxout.redash/dailies-menu"))
				{
					auto mainLevelBtn = static_cast<CCMenuItemSpriteExtra*>(dailiesMenu->getChildByID("main-levels-button"));

					mainLevelBtn->m_pfnSelector = menu_selector(MenuLayer::onPlay);

					//auto buttonNode = static_cast<CCNode*>(getChildren()->objectAtIndex(1));

					//auto 
				}
			}
		}
			

		return true;
}

	void showSaveAlert()
	{

		FLAlertLayer::create(
			"Savefile Notice", 
			"<co>Time Reborn</c> stores the data in\na separate <cy>savefile</c>. Your data\nwill be <cg>restored</c> when you\n<cb>turn off</c> the Mod.", 
			"OK")->show();
	}

	void onCreator(CCObject* sender) 
	{
		PromoPopup::create()->show();
		//MenuLayer::onCreator(sender);
	}

	void onPlay(CCObject* sender) 
	{
		SelectActPopup::create()->show();
	}

	void onDaily(CCObject* sender) 
	{
		CreditsPopup::create()->show();
	}

};


class $modify(OptionsLayer)
{
	void onAccount(CCObject* sender) {
		
		FLAlertLayer::create("Disabled :(", "This button is disabled on this fangame", "OK")->show();
	}

	void customSetup()
	{
		OptionsLayer::customSetup();

		if (auto button = this->getChildByIDRecursive("vault-button"))
			button->setVisible(false);
	}
};

class $modify(LocalLevelManager)
{
	$override gd::string getMainLevelString(int id)
	{
		// auto file = CCString::createWithFormat("level-%i.txt"_spr, id);
		auto file = CCString::createWithFormat("%i.txt"_spr, id);

		if (file == nullptr)
			return "";

		auto content = CCString::createWithContentsOfFile(file->getCString());
		if (content == nullptr)
			return "";

		return gd::string(content->getCString());
		return LocalLevelManager::getMainLevelString(id);
	}
};


class $modify(MusicDownloadManager)
{
	gd::string pathForSFXFolder(int sfxID)
	{
		std::string path = MusicDownloadManager::pathForSFXFolder(sfxID);

		if (path == "sfx/")
			path = "/"_spr;

		return path;
	}

	gd::string pathForSongFolder(int songID)
	{
		std::string path = MusicDownloadManager::pathForSongFolder(songID);

		if (path == "songs/")
			path = "/"_spr;

		return path;
	}
};

class $modify(SongsLayer)
{
	void customSetup()
	{
		CCArray *songObjectArray = CCArray::create();
		songObjectArray->addObject(SongObject::create(1));
		songObjectArray->addObject(SongObject::create(2));
		songObjectArray->addObject(SongObject::create(3));
		songObjectArray->addObject(SongObject::create(4));
		songObjectArray->addObject(SongObject::create(5));
		songObjectArray->addObject(SongObject::create(6));
		songObjectArray->addObject(SongObject::create(7));
		songObjectArray->addObject(SongObject::create(8));
		songObjectArray->addObject(SongObject::create(9));
		songObjectArray->addObject(SongObject::create(-1));

		m_listLayer->m_listView = CustomListView::create(songObjectArray, nullptr, 220.0, 356.0, 0, BoomListType::Song, 0.0);
		m_listLayer->addChild(m_listLayer->m_listView);
	}
};