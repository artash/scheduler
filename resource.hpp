/*
 * Resource.h
 *
 *  Created on: Jun 27, 2014
 *      Author: aaghajanyan
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <stdexcept>
#include <set>

/**
 * Resource is defined per the problem statement: it represents a computational resource that can be used by the
 * scheduler to execute jobs.
 */
class Resource
{
public:

	/**
	 * Default constructor for map subscript operator.
	 */
	Resource()
		: node(-1)
		, units(0)
	{
	}

	/**
	 * @param n node id
	 * @param u number of computing units
	 */
	Resource(int n, int u)
		: node(n)
		, units(u)
	{
	}

	int getNode() const
	{
		return node;
	}

	int getUnits() const
	{
		return units;
	}

	Resource& operator+=(const Resource& other)
	{
		if (node == -1 || node == other.node)
		{
			node = other.node;
			units += other.units;
			return *this;
		}
		throw std::invalid_argument("Invalid use of += operator. Attempt to assign to add units of different nodes.");
	}

private:
	int node;
	int units;
};

/**
 * We store resources in a set sorted by processing units available in ascending order. This simplifies job-to-node
 * matching.
 */
struct compute_unit_less
{
	bool operator()(const Resource& left, const Resource& right) const
	{
		return left.getUnits() < right.getUnits();
	}
};

typedef std::set<Resource, compute_unit_less> Resources;

#endif /* RESOURCE_H_ */
