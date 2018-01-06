#ifndef H_RANKING
#define H_RANKING
#endif // !H_RANKING

#include "Engine/Behaviour.h"
#include "Engine/Reference.h"
#include "Engine/Music.h"
class GameObject;
class TextRenderer;
class ClippableTextRenderer;
struct ScoreInfo;


class Ranking :
	public Behaviour
{
public:
	virtual void onDestroy() override;
	virtual void awake() override;
	virtual void update() override;

	void show(int playerScore);

private:
	void hide();
	void updateScoresInfo();
	void setupRankingList();
	std::string getNumberAndNameString(int index, const ScoreInfo& info);

	void setTopScore(ScoreInfo topScoreInfo);
	void updatePlayerPositionInRanking();
	void startNameEntryAnim();
	void startNameEntry();
	void startShowRankingAnim();
	void startRankingListEntry();
	void finishNameEntry();

	void highlightPreviousChar();
	void highlightNextChar();
	void updateHighlightedChar();
	void selectHighlightedChar();

	int m_playerScore;
	int m_playerRank;
	// Containing GO
	Reference<GameObject> m_rankingGO;
	bool m_isActive;

	// Constant UI
	Reference<TextRenderer> m_showRankingTableLabel;
	Reference<TextRenderer> m_nameEntryTableLabel;
	Reference<TextRenderer> m_charSelectionLabel;

	// Variable UI
	Reference<TextRenderer> m_livesLabel;
	Reference<TextRenderer> m_topScoreValue;
	Reference<TextRenderer> m_nameEntryTableCounterValue;
	Reference<TextRenderer> m_selectedCharacterValue;
	Reference<ClippableTextRenderer> m_inRankingPlayerName;
	Reference<TextRenderer> m_topScoreNameValue;

	// Moving UI
	Reference<GameObject> m_rankingListGO;
	int m_rankingListGOStartYPos;
	int m_rankingListGOtargetYPos;
	int m_rankingListScrollElapsedTime;
	int m_rankingListEntryEndTime = -1;
	int m_rankingListEntryDuration;
	int m_yClipTop;
	int m_yClipBottom;

	// Timing and messages info
	int m_totalElapsedTime;
	int m_showRankingEndTime = -1;
	int m_nameEntryNextCounterTime = -1;
	int m_nameEntryCounterNumber;

	// Name entry specific data
	std::string m_characters;
	std::string m_selectedName;
	int m_highlightedCharIndex;

	Music m_musicNameEntry;
};

