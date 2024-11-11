#include "GUI/GP4_MenuBase.h"

void UGP4_MenuBase::EnableMenu(bool bShouldEnable)
{
	if(bShouldEnable)
		AddToViewport();
	else
		RemoveFromParent();
}