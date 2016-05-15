// Player.cpp

#include "provided.h"
#include <string>
#include <iostream>
using namespace std;

class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
	cout << "Make your move (Choose the column number, Left to right increasing): ";
	int move;
	cin >> move;
	cout << endl;
	while (move < 1 || move > s.cols() || s.checkerAt(move, s.levels() != VACANT))
	{
		cout << "Please enter a valid move. ";
		cin >> move;
		cout << endl;
	}
	return move;  //  This is not always correct; it's just here to compile
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color) // leftmost checker
{
	int move;
	move = 1;
	if (s.checkerAt(move, s.levels()) == VACANT) // the top of the column is clear, we can drop a checker.
	{
		return move;
	}
	while (s.checkerAt(move, s.levels()) != VACANT) //the top of the column isn't clear. keep going until it is
	{
		if (s.checkerAt(move, s.levels()) == VACANT) // new column is clear. drop a checker
			return move;
		move++;
	}
    return move;  //  This is not always correct; it's just here to compile
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    return -1;  //  This is not always correct; it's just here to compile
}

//******************** Player derived class functions *************************

// These functions simply delegate to the Impl classes' functions.
// You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
