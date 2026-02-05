#pragma once
#include <array>

enum class DataType
{
	BgmVolume,
	SeVolume,	
	Stage,
	ClearStage,
	Score,
	Residue,
	HighScore
};

enum class ItemType
{
	SnowBall,
	StarDust,
	Mushroom,
	Crystal,
	Water,
	Max
};

enum class StageType
{
	Max
};

namespace {
	const int ZERO_DATA = 0;
	const int MAX_ITEM_COUNT = 99;
	const int MIN_ITEM_COUNT = 0;
	const int MAX_VOLUME = 100;
	const int MIN_VOLUME = 0;
}


/*
* GameData.h
* ゲームデータ管理クラス
*/
class GameData
{
private:
	GameData() {};
	~GameData() =default;


public:
	//インスタンス管理関数
	static GameData& GetInstance()
	{
		static GameData instance;
		return instance;
	}
	/**
	  *データ記録関数
	  *引数：識別番号
	  *　　：記録するデータ	
	  *0：BGM音量データ			1：SE音量データ
	  *2：ステージデータ		3：クリアステージデータ
	  *4：スコアデータ			5：残基データ
	  *6：ハイスコアデータ
	  *使用例:GameData::GetInstance().DataRecord(DataType::Score, 100);
	  */
	void DataRecord(DataType type,int Data)
	{
		//データ記録処理
		switch (type)
		{
			//BGM音量データ
		case DataType::BgmVolume:
			SetBgmVolume(Data);
			break;
			//SE音量データ
		case DataType::SeVolume:
			SetSeVolume(Data);
			break;
			//ステージデータ
			case  DataType::Stage:
				SetStage(Data);
			break;
			//クリアステージデータ
			case  DataType::ClearStage:
				SetClearStage(Data);
			break;
			//スコアデータ
			case  DataType::Score:
				SetScore(Data);
			break;
			//残基データ
			case  DataType::Residue:
				SetResidue(Data);
			break;
			//ハイスコアデータ
			case  DataType::HighScore:
				SetHighScore(Data);
			break;
			default:
				return;
			break;
		}
	}
	/**
	  *データ取得関数
	  *引数：識別番号
	  *戻り値：取得したデータ
	  *0：BGM音量データ			1：SE音量データ
	  *2：ステージデータ		3：クリアステージデータ	
	  *4：スコアデータ			5：残基データ
	  *6：ハイスコアデータ
	  *使用例:int score = GameData::GetInstance().DataGet(DataType::Score);
	  */
	int DataGet(DataType type)
	{
		//データ取得処理
		switch (type)
		{
			//BGM音量データ
			case  DataType::BgmVolume:
				return GetBgmVolume();
			break;
			//SE音量データ
			case  DataType::SeVolume:
				return GetSeVolume();
			break;			
			//ステージデータ
			case  DataType::Stage:
				return GetStage();
			break;
			//クリアステージデータ
			case  DataType::ClearStage:
				return GetClearStage();
			break;
			//スコアデータ
			case  DataType::Score:
				return GetScore();
			break;
			//残基データ
			case  DataType::Residue:
				return GetResidue();
			break;
			//ハイスコアデータ
			case  DataType::HighScore:
				return GetHighScore();
			break;
			default:
				return ZERO_DATA;
		}		
	}

	/**
	* アイテム所持数加算処理
	* 呼び出し方
	* 例：GameData::GetInstance().AddItem(ItemType::SnowBall, 5);
	*/
	void AddItem(ItemType type, int count)
	{
		// 所持数加算
		m_itemInventoryData[static_cast<int>(type)] += count;
		// 所持数上限チェック
		// 所持数が上限を超えた場合、上限値に設定
		m_itemInventoryData[static_cast<int>(type)] =
			min(m_itemInventoryData[static_cast<int>(type)], MAX_ITEM_COUNT);
	}

	/**
	 * アイテム所持数減算処理
	 * 呼び出し方
	 * 例：GameData::GetInstance().DecItem(ItemType::SnowBall, 5);
	 */
	void DecItem(ItemType type, int count)
	{
		m_itemInventoryData[static_cast<int>(type)] -= count;
		// 所持数下限チェック
		// 所持数が下限を下回った場合、下限値に設定
		m_itemInventoryData[static_cast<int>(type)] = 
			max(m_itemInventoryData[static_cast<int>(type)], MIN_ITEM_COUNT);
	}

	/**
	* アイテム所持数取得処理
	* 呼び出し方
	* 例：int itemCount = GameData::GetInstance().GetItemCount(ItemType::SnowBall);
	*/
	int GetItemCount(ItemType type)const
	{
		return m_itemInventoryData[static_cast<int>(type)];
	}


	private:

	void SetBgmVolume(int volume)
	{
		m_bgmVolumeData = volume;
		m_stageData = max(m_stageData, ZERO_DATA);
		m_bgmVolumeData = min(m_bgmVolumeData, MAX_VOLUME);
	}

	int GetBgmVolume()const
	{
		return m_bgmVolumeData;
	}

	void SetSeVolume(int volume)
	{
		m_seVolumeData = volume;
		m_seVolumeData = min(m_seVolumeData, MAX_VOLUME);
		m_seVolumeData = max(m_seVolumeData, MIN_VOLUME);
	}

	int GetSeVolume()const
	{
		return m_seVolumeData;
	}

	void SetStage(int stage)
	{
		m_stageData = stage;

	}

	int GetStage()const
	{
		return m_stageData;
	}

	void SetClearStage(int stage)
	{
		if (m_clearStageData < stage)
		{
			m_clearStageData = stage;
		}
	}

	int GetClearStage()const
	{
		return m_clearStageData;
	}

	void SetScore(int score)
	{
		m_scoreData = score;
	}

	int GetScore()const
	{
		return m_scoreData;
	}

	void SetHighScore(int score)
	{
		if (m_highScoreData < score)
		{
			m_highScoreData = score;
		}
	}

	int GetHighScore()const
	{
		return m_highScoreData;
	}

	void SetResidue(int residue)
	{
		m_residueData = residue;
	}

	int GetResidue()const
	{
		return m_residueData;
	}

private:
	std::array<int, static_cast<int>(ItemType::Max)>m_itemInventoryData{}; //アイテムごとの所持量データ
	int m_bgmVolumeData=50; //音量データ
	int m_seVolumeData=50; //SE音量データ
	int m_stageData=0;//ステージデータ
	int m_clearStageData=0;//クリアステージデータ
	int m_scoreData = 0;//スコアデータ
	int m_highScoreData = 0;//ハイスコアデータ
	int m_residueData = 3; //残基データ
	int m_dummyData = 0;//ダミーデータ
};