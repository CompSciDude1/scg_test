﻿// See https://aka.ms/new-console-template for more information

using Google.Protobuf;
using System.Text;

public class Program
{
    private static void TestSCG_TestMessage()
    {
        // Create a SCG.Test.TestMessage
        var oScgMessage = new SCG.Test.TestMessage();

        // Set the members
        {
            var oTimeNow = new DateTime(2023, 5, 23, 18, 13, 0);
            DateTime oTimeNowUTC = oTimeNow.ToUniversalTime();
            var oTimestampNow = Google.Protobuf.WellKnownTypes.Timestamp.FromDateTime(oTimeNowUTC);
            oScgMessage.Timestamp = oTimestampNow;
            string oNotes = "Hello World!";
            oScgMessage.Notes = oNotes;
        }

        // Print the members
        System.Console.WriteLine("Timestamp: " + oScgMessage.Timestamp);
        System.Console.WriteLine("Notes: " + oScgMessage.Notes);
    }
    public static void Main(string[] args)
    {
        //TestSCG_TestMessage();

        // Open scg_test.pb
        string szPROTO_MESSAGE = "protomessage/scg_test.pb";
        System.IO.FileStream oStream = System.IO.File.Open(szPROTO_MESSAGE, FileMode.Open);
        if (oStream.CanRead == false )
        {
            System.Console.WriteLine("Failed to open " +  szPROTO_MESSAGE);
            return;
        }

        // Read message
        SCG.Test.TestMessage oScgMessage = SCG.Test.TestMessage.Parser.ParseFrom(oStream);

        // Convert to JSON
        // Make the JSON pretty
        var oSettings = JsonFormatter.Settings.Default.WithIndentation("  ");
        var oJsonWriter = new JsonFormatter(oSettings);

        // Print message in JSON format
        System.Console.WriteLine("SCG.Test.TestMessage oScgMessage as JSON string");
        System.Console.WriteLine(oJsonWriter.Format(oScgMessage));

        // Close scg_test.pb
        oStream.Close();
        if (oStream.CanRead == true)
        {
            System.Console.WriteLine("Failed to close " + szPROTO_MESSAGE);
            return;
        }
    }
}
