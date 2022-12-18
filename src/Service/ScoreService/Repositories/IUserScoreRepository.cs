using ScoreService.Models;

namespace ScoreService.Repositories
{
	public interface IUserScoreRepository
	{
		Task<IEnumerable<UserScoreWithPosition>> GetByUserName(string userName);

		Task<UserScoreWithPosition> Add(UserScore newScore);

		Task<UserScore> Delete(UserScore score);

		Task<IEnumerable<UserScore>> GetTopScores(int pageIndex, int pageSize);
	}
}
