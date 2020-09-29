#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include "raq.h"

//RAQ calculation and printing
RAQ::RAQ(std::vector<float> data)
{
	for (int i = 0; i < data.size(); i++)
	{
		std::vector<float> solnArr;
		solnArr.push_back(data[i]);

		if (i < data.size() - 1)
		{
			for (int j = i; j < data.size() - 1; j++)
			{
				//calc what to put into soln vector
				float addToSoln = (1.0 / (j - i + 2)) * ((j - i + 1) * solnArr.back() + data[j + 1]);
				solnArr.push_back(addToSoln);
			}
		}
		soln.push_back(solnArr);
	}
}

float RAQ::query(int i, int j) const
{
	return soln[i][j - i];
}

void RAQ::dump() const
{
	for (int i = 0; i < soln.size(); i++)
	{
		for (int j = 0; j < soln.size() - i; j++)
		{
			std::cout.width(9); std::cout << std::left << soln[i][j];
		}
		std::cout << std::endl;
	}
}

//BlockRAQ and printing
BlockRAQ::BlockRAQ(std::vector<float> data)
{
	setBSize(data);
	setBNum(data);
	setSize(data);
	bool keepGoing = true;
	int blockNum = 0;
	soln = data;

	while (keepGoing)
	{
		float tempAdd = 0;
		float addToSoln = 0;

		for (int i = blockNum; i < (m_blockSize + blockNum); i++)
		{
			//calc what to put into soln vector
			tempAdd += data[i];
		}
		addToSoln = tempAdd / m_blockSize;
		soln.push_back(addToSoln);
		blockNum += m_blockSize;

		//in the case that the last block is smaller than the other block sizes
		if (data.size() - blockNum < m_blockSize)
		{
			for (int i = 0 + blockNum; i < data.size(); i++)
			{
				//calc what to put into soln vector
				tempAdd += data[i];
			}
			addToSoln = tempAdd / m_blockSize;
			soln.push_back(addToSoln);
			keepGoing = false;
		}
		else if (blockNum == data.size())
		{
			keepGoing = false;
		}
	}
}

float BlockRAQ::query(int i, int j) const
{
	//calculate how far i and j are from a block
	int distToBlock = 0;
	for (int o = 0; o < m_blockSize; o++)
	{
		if ((i + o) % m_blockSize == 0)
		{
			distToBlock = o;
		}
	}
	int distFromBlock = (j + 1) % m_blockSize;

	//calculate how many precomuted blocks are used
	int numBlocks = ((j - distFromBlock) - (i + distToBlock) + 1) / m_blockSize; 

	//calculate how much to add before the first block
	float tempAddF = 0;
	for (int k = 0; k < distToBlock; k++)
	{
		tempAddF += soln[i + k];
	}

	//calculate the amount to add to the back of the last full block
	float tempAddB = 0;
	for (int l = 0; l < distFromBlock; l++)
	{
		tempAddB += soln[j - l];
	}

	//if there is at least one full block, this calculates which blocks are used 
	int whichBlock = 0;
	if (numBlocks != 0)
	{
		for (int p = 0; p < m_blockNum; p++)
		{
			if (p * m_blockSize == i + distToBlock)
			{
				whichBlock = p;
			}
		}
	}

	//calculates the sum of the blocks averages
	float tempAddBlocks = 0;
	for (int m = 0; m < numBlocks; m++)
	{
		tempAddBlocks += (m_blockSize * soln[m_size + whichBlock + m]);
	}


	float ave = 0;
	//no full blocks
	if (j - i <= m_blockSize)
	{
		float tempAddX = 0;
		for (int n = i; n <= j; n++)
		{
			tempAddX += soln[n];
		}
		ave = tempAddX / (j - i + 1);
	}
	//at least one full block
	else
	{
		ave = (tempAddF + tempAddBlocks + tempAddB) / (j - i + 1);
	}

	return ave;
}

void BlockRAQ::dump() const
{
	std::cout << "Num Blocks: " << m_blockNum << std::endl;
	std::cout << "Block Size: " << m_blockSize << std::endl;
	std::cout << "Block averages:" << std::endl;

	for (int i = m_size; i < m_size + m_blockNum; i++)
	{
		std::cout.width(6); std::cout << soln[i];
	}
	std::cout << "\n\n";
}

void BlockRAQ::setBSize(std::vector<float> data)
{
	m_blockSize = sqrt(data.size());
}

void BlockRAQ::setBNum(std::vector<float> data)
{
	if (data.size() % m_blockSize == 0)
	{
		m_blockNum = data.size() / m_blockSize;
	}
	else
	{
		m_blockNum = data.size() / m_blockSize + 1;
	}
}

void BlockRAQ::setSize(std::vector<float> data)
{
	m_size = data.size();
}