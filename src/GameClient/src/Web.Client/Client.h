#include <greet.pb.h>
#include <greet.grpc.pb.h>

#include <grpcpp/grpcpp.h>

namespace GameClient::Web::Client
{
    using grpc::Channel;
    using greet::Greeter;

    class GreeterClient {
        private:
            std::unique_ptr<Greeter::Stub> stub_;

        public:
            explicit GreeterClient(std::shared_ptr<Channel> channel);

            std::string SayHello(const std::string& user);
    };

    std::string SayHello();
}
