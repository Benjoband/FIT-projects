/**
 * @author Alexej Beňuš <xbenus01@stud.fit.vut.cz>
 * @author Patrik Olszar <xolsza00@stud.fit.vut.cz>
 */

#include "memusage.h"
#include "search-strategies.h"
#include <algorithm>
#include <fstream>

using namespace std;

/**
 * @brief Check if state exists in visited states
 *
 * @param state The state to check
 * @param visitedStates Vector of visited states
 *
 * @return True if state exists in visited states, false otherwise
 */
bool stateExists(SearchState state, vector<SearchState> visitedStates)
{
    for (auto visitedState : visitedStates)
    {
        if (visitedState == state)
        {
            return true;
        }
    }
    return false;
}

bool operator==(const SearchState &a, const SearchState &b)
{
    return a.state_ == b.state_;
}

/**
 * @brief Breadth-first search
 *
 * @param init_state The initial state
 *
 * @return The solution
 */
vector<SearchAction> BreadthFirstSearch::solve(const SearchState &init_state)
{
    // Vector of pairs containing the state and the solution
    vector<pair<SearchState, vector<SearchAction>>> states = {
        make_pair(init_state, vector<SearchAction>())}; //
    vector<SearchState> visitedStates = {init_state};

    while (!states.empty())
    {
        // Check if memory limit has been reached (50MB reserved)
        if (getCurrentRSS() > mem_limit_ - (50 * 1024 * 1024))
        {
            cerr << "Memory limit reached, returing empty solution ("
                 << getCurrentRSS() << ")" << endl;
            break;
        }

        // Get the first state from the queue
        pair<SearchState, vector<SearchAction>> stateInfo(states.front());
        auto state = stateInfo.first;
        auto actions = state.actions();
        auto actionsCount = actions.size();

        // If there are no actions, continue to the next state
        if (actionsCount == 0)
        {
            continue;
        }

        // Check all possible actions
        for (unsigned i = 0; i < actionsCount; i++)
        {
            SearchState newState = actions[i].execute(state);
            // If the new state has not been visited yet
            if (!stateExists(newState, visitedStates))
            {
                vector<SearchAction> newSolution = stateInfo.second;
                newSolution.push_back(actions[i]);
                // If the new state is final, return the solution
                if (newState.isFinal())
                {
                    cout << "Solution found" << endl;
                    return newSolution;
                }
                visitedStates.push_back(newState);
                states.push_back(make_pair(newState, newSolution));
            }
        }
    }
    cout << "No solution found" << endl;
    return {};
}

/**
 * @brief Depth-first search
 *
 * @param init_state The initial state
 *
 * @return The solution
 */
vector<SearchAction> DepthFirstSearch::solve(const SearchState &init_state)
{
    // Tuple containing the state, the solution and the number of used actions
    vector<tuple<SearchState, vector<SearchAction>, unsigned>> statesInfo = {
        make_tuple(init_state, vector<SearchAction>(), 0)};

    vector<SearchState> visitedStates = {init_state};
    unsigned maxDepth = depth_limit_;

    while (!statesInfo.empty())
    {
        // Check if memory limit has been reached (50MB reserved)
        if (getCurrentRSS() > mem_limit_ - (50 * 1024 * 1024))
        {
            cerr << "Memory limit reached, returing empty solution ("
                 << getCurrentRSS() << ")" << endl;
            break;
        }

        auto &stateInfo = statesInfo.back();
        auto newSolution = get<1>(stateInfo);
        auto state = get<0>(stateInfo);
        auto actions = state.actions();
        auto *usedActions = &get<2>(stateInfo);
        auto actionsCount = actions.size();

        // If there are no actions or all actions have been used, continue to
        // the next state
        if (actionsCount == 0 || *usedActions == actionsCount)
        {
            statesInfo.pop_back();
            continue;
        }

        // Find first not visited state
        for (auto i = 0 + *usedActions; i < actionsCount; i++)
        {
            newSolution.push_back(actions[i]);

            SearchState newState = actions[i].execute(state);

            if (!stateExists(newState, visitedStates))
            {
                // If the new state is final, return the solution
                if (newState.isFinal())
                {
                    cout << "Solution found" << endl;
                    return newSolution;
                }
                visitedStates.push_back(newState);
                // If the solution is not at the maximum depth, add the new
                // state to the stack
                if (newSolution.size() != maxDepth)
                {
                    (*usedActions)++;
                    statesInfo.push_back(make_tuple(newState, newSolution, 0));
                    break;
                }
            }

            (*usedActions)++;
            newSolution.pop_back();
        }

        // If all actions have been used, remove the state from the stack
        if (*usedActions == actionsCount)
        {
            statesInfo.pop_back();
        }
    }
    cout << "No solution found" << endl;
    return {};
}

