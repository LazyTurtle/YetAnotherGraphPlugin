// Copyright (c) 2018 Jhonny Hueller
#include "StartNode.h"

#define LOCTEXT_NAMESPACE "StartNode"

UStartNode::UStartNode()
{
	bHasInputPins = false;
	DefaultNodeTitle = LOCTEXT("Start Node Title", "Start");
}

#undef LOCTEXT_NAMESPACE