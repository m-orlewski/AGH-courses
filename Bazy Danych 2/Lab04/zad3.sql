USE AdventureWorks2008;
GO

DROP FUNCTION dbo.fun3;
GO

CREATE FUNCTION dbo.fun3(@lname varchar(40))
RETURNS TABLE
AS RETURN(
SELECT P.LastName, P.FirstName, SOH.DueDate, SOH.TotalDue FROM Person.EmailAddress EA
JOIN Person.BusinessEntity BE ON EA.BusinessEntityID = BE.BusinessEntityID
JOIN Person.BusinessEntityAddress BEA ON BEA.BusinessEntityID = BE.BusinessEntityID
JOIN Person.Address A ON BEA.AddressID = A.AddressID
JOIN Person.Person P ON P.BusinessEntityID = BE.BusinessEntityID
JOIN HumanResources.Employee Emp ON P.BusinessEntityID = Emp.BusinessEntityID
JOIN Sales.SalesPerson SP ON SP.BusinessEntityID = Emp.BusinessEntityID
JOIN Sales.SalesOrderHeader SOH ON SOH.SalesPersonID = SP.BusinessEntityID
WHERE P.LastName = @lname);
GO

SELECT * FROM dbo.fun3('Jiang');
