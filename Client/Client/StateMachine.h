#pragma once

template<typename T>
class StateMachine
{
public:
	virtual ~StateMachine() = default;

public:
	virtual void Enter(const shared_ptr<T>& controller) abstract;
	virtual void Update(const shared_ptr<T>& controller) abstract;
	virtual void Exit(const shared_ptr<T>& controller) abstract;
};

