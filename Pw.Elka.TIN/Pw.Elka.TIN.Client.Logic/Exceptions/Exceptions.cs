using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Exceptions
{
    public class NotAuthorizedException : Exception
    { }

    public class BadGroupException : Exception
    { }

    public class BadMessageException : Exception
    { }

    public class BadAddressException : Exception
    { }

    public class TimeoutException : Exception
    { }
}
