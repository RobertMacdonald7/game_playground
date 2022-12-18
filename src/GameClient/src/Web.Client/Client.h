#pragma once
#include <score.grpc.pb.h>

#include <grpcpp/grpcpp.h>

namespace GameClient::Web::Client
{
	using grpc::Channel;
	using score::ScoreService;

	struct Score
	{
		int position{};
		int score{};
		std::wstring user_name;
	};

	class ScoreClient
	{
	private:
		std::unique_ptr<ScoreService::Stub> _stub;

	public:
		ScoreClient();

		std::map<int, Score> GetTopScores(int page, int resultsPerPage);

		/// @brief Sets the score for the user
		/// @param username The current user's username
		/// @param score The current score
		/// @param callback Invoked when the rpc has completed
		void SetScoreForUser(const std::wstring& username, int score, const std::function<void(bool, Score, Score)>& callback) const;

	private:
		template <typename TReply>
		struct AsyncClientCall
		{
			TReply reply;
			grpc::ClientContext context;
			grpc::Status status;
		};

		grpc::SslCredentialsOptions GetSslOptions() const;
	};
}