double StudentHeuristic::distanceLowerBound(const GameState &state) const
{
    return 0;
}

/**
 * @brief Check if state is in closed states
 *
 * @param state The state to check
 * @param closed Vector of closed states
 *
 * @return True if state is in closed states, false otherwise
 */
bool isClosed(const SearchState *state,
              const vector<const SearchState *> &closed)
{
    for (const auto &closedState : closed)
    {
        if (*state == *closedState)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Stable sort open states by f
 *
 * @param open The open list
 */
void sort(
    vector<tuple<const SearchState *, double, vector<const SearchState *>>>
        &open)
{
    stable_sort(open.begin(), open.end(),
                [](const auto &a, const auto &b)
                {
                    return get<1>(a) <
                           get<1>(b); // Compare the second element (cost)
                });
}

/**
 * @brief Reconstruct the path from the first entry in the open list
 *
 * @param open The open list
 *
 * @return The path to the solution
 *
 * @note Not the best solution that could be implemented, but it works and is
 * only called once, so not that bad
 */
vector<SearchAction> reconstructPath(
    const vector<
        tuple<const SearchState *, double, vector<const SearchState *>>> &open)
{
    vector<SearchAction> solution;

    // Get the path from the first entry in the open list
    const auto &path = get<2>(open[0]);

    // Iterate through consecutive pairs of states in the path
    for (size_t i = 1; i < path.size(); ++i)
    {
        const SearchState *prevState = path[i - 1];
        const SearchState *currState = path[i];

        // Find the action that transitions from prevState to currState
        bool foundAction = false;
        for (const auto &action : prevState->actions())
        {
            if (action.execute(*prevState) == *currState)
            {
                solution.push_back(action); // Add action to solution
                foundAction = true;
                break;
            }
        }

        if (!foundAction)
        {
            cerr << "Error: No valid action found between states in the path"
                 << endl;
            return {};
        }
    }

    return solution;
}

/**
 * @brief Compute the heuristic value for a state
 *
 * @param init_state The state to compute the heuristic for
 *
 * @return Path to the solution
 */
vector<SearchAction> AStarSearch::solve(const SearchState &init_state)
{
    const SearchState *working_state =
        &init_state; // first state (as a pointer)
    vector<tuple<const SearchState *, double, vector<const SearchState *>>>
        open = {make_tuple(
            working_state, 0,
            vector<const SearchState *>{working_state})}; // open list
    vector<const SearchState *> closed;                   // closed list

    while (!working_state
                ->isFinal()) // go through states until final state is reached
    {
        if (getCurrentRSS() > mem_limit_ - (50 * 1024 * 1024))
        {
            cout << "Memory limit reached, returing empty solution ("
                 << getCurrentRSS() << ")" << endl;
            break;
        }
        if (open.empty())
        {
            return {};
        }

        // Extract the first state from open
        auto [state, price, path] = open[0];
        vector<SearchAction> actions = working_state->actions();
        for (const auto &action : actions) // go through actions
        {
            const SearchState *newState =
                new SearchState(action.execute(*working_state));

            if (isClosed(newState, closed))
            {
                delete newState; // Clean up dynamically allocated state
                continue;
            }

            // Compute new values
            vector<const SearchState *> newPath = path;
            newPath.push_back(newState);
            double heuristic = compute_heuristic(*newState, *heuristic_);
            double f = newPath.size() + heuristic;
            bool isOpenBool = false;
            for (auto &openState : open) // check if state is already in open
            {
                if (*get<0>(openState) == *newState)
                {
                    if (get<1>(openState) > f) // Update the state if f is lower
                    {
                        get<1>(openState) = f;
                        get<2>(openState) = newPath;
                    }
                    delete newState;
                    isOpenBool = true;
                    break;
                }
            }
            if (!isOpenBool) // Add new state to open if it is not already there
            {
                open.push_back(make_tuple(newState, f, newPath));
            }
        }

        // Clean up the working state and move it to closed
        open.erase(open.begin());
        closed.push_back(working_state);

        sort(open); // Sort open states by f

        working_state = get<0>(open[0]); // Update working_state
    }

    bool foundSolution = false;
    vector<SearchAction> solution; // vector for path to solution

    if (working_state->isFinal()) // found solution, reconstruct path
    {
        foundSolution = true;
        solution = reconstructPath(open);
    }

    // Clean up dynamically allocated states
    for (auto &entry : open)
    {
        delete get<0>(entry);
    }
    for (const auto &state : closed)
    {
        if (state != &init_state)
        {
            delete state;
        }
    }

    if (foundSolution)
        return solution;
    else
        return {};
}
