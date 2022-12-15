using Grpc.Core;
using ScoreService.Repositories;
using ScoreService.Grpc.Service;
using ScoreService.Models;

namespace ScoreService.Services
{
	public class ScoreService : Grpc.Service.ScoreService.ScoreServiceBase
	{
		private readonly IUserScoreRepository _scoreRepository;
		public ScoreService(IUserScoreRepository scoreRepository) {
			_scoreRepository = scoreRepository;
		}

		public override Task<GetTopScoresReply> GetTopScores(GetTopScoresRequest request, ServerCallContext context)
		{
			var response = new GetTopScoresReply();
			var items = new List<Score> {
				new() { Position = 0, Score_ = 10, Username = "User1" },
				new() { Position = 1, Score_ = 5, Username = "User2" }
			};

			response.Scores.AddRange(items);

			return Task.FromResult(response);
		}

		public override async Task<SetScoreForUserReply> SetScoreForUser(SetScoreForUserRequest request, ServerCallContext context)
		{
			var score  = new UserScore {
				Username = request.Username,
				Score = request.Score,
			};

			var scoreWithPosition = await _scoreRepository.Add(score);
			var highScore = (await _scoreRepository.GetByUserName(request.Username)).First();

			return new SetScoreForUserReply {
				CurrentScore = new Score {
					Username = scoreWithPosition.Score.Username,
					Score_= scoreWithPosition.Score.Score,
					Position = scoreWithPosition.Position,
				},
				HighScore = new Score {
					Username = highScore.Score.Username,
					Score_ = highScore.Score.Score,
					Position = highScore.Position,
				}
			};
		}
	}
}
