#include "Combination.h"
#include <iostream>


Cell::Cell(int& x) : value_(x) {}
int Cell::GetVal() const { return value_; }


Trio::Trio(const Cell& out, const Cell& self, const Cell& in) :
  out_(out), center_(self), inside_(in), sum_(center_.GetVal() + out_.GetVal() + inside_.GetVal()) {}
	
Cell Trio::GetCenter() const { return center_; }
Cell Trio::GetOut() const { return out_; }
Cell Trio::GetIn() const { return inside_; }
int Trio::GetSum() const { return sum_; }


Combination::Combination(int& n) : size_(n) {}

void Combination::Push(const Trio& trio) {
	comb_.push_back(trio);
}

std::vector<Trio> Combination::GetComb_const() const { return comb_; }

std::vector<Trio> Combination::GetComb() { return comb_; }

bool Combination::Is_minimal_comb() {
	int comp = comb_[0].GetOut().GetVal();
	for(const Trio& t : comb_) {
		if (t.GetOut().GetVal() < comp)
		  return false;
	}
	return true;
}
	

std::ostream& operator << (std::ostream& os, const Cell& cell) {
	os << cell.GetVal();
	return os;
}

bool operator < (const Cell& c1, const Cell& c2) {
	return c1.GetVal() < c2.GetVal();
}

std::ostream& operator << (std::ostream& os, const Trio& trio) {
	os << trio.GetOut() << "," << trio.GetCenter() << "," << trio.GetIn() << "; ";
	return os;
}

bool operator < (const Trio& t1, const Trio& t2) {
	return std::vector<Cell>{t1.GetOut(), t1.GetCenter(), t1.GetIn()} <
         std::vector<Cell>{t2.GetOut(), t2.GetCenter(), t2.GetIn()};
}

std::ostream& operator << (std::ostream& os, const Combination& comb) {
	std::vector<Trio> trios = comb.GetComb_const();
	for (const Trio& trio : trios) {
		os << trio;
	}
	return os;
}
