using System;
using System.Data;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Server;

public partial class UserDefinedFunctions
{
    [Microsoft.SqlServer.Server.SqlFunction(DataAccess = DataAccessKind.Read)]
    public static SqlInt32 ex1(SqlInt32 beid)
    {
        Int32 result = -1;
        SqlDateTime today, hired;

        string todayCommand = @"SELECT GETDATE();";
        string hiredCommand = @"SELECT HireDate FROM [HumanResources].[Employee] WHERE BusinessEntityID = @beid";
        string diffCommand = @"SELECT DATEDIFF(year, @hired, @today)";

        using (SqlConnection conn = new SqlConnection("context connection=true"))
        {
            conn.Open();

            try
            {
                SqlCommand command = new SqlCommand(todayCommand, conn);
                today = Convert.ToDateTime(command.ExecuteScalar());

                command = new SqlCommand(hiredCommand, conn);
                command.Parameters.Add("@beid", SqlDbType.Int).Value = beid;
                hired = Convert.ToDateTime(command.ExecuteScalar());

                command = new SqlCommand(diffCommand, conn);
                command.Parameters.Add("@hired", SqlDbType.DateTime).Value = hired;
                command.Parameters.Add("@today", SqlDbType.DateTime).Value = today;

                result = (Int32)command.ExecuteScalar();
            }
            catch (Exception ex)
            {
                SqlContext.Pipe.Send(ex.Message);
            }
        }
        
        return result;
    }
}
