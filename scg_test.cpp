// Author:  Thomas Smith
// Date:  5/22/2023
// Purpose:  Output scg_test.pb in JSON format

#include <cstdlib>

#include "protodef/scg_test.pb.h"

int main(int a_iArgc, char** a_ppchArgv) {
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

	return EXIT_SUCCESS;
}
