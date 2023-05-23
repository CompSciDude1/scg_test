// See https://aka.ms/new-console-template for more information

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
            var oTimeNow = Google.Protobuf.WellKnownTypes.Timestamp.FromDateTime(DateTime.UtcNow);
            oScgMessage.Timestamp = oTimeNow;
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
        string szPROTO_MESSAGE = "protomessage/scg_test.pb";
        System.IO.FileStream oStream = System.IO.File.Open(szPROTO_MESSAGE, FileMode.Open);
        if (oStream.CanRead == false )
        {
            System.Console.WriteLine("Failed to open " +  szPROTO_MESSAGE);
            return;
        }
        SCG.Test.TestMessage oScgMessage = SCG.Test.TestMessage.Parser.ParseFrom(oStream);
        System.Console.WriteLine("SCG.Test.TestMessage oScgMessage as JSON string");
        var oJsonWriter = new JsonFormatter(JsonFormatter.Settings.Default);
        System.Console.WriteLine(oJsonWriter.Format(oScgMessage));
        oStream.Close();
        if (oStream.CanRead == true)
        {
            System.Console.WriteLine("Failed to close " + szPROTO_MESSAGE);
            return;
        }
    }
}
