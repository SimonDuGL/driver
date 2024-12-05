///////////////////////////////////////
// COMP/ELEC/MECH 450/550
// Project 3
// Authors: Connor Kelly, Simon (Guoliang Du)
//////////////////////////////////////

#ifndef RANDOM_TREE_H
#define RANDOM_TREE_H

//#include "ompl/datastructures/NearestNeighbors.h"
#include <vector>
#include "ompl/geometric/planners/PlannerIncludes.h"

namespace ompl
{
    namespace geometric
    {
        // TODO: Implement RTP as described

        class RTP : public base::Planner //inheritance   from   the   grandparent
        {
            

            public:
                
                /**  \brief Constructor */
                RTP(const base::SpaceInformationPtr &si);

                ~RTP() override; //destructor   ??   but   why   override

                void getPlannerData(base::PlannerData &data) const override;

                base::PlannerStatus solve(const base::PlannerTerminationCondition &ptc) override;

                void clear() override;



                /**  \brief Set the goal bias

                In the process of randomly selecting states in
                the state space to attempt to go towards, the
                algorithm may in fact choose the actual goal state, if
                it knows it, with some probability. This probability
                is a real number between 0.0 and 1.0; its value should
                usually be around 0.05 and should not be too large. It
                is probably a good idea to use the default value. */
                void setGoalBias(double goalBias)
                {
                    goalBias_ = goalBias;
                }

                /**  \brief Get the goal bias the planner is using */
                double getGoalBias() const
                {
                    return goalBias_;
                }

                                    /**    \brief   Set   the   range   the   planner   is   supposed   to   use.

                                                This   parameter   greatly   influences   the   runtime   of   the
                                                algorithm.   It   represents   the   maximum   length   of   a
                                                motion   to   be   added   in   the   tree   of   motions.   */
                                    void   setRange(double   distance)
                                    {
                                                maxDistance_   =   distance;
                                    }

                                    /**    \brief   Get   the   range   the   planner   is   using   */
                                    double   getRange()   const
                                    {
                                                return   maxDistance_;
                                    }


				    
            void setup() override;

            protected:
            /**  \brief Representation of a motion

                This only contains pointers to parent motions as we
                only need to go backwards in the tree. */
            class Motion
            {
            public:
                Motion() = default;

                /**  \brief Constructor that allocates memory for the state */
                Motion(const base::SpaceInformationPtr &si) : state(si->allocState())
                {
                }

                ~Motion() = default;

                /**  \brief The state contained by the motion */
                base::State * state{nullptr};

                /**  \brief The parent motion in the exploration tree */
                Motion * parent{nullptr};
            };

            /**  \brief Free the memory allocated by this planner */
            void freeMemory();
	    
            /**   \brief   A   tree   datastructure   containing   the   tree   of   motions   */
                                    std::shared_ptr<std::vector<Motion *>> tree;

            /**  \brief State sampler */
            base::StateSamplerPtr sampler_;

            /**  \brief The fraction of time the goal is picked as the state to expand towards (if such a state is
             *  available) */
            double goalBias_{.05};

                                    /**   \brief   The   maximum   length   of   a   motion   to   be   added   to   a   tree   */
                                    double   maxDistance_{0.};

            /**  \brief The random number generator */
            RNG rng_;

            /**  \brief The most recent goal motion.  Used for PlannerData computation */
            Motion * lastGoalMotion_{nullptr};

        };

    }  // namespace geometric
}  // namespace ompl

#endif
