// Scaffold.cpp
#include "provided.h"
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels); 
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const; 
    void display() const; 
    bool makeMove(int column, int color); 
    int undoMove(); 
private:
	int m_cols;
	int m_levels;
	stack<int> moves;
	vector<vector<int>> grid;
	
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
 : m_cols(nColumns), m_levels(nLevels)
{
	if (nColumns <= 0 || nLevels <= 0)
		exit(1);
	grid.resize(nColumns); // initialize grid
	for (int i = 1; i < nColumns; i++)
		grid[i].resize(nLevels);

	
	for (int i = 1; i < nColumns; i++)
		for (int j = 1; j < nLevels; j++)
			grid[i][j] == VACANT; // set all values in grid to vacant. this will be changed when we make a move // do i need to do this? I don't think so.
}

int ScaffoldImpl::cols() const
{
    return m_cols;  
}

int ScaffoldImpl::levels() const
{
    return m_levels;  
}

int ScaffoldImpl::numberEmpty() const
{
	int n = 0;
	for (int i = 1; i < m_cols; i++)
	{
		for (int j = 1; j < m_levels; j++)
		{
			if (checkerAt(i, j) == VACANT)
				n++;
		}
	}
	return n;  
}

int ScaffoldImpl::checkerAt(int column, int level) const // done
{
	if (grid[column][level] == RED)
		return RED;
	else if (grid[column][level] == BLACK) 
		return BLACK;
	return VACANT; 
}

void ScaffoldImpl::display() const // not finished
{
	for (int i = 1; i < m_cols; i++)
	{
		for (int j = m_levels; j > 1; j--)
		{
			cout << "|";
			if (checkerAt(i, j) == RED)
				cout << "R";
			else if (checkerAt(i, j) == BLACK)
				cout << "B";
			else
				cout << " ";
		}
		cout << "|" << endl;
	}
	for (int k = 1; k < m_cols; k++)
		cout << "+-";
	cout << "+";
}

bool ScaffoldImpl::makeMove(int column, int color)
{
	if (column > m_cols || column <= 0 || color != RED || color != BLACK )
		return false;  //  out of bounds or color isn't a valid input
	if (checkerAt(column, m_levels) != VACANT) // there is no space in the column, we cannot use this
		return false;
	int i = 1;
	for (; i < m_levels; i++) // parse through until we are at the location we want to drop a move
	{
		if (checkerAt(column, i) == VACANT)
			break;
	}
	grid[column][i] = color;
	moves.push(column); // we made a move, so we add it to the stack of moves made. 
	//we record the column it is dropped in.
	return true;
}

int ScaffoldImpl::undoMove() // we need to grab the last changed element in the vector.
{
	int lastCol = moves.top();
	moves.pop();
	int i = 1;
	for (; i < m_levels; i++) // parse through until we are at the location we want to erase the move
	{
		if (checkerAt(lastCol, i+1) == VACANT)
			break;
	}
	grid[lastCol][i] = VACANT;
	return lastCol;


}

//******************** Scaffold functions *******************************

// These functions simply delegate to ScaffoldImpl's functions.
// You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
