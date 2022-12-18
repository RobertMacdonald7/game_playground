using ScoreService.Models;

namespace ScoreService.Repositories
{
	public class UserScoreDummyRepository : IUserScoreRepository
	{
		public Task<IEnumerable<UserScoreWithPosition>> GetByUserName(string userName)
		{
			var list = new List<UserScoreWithPosition>() {
				new UserScoreWithPosition {
					Position = 0, Score = new UserScore { Score = 209120, Username = "Robert Macdonald" }
				}
			};
			return Task.FromResult(list.AsEnumerable());
		}

		public Task<UserScoreWithPosition> Add(UserScore newScore)
		{
			return Task.FromResult(new UserScoreWithPosition {
				Position = 0,
				Score = newScore
			});
		}

		public Task<UserScore> Delete(UserScore score)
		{
			return Task.FromResult(score);
		}

		public Task<IEnumerable<UserScore>> GetTopScores(int pageIndex, int pageSize)
		{
			var list = new List<UserScore>() {
				new UserScore {
					Score = 12039812,
					Username = "Bob"
				}
			};
			return Task.FromResult(list.AsEnumerable());
		}
	}
}
