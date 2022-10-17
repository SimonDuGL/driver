///////////////////////////////////////
// COMP/ELEC/MECH 450/550
// Project 3
// Authors: Connor Kelly, Simon (Guoliang Du)
//////////////////////////////////////

#include "RTP.h"
#include <limits>
#include "ompl/base/goals/GoalSampleableRegion.h"
// often useful headers:
#include <ompl/util/RandomNumbers.h>
//#include "ompl/base/spaces/RealVectorStateSpace.h"
//RealVectorStateSpace
#include "ompl/tools/config/SelfConfig.h"




ompl::geometric::RTP::RTP(const base::SpaceInformationPtr &si) : base::Planner(si, "RTP")
{
// the specifications of this planner (ompl::base::PlannerSpecs)
    specs_.approximateSolutions = true;
    specs_.directed = true;

    Planner::declareParam<double>("range", this, &RTP::setRange, &RTP::getRange, "0.:1.:10000.");
    Planner::declareParam<double>("goal_bias", this, &RTP::setGoalBias, &RTP::getGoalBias, "0.:.05:1.");
    // Planner::declareParam<bool>("intermediate_states", this, &RRT::setIntermediateStates, &RRT::getIntermediateStates, "0,1");

    // addIntermediateStates_ = addIntermediateStates;
}




ompl::geometric::RTP::~RTP()
{
            // free any allocated memory
    freeMemory();
}


void ompl::geometric::RTP::clear()
{


    Planner::clear();
    sampler_.reset();
    freeMemory();
                // clear the data structures here
    // if (nn_)
    //     nn_->clear();
    if (tree) {
        tree->clear();
    }
    lastGoalMotion_ = nullptr;
}

// optional, if additional setup/configuration is needed, the setup() method can be implemented
void ompl::geometric::RTP::setup()
{
    Planner::setup();
 
            // perhaps attempt some auto-configuration
    tools::SelfConfig sc(si_, getName());
    // This RTP inherits from ompl::base::planner class
    // the planner class has a built-in function called "getName()"
    
    sc.configurePlannerRange(maxDistance_);

    // if (!nn_)
    //     nn_.reset(tools::SelfConfig::getDefaultNearestNeighbors<Motion *>(this));
    //if (!tree)
     //    tree_reset();
    
    // nn_->setDistanceFunction
    // 	(
    //		[this](const   Motion   *a,   const   Motion   *b)   
    //		{   
    //			return   distanceFunction(a,   b);   
    //		}
    //  );
}
/*void tree_reset()
{
as<RealVectorStateSpace::StateType>(0)->values[0];
}
*/
void ompl::geometric::RTP::freeMemory()
{
    if (tree)
    {
        //the tree information has already been stored in an arraylist(the root pointer) called tree, we do not need to creat a new list
        for (auto &motion : *tree)
        //meaning: for ( auto i = begin(*tree); i != end(*tree); ++i)
        {
        //besides:
	//  auto &motion = *i; // motion is a node on the tree, besides the node has some property (state)
            if (motion->state != nullptr)
                si_->freeState(motion->state);
            delete motion;
        }
    }
}




