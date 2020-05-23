#pragma once
//include header files
#include<Memory>
#include<stack>

#include "State.h"

namespace Mer
{
	typedef std::unique_ptr<State> StateRef;

	class StateMachine
	{
	public:
		StateMachine(){ }
		~StateMachine(){ }

		void AddState(StateRef newState, bool isReplacing = true); //sets _newstate
		//to incoming new state and sets _isAdding to true, isReplacing is true by deafault
		void RemoveState();//sets _isRemoving to true

		void ProcesssStateChanges(); // process current state changes based on boolean variables

		StateRef& GetActiveState(); //returns active state
	private:
		std::stack<StateRef> _states; // stack holding current states
		StateRef _newState; //variable for new state before its moved to stack

		//boolean variables for current state changes
		bool _isRemoving = false;
		bool _isAdding = false;
		bool _isReplacing = false; // replaces current state with new incoming state
	};
}

