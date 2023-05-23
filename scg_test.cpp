// Author:  Thomas Smith
// Date:  5/22/2023
// Purpose:  Output scg_test.pb in JSON format

#include <cstdlib>
#include <fstream>

#include <google/protobuf/util/json_util.h>

#include "protodef/scg_test.pb.h"

void TestSCG_TestMessage() {
	// Create a SCG::Test::TestMessage
	SCG::Test::TestMessage oScgMessage;

	// Set the members
	{
		google::protobuf::Timestamp oTimeNow;
		oTimeNow.ParseFromString("2023-05-22T18:43:00.0Z");
		auto* pScgTimestamp = oScgMessage.mutable_timestamp();
		pScgTimestamp->CopyFrom(oTimeNow);
		std::string oNotes{ "Hello World!" };
		oScgMessage.set_notes(oNotes);
	}

	// Get the members
	const google::protobuf::Timestamp& oTimestamp = oScgMessage.timestamp();
	const std::string& oNotes = oScgMessage.notes();

	// Print the members
	std::cout << "Timestamp: " << oTimestamp.DebugString()
		<< "\nNotes: " << oNotes << std::endl;
}

int main(int a_iArgc, char** a_ppchArgv) {
	//TestSCG_TestMessage();

	std::string szPROTO_MESSAGE{ "../source/protomessage/scg_test.pb" };
	std::ifstream ifs;
	ifs.open(szPROTO_MESSAGE);
	if (!ifs.is_open()) {
		std::cout << "Failed to open " << szPROTO_MESSAGE << '\n';
		return EXIT_FAILURE;
	}
	SCG::Test::TestMessage oScgMessage;
	oScgMessage.ParseFromIstream(&ifs);
	std::string szScgMessageJson;
	google::protobuf::util::MessageToJsonString(oScgMessage, &szScgMessageJson);
	std::cout << "SCG::Test::TestMessage oScgMessage as JSON string\n" << szScgMessageJson << '\n';
	ifs.close();
	if (ifs.is_open()) {
		std::cout << "Failed to close " << szPROTO_MESSAGE << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
