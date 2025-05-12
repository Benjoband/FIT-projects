/**
 * @file main.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Parallel algorithm for computing the levels of a tree using MPI.
 * @version 1.0
 * @date 2025-05-04
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <mpi.h>
#include <vector>

using namespace std;

// Toggle debug prints
#define DEBUG 0

/**
 * @brief Represents the node in tree, with indexes to its children in node vector
 */
struct Node
{
        char name;
        int parent;
        int left;
        int right;
};

/**
 * @brief Represents the edge between nodes
 */
struct Edge
{
        int id;
        int from;
        int to;
        int weight;
};

/**
 * @brief Returns the edge ID for a given edge (u, v) in the edges vector.
 *
 * @param u
 * @param v
 * @param edges
 * @return int
 */
int findEdgeId(int u, int v, const vector<Edge> &edges)
{
    for (const auto &edge : edges)
    {
        if (edge.from == u && edge.to == v)
        {
            return edge.id;
        }
    }
    return -1; // Not found
}

/**
 * @brief Function for main process to build the tree structure.
 *
 * @param input input string representing the tree
 * @param nodes vector of nodes to be filled
 */
void buildTree(const string &input, vector<Node> &nodes)
{
    int n = input.size();
    nodes.resize(n);

    for (int i = 0; i < n; ++i)
    {
        nodes[i].name = input[i];
        nodes[i].parent = -1;
        nodes[i].left = -1;
        nodes[i].right = -1;
    }

    for (int i = 0; i < n; ++i)
    {
        if (2 * i + 1 < n)
        {
            nodes[i].left = 2 * i + 1;
            nodes[2 * i + 1].parent = i;
        }
        if (2 * i + 2 < n)
        {
            nodes[i].right = 2 * i + 2;
            nodes[2 * i + 2].parent = i;
        }
    }
}

/**
 * @brief Builds the edges of the tree in a depth-first manner.
 *
 * @param nodes
 * @param u
 * @param edges
 * @param adjacency_list
 * @param edge_id
 */
void buildEdges(const vector<Node> &nodes, int u, vector<Edge> &edges,
                vector<vector<int>> &adjacency_list, int &edge_id)
{
    if (u == -1)
        return;

    if (nodes[u].left != -1) // Check if left child exists
    {
        edges[edge_id++] = {edge_id - 1, u, nodes[u].left, -1}; // forward = -1
        adjacency_list[u].push_back(nodes[u].left);

        buildEdges(nodes, nodes[u].left, edges, adjacency_list, edge_id);

        // Backward edge from left child to parent
        edges[edge_id++] = {edge_id - 1, nodes[u].left, u, +1}; // backward = +1
        adjacency_list[nodes[u].left].push_back(u);
    }

    if (nodes[u].right != -1) // Check if right child exists
    {
        edges[edge_id++] = {edge_id - 1, u, nodes[u].right, -1}; // forward = -1
        adjacency_list[u].push_back(nodes[u].right);

        buildEdges(nodes, nodes[u].right, edges, adjacency_list, edge_id);

        // Backward edge from right child to parent
        edges[edge_id++] = {edge_id - 1, nodes[u].right, u, +1}; // backward = +1
        adjacency_list[nodes[u].right].push_back(u);
    }
}

/**
 * @brief Initializes the tree structure and builds the edges. Then broadcasts the data to all
 * processes.
 *
 * @param input input string
 * @param nodes vector of nodes
 * @param edges vector of edges
 * @param adjacency_list adjacency list of the tree
 * @param flat_adj_list flattened adjacency list
 * @param offsets offsets for the flattened adjacency list
 * @param node_count number of nodes
 * @param edge_count number of edges
 * @param world_rank rank of the current process
 */
