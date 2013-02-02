//
//  NeuralCore.cpp
//  NeuralCore
//
//  Created by Jeremy Bridon on 2/2/13.
//  Copyright (c) 2013 Jeremy Bridon. All rights reserved.
//

#include "NeuralCore.h"

static const int NeuralCore_InputDepth = 4;

NeuralCore::NeuralCore(size_t CubeSize)
{
    // 3D continuous array
    this->CubeSize = CubeSize;
    Nodes = new NeuralNode[CubeSize * CubeSize * CubeSize];
    
    // We must start with randomly initialized cube-items
    for(int y = (int)CubeSize - 1; y >= 0; y--)
    for(int z = 0; z < (int)CubeSize; z++)
    for(int x = 0; x < (int)CubeSize; x++)
    {
        // Get the node in question
        NeuralNode* Node = &Nodes[CubeSize * CubeSize * y + CubeSize * z + x];
        
        Node->Initialize(Nodes, CubeSize, x, y, z);
        Node->Randomize();
    }
}

NeuralCore::~NeuralCore()
{
    delete[] Nodes;
}

float NeuralCore::Step(float Input, float ExpectedOutput)
{
    // Special rule: if we are an input rod, set the output value...
    for(int y = (int)CubeSize - 1; y >= CubeSize - NeuralCore_InputDepth - 1; y--)
    {
        // Center of this sheet
        int z = CubeSize / 2;
        int x = CubeSize / 2;
        
        // Get the node in question
        NeuralNode* Node = &Nodes[CubeSize * CubeSize * y + CubeSize * z + x];
        Node->Value = Input;
    }
    
    // From the top to bottom...
    // OpenGL coordinate system
    for(int y = (int)CubeSize - 1; y >= 0; y--)
    for(int z = 0; z < (int)CubeSize; z++)
    for(int x = 0; x < (int)CubeSize; x++)
    {
        // Get the node in question
        NeuralNode* Node = &Nodes[CubeSize * CubeSize * y + CubeSize * z + x];
        
        // Get the sum of all inputs... (and normalize)
        float Sum = 0.0f;
        for(int i = 0; i < Node->InputCount; i++)
            Sum += Node->Inputs[i]->Value;
        Sum /= (float)Node->InputCount;
        
        // Are we passing our threshold, and if so, what is our signal value?
        // Note the inverse-logic check
        if((!Node->Inverted && Sum >= Node->Threshold) || (Node->Inverted && Sum <= Node->Threshold))
        {
            // What's the delta between our threshold and max?
            float OutputValue = 0.0f;
            if(!Node->Inverted)
                OutputValue = (1.0f - Node->Threshold) * Sum;
            else
                OutputValue = (0.0f - Node->Threshold) * -Sum;
            
            // We are now going to set our edge's outputs
            for(int i = 0; i < Node->OutputCount; i++)
            {
                Node->Outputs[i]->Value = OutputValue;
            }
        }
    }
    
    // TODO: Add age to only sucesfull paths
    // This will require me to retain a list of visited nodes, and do a reverse-path look-up
    //Node->Outputs[i]->Age++;
    
    // What's our result?
    float Result = 0.0f;
    for(int y = 0; y < NeuralCore_InputDepth; y++)
    {
        // Center of this sheet
        int z = CubeSize / 2;
        int x = CubeSize / 2;
        
        // Get the node in question
        NeuralNode* Node = &Nodes[CubeSize * CubeSize * y + CubeSize * z + x];
        
        // Get the sum of all inputs... (and normalize)
        float Sum = 0.0f;
        for(int i = 0; i < Node->InputCount; i++)
            Sum += Node->Inputs[i]->Value;
        Sum /= (float)Node->InputCount;
        
        // Add sum to result
        Result += Sum;
    }
    
    // Return the result average
    return Result / (float)NeuralCore_InputDepth;
}

void Cull()
{
    // What's our average age?
    float Average = 0.0f;
}
