//
//  NeuralNode.h
//  NeuralCore
//
//  Created by Jeremy Bridon on 2/2/13.
//  Copyright (c) 2013 Jeremy Bridon. All rights reserved.
//

#ifndef __NeuralCore__NeuralNode__
#define __NeuralCore__NeuralNode__

#include <iostream>

class NeuralNode
{
public:
    
    // Constructs a node with no properties
    NeuralNode();
    ~NeuralNode();
    
    // The true constructor; initializes at a given position
    void Initialize(NeuralNode* Nodes, size_t CubeSize, int x, int y, int z);
    
    // Randomize the internal connections
    void Randomize();
    
    /*** Public variables (messy, but just to keep things easy to access) ***/
    
    size_t OutputCount;
    NeuralNode** Outputs; // Array of pointers to nodes
    
    size_t InputCount;
    NeuralNode** Inputs; // Array of pointers to nodes
    
    float Threshold;
    bool Inverted;
    
    size_t Age;
    float Value;
    
private:
    
    // Get a random node around us based on the max distance; will return null if out of bounds
    NeuralNode* GetRandomNode(int tx, int ty, int tz);
    
    // Internal helper (just a shorthand function)
    inline NeuralNode* GetNode(int tx, int ty, int tz);
    
    // Internal info to retain
    int x, y, z;
    NeuralNode* Nodes;
    size_t CubeSize;
};

#endif /* defined(__NeuralCore__NeuralNode__) */
