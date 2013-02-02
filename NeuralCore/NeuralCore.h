//
//  NeuralCore.h
//  NeuralCore
//
//  Created by Jeremy Bridon on 2/2/13.
//  Copyright (c) 2013 Jeremy Bridon. All rights reserved.
//

#ifndef __NeuralCore__NeuralCore__
#define __NeuralCore__NeuralCore__

#include <iostream>
#include "NeuralNode.h"

class NeuralCore
{
    
public:
    
    // Construct a cube with a given volume size (in all three dimensions)
    NeuralCore(size_t CubeSize);
    ~NeuralCore();
    
    // Simulate the entire system once
    float Step(float Input, float ExpectedOutput);
    
    // Cull (i.e. clean bad paths, and re-inforce good paths)
    void Cull();
    
private:
    
    size_t CubeSize;
    NeuralNode* Nodes; // 3D array; initialized via constructor
};

#endif /* defined(__NeuralCore__NeuralCore__) */
