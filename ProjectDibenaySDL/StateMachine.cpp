#include "StateMachine.h"
namespace Mer
{
	void StateMachine::AddState(StateRef newState, bool isReplacing)
	{
		this->_isAdding = true;//signal 'ProcessStateChanges' that a state is being added
		this->_isReplacing = isReplacing;//true by default signal 'ProcessStateChanges' whether to replace current state with the new state or not

		this->_newState = std::move(newState);//new state to be added
	}
	void StateMachine::RemoveState()
	{
		this->_isRemoving = true;//signs 'ProcessStateChanges' that the current state is to be removed 
	}

	void StateMachine::ProcesssStateChanges()//process any changes to state to be made
	{
		if (this->_isRemoving && !this->_states.empty())//if state is to be removed and states stack isnt empty
		{
			this->_states.top()->CleanUp();//clean up assets used by that state
			this->_states.pop();//remove top state
			if (!this->_states.empty())//if states stack still isnt empty resume new top state
			{
				this->_states.top()->Resume();
			}

			this->_isRemoving = false;//set _isRemoving to false
		}

		if (this->_isAdding)//if adding new state
		{
			if (!this->_states.empty())//if state stack isnt empty
			{
				if (this->_isReplacing)//if replacing current state with new state
				{
					this->_states.top()->CleanUp();//clean up current state
					this->_states.pop();//pop current state
				}
				else//else just pause current state
				{
					this->_states.top()->Pause();
				}
			}

			
			this->_states.push(std::move(this->_newState));//add new state to top of stack
			this->_states.top()->Init();//initialise new state
			this->_isAdding = false;//set _isAdding to false
			std::cout << "StateMachine: Added new state" << std::endl;
		}
	}

	StateRef& StateMachine::GetActiveState()//returns current acitve state (state at top of stack)
	{
		return this->_states.top();
	}

}