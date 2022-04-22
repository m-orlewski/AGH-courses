using System;
using System.Data;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Server;

public partial class UserDefinedFunctions
{
    [Microsoft.SqlServer.Server.SqlFunction(DataAccess = DataAccessKind.Read)]
    public static SqlString ex3(SqlInt32 beid, SqlDateTime date)
    {
        string select = "SELECT LastName + ';' + FirstName + ';' + CONVERT(nvarchar, DATEDIFF(year, BirthDate, @date)) " +
                        "FROM HumanResources.Employee E " +
                        "JOIN Person.Person P ON E.BusinessEntityID = P.BusinessEntityID " +
                        "WHERE P.BusinessEntityID = @beid";

        using (SqlConnection conn = new SqlConnection("context connection=true"))
        {
            conn.Open();

            SqlCommand command = new SqlCommand(select, conn);

            command.Parameters.Add("@date", SqlDbType.DateTime).Value = date;
            command.Parameters.Add("@beid", SqlDbType.Int).Value = beid;

            SqlString result = command.ExecuteScalar().ToString();
            return result;
        }
    }
}