ompl::base::PlannerStatus ompl::geometric::RTP::solve(const base::PlannerTerminationCondition &ptc)
{
    //Todo: 
    // init tree vector
            // make sure the planner is configured correctly; ompl::base::Planner::checkValidity
            // ensures that there is at least one input state and a ompl::base::Goal object specified
    checkValidity();
    base::Goal *goal = pdef_->getGoal().get();
    // pdef_ is a field or memeber variable of planner class
    // it is about the problem defined by an user
                // get a handle to the Goal from the ompl::base::ProblemDefinition member, pdef_
    auto *goal_s = dynamic_cast<base::GoalSampleableRegion *>(goal);
    
            // get input states with PlannerInputStates helper, pis_
	        // initialize tree to start states
    while (const base::State *st = pis_.nextStart())
    //pis_ means PlannerInputStates, Utility class to extract valid input states

    {
                // st will contain a start state.  Typically this state will
                // be cloned here and inserted into the Planner's data structure.
        auto *motion = new Motion(si_);
        si_->copyState(motion->state, st);
        // nn_->add(motion);
        tree->push_back(motion);
    }
    
    
            // if needed, sample states from the goal region (and wait until a state is sampled)
            //const base::State *st = pis_.nextGoal(ptc);
            // or sample a new goal state only if available:
            //const base::State *st = pis_.nextGoal();
	    
	    
    // if init tree is empty, exit
    if (tree->size() == 0)
    {
        OMPL_ERROR("%s: There are no valid initial states!", getName().c_str());
        return base::PlannerStatus::INVALID_START;
    }

    if (!sampler_)
        sampler_ = si_->allocStateSampler();

    OMPL_INFORM("%s: Starting planning with %u states already in datastructure", getName().c_str(), tree->size());


    // ------------------------------------------------------------------------------------------

    Motion *solution = nullptr;
    Motion *approxsol = nullptr;
    double approxdif = std::numeric_limits<double>::infinity();
    auto *rmotion = new Motion(si_); //random node, could be the state of a node in the space, 
    base::State *rstate = rmotion->state;//
    //base::State *xstate = si_->allocState();// state of the intermediate node
	//nmotion is a tree node
	//dstate is originially for the state of the intermediate tree node, but
	//we do not need intermediate nodes, therefore dstate = rstate all the time in the algorithm
	//which means dstate is just the state of the random node above

            // periodically check if ptc() returns true.
            // if it does, terminate planning.
    while (!ptc)
    {
// TODO: Implement RTP as described
// 1. Select a random configuration qa from the existing Random tree.
// 2. Sample a random configuration qb from the configuration space. With a small probability, select the
// goal configuration as qb instead of a random one.
// 3. Check whether the straight-line path between qa and qb in the C-space is valid (i.e., collision free). If
// the path is valid, add the path from qa to qb to the tree.
// 4. Repeat steps 1 - 3 until the goal state is added to the tree. Extract the final motion plan from the tree

                // Start planning here.
 
                // call routines from SpaceInformation (si_) as needed. i.e.,
                // si_->allocStateSampler() for sampling,
                // si_->checkMotion(state1, state2) for state validity, etc...
 
                // use the Goal pointer to evaluate whether a sampled state satisfies the goal requirements
 
                // use log macros for informative messaging, i.e., logInfo("Planner found a solution!");
		
        // 1. Select a random configuration qa from the existing Random tree.
        
        /* find a random state in the tree */
        // pick an existing node from the tree
        Motion *nmotion = tree->at(rng_.uniformInt(0, tree->size() - 1));
        //base::State *stateNodePicked = nmotion->state;// the state of the existing tree node picked above
        base::State *dstate = rstate;// state of the random node


        // 2. Sample a random configuration qb from the configuration space. With a small probability, select the
        // goal configuration as qb instead of a random one.

        /* sample random state (with goal biasing) */
        if ((goal_s != nullptr) && rng_.uniform01() < goalBias_ && goal_s->canSample())
            goal_s->sampleGoal(rstate);
        else
            sampler_->sampleUniform(rstate);


        // 3. Check whether the straight-line path between qa and qb in the C-space is valid (i.e., collision free). If
        // the path is valid, add the path from qa to qb to the tree.

        /* find state to add */
        // double d = si_->distance(nmotion->state, rstate);
        // if (d > maxDistance_)
        // {
        //     si_->getStateSpace()->interpolate(nmotion->state, rstate, maxDistance_ / d, xstate);
        //     dstate = xstate;
        // }

        if (si_->checkMotion(nmotion->state, dstate))
        {

            auto *motion = new Motion(si_);
            si_->copyState(motion->state, dstate);// the random node becomes a new tree node 
            motion->parent = nmotion;
            tree->push_back(motion);

            nmotion = motion;


            // 4. Repeat steps 1 - 3 until the goal state is added to the tree. Extract the final motion plan from the tree
            double dist = 0.0;
            bool sat = goal->isSatisfied(nmotion->state, &dist);
            if (sat)
            {
                approxdif = dist;
                solution = nmotion;
                break;
            }
            if (dist < approxdif)
            {
                approxdif = dist;
                approxsol = nmotion;
            }
        }
    }


    // ------------------------------------------------------------------------------------------


    bool solved = false;
    bool approximate = false;
    if (solution == nullptr)
    {
        solution = approxsol;
        approximate = true;
    }

    if (solution != nullptr)
    {
        lastGoalMotion_ = solution;

        /* construct the solution path */
        std::vector<Motion *> mpath;
        while (solution != nullptr)
        {
            mpath.push_back(solution);
            solution = solution->parent;
        }

        /* set the solution path */
        auto path(std::make_shared<PathGeometric>(si_));
        for (int i = mpath.size() - 1; i >= 0; --i)
            path->append(mpath[i]->state);
	    
	                // When a solution path is computed, save it here
        pdef_->addSolutionPath(path, approximate, approxdif, getName());
        solved = true;
    }

    //si_->freeState(xstate);// state of the intermediate node
    if (rmotion->state != nullptr)
        si_->freeState(rmotion->state);
    delete rmotion;


    OMPL_INFORM("%s: Created %u states", getName().c_str(), tree->size());

    return {solved, approximate};
    
                // Return a value from the PlannerStatus enumeration.
            // See ompl::base::PlannerStatus for the possible return values
            //return base::PlannerStatus::EXACT_SOLUTION;

}


void ompl::geometric::RTP::getPlannerData(base::PlannerData &data) const
{
            // fill data with the states and edges that were created
            // in the exploration data structure
            // perhaps also fill control::PlannerData
    Planner::getPlannerData(data);

    if (lastGoalMotion_ != nullptr)
        data.addGoalVertex(base::PlannerDataVertex(lastGoalMotion_->state));

    for (auto &motion : *tree)
    {
        if (motion->parent == nullptr)
            data.addStartVertex(base::PlannerDataVertex(motion->state));
        else
            data.addEdge(base::PlannerDataVertex(motion->parent->state), base::PlannerDataVertex(motion->state));
    }
}
