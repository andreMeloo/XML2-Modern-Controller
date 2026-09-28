#ifndef XML2_CONTROLLER_PROMPTS_H
#define XML2_CONTROLLER_PROMPTS_H
#include "controller_model.h"
void mc_prompts_prepare(uintptr_t image, const WCHAR *ini, const McCore *core);
void mc_prompts_state(int role,int slot,const void *state,unsigned size);
int mc_prompts_enabled(void);
#endif
