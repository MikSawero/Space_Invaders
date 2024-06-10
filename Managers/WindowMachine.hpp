#pragma once

#include <memory>
#include <stack>

#include "Window.hpp"

namespace ms
{
	typedef std::unique_ptr<Window> StateRef;

	class StateMachine
	{
	public:
		StateMachine() {};
		~StateMachine() {};
		
		void AddState(StateRef newState, bool isReplaced = true); //Add new State
		void RemoveState(); //Remove State
		
		void ProcessStateChanges(); //Change State

		StateRef& GetActiveState(); //Return Active State

	private:
		std::stack<StateRef> _states; //Stack of all States
		StateRef _newState; //New State
		
		//Flags about States
		bool _isRemoving = 0;
		bool _isAdding = 0;
		bool _isReplacing = 0;
	};
}
