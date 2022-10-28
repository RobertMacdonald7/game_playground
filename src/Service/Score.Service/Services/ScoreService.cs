using Grpc.Core;

namespace Score.Service.Services
{
	public class ScoreService : Service.ScoreService.ScoreServiceBase
	{
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

		public override Task<SetScoreForUserReply> SetScoreForUser(SetScoreForUserRequest request, ServerCallContext context)
		{
			var response = new SetScoreForUserReply {
				CurrentScore = new Score {
					Position = 3,
					Score_ = request.Score,
					Username = request.Username
				},
				HighScore = new Score {
					Position = 0,
					Score_ = 100,
					Username = request.Username
				}
			};

			return Task.FromResult(response);
		}
	}
}
