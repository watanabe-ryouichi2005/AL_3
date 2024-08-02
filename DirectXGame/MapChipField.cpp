
#include <assert.h>
#include <cassert>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include "MapChipField.h"

    namespace {
	std::map<std::string, MapChipType> MapChipTable = {
	    {"0", MapChipType::kBlank},
	    {"1", MapChipType::kBlock},
	};
}
uint32_t MapChipField::GetkNumBlockVirtical() { return kNumBlockVirtical; }
uint32_t MapChipField::GetkNumBlockHorizontal() { return kNumBlockHorizontal; }

void MapChipField::ResetMapChipData() {
	//マップチップデータリセット
	mapChipData_.data.clear();
	mapChipData_.data.resize(kNumBlockVirtical);

	for (std::vector<MapChipType>& mapChipDataLine : mapChipData_.data) {

		mapChipDataLine.resize(MapChipField::kNumBlockHorizontal);
	}
}
void MapChipField::LoadMapChipCsv(const std::string& filepath) {
	//ファイルを開く
	std::ifstream file;
	file.open(filepath);
	assert(file.is_open());
	//マップチップCSV
	std::stringstream mapChipCsv;
	//ファイルの内容を文字列ストリームにコピー
	mapChipCsv << file.rdbuf();
	//ファイルを閉じる
	file.close();
	//マップチップをリセット
	ResetMapChipData();	
	std::string line;
	//CSVからマップチップデータを読み込む
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		getline(mapChipCsv, line);
		//1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			std::string word;
			getline(line_stream, word, ',');
			if (MapChipTable.contains(word)) {
				mapChipData_.data[i][j] = MapChipTable[word];
			}
		}
	}
}
MapChipType MapChipField::GetMapChipTypeByIndex(uint32_t xindex, uint32_t yindex) {
	if (xindex < 0 || kNumBlockHorizontal - 1 < xindex) {
		return MapChipType::kBlank;
	}
	if (yindex < 0 || kNumBlockVirtical - 1 < yindex) {
		return MapChipType::kBlank;
	}
	return mapChipData_.data[yindex][xindex];
}
Vector3 MapChipField::GetMapChipPositionByIndex(uint32_t xindex, uint32_t yindex) {
	return Vector3(kBlockWidth * xindex, kBlockHeight * (kNumBlockVirtical - 1 - yindex), 0);
}
MapChipType MapChipField::GetMapChipTypeByPosition(const Vector3& position)
{
	IndexSet indexset =  GetMapChipIndexSetByPosition(position);
	return GetMapChipTypeByIndex(indexset.xindex,indexset.yindex);
}

MapChipField::IndexSet MapChipField::GetMapChipIndexSetByPosition(const Vector3& position) {
	IndexSet indexSet = {};
	indexSet.xindex = static_cast<uint32_t>((position.x + kBlockWidth/2.0f)/kBlockWidth);
	indexSet.yindex = kNumBlockVirtical-1-static_cast<uint32_t>(position.y + kBlockHeight/2.0f/kBlockHeight);
	return indexSet;
}
MapChipField::Rect MapChipField::GetRectByIndex(uint32_t xindex, uint32_t yindex)
{Vector3 center = GetMapChipPositionByIndex(xindex,yindex);
Rect rect;
rect.left = center.x-kBlockWidth/2.0f;
rect.right = center.y+kBlockWidth/2.0f;
rect.bottom = center.x-kBlockWidth/2.0f;
rect.top = center.x-kBlockWidth/2.0f;

return rect;
}