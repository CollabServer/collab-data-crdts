#pragma once

#include "collab/CmRDT/LWWGraph.h"

#include <iostream>
#include <string>

namespace collab {
namespace CmRDT {


void LWWGraph_example() {
    std::cout << "\n----- CmRDT LWWGraph Example ----------\n";

    LWWGraph<std::string, int, int> data0;
    LWWGraph<std::string, int, int> data1;


    // User 0 creates 2 vertex and link v2 -> v1
    data0.addVertex("v1", 110);
    data0.addVertex("v2", 120);
    data0.addEdge("v1", "v2", 130);

    // User 1 creates 2 vertex and link v2 -> v1
    data1.addVertex("v1", 111);
    data1.addVertex("v2", 121);
    data1.addEdge("v1", "v2", 131);


    // Broadcast changes from 0 to 1
    data1.addVertex("v1", 110);
    data1.addVertex("v2", 120);
    data1.addEdge("v1", "v2", 130);

    // Broadcast changes from 1 to 0
    data0.addVertex("v1", 111);
    data0.addVertex("v2", 121);
    data0.addEdge("v1", "v2", 131);


    // At this point, user0 and user1 have actually the same graph.


    // User0 add vertex v3 + edge v2 -> v3
    data0.addEdge("v2", "v3", 140);

    // User1 remove vertex v1
    data1.removeVertex("v1", 151);


    // Broadcast changes
    data1.addEdge("v2", "v3", 140);
    data0.removeVertex("v1", 151);


    // At this point, user0 and user1 have the same graph.
    // RemoveVertex was later, so all edges with v2 are removed.


    // Final state
    std::cout << "data0 (at the end): " << data0 << "\n";
    std::cout << "data1 (at the end): " << data1 << "\n";

    std::cout << "(data0 == data1) = " << (data0 == data1);
    std::cout << " (true=" << true << ")\n";
    std::cout << "(data0 != data1) = " << (data0 != data1) << "\n";
}


}} // End namespace

