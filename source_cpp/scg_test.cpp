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
		<< "\nNotes: " << oNotes << '\n';
}

int main(int a_iArgc, char** a_ppchArgv) {
	//TestSCG_TestMessage();
	
	// Open scg_test.pb
	std::string szPROTO_MESSAGE{ "protomessage/scg_test.pb" };
	std::ifstream oIfs;
	oIfs.open(szPROTO_MESSAGE);
	if (!oIfs.is_open()) {
		std::cout << "Failed to open " << szPROTO_MESSAGE << '\n';
		return EXIT_FAILURE;
	}

	// Read message
	SCG::Test::TestMessage oScgMessage;
	oScgMessage.ParseFromIstream(&oIfs);

	// Convert to JSON
	std::string szScgMessageJson;
	google::protobuf::util::JsonOptions oJsonOptions;
	// Make the JSON pretty
	oJsonOptions.add_whitespace = true;
	google::protobuf::util::MessageToJsonString(oScgMessage, &szScgMessageJson, oJsonOptions);

	// Print message in JSON format
	std::cout << "SCG::Test::TestMessage oScgMessage as JSON string\n" << szScgMessageJson << '\n';

	// Close scg_test.pb
	oIfs.close();
	if (oIfs.is_open()) {
		std::cout << "Failed to close " << szPROTO_MESSAGE << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
