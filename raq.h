#ifndef _RAQ_H
#define _RAQ_H

#include <vector>
#include <array>

// RAQ Class implements the Dynamic Programming solution

class RAQ {
 public:
  
  // Create the RAQ object; perform precomputation
  RAQ(std::vector<float> data);

  // ******************************************************
  // **
  // ** IF NEEDED (depends on class variables),
  // **   constructor, destructor, assignment operator
  // **   go here
  // **
  // ******************************************************

  // Query the RAQ for interval [i, j]
  float query(int i, int j) const;
  
  // Dump the RAQ data structure to stdout
  void dump() const;
  
 private:

  // ******************************************************
  // **
  // **  Define the class variables here
  // **
  // ******************************************************
	 std::vector<std::vector <float>> soln;
  // ******************************************************
  // **
  // ** Declare private helper functions here
  // **
  // ******************************************************  

};

// BlockRAQ class implements the Block Decomposition solution

class BlockRAQ {
public:
  // Create the BlockRAQ object; perform precomputation
  BlockRAQ(std::vector<float> data);

  // ******************************************************
  // **
  // ** IF NEEDED (depends on class variables),
  // **   constructor, destructor, assignment operator
  // **   go here
  // **
  // ******************************************************

  // Query the BlockRAQ for interval [i, j]
  float query(int i, int j) const;
  
  // Dump the BlockRAQ data structure to stdout
  void dump() const;
  
 private:
  
  // ******************************************************
  // **
  // **  Define the class variables here
  // **
  // ******************************************************
	 std::vector <float> soln;
	 int m_blockSize;
	 int m_blockNum;
	 int m_size;
  // ******************************************************
  // **
  // ** Declare private helper functions here
  // **
  // ******************************************************  
	 void setBSize(std::vector<float> data);
	 void setBNum(std::vector<float> data);
	 void setSize(std::vector<float> data);
};


#endif
