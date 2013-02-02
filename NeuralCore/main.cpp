//
//  main.cpp
//  NeuralCore
//
//  Created by Jeremy Bridon on 2/2/13.
//  Copyright (c) 2013 Jeremy Bridon. All rights reserved.
//

#include <iostream>
#include "NeuralCore.h"

// Test data is strictly a logical-not truth-table (false -> true, true -> false)
float TestData[10][2] = {
    {0, 1},
    {1, 0},
    {0, 1},
    {1, 0},
    {0, 1},
    {1, 0},
    {0, 1},
    {1, 0},
    {0, 1},
    {1, 0},
};

int main(int argc, const char * argv[])
{
    // Initialize structures
    // For now, our test will be to create an inteverter (1 --> 0, and 0 --> 1)
    NeuralCore TestCore(32);
    
    // Simulate 10000 cycles, with 1000 cycles per test (so 10 tests)
    for(int TestIndex = 0; TestIndex < 10; TestIndex++)
    {
        // Simulate with this test data
        // We currently only deal with one input and one output
        for(int TestCycle = 0; TestCycle < 1000; TestCycle++)
            TestCore.Step(TestData[TestIndex][0], TestData[TestIndex][1]);
        
        // What's the result of running through the test one last time?
        float ResultSignal = TestCore.Step(TestData[TestIndex][0], TestData[TestIndex][1]);
        printf("The result for testing a logical-not, with input %d is signal %f\n", TestData[TestIndex][0], ResultSignal);
        
        // Now cull the system
        TestCore.Cull();
    }
    
    // Start sim
    return 0;
}