void initialize(const string &input, vector<Node> &nodes, vector<Edge> &edges,
                vector<vector<int>> &adjacency_list, vector<int> &flat_adj_list,
                vector<int> &offsets, int &node_count, int &edge_count, int world_rank)
{
    int n = input.length();
    int expected_edges = 2 * (n - 1);

    if (world_rank == 0)
    {
        node_count = n;
        edge_count = expected_edges;

        // Build tree
        buildTree(input, nodes);

        int edge_id = 0;
        edges.resize(2 * (n - 1));
        adjacency_list.resize(n);

        buildEdges(nodes, 0, edges, adjacency_list, edge_id);

        // Flatten adjacency list, better for parallel broadcast
        for (int i = 0; i < node_count; ++i)
        {
            offsets.push_back(flat_adj_list.size());
            for (int neighbor : adjacency_list[i])
            {
                flat_adj_list.push_back(neighbor);
            }
        }
        offsets.push_back(flat_adj_list.size());
    }

    // Broadcast basic sizes
    MPI_Bcast(&node_count, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&edge_count, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Resize on non-root
    if (world_rank != 0)
    {
        nodes.resize(node_count);
        edges.resize(edge_count);
    }

    // Broadcast actual data
    MPI_Bcast(nodes.data(), node_count * sizeof(Node), MPI_BYTE, 0, MPI_COMM_WORLD);
    MPI_Bcast(edges.data(), edge_count * sizeof(Edge), MPI_BYTE, 0, MPI_COMM_WORLD);

    // Broadcast flattened adjacency list
    int flat_size;
    if (world_rank == 0)
        flat_size = flat_adj_list.size();

    MPI_Bcast(&flat_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank != 0)
    {
        flat_adj_list.resize(flat_size);
        offsets.resize(node_count + 1);
    }

    MPI_Bcast(flat_adj_list.data(), flat_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(offsets.data(), node_count + 1, MPI_INT, 0, MPI_COMM_WORLD);
}

/**
 * @brief Does a parallel build of the Etour array.
 *
 * @param edges
 * @param flat_adj_list
 * @param offsets
 * @param world_rank
 * @param world_size
 * @param etour
 */
void buildEtourParallel(const vector<Edge> &edges, const vector<int> &flat_adj_list,
                        const vector<int> &offsets, int world_rank, int world_size,
                        vector<int> &etour)
{
    Edge myEdge = edges[world_rank];
    int u = myEdge.from;
    int v = myEdge.to;

    int reverse_from = v;
    int reverse_to = u;

    int mySuccessor = -1;

    int start = offsets[reverse_from];
    int end = offsets[reverse_from + 1];

    bool found = false;
    for (int i = start; i < end; ++i)
    {
        if (flat_adj_list[i] == reverse_to)
        {
            if (i + 1 < end)
            {
                int next_neighbor = flat_adj_list[i + 1];
                mySuccessor = findEdgeId(reverse_from, next_neighbor, edges);
                found = true;
            }
            break;
        }
    }

    if (!found)
    {
        int start_v = offsets[v];
        int end_v = offsets[v + 1];
        if (start_v < end_v)
        {
            int first_neighbor = flat_adj_list[start_v];
            mySuccessor = findEdgeId(v, first_neighbor, edges);
        }
        else
        {
            mySuccessor = -1; // No successor
        }
    }
    if (v == 0 && myEdge.weight == +1)
    {
        mySuccessor = -1;
    }

    etour[world_rank] = mySuccessor;
}

/**
 * @brief Parallel suffix sum computation.
 *
 * @param myOriginalWeight
 * @param mySuffixSum
 * @param mySucc
 * @param world_rank
 * @param world_size
 */
void parallelSuffixSum(int myOriginalWeight, int &mySuffixSum, int mySucc, int world_rank,
                       int world_size)
{
    mySuffixSum = myOriginalWeight;
    int succ = mySucc;

    vector<int> allSuffixSums(world_size, 0);
    vector<int> allSuccessors(world_size, -1);

    int log_p = ceil(log2(world_size));
    for (int k = 0; k < log_p; ++k)
    {
        // Gather all suffix sums and successors
        MPI_Allgather(&mySuffixSum, 1, MPI_INT, allSuffixSums.data(), 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Allgather(&succ, 1, MPI_INT, allSuccessors.data(), 1, MPI_INT, MPI_COMM_WORLD);

        if (succ != -1)
        {
            mySuffixSum += allSuffixSums[succ];
            succ = allSuccessors[succ];
        }

        MPI_Barrier(MPI_COMM_WORLD);
    }
}

/**
 * @brief Computes the levels of nodes in parallel.
 *
 * @param nodes all nodes
 * @param edges all edges
 * @param mySuffixSum suffix sum of the current node
 * @param world_rank process rank
 * @param world_size number of processes
 * @param finalLevels array to store the final levels
 */
void computeLevelsParallel(const vector<Node> &nodes, const vector<Edge> &edges, int mySuffixSum,
                           int world_rank, int world_size, vector<int> &finalLevels)
{
    int node_count = nodes.size();

    int myNode = -1;
    int myLevel = -1;

    Edge myEdge = edges[world_rank];
    if (myEdge.weight == -1)
    {
        myNode = myEdge.to;
        myLevel = mySuffixSum + 1;
    }

    vector<int> gatheredNodes(world_size, -1);
    vector<int> gatheredLevels(world_size, -1);

    MPI_Gather(&myNode, 1, MPI_INT, gatheredNodes.data(), 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Gather(&myLevel, 1, MPI_INT, gatheredLevels.data(), 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank == 0) // root process writes the final levels
    {
        finalLevels.resize(node_count, -1);

        finalLevels[0] = 0; // root node

        for (int i = 0; i < world_size; ++i)
        {
            if (gatheredNodes[i] != -1)
            {
                finalLevels[gatheredNodes[i]] = gatheredLevels[i];
            }
        }
    }
}

/**
 * @brief Prints the levels of nodes in the assigned format.
 *
 * @param nodes Nodes of the tree
 * @param levels Levels of the nodes
 */
void printLevels(const vector<Node> &nodes, const vector<int> &levels)
{
    int node_count = nodes.size();
    cout << nodes[0].name << ":" << levels[0];
    for (int i = 1; i < node_count; ++i)
    {
        cout << "," << nodes[i].name << ":" << levels[i];
    }
    cout << endl;
}

/**
 * @brief Main function to initialize MPI and run the parallel algorithm.
 *
 * @param argc argument count
 * @param argv argument array
 * @return int
 */
int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (argc < 2) // check for input string of nodes
    {
        if (world_rank == 0)
            cerr << "Usage: " << argv[0] << " <input_string>" << endl;
        MPI_Finalize();
        return 1;
    }

    string input = argv[1]; // just for initialization

    if (input.length() == 1) // edge case for a single node
    {
        if (world_rank == 0)
        {
            cout << input[0] << ":0" << endl;
        }
        MPI_Finalize();
        return 0;
    }

    vector<Node> nodes;                 // All nodes
    vector<Edge> edges;                 // All edges
    vector<vector<int>> adjacency_list; // Only used by Rank 0
    vector<int> flat_adj_list;          // Flattened adjacency list
    vector<int> offsets;                // Offsets in flat list
    int node_count, edge_count;         // Number of nodes and edges

    // Initialize the tree structure and build edges
    initialize(input, nodes, edges, adjacency_list, flat_adj_list, offsets, node_count, edge_count,
               world_rank);

    // Build the Etour vector
    vector<int> etour(edge_count, -1);
    buildEtourParallel(edges, flat_adj_list, offsets, world_rank, world_size, etour);

    int myOriginalWeight =
        (edges[world_rank].weight == -1) ? -1 : +1; // -1 for backward, +1 for forward
    int next_edge_id = etour[world_rank];           // successor in the Etour array

    if (DEBUG)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        cout << "Rank " << world_rank << ": owns edge (" << nodes[edges[world_rank].from].name
             << " -> " << nodes[edges[world_rank].to].name
             << "), Original Weight = " << myOriginalWeight
             << ", Etour successor = " << next_edge_id << endl;
        MPI_Barrier(MPI_COMM_WORLD);
    }

    // Compute the suffix sum in parallel
    int mySuffixSum = 0;
    parallelSuffixSum(myOriginalWeight, mySuffixSum, next_edge_id, world_rank, world_size);

    if (DEBUG)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        cout << "Rank " << world_rank << ": Final Suffix Sum = " << mySuffixSum << endl;
        MPI_Barrier(MPI_COMM_WORLD);
    }

    // Compute the levels of nodes in parallel
    vector<int> finalLevels;
    computeLevelsParallel(nodes, edges, mySuffixSum, world_rank, world_size, finalLevels);

    if (DEBUG)
    {
        Edge myEdge = edges[world_rank];
        if (myEdge.weight == -1)
        {
            cout << "Rank " << world_rank << ": Computed level for node " << nodes[myEdge.to].name
                 << " = " << (mySuffixSum + 1) << endl;
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    if (world_rank == 0)
    {
        printLevels(nodes, finalLevels);
    }

    MPI_Finalize();
    return 0;
}