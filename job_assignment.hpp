/*
 * action.hpp
 *
 *  Created on: Jun 27, 2014
 *      Author: aaghajanyan
 */

#ifndef JOBASSIGNMENT_HPP_
#define JOBASSIGNMENT_HPP_

#include <ostream>

/**
 * JobAssignment is a Job assigned to a specific node. It represents a scheduler's decision to execute a given job
 * on a given node.
 */
class JobAssignment {
public:
	// a no-op assignment
	JobAssignment()
	: nodeId(-1)
	, jobId(-1)
	, units(-1)
	{

	}

	JobAssignment(int nodeId_, int jobId_, int units_)
		: nodeId(nodeId_)
		, jobId(jobId_)
		, units(units_)
	{

	}

	bool isNoOp() const
	{
		return nodeId == -1;
	}

	int getNodeId() const
	{
		return nodeId;
	}
	int getJobId() const
	{
		return jobId;
	}
	int getUnits() const
	{
		return units;
	}

private:
	int nodeId;
	int jobId;

	// we redundantly store units here for convenience
	int units;

};

inline std::ostream& operator<<(std::ostream& os, const JobAssignment& ja)
{
	os << "[jobId=" << ja.getJobId() << ", nodeId=" << ja.getNodeId() << ", units=" << ja.getUnits() << "]";
	return os;
}

#endif /* JOBASSIGNMENT_HPP_ */
