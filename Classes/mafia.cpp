#pragma execution_character_set("utf-8")

#include "karapList.h"

Mafia::Mafia() {
	mCharaImage = "mafia.png";
	mBGImage = "mafia_r.png";

	//�f�t�H���g
	setWords("�������撣���Ă��");
	setWords("���H�������S�R�_�����������āH");
	setWords("�������Ă�񂾁B���A�������Ă����Ƒ������ĉ��̖ڂ̑O�ɂ��Ă���邶��Ȃ����B");
	setWords("���ꂾ���łP�O�O�_���_�̂͂Ȃ܂�҂��҂�");
	addWords();
	setWords("�͂́A�K�[���͊Â���V���񂾂�");
	setWords("�ł��A�����ɂ���Ԃ͂�����ł����ɊÂ����");
	setWords("���͂��ł��A���O�̒��̗��z�̓����ɂȂ�悤�ɓw�߂�");
	setWords("���ꂪ���Ƃ������̂�");
	addWords();
	addRemark();

	//�I���
	setMsg("finish");
	setWords("�悭�撣������");
	setWords("���̉�����낵�����ނ�");
	setWords("���ꂶ��A�܂��������܂�");
	setWords("�O�b�o�C�A�����K�[��");
	addWords();
	addRemark();

	//���ɂ���
	setMsg("���ɂ���");
	setWords("���ɂ����c��");
	setWords("��l�����ɖ����Ă΁A���̐��E�ł܂��������Ƃ��ł��邾�낤��");
	setWords("���������ƍK���Ȑ��E�ŁA��l�i���Ɉ������������邱�Ƃ��ł���̂��낤��");
	setWords("���͍��̂��O����ԍD���Ȃ񂾂�");
	addWords();
	addRemark();

}