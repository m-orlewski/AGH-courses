using System;
using System.Collections;
using System.Data;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Server;

public partial class UserDefinedFunctions
{

    private class Invoice
    {
        public SqlString symbol;
        public SqlDecimal value;
        public SqlDateTime date;

        public Invoice(SqlString s, SqlDecimal v, SqlDateTime d)
        {
            symbol = s;
            value = v;
            date = d;
        }
    }

    public static void InvoiceFillRow(object result, out SqlString s, out SqlDecimal v, out SqlDateTime d)
    {
        Invoice invoice = (Invoice)result;
        s = invoice.symbol;
        v = invoice.value;
        d = invoice.date;
    }

    [Microsoft.SqlServer.Server.SqlFunction(
        DataAccess = DataAccessKind.Read,
        FillRowMethodName = "InvoiceFillRow",
        TableDefinition = "symbol nvarchar(20), value decimal, date datetime")]
    public static IEnumerable udfInvoiceTable()
    {
        ArrayList result = new ArrayList();

        using (SqlConnection conn = new SqlConnection("context connection=true"))
        {
            conn.Open();
            using (SqlCommand selectInvoice = new SqlCommand(
                "SELECT " +
                "[symbol], [value], [date] " +
                "FROM test_table", conn))
            {
                using (SqlDataReader aReader =  selectInvoice.ExecuteReader())
                {
                    while (aReader.Read())
                    {
                        result.Add(new Invoice(aReader.GetSqlString(0), aReader.GetSqlDecimal(1), aReader.GetSqlDateTime(2)));
                    }
                }
            }
        }

        return result;
    }
};


