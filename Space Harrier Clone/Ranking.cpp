#include "Ranking.h"

#include <assert.h>
#include <algorithm>
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/TextRenderer.h"
#include "Engine/Sprite.h"
#include "Engine/API.h"
#include "EngineExt/ClippableTextRenderer.h"
#include "gameData.h"
#include "Messenger.h"
#include "MessengerEventType.h"
#include "ScoreInfo.h"


void Ranking::onDestroy()
{
	Audio::unloadMusic(m_musicNameEntry);
}


void Ranking::awake()
{
	m_musicNameEntry = Audio::loadMusic("assets/audio/bgm/Winners Song (Name Entry).wav");
	assert(m_musicNameEntry);

	m_rankingListEntryDuration = 1733;
	m_yClipTop = 56;
	m_yClipBottom = 160;

	m_characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.<>";
	m_selectedName = "";

	// Ensure the scoreInfos vector is sorted descendingly and has exactly 10 elements
	std::sort(scoreInfos.begin(), scoreInfos.end(), [](ScoreInfo info1, ScoreInfo info2) -> bool { return info1.score > info2.score; });
	assert(scoreInfos.size() == 10);

	m_rankingGO = GameObject::createNew();
	assert(m_rankingGO);
	m_rankingGO->transform->setParent(gameObject()->transform, false);

	m_isActive = false;
	m_rankingGO->setActive(false);

	// PERMANENT

	// Table_header
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_rankingGO->transform);
		go->transform->setWorldPosition(Vector2((float)SCREEN_WIDTH - 96, (float)SCREEN_HEIGHT - 24));
		auto tableHeaderLabel = go->addComponent<TextRenderer>();
		assert(tableHeaderLabel);

		tableHeaderLabel->setRenderLayer("UI");
		tableHeaderLabel->setZIndex(1);

		bool success = tableHeaderLabel->loadFont(getFont("smallGreen"));
		assert(success);
		tableHeaderLabel->setAllPivots(Vector2(1, 1));
		tableHeaderLabel->setText("SCORE  NAME");
	}

	// Lives_label
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_rankingGO->transform, false);
		go->transform->setLocalPosition(Vector2(16, 16));

		auto livesLabel = go->addComponent<TextRenderer>();
		assert(livesLabel);

		livesLabel->setRenderLayer("UI");
		livesLabel->setZIndex(1);

		bool success = livesLabel->loadFont(getFont("smallGray"));
		assert(success);
		livesLabel->setAllPivots(Vector2(0, 0));
		livesLabel->setText("PLAYER   0");
	}

	// Copyright_symbol
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_rankingGO->transform, false);
		go->transform->setLocalPosition(Vector2((float)SCREEN_WIDTH - 96, 16));

		auto sprite = go->addComponent<Sprite>();
		assert(sprite);

		sprite->setRenderLayer("UI");
		sprite->setZIndex(1);

		bool success = sprite->loadImage("assets/sprites/UI.png");
		assert(success);
		sprite->setAllPivots(Vector2(1, 0));
		sprite->setClipRect(SDL_Rect{ 96, 104, 8, 8 });
	}

	// Sega_label
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_rankingGO->transform, false);
		go->transform->setLocalPosition(Vector2((float)SCREEN_WIDTH - 16, 16));

		auto segaLabel = go->addComponent<TextRenderer>();
		assert(segaLabel);

		segaLabel->setRenderLayer("UI");
		segaLabel->setZIndex(1);

		bool success = segaLabel->loadFont(getFont("smallGray"));
		assert(success);
		segaLabel->setAllPivots(Vector2(1, 0));
		segaLabel->setText("SEGA 1985");
	}

	// m_noNewScoreTableLabel
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_rankingGO->transform);
		go->transform->setWorldPosition(Vector2(SCREEN_WIDTH /2.0f, (float)SCREEN_HEIGHT - 8));
		m_showRankingTableLabel = go->addComponent<TextRenderer>();
		assert(m_showRankingTableLabel);

		m_showRankingTableLabel->setRenderLayer("UI");
		m_showRankingTableLabel->setZIndex(1);

		bool success = m_showRankingTableLabel->loadFont(getFont("smallGreen"));
		assert(success);
		m_showRankingTableLabel->setAllPivots(Vector2(0.5f, 1));
		m_showRankingTableLabel->setText("RANKING LIST");
	}
	m_showRankingTableLabel->setActive(false);

	// m_newScoreTableLabel;
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_rankingGO->transform);
		go->transform->setWorldPosition(Vector2(48, (float)SCREEN_HEIGHT - 8));
		m_nameEntryTableLabel = go->addComponent<TextRenderer>();
		assert(m_nameEntryTableLabel);

		m_nameEntryTableLabel->setRenderLayer("UI");
		m_nameEntryTableLabel->setZIndex(1);

		bool success = m_nameEntryTableLabel->loadFont(getFont("smallRed"));
		assert(success);
		m_nameEntryTableLabel->setAllPivots(Vector2(0, 1));
		m_nameEntryTableLabel->setText("INITIAL ENTRY COUNTDOWN");
	}
	m_nameEntryTableLabel->setActive(false);

	// VARIABLE

	// m_newScoreTableCounterValue;
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_rankingGO->transform);
		go->transform->setWorldPosition(Vector2((float)SCREEN_WIDTH - 56, (float)SCREEN_HEIGHT - 8));
		m_nameEntryTableCounterValue = go->addComponent<TextRenderer>();
		assert(m_nameEntryTableCounterValue);

		m_nameEntryTableCounterValue->setRenderLayer("UI");
		m_nameEntryTableCounterValue->setZIndex(1);

		bool success = m_nameEntryTableCounterValue->loadFont(getFont("smallGreen"));
		assert(success);
		m_nameEntryTableCounterValue->setAllPivots(Vector2(1, 1));
		m_nameEntryTableCounterValue->setText("30");
	}
	m_nameEntryTableCounterValue->setActive(false);

	// m_topScoreValue
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_rankingGO->transform);
		go->transform->setWorldPosition(Vector2(88, (float)SCREEN_HEIGHT - 32));
		m_topScoreValue = go->addComponent<TextRenderer>();
		assert(m_topScoreValue);

		m_topScoreValue->setRenderLayer("UI");
		m_topScoreValue->setZIndex(1);

		bool success = m_topScoreValue->loadFont(getFont("smallGray"));
		assert(success);
		m_topScoreValue->setAllPivots(Vector2(0, 1));
	}

	// m_charSelectionLabel
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_rankingGO->transform);
		go->transform->setWorldPosition(Vector2(32, 32));
		m_charSelectionLabel = go->addComponent<TextRenderer>();
		assert(m_charSelectionLabel);

		m_charSelectionLabel->setRenderLayer("UI");
		m_charSelectionLabel->setZIndex(1);

		bool success = m_charSelectionLabel->loadFont(getFont("smallYellow"));
		assert(success);
		m_charSelectionLabel->setAllPivots(Vector2(0, 0));
		m_charSelectionLabel->setText(m_characters);
	}
	m_charSelectionLabel->setActive(false);

	// m_selectedCharacterValue
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_rankingGO->transform);
		go->transform->setWorldPosition(Vector2(32, 32));
		m_selectedCharacterValue = go->addComponent<TextRenderer>();
		assert(m_selectedCharacterValue);

		m_selectedCharacterValue->setRenderLayer("UI");
		m_selectedCharacterValue->setZIndex(2);

		bool success = m_selectedCharacterValue->loadFont(getFont("smallRed"));
		assert(success);
		m_selectedCharacterValue->setAllPivots(Vector2(0, 0));
	}
	m_selectedCharacterValue->setActive(false);

	// m_inTopScorePlayerName
	{
		auto go = GameObject::createNew();
		assert(go);
		go->transform->setParent(m_rankingGO->transform);
		go->transform->setWorldPosition(Vector2(200, (float)SCREEN_HEIGHT - 32));
		m_topScoreNameValue = go->addComponent<TextRenderer>();
		assert(m_topScoreNameValue);

		m_topScoreNameValue->setRenderLayer("UI");
		m_topScoreNameValue->setZIndex(1);

		bool success = m_topScoreNameValue->loadFont(getFont("smallGray"));
		assert(success);
		m_topScoreNameValue->setAllPivots(Vector2(0, 1));
	}

	// RANKING LIST GAME OBJECT
	m_rankingListGO = GameObject::createNew();
	assert(m_rankingListGO);
	m_rankingListGO->transform->setParent(m_rankingGO->transform);
	m_rankingListGO->setActive(false);
}


