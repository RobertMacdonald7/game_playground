#include <score.pb.h>
#include <score.grpc.pb.h>

#include <grpcpp/grpcpp.h>

namespace GameClient::Web::Client {
    using grpc::Channel;
    using score::ScoreService;

    struct Score {
        int position;
        int score;
        std::wstring userName;
    };

    class ScoreClient {
        private:
            std::unique_ptr<ScoreService::Stub> stub_;

        public:
            explicit ScoreClient();

            std::map<int, Score> GetTopScores(int page, int resultsPerPage);

            /// @brief Sets the score for the user
            /// @param username The current user's username
            /// @param score The current score
            /// @return A pairs of scores. first -> currentScore, second -> highScore
            std::pair<Score, Score> SetScoreForUser(std::wstring username, int score);
    };
}
