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
		return {};

	const int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), static_cast<int>(wstr.size()), nullptr, 0, nullptr, nullptr);
	std::string strTo(sizeNeeded, 0);
	WideCharToMultiByte(CP_UTF8, 0, wstr.data(), static_cast<int>(wstr.size()), strTo.data(), sizeNeeded, nullptr, nullptr);
	return strTo;
}

std::wstring ConvertUtf8ToWide(const std::string& str)
{
	const auto count = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), nullptr, 0);
	std::wstring wstr(count, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), wstr.data(), count);
	return wstr;
}

GameClient::Web::Client::ScoreClient::ScoreClient()
{
	auto channel = grpc::CreateChannel("localhost:8080", grpc::InsecureChannelCredentials());
	// When run against a app service, omit the protocol and port
	_stub = std::make_unique<score::ScoreService::Stub>(channel);
}

std::map<int, GameClient::Web::Client::Score> GameClient::Web::Client::ScoreClient::GetTopScores(
	int page, int resultsPerPage)
{
	return {};
}

void GameClient::Web::Client::ScoreClient::SetScoreForUser(const std::wstring& username, const int score,
                                                           const std::function<void(bool, Score, Score)>& callback) const
{
	score::SetScoreForUserRequest request;
	request.set_username(utf8Encode(username));
	request.set_score(score);

	auto call = std::make_shared<AsyncClientCall<score::SetScoreForUserReply>>();

	_stub->async()->SetScoreForUser(&call->context, &request, &call->reply,
		[call, callback](grpc::Status status)
		{
			call->status = std::move(status);
			if (!call->status.ok())
			{
				callback(false, {}, {});
			}

			try
			{
				const auto currentScore = call->reply.current_score();
				const auto highScore = call->reply.high_score();

				Score normalizedCurrentScore;
				normalizedCurrentScore.position = currentScore.position();
				normalizedCurrentScore.score = currentScore.score();
				normalizedCurrentScore.user_name = ConvertUtf8ToWide(currentScore.username());

				Score normalizedHighScore;
				normalizedHighScore.position = highScore.position();
				normalizedHighScore.score = highScore.score();
				normalizedHighScore.user_name = ConvertUtf8ToWide(highScore.username());

				callback(true, normalizedCurrentScore, normalizedHighScore);
			}
			catch (...)
			{
				callback(false, {}, {});
			}
		});
}

grpc::SslCredentialsOptions getSslOptions()
{
	// Fetch root certificate as required on Windows (s. issue 25533).
	grpc::SslCredentialsOptions result;

	// Open root certificate store.
	// NOTE: When running against an app service this should draw from "ROOT"
	const HANDLE hRootCertStore = CertOpenSystemStore(NULL, L"MY");
	if (!hRootCertStore)
		return result;

	// Get all root certificates.
	PCCERT_CONTEXT pCert = nullptr;
	while ((pCert = CertEnumCertificatesInStore(hRootCertStore, pCert)) != nullptr)
	{
		// Append this certificate in PEM formatted data.
		DWORD size = 0;
		CryptBinaryToStringW(pCert->pbCertEncoded, pCert->cbCertEncoded, CRYPT_STRING_BASE64HEADER,
		                     nullptr, &size);
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
	const std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	options.pem_root_certs = content;
	return options;
}
