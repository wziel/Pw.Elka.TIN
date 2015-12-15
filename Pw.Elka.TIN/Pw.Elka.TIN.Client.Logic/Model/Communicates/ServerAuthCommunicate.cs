using Pw.Elka.TIN.Client.Logic.Model.Parsers;

namespace Pw.Elka.TIN.Client.Logic.Model.Communicates
{
    internal class ServerAuthCommunicate : ServerCommunicate
    {
        public string Salt { get; set; }

        internal override void SetFieldsFrom(byte[] bytes)
        {
            int startIndex = 1;
            int newStartIndex = 0;

            Salt = ASIAStringParser.GetString(bytes, startIndex, out newStartIndex);
            startIndex = newStartIndex;
        }
    }
}
