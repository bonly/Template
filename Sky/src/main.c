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
{//计费状态下，自动返回
	Game_KeyCheck(code, param0, param1);
	return MR_SUCCESS;
}

int32 mrc_appPause()
{//计费状态下，自动返回
	Game_Pause();
	return MR_SUCCESS;	
}

int32 mrc_appResume()
{
	Game_Resume();
	return MR_SUCCESS;
}
