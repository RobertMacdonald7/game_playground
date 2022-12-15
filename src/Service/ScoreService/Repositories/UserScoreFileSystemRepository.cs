using System.Collections.ObjectModel;
using System.Text.Json;
using ScoreService.Models;

namespace ScoreService.Repositories
{
	public class UserScoreFileSystemRepository : IUserScoreRepository
	{
		private readonly IConfiguration _configuration;
		private readonly string _filePath;

		public UserScoreFileSystemRepository(IConfiguration configuration)
		{
			_configuration = configuration;
			var folderPath = _configuration.GetValue<string>("Scores:Folder");

			if (string.IsNullOrWhiteSpace(folderPath)) {
				folderPath = Path.Combine(
					Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData),
					"Snake");
			}

			if (!Directory.Exists(folderPath)) {
				Directory.CreateDirectory(folderPath);
			}

			_filePath = Path.Combine(folderPath, "scores");
			if (!File.Exists(_filePath)) {
				File.WriteAllText(_filePath, "[]");
			}
		}

		private async Task<IList<UserScore>> ReadAll()
		{
			try {
				await using var fileStream = File.OpenRead(_filePath);
				var scores = await JsonSerializer.DeserializeAsync<List<UserScore>>(fileStream);
				return scores ?? new List<UserScore>();
			}
			catch (Exception e) {
				Console.WriteLine(e);
				throw;
			}
			
		}

		private static IEnumerable<UserScoreWithPosition> TakeWithPositions(IEnumerable<UserScore> scores, IList<UserScore> orderedUserScores)
		{
			return from userScore in scores
				let position = orderedUserScores.IndexOf(userScore) + 1
				select new UserScoreWithPosition { Score = userScore, Position = position };
		}

		private async Task<IList<UserScore>> Save(IEnumerable<UserScore> data)
		{
			// Always write ordered data!
			var scoreOrderedData = data.OrderByDescending(s => s.Score).ToList();
			await File.WriteAllTextAsync(_filePath, JsonSerializer.Serialize(scoreOrderedData));
			return scoreOrderedData;
		}

		public async Task<UserScoreWithPosition> Add(UserScore newScore)
		{
			var scores = (await ReadAll());

			if (!scores.Any(s => s.Username == newScore.Username && s.Score == newScore.Score)) {
				 scores.Add(newScore);
			}

			var orderedScores = await Save(scores);
			var position = orderedScores.IndexOf(newScore) + 1;

			return new UserScoreWithPosition { Score = newScore, Position = position };
		}

		public async Task<UserScore> Delete(UserScore score)
		{
			// 1. Read all
			// 2. Find matching entry (return if none found)
			// 3. Remove entry
			// 4. Write entries back to the file
			return score;
		}

		public async Task<IEnumerable<UserScoreWithPosition>> GetByUserName(string userName)
		{
			var scores = await ReadAll();
			var filteredScores = scores.Where(s => s.Username == userName);

			return TakeWithPositions(filteredScores, scores);
		}

		public async Task<IEnumerable<UserScore>> GetTopScores(int pageIndex, int pageSize)
		{
			return (await ReadAll()).Skip(pageIndex*pageSize).Take(pageSize);
		}
	}
}
