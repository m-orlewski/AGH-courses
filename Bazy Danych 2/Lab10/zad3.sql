USE AdventureWorks2008
GO

-- 3)
SELECT Resume.query('declare default element namespace
"http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/Resume";
for $p in /Resume/Address
let $name := /Resume/Name
let $city := $p/Addr.Location/Location/Loc.City
let $street := $p/Addr.Street
return
<person>
<Name>{$name/Name.Last}</Name>
<City>{$city}</City>
<Street>{$street}</Street>
</person>')
FROM HumanResources.JobCandidate;
