using System;
using System.Data;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Server;

public partial class StoredProcedures
{
    [Microsoft.SqlServer.Server.SqlProcedure]
    public static void ex2(SqlDateTime date, SqlInt32 age)
    {
        using (SqlConnection conn = new SqlConnection("context connection=true"))
        {
            conn.Open();

            SqlCommand command = new SqlCommand("SELECT LastName, FirstName, EmailAddress, DATEDIFF(year, BirthDate, @date) as Age FROM " +
                                                "HumanResources.Employee E " +
                                                "JOIN Person.Person P ON E.BusinessEntityID = P.BusinessEntityID " +
                                                "JOIN Person.EmailAddress EA ON P.BusinessEntityID = EA.BusinessEntityID " +
                                                "WHERE DATEDIFF(year, BirthDate, @date) >= @age", conn);

            command.Parameters.Add("@date", SqlDbType.DateTime).Value = date;
            command.Parameters.Add("@age", SqlDbType.Int).Value = age;

            SqlContext.Pipe.ExecuteAndSend(command);

            conn.Close();
        }
    }
}
