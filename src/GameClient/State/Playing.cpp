#include "Playing.h"

GameClient::State::Playing::Playing()
{
	const auto collisionDetector = std::make_shared<GameObjects::Collision::CollisionDetector>();
	_playArea = std::make_shared<GameObjects::PlayArea>(collisionDetector);
	_food = std::make_shared<GameObjects::Food>(collisionDetector);
	_snake = std::make_shared<GameObjects::Snake>(collisionDetector);

	GameStateBase::GetDrawables().push_back(_playArea);
	GameStateBase::GetDrawables().push_back(_food);
	GameStateBase::GetDrawables().push_back(_snake);
};

GameClient::State::GameStateType GameClient::State::Playing::GetType()
{
	return GameStateType::Playing;
}

void GameClient::State::Playing::Enter(const std::shared_ptr<IGameState> previousState)
{
	_snake->Reset();
	_food->Reset();
}

void GameClient::State::Playing::Leave()
{
	_blockInputUntilNextUpdate = false;
}

void GameClient::State::Playing::OnUpdate(IStateMachine& context)
{
	_blockInputUntilNextUpdate = false;

	_snake->OnUpdate(context);
	_food->OnUpdate();

	if (_cachedInput != Input::Input::None)
	{
		_snake->OnInput(_cachedInput);
		_food->OnInput(_cachedInput);

		_cachedInput = Input::Input::None;
		_blockInputUntilNextUpdate = true;
	}
}

void GameClient::State::Playing::OnInput(IStateMachine& context, const Input::Input input)
{
	if (_blockInputUntilNextUpdate)
	{
		_cachedInput = input;
		return;
	}

	const auto snakeHandledInput = _snake->OnInput(input);
	const auto foodHandledInput = _food->OnInput(input);

	_blockInputUntilNextUpdate = snakeHandledInput || foodHandledInput;
}
