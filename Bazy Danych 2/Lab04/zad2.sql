USE AdventureWorks2008;
GO

DROP FUNCTION dbo.fun2;
GO

CREATE FUNCTION dbo.fun2(@p int, @n int)
RETURNS TABLE
AS RETURN(
SELECT * FROM
(
	SELECT LastName, FirstName, emailAddress, city, NTILE(@n) over (ORDER BY city) n
	FROM Person.EmailAddress EA
	JOIN Person.BusinessEntity BE ON EA.BusinessEntityID = BE.BusinessEntityID
	JOIN Person.BusinessEntityAddress BEA ON BEA.BusinessEntityID = BE.BusinessEntityID
	JOIN Person.Address A ON BEA.AddressID = A.AddressID
	JOIN Person.Person P ON P.BusinessEntityID = BE.BusinessEntityID
) AS S
WHERE n = @p
)
GO

SELECT * FROM dbo.fun2(3, 10);
