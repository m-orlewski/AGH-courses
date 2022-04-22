using System;
using System.Data;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Server;

public partial class StoredProcedures
{
    [Microsoft.SqlServer.Server.SqlProcedure]
    public static void ex4 (SqlInt32 beid)
    {
        string select = "SELECT LastName + ';' + MiddleName + ';' + FirstName + ';' + AddressLine1 " +
                        "FROM HumanResources.Employee HE " +
                        "JOIN Person.Person PP ON HE.BusinessEntityID = PP.BusinessEntityID " +
                        "JOIN Person.BusinessEntityAddress PBEA ON PP.BusinessEntityID = PBEA.BusinessEntityID " +
                        "JOIN Person.Address PA ON PA.AddressID = PBEA.AddressID " +
                        "JOIN Person.BusinessEntity PBE ON PBE.BusinessEntityID = PP.BusinessEntityID " +
                        "WHERE PP.BusinessEntityID = @beid";

        using (SqlConnection conn = new SqlConnection("context connection=true"))
        {
            conn.Open();

            SqlCommand command = new SqlCommand(select, conn);
            command.Parameters.Add("@BeID", SqlDbType.Int).Value = beid;
            SqlContext.Pipe.ExecuteAndSend(command);
        }
    }
}
