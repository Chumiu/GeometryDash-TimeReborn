#include <Geode/Geode.hpp>
#include <Geode/modify/LevelTools.hpp>

using namespace geode::prelude;

class $modify(OdysseyLevelTools, LevelTools)
{
	static bool verifyLevelIntegrity(std::string verifyString, int levelID)
	{
		return true;
	}

	$override static gd::string getAudioTitle(int levelID)
	{
		switch (levelID)
		{
		case 1:
			return "The Ancient Ruins";
		case 2:
			return "The Lush Forest";
		case 3:
			return "Skybound";
		case 4:
			return "Shapeshifter";
		case 5:
			return "The Snow Peaks";
		case 6:
			return "Snowdown";
		case 7:
			return "Daydreamer";
		case 8:
			return "Skystrike";
		case 9:
			return "The Star Realm";
		default:
			return LevelTools::getAudioTitle(levelID);
		}
	}

	$override static gd::string getAudioFileName(int levelID)
	{
		switch (levelID)
		{
		case 101:
			return "10005797.ogg"_spr;
		case 102:
			return "10004600.ogg"_spr;
		case 103:
			return "Skybound.mp3"_spr;
		case 104:
			return "Shapeshifter.mp3"_spr;
		case 106:
			return "Snowdown.mp3"_spr;
		case 107:
			return "Daydreamer.mp3"_spr;
		case 108:
			return "Skystrike.mp3"_spr;
		default:
			return "-";
		}
	}

	$override static int artistForAudio(int p0)
	{
		switch (p0)
		{
		case 1:
			return 12;
		case 2:
			return 13;
		case 3:
			return 14;
		case 4:
			return 15;
		case 5:
			return 16;
		case 6:
			return 7;
		case 7:
			return 17;
		case 8:
			return 11;
		case 9:
			return 18;

		default:
			return LevelTools::artistForAudio(p0);
		}
	}

	static gd::string nameForArtist(int p0)
	{
		switch (p0)
		{
		case 12:
			return "Blackmid";
		case 13:
			return "Travis Rise";
		case 14:
			return "Lockyn";
		case 15:
			return "AeronMusic";
		case 16:
			return "Andrew Goodwin";
		case 17:
			return "MegaNeko";
		case 18:
			return "Audible Dread";
		default:
			return LevelTools::nameForArtist(p0);
		}
	}

	$override static gd::string urlForAudio(int p0) {

		switch (p0)
		{
		case 1:
			return "https://www.youtube.com/channel/UClwAGafGeTwFd7AjEjLflcA";
		case 2:
			return "https://www.youtube.com/channel/UCalcJu9wSS10cw6dAvEZxYw";
		case 3:
			return "https://www.newgrounds.com/audio/listen/655358";
		case 4:
			return "https://www.newgrounds.com/audio/listen/671476";
		case 5:
			return "https://www.youtube.com/channel/UC_JLKKGU4kSqt5qn0_V0uZQ";
		case 6:
			return "https://www.youtube.com/watch?v=OCo2N4Tvns8";
		case 7:
			return "https://www.newgrounds.com/audio/listen/966998";
		case 8:
			return "https://www.newgrounds.com/audio/listen/700355";
		case 9:
			return "https://www.youtube.com/channel/UCc9RWpppO7qR_cG5Ssij-lw";
		default:
			return  LevelTools::urlForAudio(p0);
		}
	}

	$override static GJGameLevel *getLevel(int levelID, bool loaded)
	{
		GJGameLevel *level = GJGameLevel::create();
		switch (levelID)
		{
		case 1:
			level->m_levelName = getAudioTitle(1);
			level->m_audioTrack = 101;
			level->m_stars = 1;
			level->m_difficulty = GJDifficulty::Easy;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_coins = 3;
			level->m_levelLength = 5;
			break;

		case 2:
			level->m_levelName = getAudioTitle(2);
			level->m_audioTrack = 102;
			level->m_stars = 2;
			level->m_difficulty = GJDifficulty::Normal;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_coins = 3;
			level->m_levelLength = 5;
			break;

		case 3:
			level->m_levelName = getAudioTitle(3);
			level->m_audioTrack = 103;
			level->m_stars = 3;
			level->m_difficulty = GJDifficulty::Normal;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_coins = 3;
			break;

		case 4:
			level->m_levelName = getAudioTitle(4);
			level->m_audioTrack = 104;
			level->m_stars = 4;
			level->m_difficulty = GJDifficulty::Hard;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_coins = 3;
			break;

		case 5:
			level->m_levelName = getAudioTitle(5);
			level->m_audioTrack = 105;
			level->m_stars = 2;
			level->m_difficulty = GJDifficulty::Normal;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_coins = 3;
			level->m_levelLength = 5;
			break;

		case 6:
			level->m_levelName = getAudioTitle(6);
			level->m_audioTrack = 106;
			level->m_stars = 5;
			level->m_difficulty = GJDifficulty::Harder;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_coins = 3;

			break;

		case 7:
			level->m_levelName = getAudioTitle(7);
			level->m_audioTrack = 107;
			level->m_stars = 6;
			level->m_difficulty = GJDifficulty::Harder;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_coins = 3;
			break;

		case 8:
			level->m_levelName = getAudioTitle(8);
			level->m_audioTrack = 108;
			level->m_stars = 8;
			level->m_difficulty = GJDifficulty::Insane;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_coins = 3;
			break;

		case 9:
			level->m_levelName = getAudioTitle(9);
			level->m_audioTrack = 109;
			level->m_stars = 7;
			level->m_difficulty = GJDifficulty::Harder;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_coins = 3;
			level->m_levelLength = 5;
			break;
		}

		if (!loaded)
			level->m_levelString = LocalLevelManager::sharedState()->getMainLevelString(levelID);

		level->m_levelID = levelID;
		level->m_levelType = GJLevelType::Local;

		return level;
	};
};