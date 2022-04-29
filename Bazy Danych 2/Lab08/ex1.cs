using System;
using System.Data;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Server;
using System.IO;
using System.Text;


[Serializable]
[Microsoft.SqlServer.Server.SqlUserDefinedAggregate(
    Format.UserDefined,
    IsInvariantToNulls = true,
    IsInvariantToDuplicates = false,
    IsInvariantToOrder = false,
    MaxByteSize = 8000)
]

public struct Concat : IBinarySerialize
{
    public StringBuilder result;

    public void Init()
    {
        this.result = new StringBuilder();
    }

    public void Accumulate(SqlString value)
    {
        if (value.IsNull)
        {
            return;
        }

        this.result.Append(value.Value).Append(' ');
    }

    public void Merge(Concat other)
    {
        this.result.Append(other.result);
    }

    public SqlString Terminate()
    {
        string output = string.Empty;

        if (this.result != null && this.result.Length > 0)
        {
            output = this.result.ToString(0, this.result.Length - 1);
        }

        return new SqlString(output);
    }

    public void Read(BinaryReader r)
    {
        this.result = new StringBuilder(r.ReadString());
    }

    public void Write(BinaryWriter w)
    {
        w.Write(this.result.ToString());
    }
}

