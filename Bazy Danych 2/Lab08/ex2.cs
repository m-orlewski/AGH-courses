using System;
using System.Data;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Server;
using System.Text.RegularExpressions;
using System.IO;
using System.Text;

[Serializable]
[Microsoft.SqlServer.Server.SqlUserDefinedType(
                                                Format.UserDefined,
                                                IsByteOrdered=true,
                                                MaxByteSize=32)
]
public struct Pesel : INullable, IBinarySerialize
{
    private string pesel;

    public bool IsNull
    {
        get
        {
            return pesel.Length == 0 ? false : true;
        }
    }

    public static Pesel Null
    {
        get
        {
            Pesel p = new Pesel();
            p.pesel = "";
            return p;
        }
    }

    public override string ToString()
    {
        return pesel;
    }

    public static Pesel Parse(SqlString s)
    {
        if (s.IsNull)
            return Null;
        
        Pesel p = new Pesel();

        p.pesel = s.Value;
        if (p.pesel.Length == 11 || Regex.IsMatch(p.pesel, @"^\d+$"))
        {
            return p;
        }
        else
        {
            throw new ArgumentException("Pesel is invalid");
        }
    }

    public void Read(BinaryReader r)
    {
        StringBuilder builder = new StringBuilder(r.ReadString());
        this.pesel = builder.ToString();
    }

    public void Write(BinaryWriter w)
    {
        w.Write(this.pesel.ToString());
    }
}



