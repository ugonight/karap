#pragma execution_character_set("utf-8")

#include "karapList.h"

Nomal::Nomal() {
	mFormName = "カラーパーカー";

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
	
	//終わり
	setMsg("finish");
	setWords("よく頑張ったな");
	setWords("次の俺もよろしく頼むぜ");
	setWords("それじゃ、また巡り会う日まで");
	setWords("グッバイ、唐松ガール");
	addWords();
	addRemark();

	//死にたい
	setMsg("しにたい");
	setWords("死にたい…か");
	setWords("二人同時に命を絶てば、次の世界でまた巡り会うことができるだろうか");
	setWords("今よりもっと幸せな世界で、二人永遠に愛し合い続けることができるのだろうか");
	setWords("俺は今のお前が一番好きなんだが");
	addWords();
	addRemark();

	//死ね
	setMsg("しね");
	setWords("ああ、俺だってガールのためなら何度だって死ねるさ。");
	setWords("お前はいつだって、その痛みを苦しみで自分を傷付けて生きてきた。");
	setWords("その痛みを俺にも分けてくれないか。");
	addWords();
	addRemark();

	//おはよう
	setMsg("おはよう");
	setWords("グッモーニン！唐松ガール");
	setWords("ちゃんと起きることができるなんて偉いな");
	setWords("ぐっすり眠れたなら昨日できなかったこともできるかもしれない");
	setWords("さあ、今日も新たな発見を見つけに行こう");
	addWords();
	addRemark();

	//一松
	setMsg("いちまつ");
	setWords("ああ、市松のことか");
	setWords("市松は俺のブラザーだぜ");
	setWords("シャイなキティみたいでとてもキュートなんだ");
	setWords("あいつは俺のことは嫌いみたいなんだがな");
	addWords();
	addRemark();

}