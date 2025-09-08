#include "pch.h"
#include "IBehaviour.h"

IBehaviour::IBehaviour(const string& name) : Super(name) {}
IBehaviour::~IBehaviour() {}

void IBehaviour::Awake(shared_ptr<GameObject> owner) { _owner = owner; }
void IBehaviour::Init() {}
void IBehaviour::Update() {}
void IBehaviour::FixedUpdate() {}
void IBehaviour::LateUpdate() {}