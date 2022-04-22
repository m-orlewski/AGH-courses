USE AdventureWorks2008;
GO

DROP FUNCTION dbo.fun1;
GO

CREATE FUNCTION dbo.fun1(@id int, @sep nvarchar(1) = ';')
RETURNS nvarchar(200)
AS BEGIN
DECLARE @row varchar(200)
SELECT TOP 1 @row = Firstname+@sep+LastName+@sep+EmailAddress+@sep+City
FROM Person.EmailAddress EA
JOIN Person.BusinessEntity BE ON EA.BusinessEntityID = BE.BusinessEntityID
JOIN Person.BusinessEntityAddress BEA ON BEA.BusinessEntityID = BE.BusinessEntityID
JOIN Person.Address A ON BEA.AddressID = A.AddressID
JOIN Person.Person P ON P.BusinessEntityID = BE.BusinessEntityID
WHERE BE.BusinessEntityID = @id
RETURN @row
END
GO

SELECT dbo.fun1(1, '%');
