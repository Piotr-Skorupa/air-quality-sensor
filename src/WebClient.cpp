#include "WebClient.hpp"

WebClient::WebClient(std::shared_ptr<spdlog::logger> logger, std::unique_ptr<signomix::HttpClient> client)
    : logger(std::move(logger))
    , client(std::move(client))
    , isConnected(false)
{
    signomixConnect();
}

bool WebClient::signomixConnect()
{
    // Fill with proper values
    const std::string sigLogin = "";
    const std::string sigPass = "";
    const std::string sigEui = "";
    const std::string sigSecret = "";

    auto response = client->signIn(sigLogin, sigPass, sigEui, sigSecret);
    logger->info("SIGNOMIX RESPONSE: {0}", response.description);
    logger->info("HTTP code: {0}", response.httpCode);
    if (response.error)
    {
        isConnected = false;
        logger->warn("Can not sign in to the Signomix!");
        if (response.httpCode == signomix::HTTP_UNAUTHORIZED)
        {
            logger->error("[ERROR] Invalid Signomix ceredentials!");
            return false;
        }
    }

    logger->info("[SUCCESS] You are correctly signed to your Signomix account.");
    isConnected = true;

    return isConnected;
}

void WebClient::sendData(const std::string& field, int data)
{
    logger->info("Trying to send data.");
    if (not isConnected)
    {
        logger->warn("Signomix is not connected. Reconnecting.");
        if (not signomixConnect())
        {
            logger->error("Can not sign in to the Signomix. Data will not be send!");
            return;
        }
    }

    client->newRequest();
    client->addData(field, data);
    auto response = client->sendData();

    if (not response.error and (response.httpCode == signomix::HTTP_CREATED))
    {
    	logger->info("Data has been sent to the Signomix.");
    }
    else
    {
	logger->error("Something went wrong. Data will not be send!");
	logger->error("Response: {0}", response.description);
	logger->error("HTTP {0}", response.httpCode);
    }
}
