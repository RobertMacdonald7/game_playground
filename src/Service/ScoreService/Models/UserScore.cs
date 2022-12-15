namespace ScoreService.Models
{
	public class UserScore
	{
		public string Username { get; set; }

		public int Score { get; set; }
	}

	public class UserScoreWithPosition
	{
		public UserScore Score { get; set; }

		public int Position { get; set; }
	}
}
