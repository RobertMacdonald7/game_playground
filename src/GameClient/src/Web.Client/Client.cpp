#include "Client.h"

#include <wincrypt.h>
#include <fstream>

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

std::string utf8Encode(const std::wstring& wstr)
{
	if (wstr.empty())
		return std::string();

	int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo(sizeNeeded, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], sizeNeeded, NULL, NULL);
	return strTo;
}

std::wstring ConvertUtf8ToWide(const std::string& str)
{
    int count = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0);
    std::wstring wstr(count, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), &wstr[0], count);
    return wstr;
}

GameClient::Web::Client::ScoreClient::ScoreClient() {
	_putenv("GRPC_VERBOSITY=DEBUG");

	auto channel = grpc::CreateChannel("localhost:8080", grpc::InsecureChannelCredentials()); // WHen run against a app service, omit the protocol and port
	stub_ = std::make_unique<score::ScoreService::Stub>(channel);
}

std::map<int, GameClient::Web::Client::Score> GameClient::Web::Client::ScoreClient::GetTopScores(int page, int resultsPerPage)
{
	score::GetTopScoresRequest request;
	request.set_page(page);
	request.set_results_per_page(resultsPerPage);

	score::GetTopScoresReply reply;
	ClientContext context;
	CompletionQueue cq;
	Status status;

	std::unique_ptr<ClientAsyncResponseReader<score::GetTopScoresReply>> rpc(
		stub_->PrepareAsyncGetTopScores(&context, request, &cq)
	);
    rpc->StartCall();
    rpc->Finish(&reply, &status, (void*)1);

    void* got_tag;
    bool ok = false;
    GPR_ASSERT(cq.Next(&got_tag, &ok));
    GPR_ASSERT(got_tag == (void*)1);
    GPR_ASSERT(ok);

	std::map<int, GameClient::Web::Client::Score> ret;
    if (!status.ok()) {
		return ret;
    }

	auto scores = reply.scores();
	for (auto& score : scores)
	{
		GameClient::Web::Client::Score normalisedScore;
		normalisedScore.position = score.position();
		normalisedScore.score = score.score();
		normalisedScore.userName = ConvertUtf8ToWide(score.username());
		ret.emplace(score.position(), normalisedScore);
	}

	return ret;
}

std::pair<GameClient::Web::Client::Score, GameClient::Web::Client::Score> GameClient::Web::Client::ScoreClient::SetScoreForUser(std::wstring username, int score)
{
	score::SetScoreForUserRequest request;
	request.set_username(utf8Encode(username));
	request.set_score(score);

	score::SetScoreForUserReply reply;
	ClientContext context;
	CompletionQueue cq;
	Status status;

	std::unique_ptr<ClientAsyncResponseReader<score::SetScoreForUserReply>> rpc(
		stub_->PrepareAsyncSetScoreForUser(&context, request, &cq)
	);
    rpc->StartCall();
    rpc->Finish(&reply, &status, (void*)1);

    void* got_tag;
    bool ok = false;
    GPR_ASSERT(cq.Next(&got_tag, &ok));
    GPR_ASSERT(got_tag == (void*)1);
    GPR_ASSERT(ok);

	std::pair<GameClient::Web::Client::Score, GameClient::Web::Client::Score> ret;
    if (!status.ok()) {
		// TODO - what does this return look like?
		return ret;
    }

	auto currentScore = reply.current_score();
	auto highScore = reply.high_score();

	GameClient::Web::Client::Score normalizedCurrentScore;
	GameClient::Web::Client::Score normalizedHighScore;

	normalizedCurrentScore.position = currentScore.position();
	normalizedCurrentScore.score = currentScore.score();
	normalizedCurrentScore.userName = ConvertUtf8ToWide(currentScore.username());

	normalizedHighScore.position = highScore.position();
	normalizedHighScore.score = highScore.score();
	normalizedHighScore.userName = ConvertUtf8ToWide(highScore.username());

	ret = std::make_pair(normalizedCurrentScore, normalizedHighScore);
	return ret;

	return ret;
}

grpc::SslCredentialsOptions getSslOptions()
{
	// Fetch root certificate as required on Windows (s. issue 25533).
	grpc::SslCredentialsOptions result;

	// Open root certificate store.
	// NOTE: When running against an app service this should draw from "ROOT"
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
