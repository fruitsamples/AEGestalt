//	UAEClientCommand.cp// 	Copyright � 1991-92 by Apple Computer, Inc. All rights reserved.//	Kent Sandvik DTS//	This file contains all the TAEClientCommand member functions, i.e.//	for creating an Apple event which will query a server over the network.////	<1>		khs		1.0		First final version#ifndef __UAECLIENTCOMMAND__#include "UAEClientCommand.h"#endif//	Empty constructor - for avoiding ptabs in global data space#undef Inherited#define Inherited TClientCommand#pragma segment AResDefineClass(TAEClientCommand, TClientCommand);TAEClientCommand::TAEClientCommand(){}// 	Put together the client AppleEvent, which will call the server asking for//	Gestalt information#pragma segment ASelCommandvoid TAEClientCommand::IAEClientCommand(CommandNumber theNum,											   TAEDocument* theDocument,											   AEEventID theID){	AEAddressDesc theAddress;	FailInfo fi;	// save document wherefrom command is issued	fDocument = theDocument;	this->IClientCommand(theNum, theDocument, kCantUndo, kDoesNotCauseChange, NULL);		Try(fi)	{		// setup fMessage to contain the data for our Gestalt GetData AppleEvent		theDocument->GetAEGestaltAddress(theAddress);		TAppleEvent * aMessage = new TAppleEvent;// create AE object		aMessage->IAppleEvent(kMacAppClass, theID, theAddress, kAEQueueReply);		fMessage = aMessage;		fi.Success();	}	else	{		this->Free();		fi.ReSignal();	}}//	Process replies that gets back to the client side from the AE server#pragma segment ADoCommandvoid TAEClientCommand::ProcessReply(TAppleEvent* theReply){	CStr255 theResponse;	long actualSize;	DescType actualCode;	struct Configuration tempConfig;	// handle Inherited processing and check for AE errors		Inherited::ProcessReply(theReply);	//FailOSErr(theReply->ReadShort('errn'));	// if OK, continue processing the reply - store it in the document	theReply->ReadParameterPtr(kAEConfig, typeConfig, actualCode, (Ptr) & tempConfig, sizeof(Configuration), actualSize);	// Now move the tempConfig to the fDocument itself.	fDocument->ReadConfiguration(&tempConfig);	// FUTURE: Make a TProcessGestaltCommand which will process the information	// and store it in the TInformationView	// TProcessGestaltCommand aCommand = new TProcessGestaltCommand(this,tempConfig);	// and so on...	// Process the reply to a more suitable format, this is done from the	// document itself for the view class	fDocument->ProcessAEInformation();}