void Ranking::update()
{
	if (!m_isActive)
	{
		return;
	}

	// Handle Input for name entry
	if (m_nameEntryNextCounterTime != -1)
	{
		if (Input::getKeyDown(SDL_SCANCODE_LEFT))
		{
			highlightPreviousChar();
		}
		if (Input::getKeyDown(SDL_SCANCODE_RIGHT))
		{
			highlightNextChar();
		}
		if (Input::getKeyDown(SDL_SCANCODE_LCTRL))
		{
			selectHighlightedChar();
		}
	}

	// SCROLL THE RANKING LIST
	if (m_rankingListEntryEndTime != -1)
	{
		int elapsed = m_totalElapsedTime - (m_rankingListEntryEndTime - m_rankingListEntryDuration);
		float u = (float)elapsed / m_rankingListEntryDuration;
		u = u > 1 ? 1 : u;

		float currentYPos = (1 - u) * m_rankingListGOStartYPos + u * m_rankingListGOtargetYPos;
		m_rankingListGO->transform->setWorldPosition(Vector2(0, currentYPos));
		
		if (u == 1)
		{
			m_rankingListEntryEndTime = -1;
			if (m_playerRank < 7)
			{
				startNameEntry();
			}
		}
	}


	// TIMED MESSAGES

	// Simple ranking mode
	if (m_showRankingEndTime != -1 && m_totalElapsedTime >= m_showRankingEndTime)
	{
		m_showRankingEndTime = -1;
		hide();
	}

	// Name Entry Counter
	if (m_nameEntryNextCounterTime != -1 && m_totalElapsedTime >= m_nameEntryNextCounterTime)
	{
		if (m_nameEntryCounterNumber > 0)
		{
			--m_nameEntryCounterNumber;
			m_nameEntryTableCounterValue->setText(std::to_string(m_nameEntryCounterNumber));
			m_nameEntryNextCounterTime += 1000;
		}
		else
		{
			m_nameEntryNextCounterTime = -1;
			finishNameEntry();
		}
	}

	m_totalElapsedTime += Time::deltaTime();
}


