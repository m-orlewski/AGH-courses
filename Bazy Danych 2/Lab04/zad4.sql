USE AdventureWorks2008;
GO

DROP FUNCTION dbo.fun4;
GO

CREATE FUNCTION dbo.fun4(@i int)
RETURNS TABLE
AS RETURN
(
SELECT TOP(@i) P.FirstName, P.LastName, SUM(SubTotal) as s FROM Person.EmailAddress EA
JOIN Person.BusinessEntity BE ON EA.BusinessEntityID = BE.BusinessEntityID
JOIN Person.BusinessEntityAddress BEA ON BEA.BusinessEntityID = BE.BusinessEntityID
JOIN Person.Address A ON BEA.AddressID = A.AddressID
JOIN Person.Person P ON P.BusinessEntityID = BE.BusinessEntityID
JOIN HumanResources.Employee Emp ON P.BusinessEntityID = Emp.BusinessEntityID
JOIN Sales.SalesPerson SP ON SP.BusinessEntityID = Emp.BusinessEntityID
JOIN Sales.SalesOrderHeader SOH ON SOH.SalesPersonID = SP.BusinessEntityID
GROUP BY P.LastName, P.FirstName
ORDER BY s DESC
)
GO

SELECT * FROM dbo.fun4(3);
