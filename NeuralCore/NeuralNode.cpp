//
//  NeuralNode.cpp
//  NeuralCore
//
//  Created by Jeremy Bridon on 2/2/13.
//  Copyright (c) 2013 Jeremy Bridon. All rights reserved.
//

#include "NeuralNode.h"

static const size_t NeuralNode_MaxEdges = 8;
static const size_t NeuralNode_EdgeDist = 2; // How far out we can reach to

NeuralNode::NeuralNode()
{
    // Do nothing (for now)
}

NeuralNode::~NeuralNode()
{
    
}

void NeuralNode::Initialize(NeuralNode* Nodes, size_t CubeSize, int x, int y, int z)
{
    // Copy given
    this->x = x;
    this->y = y;
    this->z = z;
    this->Nodes = Nodes;
    this->CubeSize = CubeSize;
    
    // Initialize all the zero
    OutputCount = 0;
    Outputs = new NeuralNode*[NeuralNode_MaxEdges];
    
    InputCount = 0;
    Inputs = new NeuralNode*[NeuralNode_MaxEdges];
    
    Threshold = 0.5f; // Right in the middle
    Inverted = false;
    
    Age = 0;
    Value = 1.0f; // Full signal out
}

void NeuralNode::Randomize()
{
    OutputCount = rand() % NeuralNode_MaxEdges;
    for(int i = 0; i < OutputCount; i++)
    {
        // Cannot be self or out of bounds
        NeuralNode* Target = NULL;
        while(Target == NULL || Target == this)
            Target = GetRandomNode(x, y, z);
        
        // If good, save
        Outputs[i] = Target;
        
        // Inform target we are a message sender..
        Target->Inputs[Target->InputCount++] = this;
    }
    
    Threshold = (float)rand() / (float)RAND_MAX;
    Inverted = (bool)(rand() % 2); // Randomize
    
    Age = 0;
    Value = (float)rand() / (float)RAND_MAX;
}

NeuralNode* NeuralNode::GetRandomNode(int tx, int ty, int tz)
{
    tx += (rand() % (NeuralNode_EdgeDist + 1)) * ((rand() % 2) ? -1 : 1);
    ty += (rand() % (NeuralNode_EdgeDist + 1)) * ((rand() % 2) ? -1 : 1);
    tz += (rand() % (NeuralNode_EdgeDist + 1)) * ((rand() % 2) ? -1 : 1);
    return GetNode(tx, ty, tz);
}

NeuralNode* NeuralNode::GetNode(int tx, int ty, int tz)
{
    // If out of bounds, return null
    if(tx < 0 || tx >= CubeSize ||
       ty < 0 || ty >= CubeSize ||
       tz < 0 || tz >= CubeSize)
        return NULL;
    
    // Else, good
    else
        return &Nodes[CubeSize * CubeSize * ty + CubeSize * tz + tx];
}
