// 	Copyright � 1991-92 Apple Computer, Inc. All rights reserved.//	UAEServerCommand.cp//	Kent Sandvik DTS//	This file contains the TAEServer member functions, for serving//	incoming Apple events.////	<1>		khs		1.0		First final version#ifndef __UAESERVERCOMMAND__#include "UAEServerCommand.h"#endif//	Empty constructor - for avoiding ptabs in global data space#undef Inherited#define Inherited TServerCommand#pragma segment AResDefineClass(TAEServerCommand, TServerCommand);TAEServerCommand::TAEServerCommand(){}//	Process the incoming client AppleEvent, and return the needed information,//	in our case the gConfiguration structure resident in memory.#pragma segment ADoCommandvoid TAEServerCommand::DoIt(){	fReply->WriteParameterPtr(kAEConfig, typeConfig, (Ptr) & gConfiguration, sizeof(gConfiguration));	fReply->Send();}