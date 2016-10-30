#pragma execution_character_set("utf-8")

#include "karapList.h"

Nomal::Nomal() {
	mCharaImage = "nomal.png";
	mBGImage = "room.png";

	//デフォルト
	setWords("今日も頑張ってるな");
	setWords("え？今日も全然ダメだったって？");
	setWords("何言ってるんだ。今、こうしてちゃんと息をして俺の目の前にいてくれるじゃないか。");
	setWords("それだけで１００点満点のはなまるぴっぴだ");
	addWords();
	setWords("はは、ガールは甘えん坊さんだな");
	setWords("でも、ここにいる間はいくらでも俺に甘えるんだ");
	setWords("俺はいつでも、お前の中の理想の唐松になるように努める");
	setWords("それが愛というものさ");
	addWords();
	addRemark();


}