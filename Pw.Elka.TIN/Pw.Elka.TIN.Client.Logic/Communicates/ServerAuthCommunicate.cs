using Pw.Elka.TIN.Client.Logic.Parsers;

namespace Pw.Elka.TIN.Client.Logic.Communicates
{
    internal class ServerAuthCommunicate : ServerCommunicate
    {
        public string Salt { get; set; }

        public override void SetFieldsFrom(byte[] bytes)
        {
            int startIndex = 1;
            int newStartIndex = 0;

            Salt = ASIAStringParser.GetString(bytes, startIndex, out newStartIndex, 4);
            startIndex = newStartIndex;
        }
    }
}
