#include "mrc_base.h"
#include "i18n.h"
#include "res_str.h"
#include "game.h"

int32 MRC_EXT_INIT(void)
{
	Game_Start();
	return MR_SUCCESS;
}

int32 MRC_EXT_EXIT(void)
{	
	Game_ReleaseSource();
	return MR_SUCCESS;
}

int32 mrc_appEvent(int32 code, int32 param0, int32 param1)
{//�Ʒ�״̬�£��Զ�����
	Game_KeyCheck(code, param0, param1);
	return MR_SUCCESS;
}

int32 mrc_appPause()
{//�Ʒ�״̬�£��Զ�����
	Game_Pause();
	return MR_SUCCESS;	
}

int32 mrc_appResume()
{
	Game_Resume();
	return MR_SUCCESS;
}
