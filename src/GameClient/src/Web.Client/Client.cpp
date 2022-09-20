#include "Client.h"

#include <greet.pb.h>
#include <greet.grpc.pb.h>

#include <grpcpp/grpcpp.h>
#include <wincrypt.h>
#include <fstream>

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
using greet::Greeter;
using greet::HelloRequest;
using greet::HelloReply;


GameClient::Web::Client::GreeterClient::GreeterClient(std::shared_ptr<Channel> channel)
    : stub_(Greeter::NewStub(channel)) {}

std::string GameClient::Web::Client::GreeterClient::SayHello(const std::string& user) {
    HelloRequest request;
    request.set_name(user);

    HelloReply reply;

    ClientContext context;

    CompletionQueue cq;

    Status status;

    std::unique_ptr<ClientAsyncResponseReader<HelloReply>> rpc(
        stub_->PrepareAsyncSayHello(&context, request, &cq));
    
    rpc->StartCall();

    rpc->Finish(&reply, &status, (void*)1);

    void* got_tag;
    bool ok = false;

    GPR_ASSERT(cq.Next(&got_tag, &ok));

    GPR_ASSERT(got_tag == (void*)1);
    GPR_ASSERT(ok);

    if (status.ok()) {
        return reply.message();
    }
    else {
        return "RPC failed";
    }
}

std::string utf8Encode(const std::wstring& wstr)
{
	if (wstr.empty())
		return std::string();

	int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo(sizeNeeded, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], sizeNeeded, NULL, NULL);
	return strTo;
}

grpc::SslCredentialsOptions getSslOptions()
{
	// Fetch root certificate as required on Windows (s. issue 25533).
	grpc::SslCredentialsOptions result;

	// Open root certificate store.
	HANDLE hRootCertStore = CertOpenSystemStore(NULL, L"MY");
	if (!hRootCertStore)
		return result;

	// Get all root certificates.
	PCCERT_CONTEXT pCert = NULL;
	while ((pCert = CertEnumCertificatesInStore(hRootCertStore, pCert)) != NULL)
	{
		// Append this certificate in PEM formatted data.
		DWORD size = 0;
		CryptBinaryToStringW(pCert->pbCertEncoded, pCert->cbCertEncoded, CRYPT_STRING_BASE64HEADER,
			NULL, &size);
		std::vector<WCHAR> pem(size);
		CryptBinaryToStringW(pCert->pbCertEncoded, pCert->cbCertEncoded, CRYPT_STRING_BASE64HEADER,
			pem.data(), &size);

		result.pem_root_certs += utf8Encode(pem.data());
	}

	CertCloseStore(hRootCertStore, 0);
	return result;
}

grpc::SslCredentialsOptions getSslOptionsFromCert(const std::string& path)
{
	grpc::SslCredentialsOptions options;

	std::ifstream ifs(path);
	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	options.pem_root_certs = content.data();
	return options;
}

std::string GameClient::Web::Client::SayHello() {
    _putenv("GRPC_VERBOSITY=DEBUG");

    auto channel_creds = grpc::SslCredentials(getSslOptions());
    auto channel = grpc::CreateChannel("localhost:7132", channel_creds);
    GreeterClient greeter(channel);
    
    std::string user = "world";
    return greeter.SayHello(user);
}
