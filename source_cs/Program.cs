// See https://aka.ms/new-console-template for more information

using Google.Protobuf;

public class Program
{
    public static void Main(string[] args)
    {
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
