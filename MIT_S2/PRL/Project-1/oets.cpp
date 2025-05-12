/**
 * @file oets.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Implementation of PRL 1st project
 * @version 1.0
 * @date 2025-04-02
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "mpi.h"    // MPI header
#include <cstdint>  // uint8_t
#include <fstream>  // working with file
#include <iostream> // cout
#include <vector>   // vector for storing the array of numbers

using namespace std;

/**
 * @brief Loads file with 8-bit numbers into a vector.
 *
 * @param numbers vector to store the numbers
 * @return int 0 on success, -1 on failure
 */
int loadFile(vector<uint8_t> &numbers)
{
    ifstream file;
    file.open("numbers", ios::binary | ios::in);
    if (!file.is_open())
    {
        cerr << "Error: Could not open the file." << "\n";
        return -1;
    }
    uint8_t byte;
    while (file.read(reinterpret_cast<char *>(&byte), sizeof(byte)))
    {
        numbers.push_back(byte);
    }
    file.close();
    return 0;
}

/**
 * @brief Computes partner rank for the given rank and counter(Odd/Even).
 *
 * @param rank cpu rank
 * @param size number of cpus
 * @param counter odd/even phase of algorithm
 * @return int -1 if no partner, otherwise the rank of the partner
 */
int partnerRank(int rank, int size, int counter)
{
    if (counter % 2 == 0) // checks if phase is even
    {
        if (rank % 2 == 0 && rank + 1 < size) // checks if rank is even and if there is a partner
            return rank + 1;
        else if (rank % 2 == 1 && rank - 1 >= 0) // checks if rank is odd and if there is a partner
            return rank - 1;
    }
    else // checks if phase is odd
    {
        if (rank % 2 == 0 && rank - 1 >= 0) // checks if rank is even and if there is a partner
            return rank - 1;
        else if (rank % 2 == 1 &&
                 rank + 1 < size) // checks if rank is odd and if there is a partner
            return rank + 1;
    }
    return -1; // No partner
}

/**
 * @brief Changes processors number with partner if needed.
 *
 * @param myRank cpu rank
 * @param pRank partners rank
 * @param myNumber cpu number
 * @param partnerNumber partners number
 */
void bubble(int myRank, int pRank, uint8_t &myNumber, uint8_t &partnerNumber)
{
    if (myRank < pRank)
    {
        if (myNumber > partnerNumber)
        {
            myNumber = partnerNumber;
        }
    }
    else
    {
        if (myNumber < partnerNumber)
        {
            myNumber = partnerNumber;
        }
    }
}

/**
 * @brief Odd-Even Transposition sort algorithm.
 *
 * @param numbers array of numbers
 * @param myRank processor rank
 * @param size number of processors
 * @return vector<uint8_t> returns sorted array
 */
vector<uint8_t> oddEvenTransposition(vector<uint8_t> &numbers, int myRank, int size)
{
    int n = numbers.size();
    uint8_t myNumber = numbers[myRank];

    for (int counter = 0; counter < n; counter++)
    {
        int pRank = partnerRank(myRank, size, counter);
        if (pRank != -1)
        {
            uint8_t partnerNumber;
            MPI_Sendrecv(&myNumber, 1, MPI_UINT8_T, pRank, 0, &partnerNumber, 1, MPI_UINT8_T, pRank,
                         0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Send and receive numbers
            bubble(myRank, pRank, myNumber, partnerNumber);     // Swap numbers if needed
        }
    }
    vector<uint8_t> sorted_numbers;
    if (myRank == 0)
    {
        sorted_numbers.resize(n);
    }
    MPI_Gather(&myNumber, 1, MPI_UINT8_T, sorted_numbers.data(), 1, MPI_UINT8_T, 0, MPI_COMM_WORLD);

    if (myRank == 0)
    {
        return sorted_numbers;
    }
    else
    {
        return {}; // Return an empty vector for non-root ranks
    }
}

/**
 * @brief Prints the summary of the numbers according to the task.
 *
 * @param numbers array before sort
 * @param sortedNumbers array after sort
 */
void summary(vector<uint8_t> numbers, vector<uint8_t> sortedNumbers)
{
    for (auto num : numbers)
    {
        cout << (int)num << " ";
    }
    cout << "\n";
    for (auto num : sortedNumbers)
    {
        cout << (int)num << "\n";
    }
}

/**
 * @brief Initializes MPI, loads file with numbers, and calls the odd-even transposition sort.
 *
 * @param argc command line argument count
 * @param argv command line arguments
 * @return int 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
    int rank, size;
    vector<uint8_t> numbers;
    vector<uint8_t> sortedNumbers;

    if (loadFile(numbers) != 0)
    {
        return 1;
    }
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    sortedNumbers = oddEvenTransposition(numbers, rank, size);
    if (rank == 0)
    {
        summary(numbers, sortedNumbers);
    }
    MPI_Finalize();
    return 0;
}