void Ranking::show(int playerScore)
{
	m_isActive = true;
	m_rankingGO->setActive(true);

	m_playerScore = playerScore;
	
	m_totalElapsedTime = 0;
	m_showRankingEndTime = -1;
	m_nameEntryNextCounterTime = -1;
	m_rankingListEntryEndTime = -1;
	m_nameEntryCounterNumber = 30;

	updatePlayerPositionInRanking();

	if (m_playerRank < 10)
	{
		updateScoresInfo();
	}

	setTopScore(scoreInfos[0]);
	setupRankingList();
	m_rankingListGO->setActive(true);

	bool playerInNamedRank = m_playerRank < 7;

	if (playerInNamedRank)
	{
		startNameEntryAnim();
	}
	else
	{
		startShowRankingAnim();
	}

}


void Ranking::hide()
{
	m_isActive = false;
	m_rankingGO->setActive(false);
	Messenger::broadcastEvent(MessengerEventType::CHANGE_SCENE);
}


void Ranking::updateScoresInfo()
{
	// Remove the last element
	scoreInfos.erase(scoreInfos.end() - 1);

	// Insert the player's score (unnamed for the moment)
	scoreInfos.insert(scoreInfos.begin() + m_playerRank, ScoreInfo(m_playerScore, ""));
}


