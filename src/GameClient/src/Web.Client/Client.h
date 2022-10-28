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

            std::map<int, GameClient::Web::Client::Score> GetTopScores(int page, int resultsPerPage);
    };
}
