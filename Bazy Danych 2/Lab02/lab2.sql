--1
GO
WITH
ClientCTE
(
	SalesOrderID,
	LastName,
	AddressLine1
)
AS
(
	SELECT SalesOrderID,p.LastName,a.AddressLine1
	FROM Sales.SalesOrderHeader soh
	JOIN Sales.Customer c ON c.CustomerID =soh.CustomerID
	JOIN Person.Person p ON c.PersonID = p.BusinessEntityID
	JOIN Person.BusinessEntityAddress bea ON bea.BusinessEntityID = p.BusinessEntityID
	JOIN Person.Address a ON a.AddressID = bea.AddressID
),
SaleCTE
(
	SalesOrderID,
	ProductID,
	OrderQty,
	LineTotal,
	Name
)
AS
(
	SELECT SalesOrderID As SOid,Det.ProductID As PRid,OrderQty As qty,LineTotal As total,Prod.Name As ProductName
	FROM Sales.SalesOrderDetail Det
	JOIN Production.Product Prod ON Det.ProductID = Prod.ProductID
)

SELECT LastName, AddressLine1, Name, COUNT(ProductID) AS 'Ilosc', SUM(LineTotal) AS 'Wartosc'
FROM ClientCTE, SaleCTE
GROUP BY LastName, AddressLine1, Name;

--2
WITH EmployeeCTE
(
    Employee,
    EmployeeID,
    ManagerID
)
AS
(
    SELECT LastName as Employee, EmployeeID, ManagerID
    FROM HumanResources.Employee
    JOIN Person.Contact
    ON HumanResources.Employee.ContactID=Person.Contact.ContactID    
),
EmployeeManagerCTE
(
    Employee,
    Manager
)
AS
(
    SELECT Employee, LastName 
    FROM GetEmployeeCte
    JOIN Person.Contact
    ON GetEmployeeCte.ManagerID=Person.Contact.ContactID
    
)
SELECT * FROM EmployeeManagerCTE;

--3
WITH
SalesCTE
(
	SalesOrderID,
	BusinessEntityID,
	LastName,
	SubTotal
)
AS
(
	SELECT TOP 20 SalesOrderID, p.BusinessEntityID, p.LastName, soh.SubTotal
	FROM Sales.SalesOrderHeader soh
	JOIN Sales.Customer c ON c.CustomerID = soh.CustomerID
	JOIN Person.Person p ON c.PersonID = p.BusinessEntityID
	JOIN Person.BusinessEntityAddress bea ON bea.BusinessEntityID = p.BusinessEntityID
	JOIN Person.Address a ON a.AddressID = bea.AddressID
	ORDER BY soh.SubTotal DESC
),
Sales2CTE
(
	SalesOrderID,
	BusinessEntityID,
	LastName,
	SubTotal,
	n
)
AS
(
	SELECT *, NTILE(4) OVER(ORDER BY SubTotal DESC)
	FROM SalesCTE
)

SELECT *
FROM Sales2CTE
WHERE n = 2;