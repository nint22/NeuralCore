NeuralCore
==========

A novel heuristic algorithm that uses both neural-networks and genetic-algorithms.

This code is just an initial test and sketch of ideas.


Todo
====

+ Change the simulation propagation from per-node to "source nodes to connected nodes" (though we may have to do some work with reverse-lookup because some inputs may not be touched, but should be active)
+ Implement culling to be based on path usage; the less used a path is, the more likely it may be thrown away during a breeding cycle
+ Implement the GA over-arching design