void Ranking::setupRankingList()
{
	for (int i = 0; i < (int)scoreInfos.size(); ++i)
	{
		bool success;
		const ScoreInfo& info = scoreInfos[i];

		// Rank and Score
		auto rankAndScoreGO = GameObject::createNew();
		assert(rankAndScoreGO);
		rankAndScoreGO->transform->setParent(m_rankingListGO->transform);
		rankAndScoreGO->transform->setWorldPosition(Vector2(88, (float)SCREEN_HEIGHT - (56 + i * 16)));
		auto rankAndScoreTR = rankAndScoreGO->addComponent<ClippableTextRenderer>();
		rankAndScoreTR->setRenderRange(0, SCREEN_WIDTH, m_yClipBottom, m_yClipTop);
		assert(rankAndScoreTR);

		rankAndScoreTR->setRenderLayer("UI");
		rankAndScoreTR->setZIndex(2);

		if (m_playerRank == i)
		{
			success = rankAndScoreTR->loadFont(getFont("smallPink"));
		}
		else
		{
			success = rankAndScoreTR->loadFont(getFont("smallGreen"));
		}
		assert(success);
		rankAndScoreTR->setAllPivots(Vector2(0, 1));
		rankAndScoreTR->setText(getNumberAndNameString(i, info));


		// Name
		auto nameGO = GameObject::createNew();
		assert(nameGO);
		nameGO->transform->setParent(m_rankingListGO->transform);
		nameGO->transform->setWorldPosition(Vector2(200, (float)SCREEN_HEIGHT - (56 + i * 16)));
		auto nameTR = nameGO->addComponent<ClippableTextRenderer>();
		nameTR->setRenderRange(0, SCREEN_WIDTH, m_yClipBottom, m_yClipTop);
		assert(nameTR);

		nameTR->setRenderLayer("UI");
		nameTR->setZIndex(2);

		if (m_playerRank == i)
		{
			success = nameTR->loadFont(getFont("smallPink"));
			m_inRankingPlayerName = nameTR;
		}
		else
		{
			success = nameTR->loadFont(getFont("smallYellow"));
		}
		assert(success);
		nameTR->setAllPivots(Vector2(0, 1));
		nameTR->setText(info.name);
	}
}


std::string Ranking::getNumberAndNameString(int index, const ScoreInfo& info)
{
	std::string text;
	if (index < 9)
	{
		text += " ";
	}
	text += std::to_string(index + 1) + ".";

	std::string scoreAsText = std::to_string(info.score);

	int spaces1Count = 9 - scoreAsText.length();
	if (spaces1Count < 0)
	{
		spaces1Count = 0;
	}

	for (int i = 0; i < spaces1Count; ++i)
	{
		text += " ";
	}

	text += scoreAsText;
	return text;
}


void Ranking::setTopScore(ScoreInfo topScoreInfo)
{
	std::string topScoreAsText = std::to_string(topScoreInfo.score);
	int spaces1Count = 9 - topScoreAsText.length();
	if (spaces1Count < 0)
	{
		spaces1Count = 0;
	}

	std::string spaces1 = "";
	for (int i = 0; i < spaces1Count; ++i)
	{
		spaces1 += " ";
	}

	m_topScoreValue->setText("TOP" + spaces1 + topScoreAsText);
	m_topScoreNameValue->setText(topScoreInfo.name);
}


