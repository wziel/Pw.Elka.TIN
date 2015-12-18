using Pw.Elka.TIN.Client.Logic.Parsers;

namespace Pw.Elka.TIN.Client.Logic.Communicates
{
    internal class ServerMessageGetOneCommunicate : ServerCommunicate
    {
        public int MessageID { get; set; }
        public string MessageTemplate { get; set; }
        public string MessageName { get; set; }

        public override void SetFieldsFrom(byte[] bytes)
        {
            int startIndex = 1;
            int newStartIndex = 0;

            MessageID = ASIAIntParser.GetInt(bytes, startIndex, out newStartIndex);
            startIndex = newStartIndex;

            MessageTemplate = ASIAStringParser.GetString(bytes, startIndex, out newStartIndex);
            startIndex = newStartIndex;

            MessageName = ASIAStringParser.GetString(bytes, startIndex, out newStartIndex);
            startIndex = newStartIndex;
        }
    }
}
