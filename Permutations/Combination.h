#pragma once

#include <vector>
#include <algorithm>
#include <tuple>


/* A class for storing a single unit of data */
class Cell {
public:
	explicit Cell(int& x);
	int GetVal() const;  //returns data from a single cell
	
private:
	int value_;
};

/* A class for storing a triple of nodes */
class Trio {
public:
	explicit Trio(const Cell& out, const Cell& self, const Cell& in);
		
	Cell GetCenter() const;  // returns the ñentral cell in the triple
	Cell GetOut() const;  // returns the outer cell in the triple
	Cell GetIn() const;  // returns the ñentral cell of the next triple in clockwise
	int GetSum() const;  // returns the sum of the triple
	
private:
	Cell out_, center_, inside_;
	int sum_;
};

/* A class for storing a combination of triples */
class Combination {
public:
	explicit Combination(int& n);
	
	void Push(const Trio& trio);  // adds a triple to the combination
	
	std::vector<Trio> GetComb_const() const;  // returns the current combination without changing it
	
	std::vector<Trio> GetComb();  // returns the current combination
	
	bool Is_minimal_comb();  // checks the minimum combination for the first element
	
private:
	int size_;
	std::vector<Trio> comb_;
};

std::ostream& operator << (std::ostream& os, const Cell& cell);

bool operator < (const Cell& c1, const Cell& c2);

std::ostream& operator << (std::ostream& os, const Trio& trio);

bool operator < (const Trio& t1, const Trio& t2);

std::ostream& operator << (std::ostream& os, const Combination& comb);