void Ranking::updatePlayerPositionInRanking()
{
	m_playerRank = INT_MAX;
	int i = 0;
	for (auto it = scoreInfos.begin(); it != scoreInfos.end(); ++it)
	{
		if (m_playerScore > (*it).score)
		{
			m_playerRank = i;
			break;
		}
		++i;
	}
}


void Ranking::startNameEntryAnim()
{
	Audio::playMusic(m_musicNameEntry);
	m_nameEntryTableLabel->setActive(true);
	m_showRankingEndTime = -1;
	startRankingListEntry();
}


void Ranking::startNameEntry()
{
	m_nameEntryTableCounterValue->setActive(true);
	m_charSelectionLabel->setActive(true);
	m_selectedCharacterValue->setActive(true);
	m_highlightedCharIndex = 0;
	updateHighlightedChar();
	m_nameEntryNextCounterTime = 1000;
}


void Ranking::startShowRankingAnim()
{
	m_showRankingEndTime = 8000;
	m_nameEntryNextCounterTime = -1;
	m_showRankingTableLabel->setActive(true);
	startRankingListEntry();
}


void Ranking::startRankingListEntry()
{
	// Push the ranking down prior to scrolling upwards
	m_rankingListGOStartYPos = -(7 * 16);
	m_rankingListGO->transform->setWorldPosition(Vector2(0, (float)m_rankingListGOStartYPos));
	if (m_playerRank < 7)
	{
		m_rankingListGOtargetYPos = 0;
	}
	else
	{
		m_rankingListGOtargetYPos = 3 * 16;
	}
	m_rankingListEntryEndTime = m_totalElapsedTime + m_rankingListEntryDuration;
}


void Ranking::finishNameEntry()
{
	// Add the last highlighted char if it's valid
	bool validExtraChar = m_highlightedCharIndex < (int)m_characters.length() - 2;
	if (m_selectedName.length() < 3 && validExtraChar)
	{
		m_selectedName += m_characters[m_highlightedCharIndex];
	}

	// Update scoresInfo name
	scoreInfos[m_playerRank].name = m_selectedName;

	hide();
}


void Ranking::highlightPreviousChar()
{
	--m_highlightedCharIndex;
	updateHighlightedChar();
}


void Ranking::highlightNextChar()
{
	++m_highlightedCharIndex;
	updateHighlightedChar();
}


void Ranking::updateHighlightedChar()
{
	int minIndex = 0;
	int maxIndex = m_characters.length() - 1;
	if (m_selectedName.length() >= 3)
	{
		minIndex = maxIndex - 1;
	}

	// Wrap around if out of range (this also ensures that the ED char is selected once a length of 3 chars is reached)
	if (m_highlightedCharIndex < minIndex)
	{
		m_highlightedCharIndex = maxIndex;
	}
	else if (m_highlightedCharIndex > maxIndex)
	{
		m_highlightedCharIndex = minIndex;
	}

	m_selectedCharacterValue->gameObject()->transform->setWorldPosition(Vector2(32.0f + m_highlightedCharIndex * 8, 32.0f));
	m_selectedCharacterValue->setText(m_characters.substr(m_highlightedCharIndex, 1));

	std::string nameDisplay = m_selectedName + m_characters[m_highlightedCharIndex];
	m_inRankingPlayerName->setText(nameDisplay);
	if (m_playerRank == 0)
	{
		m_topScoreNameValue->setText(nameDisplay);
	}
}


void Ranking::selectHighlightedChar()
{
	int endIndex = m_characters.length() - 1;
	int backIndex = endIndex - 1;

	if (m_highlightedCharIndex == endIndex)
	{
		finishNameEntry();
	}
	else if (m_highlightedCharIndex == backIndex)
	{
		if (m_selectedName.length() > 0)
		{
			m_selectedName = m_selectedName.substr(0, m_selectedName.length() - 1);
		}
	}
	else
	{
		// So any normal character
		m_selectedName += m_characters[m_highlightedCharIndex];
	}
	updateHighlightedChar();
}
